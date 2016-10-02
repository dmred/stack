#include <iostream> 
using namespace std;



template <typename T>
class stack
{
public:
	stack(); 
	stack(stack const & stck);
	auto count() const noexcept->size_t; 
	auto push(T const & value)->void;
	auto top() const->T&;
	auto pop()->T;
	auto operator=(stack const & stck)->stack &;
	bool operator==(stack const & rhs);
	~stack();
private:
	T * _array;
	size_t _array_size;
	size_t _count;
	auto copy_new(size_t count_m_c, size_t array_size_m_c, const T * tmp)->T*;
};

