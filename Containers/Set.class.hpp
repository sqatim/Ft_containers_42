#ifndef SET_CLASS_HPP
#define SET_CLASS_HPP

#include <iostream>

#include "../NeededTemplates/pair.hpp"
#include "Vector.class.hpp"
#include "../Iterators/ReverseIterator.class.hpp"
#include "../RedBlackTree/RedBlackTreeSet.class.hpp"

namespace ft
{
    template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
    class set
    {
    public:
        typedef T key_type;
        typedef T value_type;
        typedef Compare key_compare;
        typedef Compare value_compare;
        typedef NodeBaseSet<key_type> Node;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef RedBlackTreeIteratorSet<Node *, key_type> iterator;
        typedef RedBlackTreeIteratorSet<Node *, const key_type> const_iterator;
        typedef Reverse_iterator<iterator> reverse_iterator;
        typedef Reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef RedBlackTreeSet<key_type, value_type, key_compare, allocator_type> RDTree;
    protected:
        Node *m_root;
        key_compare m_compare;
        size_type m_size;
        allocator_type m_allocator;
        RDTree m_tree;

    public:
        // Constructers
        explicit set(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type()) : m_root(NULL), m_compare(comp), m_size(0), m_allocator(alloc), m_tree(RDTree(m_compare)){};

        template <class InputIterator>
        set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : m_root(NULL), m_compare(comp), m_size(0), m_allocator(alloc)
        {
            for (; first != last; first++)
                m_tree.insert(*first, m_compare);
            m_root = m_tree.getRoot();
            m_size = m_tree.getSize();
        };

        set(const set &x)
        {
            *this = x;
            return;
        };

        set &operator=(const set &x)
        {
            if (this != &x)
            {
                this->m_tree = x.getTree();
                m_root = this->m_tree.getRoot();
                m_size = this->m_tree.getSize();
            }
            return (*this);
        }
        // iterators;

        iterator begin()
        {
            Node *tmp;

            tmp = m_root;
            while (tmp && tmp->m_left)
                tmp = tmp->m_left;
            iterator it(tmp);
            return (it);
        };
        const_iterator begin() const
        {
            const Node *tmp;

            tmp = m_root;
            while (tmp && tmp->left)
                tmp = tmp->left;
            const_iterator it(tmp);
            return (it);
        };

        iterator end()
        {
            iterator it(m_tree.getEnd());
            return it;
        };
        const_iterator end() const
        {
            const_iterator it = m_tree.getEnd();
            return it;
        };

        reverse_iterator rbegin()
        {
            reverse_iterator it(m_tree.getEnd());
            return (it);
        };

        const_reverse_iterator rbegin() const
        {
            const_reverse_iterator it(m_tree.getEnd());
            return it;
        };
        reverse_iterator rend()
        {
            Node *tmp;

            tmp = m_root;
            while (tmp->m_left)
                tmp = tmp->m_left;
            reverse_iterator it(tmp);
            return (it);
        };
        const_reverse_iterator rend() const
        {

            Node *tmp;
            tmp = m_root;
            while (tmp->m_left)
                tmp = tmp->m_left;
            const_reverse_iterator it(it);
            return (it);
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
            return m_tree.getMaxSize();
        }

        // Modifiers

        ft::pair<Node *, bool> insert(const value_type &value)
        {
            ft::pair<Node *, bool> k;
            k = m_tree.insert(value, m_compare);
            m_root = m_tree.getRoot();
            m_size = m_tree.getSize();
            return k;
        };

        iterator insert(iterator position, const value_type &val)
        {
            position = iterator();
            ft::pair<Node *, bool> result;
            result = m_tree.insert(val, m_compare);
            m_root = m_tree.getRoot();
            m_size = m_tree.getSize();
            return result.first;
        };
        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first != last; first++)
                m_tree.insert(*first, m_compare);
            m_root = m_tree.getRoot();
            m_size = m_tree.getSize();
        }

        void erase(iterator position)
        {
            erase(*position);
        }

        size_type erase(const key_type &k)
        {
            size_type tmp = m_size;
            m_tree.erase(k);
            m_root = m_tree.getRoot();
            m_size = m_tree.getSize();
            if (tmp == m_size)
                return (0);
            return (1);
        }
        void erase(iterator first, iterator last)
        {
            ft::vector<key_type> vect;
            for (; first != last; first++)
                vect.push_back(*first);
            for (size_t i = 0; i < vect.size(); i++)
                erase(vect.at(i));
        }
        void swap(set &x)
        {
            set tmp(*this);
            *this = x;
            x = tmp;
        }

        void clear()
        {
            this->m_tree.~RedBlackTreeSet();
            m_root = NULL;
            m_size = 0;
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
            while (ptr)
            {
                if (m_compare(ptr->m_value, k))
                    ptr = ptr->m_right;
                else if (m_compare(k, ptr->m_value))
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
                if (m_compare(ptr->m_value, k))
                    ptr = ptr->m_right;
                else if (m_compare(k, ptr->m_value))
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
            Node *tmp = m_root;
            iterator it;
            while (ptr)
            {
                if (ptr->m_value >= k)
                    tmp = ptr;
                if (m_compare(ptr->m_value, k))
                    ptr = ptr->m_right;
                else if (m_compare(k, ptr->m_value))
                    ptr = ptr->m_left;
                else
                    break;
            }
            if (tmp != NULL)
            {
                it = tmp;
                return (it);
            }
            return this->end();
        };

        const_iterator lower_bound(const key_type &k) const
        {
            Node *ptr = m_root;
            Node *tmp = m_root;
            const_iterator it;
            while (ptr)
            {
                if (ptr->m_value >= k)
                    tmp = ptr;
                if (m_compare(ptr->m_value, k))
                    ptr = ptr->m_right;
                else if (m_compare(k, ptr->m_value))
                    ptr = ptr->m_left;
                else
                    break;
            }
            if (tmp != NULL)
            {
                it = tmp;
                return (it);
            }
            return this->end();
        };

        iterator upper_bound(const key_type &k) // k <
        {
            Node *ptr = m_root;
            Node *tmp = m_root;
            iterator it;
            while (ptr)
            {
                if (ptr->m_value > k)
                    tmp = ptr;
                if (m_compare(ptr->m_value, k) || k == ptr->m_value)
                    ptr = ptr->m_right;
                else if (m_compare(k, ptr->m_value))
                    ptr = ptr->m_left;
            }
            if (tmp != NULL)
            {
                it = tmp;
                return (it);
            }
            return this->end();
        };
        const_iterator upper_bound(const key_type &k) const
        {
            Node *ptr = m_root;
            const_iterator it;
            while (ptr && !m_compare(k, ptr->m_value))
            {
                if (m_compare(ptr->m_value, k) || ptr->m_value == k)
                    ptr = ptr->m_right;
                else if (m_compare(k, ptr->m_value))
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

        ~set()
        {
            // ~m_tree();
        }

        // FIXME Hadi khasni nhaydha ola n9adha
        const RDTree &getTree() const
        {
            return (m_tree);
        }
    };

}

#endif