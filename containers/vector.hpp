#pragma once

#include <iostream>
#include <exception>
#include "../utils/type_traits.hpp"
#include "../utils/iterator.hpp"
#include "../utils/algorithm.hpp"

namespace ft
{

template < class T, class Alloc = std::allocator<T> >
class vector
{
	public: //types
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef ft::random_access_iterator<value_type>		iterator;
		typedef ft::random_access_iterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef std::ptrdiff_t								difference_type;
		typedef	std::size_t									size_type;

	protected:
		size_type		_size;
		size_type		_capacity;
		pointer			_array;
		allocator_type	_allocator;

		void	checkRange(size_type n)
		{
			if (n >= this->_size)
				throw OutOfRangeException(n);
		}

	public: //methods
		// constructors/destructors
		explicit vector (const allocator_type& alloc = allocator_type())
			: _size(0), _capacity(0), _allocator(alloc), _array(NULL) {}
		
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _size(n), _capacity(n), _allocator(alloc), _array(this->_allocator.allocate(this->_capacity))
		{
			for (size_type i = 0; i < this->_size; i++)
				this->_allocator.construct(&this->_array[i], val);
		}
		
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			: _size(last - first), _capacity(last - first), _allocator(alloc), _array(this->_allocator.allocate(this->_size))
		{
			for (size_type i = 0; first < last; i++)
				this->_allocator.construct(&this->_array[i], *(first + i));
		}
		
		vector(const vector& x)
			: _size(0), _capacity(0), _allocator(x._allocator), _array(NULL)
		{
			*this = x;
		}
		
