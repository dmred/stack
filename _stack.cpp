#include <iostream>
using namespace std;

template <typename T>
class stack
{
public:
	stack();
	size_t count() const;
	void push(T const &);
	T pop();
	~stack();
private:
	T * _array;
	size_t _array_size;
	size_t _count;
};

template <typename T>
stack<T>::stack() : _array(nullptr), _array_size(0), _count(0) {};

template <typename T>
stack<T>::~stack() {
	delete[] _array;
}

template <typename T>
size_t stack<T>::count() const { return _count; }

template <typename T>
void stack<T>::push(T const &a) {
	if (_array == nullptr) {
		_array = new T[1]; _array[0] = a;
		_count++; _array_size++;
	}
	else {
		if (_count == _array_size) {
			T *p = _array;
			_array = new T[_array_size * 2];
			for (int i = 0; i < _count; i++) _array[i] = p[i];
			delete[]p;
			_array_size *= 2;
		}
		_array[_count] = a;
		_count++;
	}
}

template <typename T>
T stack<T>::pop() {
	if (_count == 0) throw("stack's empty");
	else {
		_count--;
		return _array[_count];
	}
}
