#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <exception>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class vector
{
public: // types
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference 							reference;
	typedef typename allocator_type::const_reference					const_reference;
	typedef typename allocator_type::pointer			 				pointer;
	typedef typename allocator_type::const_pointer 						const_pointer;
	typedef ft::random_access_iterator<value_type, T*, T&> 				iterator;
	typedef ft::random_access_iterator<value_type, const T*, const T&> 	const_iterator;
	typedef ft::reverse_iterator<iterator> 								reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> 						const_reverse_iterator;
	typedef std::ptrdiff_t 												difference_type;
	typedef std::size_t 												size_type;

protected:
	size_type		 _size;
	size_type		 _capacity;
	pointer			_array;
	allocator_type	_allocator;

	void checkRange(size_type n) const
	{
		if (n >= this->_size)
			throw std::out_of_range("vector");
	}

public: // methods
	// constructors/destructors
	explicit vector(const allocator_type &alloc = allocator_type())
		: _size(0), _capacity(0), _array(NULL), _allocator(alloc) {}

	explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
		: _size(n), _capacity(n), _allocator(alloc)
	{
		this->_array = this->_allocator.allocate(this->_capacity);
		for (size_type i = 0; i < this->_size; i++)
			this->_allocator.construct(&this->_array[i], val);
	}

	template <class InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL)
		: _size(0), _allocator(alloc)
	{
		this->_capacity = ft::distance(first, last);
		this->_array = this->_allocator.allocate(this->_capacity);
		for (; first != last; ++first)
			this->push_back(*first);
	}

	vector(const vector &x)
		: _size(x._size), _capacity(x._size), _allocator(x._allocator)
	{
		this->_array = this->_allocator.allocate(this->_capacity);
		for (size_type i = 0; i < this->_size; i++)
			this->_allocator.construct(&this->_array[i], x[i]);
	}

	~vector()
	{
		for (size_type i = 0; i < this->_size; i++)
			this->_allocator.destroy(&this->_array[i]);
		this->_allocator.deallocate(this->_array, this->_capacity);
	}

	vector &operator=(const vector &other)
	{
		if (this != &other)
		{
			this->clear();
			this->reserve(other._size);
			for (size_type i = 0; i < other._size; i++)
				this->_allocator.construct(&this->_array[i], other._array[i]);
			this->_size = other._size;
		}
		return *this;
	}

	// iterators

	iterator begin(void)
	{
		return iterator(this->_array);
	}

	const_iterator begin(void) const
	{
		return const_iterator(this->_array);
	}

	iterator end(void)
	{
		return iterator(this->_array + this->_size);
	}

	const_iterator end(void) const
	{
		return const_iterator(this->_array + this->_size);
	}

	reverse_iterator rbegin(void)
	{
		return reverse_iterator(this->end());
	}

	const_reverse_iterator rbegin(void) const
	{
		return const_reverse_iterator(this->end());
	}

	reverse_iterator rend(void)
	{
		return reverse_iterator(this->_array);
	}

	const_reverse_iterator rend(void) const
	{
		return const_reverse_iterator(this->_array);
	}

	// capacity

	size_type size(void) const
	{
		return this->_size;
	}

	size_type max_size(void) const
	{
		return this->_allocator.max_size();
	}

	void resize(size_type n, value_type val = value_type())
	{
		while (n < this->_size)
			this->pop_back();
		if (n > this->_capacity * 2)
			this->reserve(n);
		else if (n > this->_capacity)
			this->reserve(this->_capacity * 2);
		while (n > this->_size)
			this->push_back(val);
	}

	size_type capacity(void) const
	{
		return this->_capacity;
	}

	bool empty(void) const
	{
		return this->_size == 0;
	}

	void reserve(size_type n)
	{
		pointer newarray;

		if (n <= this->_capacity)
			return;
		if (n > this->max_size())
			throw std::length_error("vector::reserve");
		newarray = this->_allocator.allocate(n);
		for (size_type i = 0; i < this->_size; i++)
			this->_allocator.construct(newarray + i, this->_array[i]);
		for (size_type i = 0; i < this->_size; i++)
			this->_allocator.destroy(&this->_array[i]);
		this->_allocator.deallocate(this->_array, this->_capacity);
		this->_array = newarray;
		this->_capacity = n;
	}

	// element access

	reference operator[](size_type n)
	{
		this->checkRange(n);
		return this->_array[n];
	}

	const_reference operator[](size_type n) const
	{
		this->checkRange(n);
		return this->_array[n];
	}

	reference at(size_type n)
	{
		this->checkRange(n);
		return this->_array[n];
	}

	const_reference at(size_type n) const
	{
		this->checkRange(n);
		return this->_array[n];
	}

	reference front()
	{
		this->checkRange(0);
		return this->_array[0];
	}

	const_reference front() const
	{
		this->checkRange(0);
		return this->_array[0];
	}

	reference back()
	{
		this->checkRange(this->_size - 1);
		return this->_array[this->_size - 1];
	}

	const_reference back() const
	{
		this->checkRange(this->_size - 1);
		return this->_array[this->_size - 1];
	}

	// modifiers

	template <typename InputIterator>
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
	assign(InputIterator first, InputIterator last)
	{
		this->clear();
		for (; first != last; ++first)
			this->push_back(*first);
	}

	void assign(size_type n, const value_type &val)
	{
		this->clear();
		while (n)
		{
			this->push_back(val);
			--n;
		}
	}

	void push_back(const value_type &val)
	{
		if (this->_size + 1 > this->_capacity)
		{
			if (this->_size == 0)
				this->reserve(1);
			else
				this->reserve(this->_size * 2);
		}
		this->_allocator.construct(&this->_array[this->_size], val);
		this->_size++;
	}

	void pop_back(void)
	{
		if (this->_size == 0)
			return ;
		this->_size--;
		this->_allocator.destroy(this->_array + this->_size);
	}

	iterator insert(iterator position, const value_type &val)
	{
		size_type n = ft::distance(begin(), position);
		this->insert(position, 1, val);
		return (iterator(&this->_array[n]));
	}

	void insert(iterator position, size_type n, const value_type &val)
	{
		if (n <= 0)
			return;
		size_type sz = ft::distance(begin(), position);
		vector tmp(position, end());
		if (this->_size + n > this->_capacity * 2)
			this->reserve(this->_size + n);
		else if (this->_size + n > this->_capacity)
			this->reserve(this->_size * 2);
		while (this->_size > sz)
			this->pop_back();
		while (n)
		{
			this->push_back(val);
			--n;
		}
		iterator it = tmp.begin();
		while (it != tmp.end())
		{
			this->push_back(*it);
			++it;
		}
	}

	template <typename InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL)
	{
		vector tmp(position, end());
		size_type sz = ft::distance(begin(), position);
		while (this->_size > sz)
			this->pop_back();
		while (first != last)
		{
			this->push_back(*first);
			++first;
		}
		iterator it = tmp.begin();
		while (it != tmp.end())
		{
			this->push_back(*it);
			++it;
		}
	}

	iterator erase(iterator position)
	{
		iterator iter = position;

		while (iter != (this->end() - 1))
		{
			this->_allocator.destroy(&(*iter));
			this->_allocator.construct(&(*iter), *(++iter));
		}
		this->_allocator.destroy(&(*(this->end() - 1)));
		this->_size--;
		return (position);
	}

	iterator erase(iterator first, iterator last)
	{
		size_type i = 0;

		while((last + i) != this->end())
		{
			this->_allocator.destroy(&(*(first + i)));
			this->_allocator.construct(&(*(first + i)), *(last + i));
			i++;
		}
		while ((first + i) != this->end())
			this->_allocator.destroy(&(*(first + i++)));
		this->_size -= last - first;
		return (first);
	}

	void swap(vector &other)
	{
		size_type tmp_size = other._size;
		size_type tmp_capacity = other._capacity;
		Alloc tmp_allocator = other._allocator;
		pointer tmp_array = other._array;

		other._size = this->_size;
		other._capacity = this->_capacity;
		other._allocator = this->_allocator;
		other._array = this->_array;

		this->_size = tmp_size;
		this->_capacity = tmp_capacity;
		this->_allocator = tmp_allocator;
		this->_array = tmp_array;
	}

	void clear()
	{
		while (this->_size)
			this->pop_back();
	}

	// allocator

	allocator_type get_allocator(void) const
	{
		return this->_allocator;
	}
};

template <class T, class Alloc>
void swap(vector<T, Alloc> &lhs, vector<T, Alloc> &rhs)
{
	lhs.swap(rhs);
}

template <class T, class Alloc>
bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return rhs < lhs;
}

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return !(lhs < rhs);
}

} // namespace

#endif
