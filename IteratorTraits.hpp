#ifndef ITERATORTRAITS_HPP
#define ITERATORTRAITS_HPP

#include <iostram>

template <class Iter>
class iterator_traits
{
};

template <class T>
struct iterator_traits<T *>
{
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    // typedef T::iterator_category iterator_category;
};

#endif