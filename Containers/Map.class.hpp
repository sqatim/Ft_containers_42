#ifndef MAP_CLASS_HPP
#define MAP_CLASS_HPP

#include <iostream>
#include <map>

#include "../NeededTemplates/pair.hpp"
#include "../Iterators/NormalIterator.class.hpp"
#include "../Iterators/ReverseIterator.class.hpp"

//template < class Key,                                 // map::key_type\
           class T,                                       // map::mapped_type\
           class Compare = less<Key>,                     // map::key_compare\
           class Alloc = allocator<pair<const Key,T> >    // map::allocator_type\
           > class map

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
    class map
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef pair < const Key_type, mapped_type >> value_type;
        typedef Compare key_compare;
        // khassani shi wahda hna (value_compare)
        typedef Alloc allocator_type;
        typedef allocator_type::reference reference;
        typedef allocator_type::const_reference const_reference;
        typedef allocator_type::pointer pointer;
        typedef allocator_type::const_pointer const_pointer;
        typedef Normal_iterator<pointer> iterator;
        typedef Normal_iterator<const_pointer> const_iterator;
        typedef Reverse_iterator<pointer> reverse_iterator;
        typedef Reverse_iterator<const_pointer> const_reverse_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;

    protected:
        
    };
}

#endif