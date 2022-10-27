#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft
{

// usefull

template<typename Iterator>
std::ptrdiff_t distance(Iterator first, Iterator last)
{
	std::ptrdiff_t dist = 0;
	while (first != last) {
		++dist;
		++first;
	}
	return dist;
}

// iterator_traits

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
		iterator_type _current;
	
	public: //methods
		reverse_iterator() : _current() {}
		explicit reverse_iterator(iterator_type it): _current(it) {}
		template<class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it): _current(rev_it.base()) {}
		~reverse_iterator() {}

		//getter
		iterator_type base() const
		{
			return this->_current;
		}

		//overloads
		template<class Iter>
		reverse_iterator &operator=(const reverse_iterator<Iter> &rev_it)
		{
			this->_current = rev_it.base();
			return *this;
		}

		reference operator*(void) const
		{
			iterator_type tmp = this->_current;
			return *--tmp;
		}

		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(this->_current - n);
		}

		reverse_iterator &operator++(void)
		{
			--this->_current;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			--this->_current;
			return tmp;
		}

		reverse_iterator &operator+=(difference_type n)
		{
			this->_current -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(this->_current + n);
		}

		reverse_iterator &operator--(void)
		{
			++this->_current;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			++this->_current;
			return tmp;
		}

		reverse_iterator &operator-=(difference_type n)
		{
			this->_current += n;
			return *this;
		}

		pointer operator->(void) const
		{
			return &(this->operator*());
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
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
	return lhs.base() > rhs.base();
}

template <class Iterator>
bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() < rhs.base();
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() >= rhs.base();
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() <= rhs.base();
}

// external comparison overloads for const

template <class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
	return lhs.base() == rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator!=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
	return lhs.base() != rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
	return lhs.base() > rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
	return lhs.base() < rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
	return lhs.base() >= rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
	return lhs.base() <= rhs.base();
}

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
{
	return reverse_iterator<Iterator>(rev_it.base() - n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
{
	return lhs.base() - rhs.base();
}

template <class Iterator1, class Iterator2>
typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
{
	return -(lhs.base() - rhs.base());
}

template <typename T, typename Pointer, typename Reference, class Category = std::random_access_iterator_tag>
class random_access_iterator
{
	public:
		typedef random_access_iterator<T, Pointer, Reference>	this_type;
		typedef random_access_iterator<T, T*, T&>				iterator;
		typedef random_access_iterator<T, const T*, const T&>	const_iterator;
		typedef T												value_type;
		typedef Pointer											pointer;
		typedef Reference										reference;
		typedef size_t											size_type;
		typedef std::ptrdiff_t									difference_type;
		typedef	Category										iterator_category;
		template <class T2, class A>
		friend class vector;

	// protected:
		pointer	_array;

	public:

		random_access_iterator() : _array(NULL) {}
		random_access_iterator(const pointer elem) : _array(elem) {}
		random_access_iterator(const iterator& x) : _array(const_cast<pointer>(x._array)) {}
		virtual ~random_access_iterator() {}

		this_type&	operator=(const iterator& x)
		{
			this->_array = x._array;
			return *this;
		}

		this_type	operator++(int)
		{
			this_type out(*this);
			++this->_array;
			return out;
		}

		this_type&	operator++() {
			this->_array++;
			return *this;
		}

		this_type	operator+(difference_type n) const
		{
			this_type out(*this);
			out._array += n;
			return out;
		}

		this_type&	operator+=(difference_type n)
		{
			this->_array += n;
			return *this;
		}

		this_type	operator--(int)
		{
			this_type out(*this);
			--this->_array;
			return out;
		}

		this_type&	operator--()
		{
			--this->_array;
			return *this;
		}

		difference_type	operator-(random_access_iterator it) const
		{
			return this->_array - it._array;
		}

		this_type	operator-(difference_type n) const
		{
			this_type out(*this);
			out -= n;
			return out;
		}

		this_type&	operator-=(difference_type n)
		{
			this->_array -= n;
			return *this;
		}

		reference	operator*() const
		{
			return *this->_array;
		}

		pointer		operator->()
		{
			return *(&(this->_array));
		}

		template<typename T2, typename P, typename R, class C>
		friend inline bool operator==(const this_type& lhs, const random_access_iterator<T2, P, R, C>& rhs)
		{
			return lhs._array == rhs._array;
		}

		template<typename T2, typename P, typename R, class C>
		friend inline bool operator!=(const this_type& lhs, const random_access_iterator<T2, P, R, C>& rhs)
		{
			return !(lhs == rhs);
		}

		template<typename T2, typename P, typename R, class C>
		friend inline bool operator<(const this_type& lhs, const random_access_iterator<T2, P, R, C>& rhs)
		{
			return lhs._array < rhs._array;
		}

		template<typename T2, typename P, typename R, class C>
		friend inline bool operator>(const this_type& lhs, const random_access_iterator<T2, P, R, C>& rhs)
		{
			return rhs < lhs;
		}

		template<typename T2, typename P, typename R, class C>
		friend inline bool operator<=(const this_type& lhs, const random_access_iterator<T2, P, R, C>& rhs)
		{
			return !(rhs < lhs);
		}

		template<typename T2, typename P, typename R, class C>
		friend inline bool operator>=(const this_type& lhs, const random_access_iterator<T2, P, R, C>& rhs)
		{
			return !(lhs < rhs);
		}

		reference	operator[](difference_type n)
		{
			return *(this->_array + n);
		}
	};

template <typename T, typename P, typename R, typename C>
inline random_access_iterator<T,P,R,C>	operator+(typename random_access_iterator<T,P,R,C>::difference_type n, const random_access_iterator<T,P,R,C>& x) 
{
	return x + n;
}


} // namespace ft

#endif
