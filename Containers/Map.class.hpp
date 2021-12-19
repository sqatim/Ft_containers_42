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
        typedef ft::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef NodeBase<value_type> Node;
        // khassani shi wahda hna (value_compare)
        typedef typename Alloc::template rebind<Node>::other allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef RedBlackTreeIterator<pointer, value_type> iterator;
        typedef RedBlackTreeIterator<pointer, const value_type> const_iterator;
        typedef Reverse_iterator<iterator> reverse_iterator;
        typedef Reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef RedBlackTree<key_type, mapped_type, key_compare, allocator_type> RDTree;

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
        size_type m_size;
        allocator_type m_allocator;
        RDTree m_tree;

    public:
        // Constructers
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type()) : m_root(NULL), m_compare(comp), m_size(0), m_allocator(alloc), m_tree(RDTree(m_allocator)){};

        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : m_root(NULL), m_compare(comp), m_size(0), m_allocator(alloc)
        {
            for (; first != last; first++)
                m_tree.insert(*first, m_compare, m_allocator);
            m_root = m_tree.getRoot();
        };

        map(const map &x)
        {
            *this = x;
            return;
        };

        map &operator=(const map &x)
        {
            if(this != &x)
            {
                if (m_size > 0)
                    deleteNodes(m_tree.getEnd());
                m_tree.reallocation(m_tree.getEnd(), x.m_tree.getEnd(), NULL);
            }
            return (*this);
        }
        // iterators;

        iterator begin()
        {
            Node *tmp;

            tmp = m_root;
            while (tmp->m_left)
                tmp = tmp->m_left;
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
        const_iterator end() const
        {
            const Node *tmp = m_tree.getEnd();
            return tmp;
        };

        reverse_iterator rbegin()
        {
            Node *tmp;

            tmp = m_root;
            while (tmp->m_right)
                tmp = tmp->m_right;
            return (tmp);
        };
        const_reverse_iterator rbegin() const
        {
            Node *tmp;

            tmp = m_root;
            while (tmp->m_right)
                tmp = tmp->m_right;
            return (tmp);
        };
        reverse_iterator rend()
        {
            Node *tmp = m_tree.getEnd();
            return tmp;
        };
        const_reverse_iterator rend() const
        {
            const Node *tmp = m_tree.getEnd();
            return tmp;
        };

        // Capacity
        bool empty() const
        {
            if (m_size == 0)
                return true;
            return false;
        };

        size_type size() const
        {
            return m_size;
        }

        size_type max_size() const
        {
            return m_allocator.max_size();
        }

        // Element Access
        mapped_type &operator[](const key_type &k)
        {
            iterator it;

            it = this->find(k);
            if (it != this->end())
                return (it->second);
            it = this->insert(it, ft::make_pair(k, mapped_type()));
            return (it->second);
        }

        // Modifiers

        ft::pair<Node *, bool> insert(const value_type &value)
        {
            ft::pair<Node *, bool> k;
            k = m_tree.insert(value, m_compare, m_allocator);
            m_root = m_tree.getRoot();
            m_size = m_tree.getSize();
            return k;
        };

        iterator insert(iterator position, const value_type &val)
        {
            ft::pair<Node *, bool> result;
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

        iterator find(const key_type &k)
        {
            Node *ptr = m_root;
            iterator it;
            // std::cout << GREEN << m_size << DEFAULT << std::endl;
            while (ptr)
            {
                // std::cout << "i am here" << std::endl;
                // std::cout << YELLOW << ptr->m_pair.first << DEFAULT << std::endl;
                // std::cout << "first: " << RED << ptr->m_pair.first << "\t second: " << YELLOW << ptr->m_pair.second << std::endl;
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
            if (this->find(k) != this->end())
                return 1;
            return 0;
        }

        iterator lower_bound(const key_type &k) // k >=
        {
            Node *ptr = m_root;
            iterator it;
            while (ptr && m_compare(ptr->m_pair.first, k))
            {
                if (m_compare(ptr->m_pair.first, k))
                    ptr = ptr->m_right;
                else if (m_compare(k, ptr->m_pair.first))
                    ptr = ptr->m_left;
            }
            if (ptr != NULL)
            {
                it = ptr;
                return (it);
            }
            return this->end();
        };

        const_iterator lower_bound(const key_type &k) const
        {
            Node *ptr = m_root;
            const_iterator it;
            while (ptr && m_compare(ptr->m_pair.first, k))
            {
                if (m_compare(ptr->m_pair.first, k))
                    ptr = ptr->m_right;
                else if (m_compare(k, ptr->m_pair.first))
                    ptr = ptr->m_left;
            }
            if (ptr != NULL)
            {
                it = ptr;
                return (it);
            }
            return this->end();
        };

        iterator upper_bound(const key_type &k) // k <
        {
            Node *ptr = m_root;
            iterator it;
            while (ptr && !m_compare(k, ptr->m_pair.first))
            {
                if (m_compare(ptr->m_pair.first, k) || ptr->m_pair.first == k)
                    ptr = ptr->m_right;
                else if (m_compare(k, ptr->m_pair.first))
                    ptr = ptr->m_left;
            }
            if (ptr != NULL)
            {
                it = ptr;
                return (it);
            }
            return this->end();
        };
        const_iterator upper_bound(const key_type &k) const
        {
            Node *ptr = m_root;
            const_iterator it;
            while (ptr && !m_compare(k, ptr->m_pair.first))
            {
                if (m_compare(ptr->m_pair.first, k) || ptr->m_pair.first == k)
                    ptr = ptr->m_right;
                else if (m_compare(k, ptr->m_pair.first))
                    ptr = ptr->m_left;
            }
            if (ptr != NULL)
            {
                it = ptr;
                return (it);
            }
            return this->end();
        };

        ft::pair<iterator, iterator> equal_range(const key_type &k)
        {
            ft::pair<iterator, iterator> pair;

            pair = ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
            return pair;
        };
        ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            ft::pair<const_iterator, const_iterator> pair;

            pair = ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
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

        ~map()
        {
            if (m_size > 0)
                deleteNodes(m_tree.getEnd());
        }

    private:
        void deleteNodes(Node *node)
        {
            if (node != NULL)
            {
                deleteNodes(node->m_left);
                deleteNodes(node->m_right);
                m_allocator.deallocate(node, 1);
            }
        }
    };

}

#endif