#ifndef NORMALITERATOR_CLASS_HPP
#define NORMALITERATOR_CLASS_HPP

#include "iterator.hpp"

template <class Iter>
class Normal_iterator
{
public:
    typedef Iter iterator_type;
    typedef typename std::random_access_iterator_tag iterator_category;
    typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
    typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
    typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
    typedef typename ft::iterator_traits<iterator_type>::reference reference;

protected:
    iterator_type m_current;

public:
    Normal_iterator() : m_current(){};
    Normal_iterator(iterator_type x) : m_current(x) {};
    template<class T>
    Normal_iterator(const Normal_iterator<T> &other) : m_current(other.base()){};
    Normal_iterator &operator=(const Normal_iterator<Iter> &other)
    {
        if (this != &other)
            this->m_current = other.m_current;
        return (*this);
    };
    iterator_type base() const { return this->m_current; };
    reference operator*() const
    {
        return (*m_current);
    };
    pointer operator->() const
    {
        return &(operator*());
    };
    reference operator[](difference_type n) const
    {
        return this->m_current[n];
    };
    Normal_iterator &operator++()
    {
        ++m_current;
        return *this;
    };
    Normal_iterator &operator--()
    {
        --m_current;
        return *this;
    };
    Normal_iterator operator++(int)
    {
        Normal_iterator copy = *this;
        ++(*this);
        return copy;
    };
    Normal_iterator operator--(int)
    {
        Normal_iterator copy = *this;
        --(*this);
        return copy;
    };
    Normal_iterator operator-(difference_type n) const
    {
        return Normal_iterator(this->m_current - n);
    };
    Normal_iterator operator+(difference_type n) const
    {
        return Normal_iterator(this->m_current + n);
    };
    Normal_iterator &operator+=(difference_type n)
    {
        m_current = this->m_current + n;
        return *this;
    };
    Normal_iterator &operator-=(difference_type n)
    {
        m_current = this->m_current - n;
        return *this;
    };
};

template <class Iterator>
Normal_iterator<Iterator> operator+(typename Normal_iterator<Iterator>::difference_type n, const Normal_iterator<Iterator> &rev_it)
{
    rev_it.m_current = rev_it.base() + n;
    return *rev_it;
}

template <class Iterator>
Normal_iterator<Iterator> operator-(typename Normal_iterator<Iterator>::difference_type n, const Normal_iterator<Iterator> &rev_it)
{
    rev_it.m_current = rev_it.base() - n;
    return *rev_it;
}

template <class Iterator>
typename Normal_iterator<Iterator>::difference_type operator-(const Normal_iterator<Iterator> &lhs, const Normal_iterator<Iterator> &rhs)
{
    return lhs.base() - rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator==(const Normal_iterator<Iterator1> &lhs,
                const Normal_iterator<Iterator2> &rhs)
{
    return lhs.base() == rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator!=(const Normal_iterator<Iterator1> &lhs,
                const Normal_iterator<Iterator2> &rhs)
{
    return lhs.base() != rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<(const Normal_iterator<Iterator1> &lhs,
               const Normal_iterator<Iterator2> &rhs)
{
    return lhs.base() < rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<=(const Normal_iterator<Iterator1> &lhs,
                const Normal_iterator<Iterator2> &rhs)
{
    return lhs.base() <= rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>(const Normal_iterator<Iterator1> &lhs,
               const Normal_iterator<Iterator2> &rhs)
{
    return lhs.base() > rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>=(const Normal_iterator<Iterator1> &lhs,
                const Normal_iterator<Iterator2> &rhs)
{
    return lhs.base() >= rhs.base();
}

#endif