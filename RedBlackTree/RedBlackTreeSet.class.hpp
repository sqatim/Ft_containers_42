#ifndef REDBLACKTREESET_CLASS_HPP
#define REDBLACKTREESET_CLASS_HPP

#include <iostream>

#define RED "\033[1;31m"
#define BLACK "\033[1;30m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define DEFAULT "\033[0m"
#define SMILE "\U0001F600"

#include "../Iterators/iterator.hpp"
#include "../NeededTemplates/pair.hpp"
#include <typeinfo>

template <class T>
struct NodeBaseSet
{
    typedef T value_type;

    bool m_isLeftChild;
    bool m_black;
    value_type m_value;
    NodeBaseSet *m_left;
    NodeBaseSet *m_right;
    NodeBaseSet *m_parent;
    NodeBaseSet() : m_isLeftChild(false), m_black(false), m_left(0), m_right(0), m_parent(0)
    {
    }
    NodeBaseSet(value_type value) : m_isLeftChild(false), m_black(false), m_value(value), m_left(0),
                                    m_right(0), m_parent(0)
    {
    }
};

// template<typename Tp>
template <class Iter, class P>
class RedBlackTreeIteratorSet
{
public:
    typedef Iter iterator_type;
    typedef typename std::bidirectional_iterator_tag iterator_category;
    typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
    typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
    typedef typename ft::iterator_traits<P *>::pointer pointer;
    typedef typename ft::iterator_traits<P *>::reference reference;
    iterator_type m_current;

    RedBlackTreeIteratorSet() : m_current(){};
    RedBlackTreeIteratorSet(iterator_type x) : m_current(x){};
    template <class T, class K>
    RedBlackTreeIteratorSet(const RedBlackTreeIteratorSet<T, K> &other) : m_current(other.base()){};
    RedBlackTreeIteratorSet &operator=(const RedBlackTreeIteratorSet &other)
    {
        if (this != &other)
            this->m_current = other.m_current;
        return (*this);
    };
    iterator_type base() const { return this->m_current; };
    reference operator*() const
    {
        return (*m_current).m_value;
    };
    pointer operator->() const
    {
        return &(operator*());
    };
    reference operator[](difference_type n) const
    {
        return this->m_current[n].m_value;
    };
    RedBlackTreeIteratorSet &operator++()
    {
        iterator_type tmp;
        if (m_current->m_right != NULL)
        {
            m_current = m_current->m_right;
            while (m_current->m_left)
                m_current = m_current->m_left;
            return (*this);
        }
        tmp = m_current;
        m_current = m_current->m_parent;
        while (m_current && m_current->m_right == tmp)
        {
            tmp = m_current;
            m_current = m_current->m_parent;
        }
        return *this;
    };
    RedBlackTreeIteratorSet &operator--()
    {
        iterator_type tmp;
        if (m_current->m_left != NULL)
        {
            m_current = m_current->m_left;
            while (m_current->m_right)
                m_current = m_current->m_right;
            return (*this);
        }
        tmp = m_current;
        m_current = m_current->m_parent;
        while (m_current && m_current->m_left == tmp)
        {
            tmp = m_current;
            m_current = m_current->m_parent;
        }
        return *this;
    };
    RedBlackTreeIteratorSet operator++(int)
    {
        RedBlackTreeIteratorSet copy = *this;
        ++(*this);
        return copy;
    };
    RedBlackTreeIteratorSet operator--(int)
    {
        RedBlackTreeIteratorSet copy = *this;
        --(*this);
        return copy;
    };
};

template <class Iter, class Pair>
bool operator==(const RedBlackTreeIteratorSet<Iter, Pair> &lhs,
                const RedBlackTreeIteratorSet<Iter, Pair> &rhs)
{
    return lhs.base() == rhs.base();
}

template <class Iter, class Pair>
bool operator!=(const RedBlackTreeIteratorSet<Iter, Pair> &lhs,
                const RedBlackTreeIteratorSet<Iter, Pair> &rhs)
{
    return lhs.base() != rhs.base();
}

template <class Key, class T, class Compare, class Alloc>
class RedBlackTreeSet
{
public:
    typedef Key key_type;
    typedef T value_type;
    typedef NodeBaseSet<value_type> Node;
    typedef typename Alloc::template rebind<Node>::other allocator_type;
    typedef Compare key_compare;

