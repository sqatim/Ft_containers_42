#ifndef MAP_CLASS_HPP
#define MAP_CLASS_HPP

#include <iostream>
#include <map>

#include "../NeededTemplates/pair.hpp"
// #include "../Iterators/NormalIterator.class.hpp"
#include "../Iterators/ReverseIterator.class.hpp"
#include "../RedBlackTree/RedBlackTree.class.hpp"

//template < class Key,                                 // map::key_type\
           class T,                                       // map::mapped_type\
           class Compare = less<Key>,                     // map::key_compare\
           class Alloc = allocator<pair<const Key,T> >    // map::allocator_type\
           > class map

namespace ft
{
    template <class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
        result_type operator()(const first_argument_type &a, const second_argument_type &b)
        {
            return a == b;
        };
    };

    template <class Arg1, class Arg2>
    struct value_comp : public binary_function<Arg1, Arg2, bool>
    {
    };

    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
    class map
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef NodeBase<value_type> Node;
        typedef value_comp<key_type, key_type> value_compare;
        // khassani shi wahda hna (value_compare)
        typedef typename Alloc::template rebind<Node>::other allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef RedBlackTreeIterator<pointer, value_type> iterator;
        typedef RedBlackTreeIterator<const_pointer, value_type> const_iterator;
        typedef Reverse_iterator<iterator> reverse_iterator;
        typedef Reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;

    protected:
        Node *m_root;
        key_compare m_compare;
        RedBlackTree<key_type, mapped_type> m_tree;
        size_type m_size;
        allocator_type m_allocator;

    public:
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type()) : m_root(NULL){
                                                                           // m_allocator
                                                                       };
        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : m_tree()
        {
            difference_type difference;

            difference = last - first;
            std::cout << difference << std::endl;
            for (difference_type i = 0; i < difference; i++)
            {
            }
        };

        iterator begin()
        {
            Node *tmp;

            tmp = m_root;
            while (tmp->m_left)
            {
                std::cout << "************************************" << std::endl;
                tmp = tmp->m_left;
            }
            return (tmp);
        };
        const_iterator begin() const
        {
            Node *tmp;

            tmp = m_root;
            while (tmp->left)
                tmp = tmp->left;
            return (tmp);
        };
        // std::pair<iterator, bool> insert(const value_type &value)
        // {
        //     m_tree.insert(value);

        // };
        int insert(const value_type &value)
        {
            int k = 0;
            k = m_tree.insert(value);
            m_root = m_tree.getRoot();
            return k;
        };
    };

}

#endif