#ifndef RERVSERITERATOR_CLASS_HPP
#define RERVSERITERATOR_CLASS_HPP

#include "IteratorTraits.hpp"

template <typename Iter>
class ReverseIterator
{
public:
    // typedef Iter iterator_type;
    // typedef typename iterator_traits<Iter>::iterator_category iterator_category;
    // typedef typename iterator_traits<Iter>::value_type value_type;
    // typedef typename iterator_traits<Iter>::difference_type difference_type;
    // typedef typename iterator_traits<Iter>::pointer pointer;
    // typedef typename iterator_traits<Iter>::reference reference;

private:
    pointer m_ptr;
public:
    ReverseIterator(/* args */);
    ReverseIterator(Iter *ptr);
    ReverseIterator& operator++();
    ReverseIterator& operator--();
    ReverseIterator operator++(int);
    ReverseIterator operator--(int);
    ReverseIterator& operator+=(int);
    ReverseIterator& operator-=(int);
    ReverseIterator operator+(int) const;;
    ReverseIterator operator-(int) const;;
    ~ReverseIterator();
};


#endif