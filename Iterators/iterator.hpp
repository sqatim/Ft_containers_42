#ifndef ITRATOR_HPP
#define ITRATOR_HPP

#include <iostream>

struct input_iterator_tag
{
};
struct output_iterator_tag
{
};
struct forward_iterator_tag : public input_iterator_tag
{
};
struct bidirectional_iterator_tag : public forward_iterator_tag
{
};
struct random_iterator_tag : public bidirectional_iterator_tag
{
};
struct contiguous_iterator_tag : public random_iterator_tag
{
};

template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T *, class Reference = T &>
struct Iterator
{
public:
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
    typedef Category iterator_category;
};

template <class Iterator>
struct Iterator_traits
{
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
    // iterator_traits() { std::cout << "iterator_traits1" << std::endl; };
};

template <class T>
struct Iterator_traits<T *>
{
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef std::random_access_iterator_tag iterator_category;
};

template <class T>
struct Iterator_traits<const T *>
{
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef const T *pointer;
    typedef const T &reference;
    typedef std::random_access_iterator_tag iterator_category;
};

#endif