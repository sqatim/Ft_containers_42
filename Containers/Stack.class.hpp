#ifndef STACK_CLASS_HPP
#define STACK_CLASS_HPP

#include "Vector.class.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
    public:
        typedef T value_type;
        typedef Container container_type;
        typedef size_t size_type;

    private:
        container_type m_container;

    public:
        explicit stack(const container_type &ctnr = container_type()) : m_container(ctnr)
        {
        }
        bool empty() const
        {
            return (m_container.empty());
        }
        size_type size() const
        {
            return m_container.size();
        }
        value_type &top()
        {
            return (m_container.back());
        };
        const value_type &top() const
        {
            return (m_container.back());
        };
        void push(const value_type &val)
        {
            m_container.push_back(val);
        }
        void pop()
        {
            m_container.pop_back();
        };
        template <class Type, class V>
        friend bool operator==(const stack<Type, V> &lhs, const stack<Type, V> &rhs);
        template <class Type, class V>
        friend bool operator!=(const stack<Type, V> &lhs, const stack<Type, V> &rhs);
        template <class Type, class V>
        friend bool operator>=(const stack<Type, V> &lhs, const stack<Type, V> &rhs);
        template <class Type, class V>
        friend bool operator>(const stack<Type, V> &lhs, const stack<Type, V> &rhs);
        template <class Type, class V>
        friend bool operator<=(const stack<Type, V> &lhs, const stack<Type, V> &rhs);
        template <class Type, class V>
        friend bool operator<(const stack<Type, V> &lhs, const stack<Type, V> &rhs);
    };

    template <class T, class Container>
    bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (lhs.m_container == rhs.m_container);
    };

    template <class T, class Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (lhs.m_container != rhs.m_container);
    };

    template <class T, class Container>
    bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (lhs.m_container < rhs.m_container);
    };

    template <class T, class Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (lhs.m_container <= rhs.m_container);
    };

    template <class T, class Container>
    bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (lhs.m_container > rhs.m_container);
    };

    template <class T, class Container>
    bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (lhs.m_container >= rhs.m_container);
    };

}

#endif