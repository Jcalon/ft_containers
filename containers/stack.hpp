#pragma once

#include "vector.hpp"
#include <vector>

namespace ft
{
template<class T, typename Container = std::vector<T> >
class stack
{
    public : //types
        typedef Container container_type;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::size_type size_type;
		//methods
        explicit stack(const Container& c = Container()) : c(c) {}
        bool empty() const { return c.empty(); }
        size_type size() const { return c.size(); }
        value_type& top() { return c.back(); }
        const value_type& top() { return c.back(); }
        void push(const value_type& v) { c.push_back(v); }
        void pop() { c.pop_back(); }
		//friends
        template <class T1, class C1>
        friend bool operator==(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
        
        template <class T1, class C1>
        friend bool operator<(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

    protected :
        container_type c;
};

//external overloads

template <class T, class Container>
bool operator==(const stack <T, Container>& lhs, const stack <T, Container>& rhs)
{
    return lhs.c == rhs.c;
}

template <class T, class Container>
bool operator!=(const stack <T, Container>& lhs, const stack <T, Container>& rhs)
{
    return !(lhs == rhs);
}

template <class T, class Container>
bool operator<(const stack <T, Container>& lhs, const stack <T, Container>& rhs)
{
    return lhs.c < rhs.c;
}

template <class T, class Container>
bool operator>(const stack <T, Container>& lhs, const stack <T, Container>& rhs)
{
    return lhs > rhs;
}

template <class T, class Container>
bool operator<=(const stack <T, Container>& lhs, const stack <T, Container>& rhs)
{
    return !(lhs > rhs);
}

template <class T, class Container>
bool operator>=(const stack <T, Container>& lhs, const stack <T, Container>& rhs)
{
    return !(lhs < rhs);
}

}