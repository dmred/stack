#include "stack.h"
template <typename T>
stack<T>::stack() : _array(nullptr), _array_size(0), _count(0) {};

template <typename T>
stack<T>::~stack() {
	delete[] _array;
}

template <typename T>
stack<T>::stack(stack const &stck) : _array_size(stck._array_size), _count(stck._count), _array(copy_new(stck._count,stck._array_size,stck._array))  {

}


template <typename T>
inline auto stack<T>::operator=(const stack &stck)->stack& {
	if (this != &stck) {
		(stack(stck)).swap(*this);
	}
	

template <typename T>
auto stack<T>::count() const noexcept->size_t { return _count; }

template<typename T>
auto stack<T>::push(T const & value) -> void {
	if (_count == _array_size) {
		size_t size = _array_size * 2 + (_array_size == 0);
		T * new_ar = copy_new(_count, size, _array);
		delete[] _array;
		_array = new_ar;
		_array_size = size;
	}
	_array[_count] = value;
	++_count;
}

template <typename T>
auto stack<T>::top() const -> T& {
	if (_count == 0) throw logic_error("stack's empty");
	return _array[_count];
}

template <typename T>
auto stack<T>::pop() -> T {
	if (_count == 0) throw("stack's empty");
	return --_count;
}

template <typename T>
auto stack<T>::copy_new(size_t count_m_c, size_t array_size_m_c, const T * tmp)->T* {
	T *mass = new T[array_size_m_c];
	copy(tmp, tmp + count_m_c, mass);
	return mass;
}
template<typename T>
bool stack<T>::operator==(stack const & rhs) 
{
	if ((rhs._count != _count) || (rhs._array_size != _array_size)) {
		return false;
	}
	else {
		for (size_t i = 0; i < _count; i++) {
			if (rhs._array[i] != _array[i]) {
				return false;
			}
		}
	}
	return true;
}

template<typename T> 
auto stack<T>::empty()->bool {
	return (_count == 0);
}

template<typename T>
auto stack<T>::swap(stack & stack) -> void {
	std::swap(stack._array, _array);
	std::swap(stack._array_size, _size);
	std::swap(stack._count, _count);
}
