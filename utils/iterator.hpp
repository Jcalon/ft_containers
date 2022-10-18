#pragma once

#include <iterator>
#include <cstddef>

namespace ft
{

// iterator_traits

template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator
{
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

template <class Iterator>
struct iterator_traits
{
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};


template <class T>
struct iterator_traits<T*>
{
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

template <class T>
struct iterator_traits<const T*>
{
	typedef std::ptrdiff_t					difference_type;
	typedef T								value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::random_access_iterator_tag	iterator_category;
};

//reverse_iterator

template <class Iterator>
class reverse_iterator
{
	public: //types
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
	
	protected:
		iterator_type current;
	
	public: //methods
		reverse_iterator() : current() {}
		explicit reverse_iterator(iterator_type it): current(it) {}
		template<class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it): current(rev_it.base()) {}
		~reverse_iterator() {}

		//getter
		iterator_type base() const
		{
			return this->current;
		}

		//overloads
		template<class Iter>
		reverse_iterator &operator=(const reverse_iterator<Iter> &rev_it)
		{
			this->current = rev_it.base();
			return *this;
		}

		reference operator*(void) const
		{
			iterator_type tmp = this->current;
			return *--tmp;
		}

		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(this->current + n);
		}

		reverse_iterator &operator++(void)
		{
			--this->current;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			--this->current;
			return tmp;
		}

		reverse_iterator &operator+=(difference_type n)
		{
			this->current -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(this->current - n);
		}

		reverse_iterator &operator--(void)
		{
			++this->current;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			++this->current;
			return tmp;
		}

		reverse_iterator &operator-=(difference_type n)
		{
			this->current += n;
			return *this;
		}

		pointer operator->(void) const
		{
			return &(operator*());
		}

		reference operator[](difference_type n) const
		{
			return *(this + n);
		}

};

// external overloads for reverse_iterator
template <class Iterator>
bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() == rhs.base();
}

template <class Iterator>
bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() != rhs.base();
}

template <class Iterator>
bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() < rhs.base();
}

template <class Iterator>
bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() > rhs.base();
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() <= rhs.base();
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() >= rhs.base();
}

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
{
	return (rev_it.base() - n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return rhs.base() - lhs.base();
}

// random_access_iterator

template <class Iterator>
class random_access_iterator
{
	public: //types
		typedef random_access_iterator<Iterator> iterator;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
	
	protected:
		pointer pt;
	
	public: //methods
		random_access_iterator() : pt(NULL) {}
		explicit random_access_iterator(pointer ptr): pt(ptr) {}
		random_access_iterator(const random_access_iterator &instance) {*this = instance; }
		~random_access_iterator() {}

		//getter
		random_access_iterator base() const
		{
			return this->pt;
		}

		//overloads
		random_access_iterator &operator=(const random_access_iterator &rhs)
		{
			this->pt = rhs.base();
			return *this;
		}

		reference operator*(void) const
		{
			return *this->pt;
		}

		iterator operator+(int rhs)
		{
			return iterator(this->pt + rhs);
		}

		iterator &operator++(void)
		{
			this->pt++;
			return *this;
		}

		iterator operator++(int)
		{
			iterator copy(*this);
			this->pt++;
			return copy;
		}

		iterator &operator+=(int rhs)
		{
			this->pt -= rhs;
			return *this;
		}

		iterator operator-(int rhs)
		{
			return iterator(this->pt - rhs);
		}

		iterator &operator--(void)
		{
			this->pt--;
			return *this;
		}

		iterator operator--(int)
		{
			iterator copy(*this);
			this->pt--;
			return copy;
		}

		iterator &operator-=(int rhs)
		{
			this->pt += rhs;
			return *this;
		}

		pointer operator->(void) const
		{
			return this->pt;
		}

		reference operator[](const int n) const
		{
			return this->pt[n];
		}

};

// external overloads for random_access_iterator
template <class T>
bool operator==(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
{
	return lhs.base() == rhs.base();
}

template <class T>
bool operator!=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
{
	return lhs.base() != rhs.base();
}

template <class T>
bool operator<(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
{
	return lhs.base() < rhs.base();
}

template <class T>
bool operator>(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
{
	return lhs.base() > rhs.base();
}

template <class T>
bool operator<=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
{
	return lhs.base() <= rhs.base();
}

template <class T>
bool operator>=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
{
	return lhs.base() >= rhs.base();
}

// Comparison of reverse and const_reverse

template <class T_L, class T_R>
bool operator==(const random_access_iterator<T_L> &lhs, const random_access_iterator<T_R> &rhs)
{
	return lhs.base() == rhs.base();
}

template <class T_L, class T_R>
bool operator!=(const random_access_iterator<T_L> &lhs, const random_access_iterator<T_R> &rhs)
{
	return lhs.base() != rhs.base();
}

template <class T_L, class T_R>
bool operator<(const random_access_iterator<T_L> &lhs, const random_access_iterator<T_R> &rhs)
{
	return lhs.base() < rhs.base();
}

template <class T_L, class T_R>
bool operator>(const random_access_iterator<T_L> &lhs, const random_access_iterator<T_R> &rhs)
{
	return lhs.base() > rhs.base();
}

template <class T_L, class T_R>
bool operator<=(const random_access_iterator<T_L> &lhs, const random_access_iterator<T_R> &rhs)
{
	return lhs.base() <= rhs.base();
}

template <class T_L, class T_R>
bool operator>=(const random_access_iterator<T_L> &lhs, const random_access_iterator<T_R> &rhs)
{
	return lhs.base() >= rhs.base();
}

} // namespace ft
