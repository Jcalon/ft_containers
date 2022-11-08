/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crazyd <crazyd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:15:10 by jcalon            #+#    #+#             */
/*   Updated: 2022/11/08 13:18:25 by crazyd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef map_hpp
#define map_hpp

#include <iostream>
#include <limits>
#include "utility.hpp"
#include "iterator.hpp"
#include "map_iterator.hpp"
#include "rbtree.hpp"
#include "algorithm.hpp"

namespace ft
{

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename Alloc::reference reference;
		typedef typename Alloc::const_reference const_reference;
		typedef typename Alloc::pointer pointer;
		typedef typename Alloc::const_pointer const_pointer;
		typedef ft::map_iterator<value_type, value_type *, value_type &> iterator;
		typedef ft::map_iterator<value_type, const value_type *, const value_type &> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
		typedef typename Alloc::template rebind<ft::RedBlackTree<value_type> >::other node_allocator_type;

		class value_compare
		{
			friend class map;

		protected:
			key_compare comp;
			value_compare(key_compare c) : comp(c) {}

		public:
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

	protected:
		size_type _size;
		key_compare _compare;
		allocator_type _allocator;
		node_allocator_type _node_allocator;
		ft::RedBlackTree<value_type> *_root;

		bool _position_precedes_val(iterator position, const value_type &val)
		{
			return (this->upper_bound(val.first)-- == position);
		}

		value_type *_allocate_pair(const value_type &val)
		{
			value_type *new_pair = this->_allocator.allocate(1);
			this->_allocator.construct(new_pair, val);
			return (new_pair);
		}

	public: // methods
		// constructors/destructors

		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _size(0), _compare(comp), _allocator(alloc), _node_allocator(node_allocator_type()), _root(NULL)
		{
			ft::create_end_node(&this->_root, this->_node_allocator);
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
			: _size(0), _compare(comp), _allocator(alloc), _node_allocator(node_allocator_type()), _root(NULL)
		{
			this->insert(first, last);
		}

		map(const map &other)
			: _size(0), _compare(other.key_comp()), _allocator(other.get_allocator()), _node_allocator(node_allocator_type()), _root(NULL)
		{
			*this = other;
		}

		~map(void)
		{
			this->clear();
		}

		map &operator=(const map &other)
		{
			if (this != &other)
			{
				this->clear();
				this->insert(other.begin(), other.end());
			}
			return *this;
		}

		mapped_type &operator[](const key_type &key)
		{
			iterator pair_iterator;
			ft::pair<iterator, bool> insert_return;

			insert_return = insert(ft::make_pair(key, mapped_type()));
			pair_iterator = insert_return.first;
			return (pair_iterator->second);
		}

		// iterators

		iterator begin(void)
		{
			return iterator(ft::tree_begin(this->_root));
		}

		const_iterator begin(void) const
		{
			return const_iterator(ft::tree_begin(this->_root));
		}

		iterator end(void)
		{
			return iterator(ft::tree_end(this->_root));
		}

		const_iterator end(void) const
		{
			return const_iterator(ft::tree_end(this->_root));
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
			return reverse_iterator(this->begin());
		}

		const_reverse_iterator rend(void) const
		{
			return const_reverse_iterator(this->begin());
		}

		// capacity

		size_type size(void) const
		{
			return this->_size;
		}

		size_type max_size(void) const
		{
			if (sizeof(T) != 4)
				return static_cast<size_type>(std::numeric_limits<size_type>::max() / (sizeof(ft::RedBlackTree<value_type>) + sizeof(T)) / 2);
			return _node_allocator.max_size();
		}

		bool empty(void) const
		{
			return this->_size == 0;
		}

		// modifiers

		void clear(void)
		{
			if (this->_size == 0 && this->_root && ft::is_nil(this->_root))
			{
				this->_node_allocator.deallocate(this->_root, 1);
				this->_root = NULL;
			}
			this->erase(this->begin(), this->end());
			this->_root = NULL;
		}

		ft::pair<iterator, bool> insert(const value_type &value)
		{
			iterator it = this->find(value.first);

			if (it != this->end())
				return (ft::make_pair(it, false));
			ft::tree_insert_data(&this->_root, _allocate_pair(value), value_compare(this->_compare), _node_allocator);
			it = this->find(value.first);
			this->_size++;
			return (ft::make_pair(it, true));
		}

		iterator insert(iterator pos, const value_type &value)
		{
			iterator it = this->find(value.first);

			if (it != this->end())
				return (it);
			if (!_position_precedes_val(pos, value))
				return (this->insert(value).first);

			ft::RedBlackTree<value_type> *position_node = pos.get_node();

			ft::tree_insert_data<value_type>(&position_node, _allocate_pair(value), value_compare(this->_compare), _node_allocator);
			ft::update_root(&(this->_root));
			it = this->find(value.first);
			this->_size++;
			return (it);
		}

		template <class InputIt>
		void insert(InputIt first, InputIt last)
		{
			while (first != last)
				this->insert(*first++);
		}

		void erase(iterator pos)
		{
			value_type *pair_erased = tree_delete(&this->_root, *pos, value_compare(this->_compare), this->_node_allocator);
			this->_allocator.deallocate(pair_erased, 1);
			this->_size--;
		}

		void erase(iterator first, iterator last)
		{
			iterator tmp;
			value_type *next;

			while (first != last)
			{
				tmp = first;
				next = &(*(++tmp));
				this->erase(first);
				if (next)
					first = this->find(next->first);
				else
					first = last;
			}
		}

		size_type erase(const Key &k)
		{
			value_type *pair_erased = ft::tree_delete<value_type>(&this->_root, ft::make_pair(k, mapped_type()), value_compare(this->_compare), this->_node_allocator);
			if (!pair_erased)
				return (0);
			this->_allocator.deallocate(pair_erased, 1);
			this->_size--;
			return (1);
		}

		void swap(map &other)
		{
			ft::RedBlackTree<value_type> *root_tmp;
			size_type size_tmp;

			root_tmp = other._root;
			size_tmp = other._size;
			other._root = this->_root;
			other._size = this->_size;
			this->_root = root_tmp;
			this->_size = size_tmp;
		}

		// observers

		key_compare key_comp(void) const
		{
			return this->_compare;
		}

		value_compare value_comp(void) const
		{
			return value_compare(this->_compare);
		}

		// operations

		iterator find(const key_type &k)
		{
			ft::RedBlackTree<value_type> *key_node;

			key_node = ft::tree_search_node<value_type, value_compare>(this->_root, ft::make_pair(k, mapped_type()), value_compare(this->_compare));
			if (key_node)
				return iterator(key_node);
			return this->end();
		}

		const_iterator find(const key_type &k) const
		{
			ft::RedBlackTree<value_type> *key_node;

			key_node = ft::tree_search_node<value_type, value_compare>(this->_root, ft::make_pair(k, mapped_type()), value_compare(this->_compare));
			if (key_node)
				return const_iterator(key_node);
			return this->end();
		}

		size_type count(const key_type &k) const
		{
			if (ft::tree_search_node<value_type, value_compare>(this->_root, ft::make_pair(k, mapped_type()), value_compare(this->_compare)))
				return (1);
			return (0);
		}

		iterator lower_bound(const key_type &k)
		{
			ft::RedBlackTree<value_type> *end_node = ft::tree_end(this->_root);
			ft::RedBlackTree<value_type> *node = ft::tree_begin(this->_root);
			value_type boundary_pair = ft::make_pair(k, mapped_type());

			while (node != end_node)
			{
				if (this->value_comp()(*node->_data, boundary_pair))
					node = ft::tree_next(node);
				else
					return iterator(node);
			}
			return (iterator(end_node));
		}

		const_iterator lower_bound(const key_type &k) const
		{
			ft::RedBlackTree<value_type> *end_node = ft::tree_end(this->_root);
			ft::RedBlackTree<value_type> *node = ft::tree_begin(this->_root);
			value_type boundary_pair = ft::make_pair(k, mapped_type());

			while (node != end_node)
			{
				if (this->value_comp()(*node->_data, boundary_pair))
					node = ft::tree_next(node);
				else
					return const_iterator(node);
			}
			return (const_iterator(end_node));
		}

		iterator upper_bound(const key_type &k)
		{
			ft::RedBlackTree<value_type> *end_node = ft::tree_end(this->_root);
			ft::RedBlackTree<value_type> *node = ft::tree_begin(this->_root);
			value_type boundary_pair = ft::make_pair(k, mapped_type());

			while (node != end_node)
			{
				if (this->value_comp()(boundary_pair, *node->_data))
					return iterator(node);
				else
					node = ft::tree_next(node);
			}
			return (iterator(end_node));
		}

		const_iterator upper_bound(const key_type &k) const
		{
			ft::RedBlackTree<value_type> *end_node = ft::tree_end(this->_root);
			ft::RedBlackTree<value_type> *node = ft::tree_begin(this->_root);
			value_type boundary_pair = ft::make_pair(k, mapped_type());

			while (node != end_node)
			{
				if (this->value_comp()(boundary_pair, *node->_data))
					return const_iterator(node);
				else
					node = ft::tree_next(node);
			}
			return (const_iterator(end_node));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
		}

		ft::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
		}

		// allocators

		allocator_type get_allocator(void) const
		{
			return this->_allocator;
		}
	};

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &lhs, map<Key, T, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return rhs < lhs;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

} // namespace ft

#endif