    Node *m_root;
    Node *m_end;
    size_t m_size;
    allocator_type m_allocator;
    key_compare m_compare;

private:
    // methodes;
    ft::pair<Node *, bool> add(Node *parent, Node *node, key_compare &compare)
    {
        if (compare(parent->m_value, node->m_value))
        {
            if (parent->m_right == NULL)
            {
                m_size++;
                parent->m_right = node;
                node->m_parent = parent;
                node->m_isLeftChild = false;
                checkColor(node);
                return ft::make_pair(node, true);
            }
            return add(parent->m_right, node, compare);
        }
        else if (compare(node->m_value, parent->m_value))
        {
            if (parent->m_left == NULL)
            {
                m_size++;
                parent->m_left = node;
                node->m_parent = parent;
                node->m_isLeftChild = true;
                checkColor(node);
                return ft::make_pair(node, true);
            }
            return add(parent->m_left, node, compare);
        }
        else
            return ft::make_pair(parent, false);
    }

    void checkColor(Node *node)
    {
        if (node == NULL || m_root == m_end) // had f7alatma tbadal root kan protecti biha
            return;
        if (node == m_root)
        {
            node->m_black = true;
            return;
        }
        if (!node->m_black && !node->m_parent->m_black)
            correctTree(node);
        checkColor(node->m_parent);
    }

    void correctTree(Node *node)
    {
        if (node->m_parent->m_isLeftChild) //  Uncle ==> node->m_parent->m_parent->m_right
        {
            if (!node->m_parent->m_parent->m_right || node->m_parent->m_parent->m_right->m_black)
                return rotation(node);
            if (node->m_parent->m_parent->m_right)
            {
                node->m_parent->m_parent->m_right->m_black = true;
                node->m_parent->m_parent->m_black = false;
                node->m_parent->m_black = true;
            }
            return;
        }
        //  Uncle ==> node->m_parent->m_parent->m_left
        if (!node->m_parent->m_parent->m_left || node->m_parent->m_parent->m_left->m_black)
            return rotation(node);
        if (node->m_parent->m_parent->m_left)
        {
            node->m_parent->m_parent->m_left->m_black = true;
            node->m_parent->m_parent->m_black = false;
            node->m_parent->m_black = true;
        }
        return;
    }

    void rotation(Node *node)
    {
        if (node->m_isLeftChild)
        {
            if (node->m_parent->m_isLeftChild)
            {
                rightRotation(node->m_parent->m_parent);
                node->m_black = false;
                node->m_parent->m_black = true;
                if (node->m_parent->m_right)
                    node->m_parent->m_right->m_black = false;
                return;
            }
            rightLeftRotation(node->m_parent->m_parent);
            node->m_black = true;
            node->m_right->m_black = false;
            node->m_left->m_black = false;
            return;
        }
        if (!node->m_parent->m_isLeftChild)
        {
            leftRotation(node->m_parent->m_parent);
            node->m_black = false;
            node->m_parent->m_black = true;
            if (node->m_parent->m_left)
                node->m_parent->m_left->m_black = false;
            return;
        }
        leftRightRotation(node->m_parent->m_parent);
        node->m_black = true;
        node->m_right->m_black = false;
        node->m_left->m_black = false;
        return;
    }

    void leftRotation(Node *node)
    {
        Node *tmp;
        tmp = node->m_right;

        node->m_right = tmp->m_left;
        if (node->m_right != NULL)
        {
            node->m_right->m_parent = node;
            node->m_right->m_isLeftChild = false;
        }
        if (node->m_parent == m_end) // *node is root
        {
            m_root = tmp;
            m_end->m_left = tmp;
            tmp->m_parent = m_end;
        }
        else
        {
            tmp->m_parent = node->m_parent;
            if (node->m_isLeftChild)
            {
                tmp->m_isLeftChild = true;
                tmp->m_parent->m_left = tmp;
            }
            else
            {
                tmp->m_isLeftChild = false;
                tmp->m_parent->m_right = tmp;
            }
        }
        tmp->m_left = node;
        node->m_isLeftChild = true;
        node->m_parent = tmp;
    }

