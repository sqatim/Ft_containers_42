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
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
    class map
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef NodeBase<value_type> Node;
        // khassani shi wahda hna (value_compare)
        typedef typename Alloc::template rebind<Node>::other allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef RedBlackTreeIterator<pointer> iterator;
        typedef RedBlackTreeIterator<const_pointer> const_iterator;
        typedef Reverse_iterator<iterator> reverse_iterator;
        typedef Reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;

        struct value_compare
        {
        protected:
            Compare m_comp;

        public:
            value_compare(Compare c) : m_comp(c) {}
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            result_type operator()(const first_argument_type &x, const second_argument_type &y) const
            {
                return m_comp(x.first, y.first);
            }
        };

    protected:
        Node *m_root;
        key_compare m_compare;
        RedBlackTree<key_type, mapped_type, key_compare, allocator_type> m_tree;
        size_type m_size;
        allocator_type m_allocator;

    public:
        // Constructers
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type()) : m_root(NULL), m_compare(comp), m_size(0), m_allocator(alloc){};
        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : m_root(NULL), m_compare(comp), m_size(0), m_allocator(alloc)
        {
            for (; first != last; first++)
            {
                m_tree.insert(*first, m_compare, m_allocator);
            }
            m_root = m_tree.getRoot();
        };

        // iterators;

        iterator begin()
        {
            Node *tmp;

            tmp = m_root;
            while (tmp->m_left)
            {
                // std::cout << "************************************" << std::endl;
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

        iterator end()
        {
            Node *tmp = m_tree.getEnd();
            return tmp;
        };
        const_iterator end() const;

        // Element Access
        mapped_type &operator[](const key_type &k)
        {
        }

        // Modifiers

        std::pair<Node *, bool> insert(const value_type &value)
        {
            std::pair<Node *, bool> k;
            k = m_tree.insert(value, m_compare, m_allocator);
            m_root = m_tree.getRoot();
            m_size = m_tree.getSize();
            return k;
        };

        iterator insert(iterator position, const value_type &val)
        {
            std::pair<Node *, bool> result;
            result = m_tree.insert(val, m_compare, m_allocator);
            m_root = m_tree.getRoot();
            m_size = m_tree.getSize();
            return result.first;
        };
        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            // std::cout << "sdasdsadsadsasda" << std::endl;
            for (; first != last; first++)
            {
                m_tree.insert(*first, m_compare, m_allocator);
                // std::cout << "first: "<< RED << first->first << "\t second: "<< YELLOW << first->second << std::endl;
            }
            m_root = m_tree.getRoot();
            m_size = m_tree.getSize();
        }

        // Observers:
        key_compare key_comp() const
        {
            return (m_compare);
        }

        value_compare value_comp() const
        {
            value_compare compare(key_comp());
            return compare;
        };

        // Operations:
        // iterator find(const key_type &k)
        // {
        //     iterator it = this->begin();
        //     iterator end = this->end();
        //     for (; it != end; it++)
        //     {
        //         if (it->first == k)
        //             return it;
        //     }
        //     return it;
        // }
        iterator find(const key_type &k)
        {
            Node *ptr = m_root;
            iterator it;
            // std::cout << GREEN << m_size << DEFAULT << std::endl;
            while (ptr)
            {
                // std::cout << "i am here" << std::endl;
                // std::cout << YELLOW << ptr->m_pair.first << DEFAULT << std::endl;
                std::cout << "first: " << RED << ptr->m_pair.first << "\t second: " << YELLOW << ptr->m_pair.second << std::endl;
                if (m_compare(ptr->m_pair.first, k))
                    ptr = ptr->m_right;
                else if (m_compare(k, ptr->m_pair.first))
                    ptr = ptr->m_left;
                else
                {
                    it = ptr;
                    return (it);
                }
            }
            return this->end();
        }

        const_iterator find(const key_type &k) const
        {
            Node *ptr = m_root;
            const_iterator it;
            while (ptr)
            {
                if (m_compare(ptr->m_pair.first, k))
                    ptr = ptr->m_right;
                else if (m_compare(k, ptr->m_pair.first))
                    ptr = ptr->m_left;
                else
                {
                    it = ptr;
                    return (it);
                }
            }
            return this->end();
        }

        size_type count(const key_type &k) const
        {
            iterator it = this->begin();
            iterator end = this->end();

            if (this->find(k) != this->end())
                return 1;
            return 0;
        }

        iterator lower_bound(const key_type &k) // <= k
        {
            iterator it = this->begin();
            iterator end = this->end();

            for (; it != end; it++)
            {
                if (!m_compare(it->first, k)) // m_compare return true if it->first < k
                    return it;
            }
            return it;
        };
        const_iterator lower_bound(const key_type &k) const
        {
            const_iterator it = this->begin();
            const_iterator end = this->end();

            for (; it != end; it++)
            {
                if (!m_compare(it->first, k))
                    return it;
            }
            return it;
        };

        iterator upper_bound(const key_type &k) // > k
        {
            iterator it = this->begin();
            iterator end = this->end();

            for (; it != end; it++)
            {
                if (m_compare(k, it->first)) //  m_compare return true if k < it->first
                    return it;
            }
            return it;
        };
        const_iterator upper_bound(const key_type &k) const
        {
            const_iterator it = this->begin();
            const_iterator end = this->end();

            for (; it != end; it++)
            {
                if (m_compare(k, it->first))
                    return it;
            }
            return it;
        };

        std::pair<iterator, iterator> equal_range(const key_type &k)
        {
            std::pair<iterator, iterator> pair;

            pair = std::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
            return pair;
        };
        std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            std::pair<const_iterator, const_iterator> pair;

            pair = std::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
            return pair;
        };

        // Allocator:
        allocator_type get_allocator() const
        {
            return (m_allocator);
        };

        void print()
        {
            m_tree.print(m_root);
        }
    };

}

#endif