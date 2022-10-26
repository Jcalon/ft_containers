#pragma once

namespace ft
{

// iterator_traits

template<typename Iterator>
std::ptrdiff_t distance(Iterator first, Iterator last)
{ //, typename ft::check_type<typename ft::iterator_traits<Iterator>::iterator_category>::type* = 0) {
	std::ptrdiff_t dist = 0;
	while (first != last) {
		++dist;
		++first;
	}
	return dist;
}

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
			return reverse_iterator(this->current - n);
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
			return reverse_iterator(this->current + n);
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

// random_access_iterator

// template <class T>
// class random_access_iterator
// {
// 	public: //types
// 			typedef	random_access_iterator<T>		iterator_type;
// 			typedef std::random_access_iterator_tag	iterator_category;
// 			typedef T								value_type;
// 			typedef T*								pointer;
// 			typedef T&								reference;
// 			typedef std::ptrdiff_t					difference_type;
// 			typedef random_access_iterator<const T>	const_iterator;
// 	protected:
// 		pointer pt;
	
// 	public: //methods
// 		random_access_iterator() : pt(NULL) {}
// 		explicit random_access_iterator(pointer ptr): pt(ptr) {}
// 		random_access_iterator(const random_access_iterator &instance) {*this = instance; }
// 		~random_access_iterator() {}

// 		//getter
// 		pointer base() const
// 		{
// 			return this->pt;
// 		}

// 		//overloads

// 		operator const_iterator(void) const
// 		{
// 			return const_iterator(this->pt);
// 		}

// 		random_access_iterator &operator=(const random_access_iterator &rhs)
// 		{
// 			this->pt = rhs.pt;
// 			return *this;
// 		}

// 		reference operator*(void) const
// 		{
// 			return *this->pt;
// 		}

// 		iterator_type operator+(int rhs) const
// 		{
// 			return iterator_type(this->pt + rhs);
// 		}

// 		iterator_type &operator++(void)
// 		{
// 			this->pt++;
// 			return *this;
// 		}

// 		iterator_type operator++(int)
// 		{
// 			iterator_type copy(*this);
// 			this->pt++;
// 			return copy;
// 		}

// 		iterator_type &operator+=(int rhs)
// 		{
// 			this->pt += rhs;
// 			return *this;
// 		}

// 		iterator_type operator-(int rhs) const
// 		{
// 			return iterator_type(this->pt - rhs);
// 		}

// 		iterator_type &operator--(void)
// 		{
// 			this->pt--;
// 			return *this;
// 		}

// 		iterator_type operator--(int)
// 		{
// 			iterator_type copy(*this);
// 			this->pt--;
// 			return copy;
// 		}

// 		iterator_type &operator-=(int rhs)
// 		{
// 			this->pt -= rhs;
// 			return *this;
// 		}

// 		pointer operator->(void) const
// 		{
// 			return this->pt;
// 		}

// 		reference operator[](const int n) const
// 		{
// 			return this->pt[n];
// 		}

// 		//relational operators overload

// 		bool operator==(const iterator_type &rhs)
// 		{
// 			return this->pt == rhs.pt;
// 		}
// 		bool operator!=(const iterator_type &rhs)
// 		{
// 			return this->pt != rhs.pt;
// 		}
// 		bool operator>(const iterator_type &rhs)
// 		{
// 			return this->pt > rhs.pt;
// 		}
// 		bool operator>=(const iterator_type &rhs)
// 		{
// 			return this->pt >= rhs.pt;
// 		}
// 		bool operator<(const iterator_type &rhs)
// 		{
// 			return this->pt < rhs.pt;
// 		}
// 		bool operator<=(const iterator_type &rhs)
// 		{
// 			return this->pt <= rhs.pt;
// 		}

// 		int operator+(const iterator_type &rhs)
// 		{
// 			return (this->pt + rhs.pt);
// 		}

// 		int operator-(const iterator_type &rhs)
// 		{
// 			return (this->pt - rhs.pt);
// 		}
// };

// // external overloads for random_access_iterator
// template <class T>
// bool operator==(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
// {
// 	return lhs.base() == rhs.base();
// }

// template <class T>
// bool operator!=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
// {
// 	return lhs.base() != rhs.base();
// }

// template <class T>
// bool operator<(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
// {
// 	return lhs.base() < rhs.base();
// }

// template <class T>
// bool operator>(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
// {
// 	return lhs.base() > rhs.base();
// }

// template <class T>
// bool operator<=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
// {
// 	return lhs.base() <= rhs.base();
// }

// template <class T>
// bool operator>=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
// {
// 	return lhs.base() >= rhs.base();
// }

// // Comparison of reverse and const_reverse

// template <class T_L, class T_R>
// bool operator==(const random_access_iterator<T_L> &lhs, const random_access_iterator<T_R> &rhs)
// {
// 	return lhs.base() == rhs.base();
// }

// template <class T_L, class T_R>
// bool operator!=(const random_access_iterator<T_L> &lhs, const random_access_iterator<T_R> &rhs)
// {
// 	return lhs.base() != rhs.base();
// }

// template <class T_L, class T_R>
// bool operator<(const random_access_iterator<T_L> &lhs, const random_access_iterator<T_R> &rhs)
// {
// 	return lhs.base() < rhs.base();
// }

// template <class T_L, class T_R>
// bool operator>(const random_access_iterator<T_L> &lhs, const random_access_iterator<T_R> &rhs)
// {
// 	return lhs.base() > rhs.base();
// }

// template <class T_L, class T_R>
// bool operator<=(const random_access_iterator<T_L> &lhs, const random_access_iterator<T_R> &rhs)
// {
// 	return lhs.base() <= rhs.base();
// }

// template <class T_L, class T_R>
// bool operator>=(const random_access_iterator<T_L> &lhs, const random_access_iterator<T_R> &rhs)
// {
// 	return lhs.base() >= rhs.base();
// }

// template <class Iterator>
// random_access_iterator<Iterator> operator+(typename random_access_iterator<Iterator>::difference_type n, const random_access_iterator<Iterator> &it)
// {
// 	it += n;
// 	return it;
// }

// template <class Iterator>
// typename random_access_iterator<Iterator>::difference_type operator-(const random_access_iterator<Iterator> &lhs, const random_access_iterator<Iterator> &rhs)
// {
// 	return lhs.base() - rhs.base();
// }

// template <class Iterator1, class Iterator2>
// typename random_access_iterator<Iterator1>::difference_type operator-(const random_access_iterator<Iterator1> &lhs, const random_access_iterator<Iterator2> &rhs)
// {
// 	return lhs.base() - rhs.base();
// }


template < typename T, typename Pointer, typename Reference, class Category = std::random_access_iterator_tag >
class random_access_iterator
{
	public:
		typedef random_access_iterator<T, Pointer, Reference>	this_type;
		typedef random_access_iterator<T, T*, T&>				iterator;
		typedef random_access_iterator<T, const T*, const T&>	const_iterator;
		typedef T				value_type;
		typedef Pointer			pointer;
		typedef Reference		reference;
		typedef size_t			size_type;
		typedef std::ptrdiff_t		difference_type;
		typedef	Category		iterator_category;
		template <class T2, class A>					friend class vector;

