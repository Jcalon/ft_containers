#ifndef map_hpp
#define map_hpp

#include <iostream>
#include "utility.hpp"
#include "iterator.hpp"

namespace ft
{

template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T>> >
class map
{
	public:
		typedef Key 																key_type;
		typedef T																	mapped_type;
		typedef ft::pair<const Key, T>								value_type;
		typedef Compare																key_compare;
		typedef Alloc																allocator_type;
		typedef typename Alloc::reference									reference;
		typedef typename Alloc::const_reference							const_reference;
		typedef typename Alloc::pointer												pointer;
		typedef typename Alloc::const_pointer										const_pointer;
		typedef ft::map_iterator<value_type>										iterator;
		typedef ft::map_iterator<value_type>										const_iterator;
		typedef ft::reverse_iterator<iterator>										reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
		typedef std::ptrdiff_t														difference_type;
		typedef std::size_t															size_type;

		class value_compare
		{
			friend class map;
			protected :
				key_compare comp;
				value_compare(key_compare c) : comp(c) {}
			public:
				bool operator()(const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
		};

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
