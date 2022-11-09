/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:15:41 by jcalon            #+#    #+#             */
/*   Updated: 2022/11/09 16:43:52 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{

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
		pointer	_array;

	public:
		random_access_iterator() : _array(NULL) {}
		random_access_iterator(const pointer elem) : _array(elem) {}
		random_access_iterator(const iterator &x) : _array(const_cast<pointer>(x._array)) {}
		virtual ~random_access_iterator() {}

		this_type &operator=(const iterator &x)
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

		this_type	&operator++() {
			this->_array++;
			return *this;
		}

		this_type	operator+(difference_type n) const
		{
			this_type out(*this);
			out._array += n;
			return out;
		}

		this_type	&operator+=(difference_type n)
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

		this_type	&operator--()
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

		this_type	&operator-=(difference_type n)
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
		friend bool operator==(const this_type &lhs, const random_access_iterator<T2, P, R, C> &rhs)
		{
			return lhs._array == rhs._array;
		}

		template<typename T2, typename P, typename R, class C>
		friend bool operator!=(const this_type &lhs, const random_access_iterator<T2, P, R, C> &rhs)
		{
			return !(lhs == rhs);
		}

		template<typename T2, typename P, typename R, class C>
		friend bool operator<(const this_type &lhs, const random_access_iterator<T2, P, R, C> &rhs)
		{
			return lhs._array < rhs._array;
		}

		template<typename T2, typename P, typename R, class C>
		friend bool operator>(const this_type &lhs, const random_access_iterator<T2, P, R, C> &rhs)
		{
			return rhs < lhs;
		}

		template<typename T2, typename P, typename R, class C>
		friend bool operator<=(const this_type &lhs, const random_access_iterator<T2, P, R, C> &rhs)
		{
			return !(rhs < lhs);
		}

		template<typename T2, typename P, typename R, class C>
		friend bool operator>=(const this_type &lhs, const random_access_iterator<T2, P, R, C> &rhs)
		{
			return !(lhs < rhs);
		}

		reference	operator[](difference_type n)
		{
			return *(this->_array + n);
		}
	};

template <typename T, typename P, typename R, typename C>
inline random_access_iterator<T,P,R,C>	operator+(typename random_access_iterator<T,P,R,C>::difference_type n, const random_access_iterator<T,P,R,C> &x) 
{
	return x + n;
}

} // namespace ft

#endif