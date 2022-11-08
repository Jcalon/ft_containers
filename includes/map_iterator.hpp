/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:15:04 by jcalon            #+#    #+#             */
/*   Updated: 2022/11/08 18:46:16 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR
#define MAP_ITERATOR

#include "iterator.hpp"
#include "rbtree.hpp"
#include "../containers/map.hpp"

namespace ft
{
	
template <typename T, typename Pointer, typename Reference, class Category = std::bidirectional_iterator_tag>
class map_iterator
{
	public:

			typedef	map_iterator<T, Pointer, Reference>	this_type;
			typedef	map_iterator<T, T*, T&>				iterator;
			typedef	map_iterator<T, const T*, const T&>	const_iterator;
			typedef Category							iterator_category;
			typedef T									value_type;
			typedef Pointer								pointer;
			typedef Reference							reference;
			typedef ft::RedBlackTree<T>*				node_pointer;
			typedef ft::RedBlackTree<T>&				node_reference;
			typedef std::ptrdiff_t						difference_type;
			template <class K, class T2, class C, class A>
			friend class map;

		// protected:
			node_pointer	_node_pointer;
			
		public:
			//canonical

			map_iterator(): _node_pointer(NULL) {}
			map_iterator(const node_pointer ptr): _node_pointer(ptr) {}
			map_iterator(const iterator &instance) {*this = instance;}
			~map_iterator() {}

			this_type	&operator=(const iterator &rhs)
			{
				this->_node_pointer = rhs._node_pointer;
				return *this;
			}

			node_pointer	get_node(void) const
			{
				return (this->_node_pointer);
			}

			//relational operators overload

			bool	operator==(const this_type &rhs)
			{
				return this->_node_pointer == rhs._node_pointer;
			}

			bool	operator!=(const this_type &rhs)
			{
				return this->_node_pointer != rhs._node_pointer;
			}

			//increment and decrement

			this_type	&operator++(void)
			{
				this->_node_pointer = ft::tree_next(this->_node_pointer);
				return *this;
			}

			this_type	&operator--(void)
			{
				this->_node_pointer = ft::tree_previous(this->_node_pointer);
				return *this;
			}

			this_type	operator++(int)
			{
				this_type copy(*this);
				this->_node_pointer = ft::tree_next(this->_node_pointer);
				return copy;
			}

			this_type	operator--(int)
			{
				this_type copy(*this);
				this->_node_pointer = ft::tree_previous(this->_node_pointer);
				return copy;
			}

			//dereference operator
			reference	operator*(void) const
			{
				return *(this->_node_pointer->_data);
			}

			pointer	operator->(void) const
			{
				return this->_node_pointer->_data;
			}
	};

// template <class Iterator>
// std::ostream &operator<<(std::ostream &o, map_iterator<Iterator> const &i)
// {
// 	o << "node adress: " << i.get_node() << std::endl;
// 	return o;
// }

} // namespace ft

#endif