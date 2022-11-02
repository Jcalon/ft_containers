/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:15:35 by jcalon            #+#    #+#             */
/*   Updated: 2022/11/02 13:15:35 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

template<class T, class Container = ft::vector<T> >
class stack
{
    public : //types
        typedef Container container_type;
        typedef typename container_type::value_type 	value_type;
        typedef typename container_type::size_type		size_type;

    protected :
        container_type c;
	
	public: //methods
        explicit stack(const Container &c = Container()) : c(c) {}
        
		bool empty(void) const
		{
			return this->c.empty();
		}

        size_type size(void) const
		{
			return this->c.size();
		}

        value_type &top(void)
		{
			return this->c.back();
		}

        const value_type &top(void) const
		{
			return this->c.back();
		}

        void push(const value_type &v)
		{
			this->c.push_back(v);
		}

        void pop(void)
		{
			this->c.pop_back();
		}

		//friends
        template <class T1, class C1>
        friend bool operator==(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs);
        
        template <class T1, class C1>
        friend bool operator<(const stack<T1, C1> &lhs, const stack<T1, C1> &rhs);

};

//external overloads

template <class T, class Container>
bool operator==(const stack <T, Container> &lhs, const stack <T, Container> &rhs)
{
    return lhs.c == rhs.c;
}

template <class T, class Container>
bool operator!=(const stack <T, Container> &lhs, const stack <T, Container> &rhs)
{
    return !(lhs == rhs);
}

template <class T, class Container>
bool operator<(const stack <T, Container> &lhs, const stack <T, Container> &rhs)
{
    return lhs.c < rhs.c;
}

template <class T, class Container>
bool operator>(const stack <T, Container> &lhs, const stack <T, Container> &rhs)
{
    return rhs < lhs;
}

template <class T, class Container>
bool operator<=(const stack <T, Container> &lhs, const stack <T, Container> &rhs)
{
    return !(lhs > rhs);
}

template <class T, class Container>
bool operator>=(const stack <T, Container> &lhs, const stack <T, Container> &rhs)
{
    return !(lhs < rhs);
}

} // namespace ft

#endif