    void rightRotation(Node *node)
    {
        Node *tmp;
        tmp = node->m_left;

        node->m_left = tmp->m_right;
        if (node->m_left != NULL)
        {
            node->m_left->m_parent = node;
            node->m_left->m_isLeftChild = true;
        }

        if (node->m_parent == m_end) // *node is root
        {
            m_root = tmp;
            m_end->m_left = tmp;
            tmp->m_parent = m_end;
        }
        else
        {
            tmp->m_parent = node->m_parent;
            if (node->m_isLeftChild)
            {
                tmp->m_isLeftChild = true;
                tmp->m_parent->m_left = tmp;
            }
            else
            {
                tmp->m_isLeftChild = false;
                tmp->m_parent->m_right = tmp;
            }
        }
        tmp->m_right = node;
        node->m_isLeftChild = false;
        node->m_parent = tmp;
    }

    void leftRightRotation(Node *node)
    {
        leftRotation(node->m_left);
        rightRotation(node);
    }

    void rightLeftRotation(Node *node)
    {
        rightRotation(node->m_right);
        leftRotation(node);
    }

    int height(Node *ptr)
    {
        int x = 0;
        int y = 0;

        if (ptr == NULL)
            return 0;
        x = height(ptr->m_left);
        y = height(ptr->m_right);
        if (x > y)
            return (x + 1);
        else
            return (y + 1);
    }

    Node *inorderPredecessor(Node *ptr)
    {
        while (ptr && ptr->m_right != NULL)
            ptr = ptr->m_right;
        return ptr;
    }

    Node *inorderSuccessor(Node *ptr)
    {
        while (ptr && ptr->m_left != NULL)
            ptr = ptr->m_left;
        return ptr;
    }

    void freeNodes(Node **node)
    {
        if (*node != NULL)
        {
            freeNodes(&(*node)->m_left);
            freeNodes(&(*node)->m_right);
            m_allocator.deallocate((*node), 1);
            *node = NULL;
        }
    }

public:
    Node *getRoot() { return (m_root); };
    RedBlackTreeSet() : m_root(0), m_end(0), m_size(0), m_allocator(allocator_type()){};
    RedBlackTreeSet(key_compare &compare) : m_root(0), m_end(0), m_size(0), m_allocator(allocator_type()), m_compare(compare){};
    RedBlackTreeSet(const RedBlackTreeSet &x)
    {
        *this = x;
        return;
    }

    ft::pair<Node *, bool> insert(const key_type &value, key_compare &compare)
    {
        ft::pair<Node *, bool> k;
        Node *node = m_allocator.allocate(1);
        m_allocator.construct(node, Node(value));
        if (m_root == NULL)
        {
            m_end = m_allocator.allocate(1);
            m_allocator.construct(m_end, Node(key_type()));
            m_end->m_black = true;
            m_root = node;
            m_end->m_left = m_root;
            m_root->m_parent = m_end;
            m_root->m_black = true;
            m_root->m_isLeftChild = true;
            m_size++;
            return ft::make_pair(node, true);
        }
        k = add(m_root, node, compare);
        if (k.second == false)
            m_allocator.deallocate(node, 1);
        return (k);
    }

    Node *reallocation(Node *node, Node *x, Node *parent)
    {
        if (!x)
            return NULL;
        else
        {
            node = m_allocator.allocate(1);
            m_allocator.construct(node, Node(x->m_value));
            node->m_black = x->m_black;
            node->m_isLeftChild = x->m_isLeftChild;
            node->m_parent = parent;
            parent = node;
            node->m_left = reallocation(node->m_left, x->m_left, parent);
            node->m_right = reallocation(node->m_right, x->m_right, parent);
            m_size++;
            return node;
        }
    }
    RedBlackTreeSet &operator=(const RedBlackTreeSet &x)
    {
        if (this != &x)
        {
            if (m_size > 0)
                this->~RedBlackTreeSet();
            m_size = 0;
            m_end = reallocation(m_end, x.getEnd(), NULL);
            if (m_end != NULL)
            {
                m_size--;
                m_root = m_end->m_left;
                m_root->m_parent = m_end;
            }
            else
                m_root = NULL;
        }
        return *this;
    }

    void deleteNode(Node **node)
    {
        if ((*node) == NULL)
            return;
        // if ((*node)->m_black)
        //     std::cout << "[delete] a BLACK node --- " << (*node)->m_pair.second << std::endl;
        // else
        //     std::cout << "[delete] a RED node --- " << (*node)->m_pair.second << std::endl;
        if (*node == m_root)
        {
            delete *node;
            m_root = NULL;
            delete (m_end);
            m_end = NULL;
            m_size = 0;
        }
        else if (!(*node)->m_black)
            caseOne((*node));
        else if ((*node)->m_black)
        {
            if (((*node)->m_isLeftChild && (*node)->m_parent->m_right && (*node)->m_parent->m_right->m_black == false) ||
                (!(*node)->m_isLeftChild && (*node)->m_parent->m_left && (*node)->m_parent->m_left->m_black == false))
                caseTwo((*node)); // f7alat makan sibling [RED]
            else
                caseThree((*node));
            m_size--;
        }
        *node = NULL;
        return;
    }
    void erase(key_type key)
    {
        erase(key, &m_root);
    }

