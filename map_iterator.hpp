/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crazyd <crazyd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:15:04 by jcalon            #+#    #+#             */
/*   Updated: 2022/11/04 00:23:49 by crazyd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR
#define MAP_ITERATOR

#include "iterator.hpp"
#include "rbtree.hpp"

namespace ft
{
	
template <typename T>
class map_iterator
{
	public:

			typedef	map_iterator<T>					iterator;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef ft::RedBlackTree<T>*			node_pointer;
			typedef ft::RedBlackTree<T>&			node_reference;
			typedef std::ptrdiff_t					difference_type;
		
		private:
			node_pointer	_node_pointer;
			
		public:
			//canonical

			map_iterator(): _node_pointer(NULL) {}
			explicit map_iterator(node_pointer ptr): _node_pointer(ptr) {}
			map_iterator(const map_iterator &instance) {*this = instance;}
			~map_iterator() {}

			map_iterator	&operator=(const map_iterator &rhs)
			{
				this->_node_pointer = rhs._node_pointer;
				return *this;
			}

			node_pointer	get_node(void) const
			{
				return (this->_node_pointer);
			}

			//relational operators overload

			bool	operator==(const iterator &rhs)
			{
				return this->_node_pointer == rhs._node_pointer;
			}
			bool	operator!=(const iterator &rhs)
			{
				return this->_node_pointer != rhs._node_pointer;
			}

			//increment and decrement

			iterator	&operator++(void)
			{
				this->_node_pointer = ft::tree_next(this->_node_pointer);
				return *this;
			}

			iterator	&operator--(void)
			{
				this->_node_pointer = ft::tree_previous(this->_node_pointer);
				return *this;
			}

			iterator	operator++(int)
			{
				iterator copy(*this);
				this->_node_pointer = ft::tree_next(this->_node_pointer);
				return copy;
			}

			iterator	operator--(int)
			{
				iterator copy(*this);
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

template <class Iterator>
std::ostream &operator<<(std::ostream &o, map_iterator<Iterator> const &i)
{
	o << "node adress: " << i.get_node() << std::endl;
	return o;
}

} // namespace ft

#endif