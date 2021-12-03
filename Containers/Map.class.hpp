#ifndef MAP_CLASS_HPP
#define MAP_CLASS_HPP

#include <iostream>
#include <map>

//template < class Key,                                 // map::key_type\
           class T,                                       // map::mapped_type\
           class Compare = less<Key>,                     // map::key_compare\
           class Alloc = allocator<pair<const Key,T> >    // map::allocator_type\
           > class map

namespace ft
{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> >    // map::allocator_type
           > class map
    {

    };
}

#endif