    void erase(key_type key, Node **parent)
    {
        Node *q;
        if ((*parent) == NULL)
            return;
        if (!(*parent)->m_left && !(*parent)->m_right)
            deleteNode(&(*parent));
        else if (*parent && m_compare((*parent)->m_value, key))
            erase(key, &(*parent)->m_right);
        else if (*parent && m_compare(key, (*parent)->m_value))
            erase(key, &(*parent)->m_left);
        else if (*parent && key == (*parent)->m_value)
        {
            // if height is 0 in parent left we cant chose inorderPredecessor  and the opposite is tree this is why we calcul the height
            if (height((*parent)->m_left) >= height((*parent)->m_right))
            {
                q = inorderPredecessor((*parent)->m_left);
                const_cast<key_type &>((*parent)->m_value) = q->m_value;
                erase(q->m_value, &(*parent)->m_left);
            }
            else
            {
                q = inorderSuccessor((*parent)->m_right);
                const_cast<key_type &>((*parent)->m_value) = q->m_value;
                erase(q->m_value, &(*parent)->m_right);
            }
        }
        return;
    }
    void caseOne(Node *node)
    {
        /*
        **                [B]
        **               /   \
        **             [B]   [B]
        **                     \
        **                    [D|R] (delete a red node)
        */
        // std::cout << GREEN << "                    [" << SMILE << RED << "CaseOne" << GREEN << SMILE << "]" << DEFAULT << std::endl;
        Node *tmp = node;
        if (!node->m_right && !node->m_left)
        {
        }
        // this else if are for when it had a one child
        else if (node->m_right)
        {
            if (node->m_isLeftChild)
            {
                tmp->m_parent->m_left = tmp->m_right;
                tmp->m_right->m_isLeftChild = true;
            }
            else
            {
                tmp->m_parent->m_right = tmp->m_right;
                tmp->m_right->m_isLeftChild = false;
            }
            tmp->m_right->m_parent = tmp->m_parent;
        }
        else if (node->m_left)
        {
            if (node->m_isLeftChild)
            {
                tmp->m_parent->m_left = tmp->m_left;
                tmp->m_left->m_isLeftChild = true;
            }
            else
            {
                tmp->m_parent->m_right = tmp->m_left;
                tmp->m_left->m_isLeftChild = false;
            }
            tmp->m_left->m_parent = tmp->m_parent;
        }
        delete node;
        m_size--;
    }

