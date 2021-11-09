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
    typedef typename iterator_traits<Iter>::difference_type difference_type;
    typedef typename iterator_traits<Iter>::reference reference;
    typedef typename iterator_traits<Iter>::pointer pointer;

public:
    Reverse_iterator() : m_current(), iterator() {};
    Reverse_iterator(iterator_type x) : m_current(x) {};
    Reverse_iterator(const Reverse_iterator<Iter>& other) {this->m_current = other->m_current; };
    Reverse_iterator& operator=(const Reverse_iterator<Iter>& other) 
    {
        if(this != other)
        this->m_current = other.base(); 
        return (*this); 
    };
    iterator_type base() const {return this->m_current};
    reference operator*() const
    {
        iterator_type tmp = m_current;
        return *(--tmp);
    };
    pointer operator->() const
    {
        return &(operator*());
    };
    reference operator[](difference_type n) const;
    Reverse_iterator& operator++(); 
    Reverse_iterator& operator--(); 
    Reverse_iterator operator++(int n); 
    Reverse_iterator operator--(int n);
    Reverse_iterator operator+(difference_type n) const;
    Reverse_iterator operator-(difference_type n) const;
    Reverse_iterator& operator+=(difference_type n);
    Reverse_iterator& operator-=(difference_type n);

protected:
    iterator_type m_current;
};

#endif