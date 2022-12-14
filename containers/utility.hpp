/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:15:25 by jcalon            #+#    #+#             */
/*   Updated: 2022/11/02 19:00:13 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft
{

template <class T1, class T2>
struct pair
{
	public: //types
		typedef T1	first_type;
		typedef T2	second_type;

	public: //attributes
		first_type	first;
		second_type second;

	public: //methods
		pair() : first(T1()), second(T2()) {}
		template <class U, class V>
		pair(const pair<U,V> &pr): first(pr.first), second(pr.second) {}
		pair(const first_type &a, const second_type &b): first(a), second(b) {}
		pair &operator=(const pair &pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return *this;
		}
};

template<class T1, class T2>
bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template<class T1, class T2>
bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return !(lhs == rhs);
}

template<class T1, class T2>
bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template<class T1, class T2>
bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return rhs < lhs;
}

template<class T1, class T2>
bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return !(rhs < lhs);
}

template<class T1, class T2>
bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
	return !(lhs < rhs);
}

template <class T1,class T2>
pair<T1, T2> make_pair (T1 x, T2 y)
{
	return pair<T1,T2>(x, y);
}

} // namespace ft

#endif