    void caseTwo(Node *node)
    {
        /*
        ** delete a black node that have a red sibling
        **                [B]
        **               /   \
        **           [D|B]   [R] S
        **                     \
        **                     [R]
        ** we Perform a rotation
        */
        Node *tmp = node;

        if (tmp->m_isLeftChild)
        {
            tmp->m_parent->m_left = tmp->m_left;
            if (tmp->m_left)
                tmp->m_left->m_parent = tmp->m_parent;
            leftRotation(tmp->m_parent);
            tmp->m_parent->m_black = false;
            tmp->m_parent->m_parent->m_black = true;
            tmp->m_parent->m_parent->m_right->m_black = false;
            colorToRed(tmp->m_parent->m_right);
        }
        else if (!tmp->m_isLeftChild)
        {
            tmp->m_parent->m_right = tmp->m_right;
            if (tmp->m_right)
                tmp->m_right->m_parent = tmp->m_parent;
            rightRotation(tmp->m_parent);
            tmp->m_parent->m_black = false;
            tmp->m_parent->m_parent->m_black = true;
            tmp->m_parent->m_parent->m_left->m_black = false;
            colorToRed(tmp->m_parent->m_left);
        }
        delete (node);
    }
    void colorToRed(Node *node)
    {
        if (node == NULL)
            return;
        colorToRed(node->m_left);
        node->m_black = false;
        checkColor(node);
        colorToRed(node->m_right);
    }
    void caseThree(Node *node)
    {
        Node *tmp = node;

        if (tmp->m_isLeftChild)
        {
            if ((!tmp->m_parent->m_right->m_left && !tmp->m_parent->m_right->m_right) ||
                ((tmp->m_parent->m_right->m_left && tmp->m_parent->m_right->m_left->m_black) && (tmp->m_parent->m_right->m_right && tmp->m_parent->m_right->m_right->m_black))) // kan checki wash childs dyal sibling wash b2 black
            {
                tmp->m_parent->m_right->m_black = false;
                tmp->m_parent->m_black = true;
                delete (node);
                tmp->m_parent->m_left = tmp->m_left;
                if (tmp->m_left)
                    tmp->m_left->m_parent = tmp->m_parent;
                checkColor(tmp->m_parent);
            }
            else
            {
                if (tmp->m_parent->m_right->m_right && !tmp->m_parent->m_right->m_right->m_black)
                {
                    tmp->m_parent->m_left = tmp->m_left;
                    if (tmp->m_left)
                        tmp->m_left->m_parent = tmp->m_parent;
                    leftRotation(tmp->m_parent);
                    tmp->m_parent->m_black = false;
                    tmp->m_parent->m_parent->m_black = true;
                    tmp->m_parent->m_parent->m_right->m_black = false;
                    colorToRed(tmp->m_parent->m_right);
                }
                else if (tmp->m_parent->m_right->m_left && !tmp->m_parent->m_right->m_left->m_black)
                {
                    tmp->m_parent->m_left = tmp->m_left;
                    if (tmp->m_left)
                        tmp->m_left->m_parent = tmp->m_parent;
                    rightLeftRotation(tmp->m_parent);
                    tmp->m_parent->m_black = true;
                    tmp->m_parent->m_parent->m_black = false;
                    tmp->m_parent->m_parent->m_right->m_black = true;
                }
                delete (node);
            }
        }
        else if (!tmp->m_isLeftChild)
        {
            if ((!tmp->m_parent->m_left->m_left && !tmp->m_parent->m_left->m_right) ||
                ((tmp->m_parent->m_left->m_left && tmp->m_parent->m_left->m_left->m_black) && (tmp->m_parent->m_left->m_right && tmp->m_parent->m_left->m_right->m_black)))
            {
                tmp->m_parent->m_left->m_black = false;
                tmp->m_parent->m_black = true;
                delete (node);
                tmp->m_parent->m_right = tmp->m_right;
                if (tmp->m_right)
                    tmp->m_right->m_parent = tmp->m_parent;
                checkColor(tmp->m_parent);
            }
            else
            {
                if (tmp->m_parent->m_left->m_left && !tmp->m_parent->m_left->m_left->m_black)
                {
                    tmp->m_parent->m_right = tmp->m_right;
                    if (tmp->m_right)
                        tmp->m_right->m_parent = tmp->m_parent;
                    rightRotation(tmp->m_parent);
                    tmp->m_parent->m_black = false;
                    tmp->m_parent->m_parent->m_black = true;
                    tmp->m_parent->m_parent->m_left->m_black = false;
                    colorToRed(tmp->m_parent->m_left);
                }
                else if (tmp->m_parent->m_left->m_right && !tmp->m_parent->m_left->m_right->m_black)
                {
                    tmp->m_parent->m_right = tmp->m_right;
                    if (tmp->m_right)
                        tmp->m_right->m_parent = tmp->m_parent;
                    leftRightRotation(tmp->m_parent);
                    tmp->m_parent->m_black = true;
                    tmp->m_parent->m_parent->m_black = false;
                    tmp->m_parent->m_parent->m_left->m_black = true;
                }
                delete (node);
            }
        }
    }
    Node *getRoot() const
    {
        return (m_root);
    }
    Node *getEnd() const
    {
        return (m_end);
    }

    size_t getSize() const
    {
        return (m_size);
    }

    size_t getMaxSize() const
    {
        return m_allocator.max_size();
    }
    
     void swap(RedBlackTreeSet& x)
    {
        std::swap(this->m_end, x.m_end);
        std::swap(this->m_root, x.m_root);
        std::swap(this->m_size, x.m_size);
        std::swap(this->m_allocator, x.m_allocator);
        std::swap(this->m_compare, x.m_compare);
    }

    ~RedBlackTreeSet()
    {
        if (m_size > 0)
        {
            freeNodes(&this->m_end);
            m_root = NULL;
            m_end = NULL;
            m_size = 0;
        }
    }
};

#endif