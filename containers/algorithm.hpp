/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crazyd <crazyd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:36:24 by jcalon            #+#    #+#             */
/*   Updated: 2022/11/08 11:56:57 by crazyd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft
{

template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
  while (first1 != last1)
  {
    if (!(*first1 == *first2))
      return false;
    ++first1;
	++first2;
  }
  return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
{
  while (first1 != last1)
  {
    if (!pred(*first1, *first2))
      return false;
    ++first1;
	++first2;
  }
  return true;
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
{
  while (first1 != last1)
  {
    if (first2 == last2 || *first2 < *first1)
		return false;
    else if (*first1 < *first2)
		return true;
    ++first1;
	++first2;
  }
  return (first2 != last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
{
  while (first1 != last1)
  {
    if (first2 == last2 || comp(*first1, *first2))
		return true;
    else if (comp(*first2, *first1))
		return false;
    ++first1;
	++first2;
  }
  return false;
}

} // namespace ft

#endif