	// protected:
		pointer	array;

	public:

		random_access_iterator() : array(NULL) {}
		random_access_iterator(const pointer elem) : array(elem) {}
		random_access_iterator(const iterator& x) : array(const_cast<pointer>(x.array)) {}
		virtual ~random_access_iterator() {}

		this_type&	operator=(const iterator& x)
		{
			this->array = x.array;
			return *this;
		}

		this_type	operator++(int)
		{
			this_type out(*this);
			++this->array;
			return out;
		}

		this_type&	operator++() {
			this->array++;
			return *this;
		}

		this_type	operator+(difference_type n) const
		{
			this_type out(*this);
			out.array += n;
			return out;
		}

		this_type&	operator+=(difference_type n)
		{
			this->array += n;
			return *this;
		}

		this_type	operator--(int)
		{
			this_type out(*this);
			--this->array;
			return out;
		}

		this_type&	operator--()
		{
			--this->array;
			return *this;
		}

		difference_type	operator-(random_access_iterator it) const
		{
			return this->array - it.array;
		}

		this_type	operator-(difference_type n) const
		{
			this_type out(*this);
			out -= n;
			return out;
		}

		this_type&	operator-=(difference_type n)
		{
			this->array -= n;
			return *this;
		}

		reference	operator*()
		{
			return *this->array;
		}

		pointer		operator->()
		{
			return *(&(this->array));
		}

		template<typename T2, typename P, typename R, class C>
		friend inline bool operator==(const this_type& lhs, const random_access_iterator<T2, P, R, C>& rhs)
		{
			return (lhs.array == rhs.array);
		}

		template<typename T2, typename P, typename R, class C>
		friend inline bool operator!=(const this_type& lhs, const random_access_iterator<T2, P, R, C>& rhs)
		{
			return !(lhs == rhs);
		}

		template<typename T2, typename P, typename R, class C>
		friend inline bool operator<(const this_type& lhs, const random_access_iterator<T2, P, R, C>& rhs)
		{
			return (lhs.array < rhs.array);
		}

		template<typename T2, typename P, typename R, class C>
		friend inline bool operator>(const this_type& lhs, const random_access_iterator<T2, P, R, C>& rhs)
		{
			return (rhs < lhs);
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
			return (*(this->array + n));
		}
	};

template <typename T, typename P, typename R, typename C>
inline random_access_iterator<T,P,R,C>	operator+(typename random_access_iterator<T,P,R,C>::difference_type n, const random_access_iterator<T,P,R,C>& x) 
{
	return x + n;
}


} // namespace ft
