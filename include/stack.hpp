#include <iostream>
#include <stdexcept>


//
//
//
//
//
//
//

template<typename T>
class allocator
{
protected:
	allocator(size_t size = 0);
	~allocator();
	auto swap(allocator& other)->void;
	allocator(allocator const&) = delete;
	auto operator=(allocator const&)->allocator& = delete;
	T * _array;
	size_t _size;
	size_t _count;
};

//placement new
template <typename T1, typename T2>
auto construct(T1 * ptr, T2 const & value)->void {
	new(ptr) T1(value);
}

//destroy obj
template <typename T>
void destroy(T * ptr) noexcept
{
	ptr->~T();
}

//destroy from to
template <typename FwdIter>
void destroy(FwdIter first, FwdIter last) noexcept
{
	for (; first != last; ++first) {
		destroy(&*first);
	}
}

//constructor allocator
template <typename T>
allocator<T>::allocator(size_t size) : _array(static_cast<T *>(size == 0 ? nullptr : operator new(size * sizeof(T)))), _size(0), _count(size) {
};

//destructor allocator
template <typename T>
allocator<T>::~allocator() {
operator delete(_array);
};

//swap allocator
template <typename T>
auto allocator<T>::swap(allocator& other)->void {
	std::swap(_array, other._array);
	std::swap(_size, other._size);
	std::swap(_count, other._count);
};
//								_________    ______________		___________		_
//								|		   		|			|				|     _/
//								|					|			|				|   _/
//								|					|			|____			|__/
//								|					|			|				|  \_
//								|					|			|				|    \_
//								|_________			|			|__________		|      \
												

template <typename T>
class stack : private allocator<T>
{
public:
	stack(size_t size = 0);/*noexcept*/
	stack(stack const &); /*strong*/
	auto count() const noexcept->size_t;/*noexcept*/
	auto push(T const &)->void;/*strong*/
	auto pop()->void;/*strong*/
	auto top() const->T&;/*strong*/
	~stack(); 	/*noexcept*/
	auto operator=(const stack&tmp)->stack&;/*strong*/
	auto empty()->bool;/*noexcept*/

};





//
// template <typename T>
// auto copy_new(size_t count_m, size_t array_size_m, const T * tmp)->T* {
// 	T *mass = new T[array_size_m];
// 	std::copy(tmp, tmp + count_m, mass);
// 	return mass;
// }




// template <typename T>
// stack<T>::stack()  {};



template <typename T>
stack<T>::stack(size_t size): allocator<T>(size) {};

template <typename T>
stack<T>::stack(stack const &stck) : allocator<T>(stck.size)
{
	for (size_t  i = 0; i < stck._count; i++)
	{
		construct(allocator<T>::_array + i, stck._array[i]);
	}
	allocator<T>::_count = stck._count;
};

template <typename T>
auto stack<T>::count() const noexcept->size_t {
	return allocator<T>::_count;
}

template <typename T>
auto stack<T>::push(T const &val)->void 
	{
	if (allocator<T>::_count == allocator<T>::_size) {
		size_t size = allocator<T>::_size * 2 + (allocator<T>::_size == 0);
		stack<T> stck(size);
		while (allocator<T>::_count > stck._count())
			stck.push(allocator<T>::_array[stck.count()]);
			this->swap(stck);//
	}
	construct(allocator<T>::_array +allocator<T>::_count,val);
	allocator<T>::_count++;
}


//count--
template <typename T>
auto stack<T>::pop()->void {
	if (allocator<T>::_count == 0) throw std::logic_error("Stack's empty");
	destroy(allocator<T>::_array +allocator<T>::_count);
	--allocator<T>::_count;
}

//el.remove();
template <typename T>
auto stack<T>::top() const->T& {
	if (allocator<T>::_count == 0) throw std::logic_error("Stack's empty");
	return allocator<T>::_array[allocator<T>::_count - 1];
}

template <typename T>
stack<T>::~stack() {
destroy(allocator<T>::_array, allocator<T>::_array + allocator<T>::_count);};

template <typename T>
auto stack<T>::operator=(const stack &tmp)->stack& {
	if (this != &tmp) {
		(stack(tmp)).swap(*this);
// 		T* cp = copy_new(tmp._count, tmp._size, tmp._array);
// 		delete[] allocator<T>::_array;
// 		allocator<T>::_array = cp;
// 		allocator<T>::_size =tmp._size;
// 		allocator<T>::_count = tmp._count;
	}
	return *this;
}

//stack.isEmpty()
template<typename T> 
auto stack<T>::empty()->bool {
	return (allocator<T>::_count == 0);
}
