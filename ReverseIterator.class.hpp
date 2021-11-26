#ifndef REVERSEITERATOR_HPP
#define REVERSEITERATOR_HPP

#include "iterator.hpp"

template <class Iter>
class Reverse_iterator : public iterator<
                             typename iterator_traits<Iter>::iterator_category,
                             typename iterator_traits<Iter>::value_type,
                             typename iterator_traits<Iter>::difference_type,
                             typename iterator_traits<Iter>::pointer,
                             typename iterator_traits<Iter>::reference>

{

public:
    typedef Iter iterator_type;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
    typedef typename iterator_traits<iterator_type>::value_type value_type;
    typedef typename iterator_traits<iterator_type>::difference_type difference_type;
    typedef typename iterator_traits<iterator_type>::reference reference;
    typedef typename iterator_traits<iterator_type>::pointer pointer;

protected:
    iterator_type m_current;

public:
    Reverse_iterator() : m_current(){};
    Reverse_iterator(iterator_type x) : m_current(x){};
    Reverse_iterator(const Reverse_iterator<Iter> &other) { this->m_current = other.m_current; };
    Reverse_iterator &operator=(const Reverse_iterator<Iter> &other)
    {
        if (this != &other)
            this->m_current = other.base();
        return (*this);
    };
    iterator_type base() const { return this->m_current; };
    reference operator*() const
    {
        iterator_type tmp = m_current;
        return *(--tmp);
    };
    pointer operator->() const
    {
        return &(operator*());
    };
    reference operator[](difference_type n) const
    {
        return this->base()[n - 1];
    };
    Reverse_iterator &operator++()
    {
        --m_current;
        return *this;
    };
    Reverse_iterator &operator--()
    {
        ++m_current;
        return *this;
    };
    Reverse_iterator operator++(int)
    {
        Reverse_iterator copy = *this;
        ++(*this);
        return copy;
    };
    Reverse_iterator operator--(int)
    {
        Reverse_iterator copy = *this;
        --(*this);
        return copy;
    };
    Reverse_iterator operator-(difference_type n) const
    {
        return Reverse_iterator(this->base() + n);
    };
    Reverse_iterator operator+(difference_type n) const
    {
        return Reverse_iterator(this->base() - n);
    };
    Reverse_iterator &operator+=(difference_type n)
    {
        m_current = this->base() - n;
        return *this;
    };
    Reverse_iterator &operator-=(difference_type n)
    {
        m_current = this->base() + n;
        return *this;
    };
};

template <class Iterator>
Reverse_iterator<Iterator> operator+(typename Reverse_iterator<Iterator>::difference_type n, const Reverse_iterator<Iterator> &rev_it)
{
    rev_it.m_current = rev_it.base() - n;
    return *rev_it;
}

template <class Iterator>
Reverse_iterator<Iterator> operator-(typename Reverse_iterator<Iterator>::difference_type n, const Reverse_iterator<Iterator> &rev_it)
{
    rev_it.m_current = rev_it.base() + n;
    return *rev_it;
}

template <class Iterator>
bool operator==(const Reverse_iterator<Iterator> &lhs,
                const Reverse_iterator<Iterator> &rhs)
{
    return lhs.base() == rhs.base();
}

template <class Iterator>
bool operator!=(const Reverse_iterator<Iterator> &lhs,
                const Reverse_iterator<Iterator> &rhs)
{
    return lhs.base() != rhs.base();
}

template <class Iterator>
bool operator<(const Reverse_iterator<Iterator> &lhs,
               const Reverse_iterator<Iterator> &rhs)
{
    return lhs.base() < rhs.base();
}

template <class Iterator>
bool operator<=(const Reverse_iterator<Iterator> &lhs,
                const Reverse_iterator<Iterator> &rhs)
{
    return lhs.base() <= rhs.base();
}

template <class Iterator>
bool operator>(const Reverse_iterator<Iterator> &lhs,
               const Reverse_iterator<Iterator> &rhs)
{
    return lhs.base() > rhs.base();
}

template <class Iterator>
bool operator>=(const Reverse_iterator<Iterator> &lhs,
                const Reverse_iterator<Iterator> &rhs)
{
    return lhs.base() >= rhs.base();
}
#endif