		~vector()
		{
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

		const_iterator	begin(void) const
		{
			return const_iterator(this->_array);
		}

		iterator	end(void)
		{
			return iterator(this->_array + this->_size);
		}

		const_iterator	end(void) const
		{
			return const_iterator(this->_array + this->_size);
		}

		reverse_iterator	rbegin(void)
		{
			return reverse_iterator(this->end());
		}

		const_reverse_iterator	rbegin(void) const
		{
			return const_reverse_iterator(this->end());
		}

		reverse_iterator	rend(void)
		{
			return reverse_iterator(this->_array());
		}

		const_reverse_iterator	rend(void) const
		{
			return const_reverse_iterator(this->_array());
		}

	// capacity

		size_type	size(void) const
		{
			return this->_size;
		}

		size_type	max_size(void) const
		{
			return this->_allocator.max_size();
		}

		void	resize(size_type n, value_type val = value_type())
		{
			if (n < this->_size)
				for (size_type i = n; i <= this->_size; i++)
					this->_allocator.destroy(&this->_array[i]);
			else if (n == this->_size)
				return ;
			else
			{
				this->reserve(n);
				for (size_type i = this->_size; i < n; i++)
					this->_allocator.construct(&this->_array[i], val);
			}
			this->_size = n;
		}

		size_type	capacity(void) const
		{
			return this->_capacity;
		}

		bool	empty(void) const
		{
			return this->_size == 0;
		}

		void	reserve(size_type n)
		{
			value_type	*newarray;

			if (n < this->_capacity)
				return ;
			newarray = this->_allocator.allocate(n);
			for (size_type i = 0; i < this->_size; i++)
				this->_allocator.construct(&newarray[i], this->_array[i]);
			this->_allocator.deallocate(this->_array, this->_capacity);
			this->_array = newarray;
			this->_capacity = n;
		}

	// element access

		reference	operator[](size_type n)
		{
			this->checkRange(n);
			return this->_array[n];
		}

		const_reference	operator[](size_type n) const
		{
			this->checkRange(n);
			return this->_array[n];
		}

		reference	at(size_type n)
		{
			this->checkRange(n);
			return this->_array[n];
		}

		const_reference	at(size_type n) const
		{
			this->checkRange(n);
			return this->_array[n];
		}

		reference	front()
		{
			this->checkRange(0);
			return this->_array[0];
		}

		const_reference	front() const
		{
			this->checkRange(0);
			return this->_array[0];
		}

		reference	back()
		{
			this->checkRange(this->_size - 1);
			return this->_array[this->_size - 1];
		}

		const_reference	back() const
		{
			this->checkRange(this->_size - 1);
			return this->_array[this->_size - 1];
		}

	// modifiers

		template<typename InputIterator>
		void	assign(InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = false)
		{
			if (this->_array)
				this->_allocator.deallocate(this->_array, this->_capacity);
			this->_size = last - first;
			if (this->_capacity < this->_size)
				this->_capacity = this->_size;
			this->_array = this->_allocator.allocate(this->_capacity);
			for (size_type i = 0; i > this->_size; i++)
				this->_allocator.construct(&this->_array[i], *(first + i));
		}

		void	assign(size_type n, const value_type& val)
		{
			if (this->_array)
				this->_allocator.deallocate(this->_array, this->_capacity);
			this->_size = n;
			if (this->_capacity < this->_size)
				this->_capacity = this->_size;
			this->_array = this->_allocator.allocate(this->_capacity);
			for (size_type i = 0; i > this->_size; i++)
				this->_array[i] = val;
		}

		void	push_back(const value_type& val)
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

		void	pop_back(void)
		{
			if (this->_size == 0)
				return ;
			this->_allocator.destroy(this->_array + this->_size - 1);
			this->_size--;
		}

		iterator	insert(iterator position, const value_type& val)
		{
			if (this->_size + 1 > this->_capacity)
			{
				if (this->_size == 0)
					this->reserve(1);
				else if (this->_size + 1 > this->_size * 2)
					this->reserve(this->_size + 1);
				else
					this->reserve(this->_size * 2);
			}
			for (size_type i = this->_size; i > position - this->begin(); i--)
					this->_allocator.construct(&this->_array[i], this->_array[i - 1]);
			this->_allocator.construct(&this->_array[position - this->begin()], val);
			this->_size++;
			return (position);
		}

		void	insert(iterator position, size_type n, const value_type& val)
		{
			if (this->_size + n > this->_capacity)
			{
				if (this->_size == 0)
					this->reserve(n);
				else if (this->_size + n > this->_size * 2)
					this->reserve(this->_size + n);
				else
					this->reserve(this->_size * 2);
			}
			for (size_type i = this->_size + n - 1; i > position - this->begin() + n - 1; i--)
					this->_allocator.construct(&this->_array[i], this->_array[i - n]);
			for (size_type i = 0; i < n; i++)
				this->_allocator.construct(&this->_array[position - this->begin() + i], val);
			this->_size += n;
		}

		template<typename InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		{
			size_type	n = last - first;

			if (this->_size + n > this->_capacity)
			{
				if (this->_size == 0)
					this->reserve(n);
				else if (this->_size + n > this->_size * 2)
					this->reserve(this->_size + n);
				else
					this->reserve(this->_size * 2);
			}
			for (size_type i = this->_size + n - 1; i > position - this->begin() + n - 1; i--)
					this->_allocator.construct(&this->_array[i], this->_array[i - n]);
			for (size_type i = 0; i < n; i++)
				this->_allocator.construct(&this->_array[position - this->begin() + i], *(first + i));
			this->_size += n;
		}

		iterator	erase(iterator position)
		{
			iterator iter = position;
			
			this->_allocator.destroy(&(*position));
			while (iter != (this->end() - 1))
				this->_allocator.construct(&(*iter), *(++iter));
			this->_size--;
			return (position);
		}

		iterator	erase(iterator first, iterator last)
		{
			for (size_type i = 0; (last + i) != this->end(); i++)
			{
				this->_allocator.destroy(&(*(first + i)));
				this->_allocator.construct(&(*(first + i)), *(last + i));
			}
			this->_size -= last - first;
			return(first);
		}

		void	swap(vector& other)
		{
				size_type	tmp_size = other._size;
				size_type	tmp_capacity = other._capacity;
				Alloc		tmp_allocator = other._allocator;
				pointer		tmp_array = other._array;

				other._size = this->_size;
				other._capacity = this->_capacity;
				other._allocator = this->_allocator;
				other._array = this->_array;

				this->_size = tmp_size;
				this->_capacity = tmp_capacity;
				this->_allocator = tmp_allocator;
				this->_array = tmp_array;
		}

		void	clear()
		{
			this->_allocator.destroy(this->_array);
			this->_size = 0;
		}

	// allocator

	allocator_type	get_allocator(void) const
	{
		return this->_allocator;
	}

	// exception

		class OutOfRangeException : public std::exception
		{
			size_t _pos;

			public:
				OutOfRangeException(int n) : _pos(n){}
				virtual const char* what() const throw()
				{
					return ("vector::_M_range_check: index >= this->_size()");
				}
		};
};

template <class T, class Alloc>
void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
{
	lhs.swap(rhs);
}

template <class T, class Alloc>
bool operator==(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
{
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
bool operator!=(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
{
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), rhs.begin(), lhs.end(), rhs.end());
}

template <class T, class Alloc>
bool operator<=(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
{
	return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
{
	return rhs < lhs;
}

template <class T, class Alloc>
bool operator>=(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
{
	return !(lhs < rhs);
}

} // namespace