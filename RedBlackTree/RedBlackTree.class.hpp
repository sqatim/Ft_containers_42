#ifndef REDBLACKTREE_CLASS_HPP
#define REDBLACKTREE_CLASS_HPP

#include <iostream>

#define RED "\033[1;31m"
#define BLACK "\033[1;30m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define DEFAULT "\033[0m"

#include "../Iterators/iterator.hpp"

template <class T>
struct NodeBase
{
    // Member Types:
    // typedef K key_type;
    // typedef T mapped_type;
    typedef T value_type;

    value_type m_pair; // FIXME hta nbadlha b type pair li creat ana
    NodeBase *m_left;
    NodeBase *m_right;
    NodeBase *m_parent;
    bool m_isLeftChild;
    bool m_black;
    NodeBase(value_type pair) : m_pair(pair), m_left(0),
                                m_right(0), m_parent(0), m_isLeftChild(false), m_black(false)
    {
    }
};

// template<typename Tp>
template <class Iter, class pair>
class RedBlackTreeIterator
{
public:
    typedef Iter iterator_type;
    typedef typename std::bidirectional_iterator_tag iterator_category;
    typedef typename Iterator_traits<iterator_type>::value_type value_type;
    typedef typename Iterator_traits<iterator_type>::difference_type difference_type;
    typedef typename Iterator_traits<pair *>::pointer pointer;
    typedef typename Iterator_traits<pair *>::reference reference;
    iterator_type m_current;

    RedBlackTreeIterator() : m_current(){};
    RedBlackTreeIterator(iterator_type x) : m_current(x){};
    RedBlackTreeIterator(const RedBlackTreeIterator &other)
    {
        this->m_current = other.m_current;
    };
    RedBlackTreeIterator &operator=(const RedBlackTreeIterator &other)
    {
        if (this != &other)
            this->m_current = other.m_current;
        return (*this);
    };
    iterator_type base() const { return this->m_current; };
    reference operator*() const
    {
        return (*m_current).m_pair;
    };
    pointer operator->() const
    {
        return &(operator*());
    };
    reference operator[](difference_type n) const
    {
        return this->m_current[n].m_pair;
    };
    RedBlackTreeIterator &operator++()
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
            m_current = m_current->m_right;
        }
        return *this;
    };
    RedBlackTreeIterator &operator--()
    {
        iterator_type tmp;
        if (m_current->m_left != NULL)
        {
            m_current = m_current->m_left;
            while (m_current->m_left)
                m_current = m_current->m_left;
            return (*this);
        }
        tmp = m_current;
        m_current = m_current->m_parent;
        while (m_current && m_current->m_left == tmp)
        {
            tmp = m_current;
            m_current = m_current->m_left;
        }
        return *this;
    };
    RedBlackTreeIterator operator++(int)
    {
        RedBlackTreeIterator copy = *this;
        ++(*this);
        return copy;
    };
    RedBlackTreeIterator operator--(int)
    {
        RedBlackTreeIterator copy = *this;
        --(*this);
        return copy;
    };
};

template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
class RedBlackTree
{
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef std::pair<const key_type, mapped_type> value_type;
    typedef NodeBase<value_type> Node;

private:
    Node *m_root;
    int m_size;

    // methodes;
    int add(Node *parent, Node *node, std::less<key_type> less = std::less<key_type>())
    {
        if (less(parent->m_pair.first, node->m_pair.first))
        {
            if (parent->m_right == NULL)
            {
                parent->m_right = node;
                node->m_parent = parent;
                node->m_isLeftChild = false;
                checkColor(node);
                return (1);
            }
            return add(parent->m_right, node);
        }
        else if (less(node->m_pair.first, parent->m_pair.first))
        {
            if (parent->m_left == NULL)
            {
                parent->m_left = node;
                node->m_parent = parent;
                node->m_isLeftChild = true;
                checkColor(node);
                return (1);
            }
            return add(parent->m_left, node);
        }
        else
            return (0);
        // std::cout << node->m_pair.first << std::endl;
        // }
    }

    void checkColor(Node *node)
    {
        if (node == NULL) // had f7alatma badalt  tbadal root kan protecti biha
            return;
        if (node == m_root)
        {
            node->m_black = true;
            return;
        }
        if (!node->m_black && !node->m_parent->m_black) // hna fen kayna segfault
        {
            correctTree(node);
        }
        checkColor(node->m_parent);
    }

    void correctTree(Node *node)
    {
        if (node->m_parent->m_isLeftChild) //  Uncle ==> node->m_parent->m_parent->m_right
        {
            // std::cout << node << std::endl;
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
        {
            if (!node->m_parent->m_parent->m_left)
                std::cout << "fen a jemi" << std::endl;
            return rotation(node);
        }
        // std::cout << node->m_pair.second << std::endl;
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

        std::cout << GREEN << "                                 [" << RED << "LEFT ROTATION" << GREEN << "]" << DEFAULT << std::endl;
        node->m_right = tmp->m_left;
        if (node->m_right != NULL)
        {
            node->m_right->m_parent = node;
            node->m_right->m_isLeftChild = false;
        }
        if (node->m_parent == NULL) // *node is root
        {
            m_root = tmp;
            tmp->m_parent = NULL;
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
        std::cout << GREEN << "                                 [" << RED << "RIGHT ROTATION" << GREEN << "]" << DEFAULT << std::endl;
        if (node->m_left != NULL)
        {
            node->m_left->m_parent = node;
            node->m_left->m_isLeftChild = true;
        }

        if (node->m_parent == NULL) // *node is root
        {
            m_root = tmp;
            tmp->m_parent = NULL;
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
        std::cout << GREEN << "                                 [" << RED << "LEFTRIGHT ROTATION" << GREEN << "]" << DEFAULT << std::endl;
        leftRotation(node->m_left);
        rightRotation(node);
    }

    void rightLeftRotation(Node *node)
    {
        std::cout << GREEN << "                                 [" << RED << "RIGHTLEFT ROTATION" << GREEN << "]" << DEFAULT << std::endl;
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
        std::cout << RED << "shamil lghzal predecessor" << ptr->m_pair.second << DEFAULT << std::endl;
        return ptr;
    }

    Node *inorderSuccessor(Node *ptr)
    {
        while (ptr && ptr->m_left != NULL)
            ptr = ptr->m_left;
        std::cout << RED << "shamil lghzal succesor " << ptr->m_pair.second << DEFAULT << std::endl;
        return ptr;
    }

public:
    Node *getRoot() { return (m_root); };
    RedBlackTree() : m_root(0), m_size(0){};
    // RedBlackTree() :
    int insert(const std::pair<key_type, mapped_type> &value)
    {
        int k = 0;
        Node *node = new Node(value);
        if (m_root == NULL)
        {
            m_root = node;
            m_root->m_black = true;
            m_size++;
            return 1;
        }
        k = add(m_root, node);
        m_size++;
        return (k);
    }

    void deleteNode(key_type key)
    {
        deleteNode(key, &m_root);
    }
    void deleteNode(key_type key, Node **parent)
    {
        Node *q;
        if ((*parent) == NULL)
            return;
        if (!(*parent)->m_left && !(*parent)->m_right)
        {
            if ((*parent) == m_root)
                m_root = NULL;
            if ((*parent)->m_black)
                std::cout << "[delete] a BLACK node --- " << (*parent)->m_pair.second << std::endl;
            else
                std::cout << "[delete] a RED node --- " << (*parent)->m_pair.second << std::endl;
            if (!(*parent)->m_black)
                caseOne((*parent));
            // // delete (*(*parent));
            else if ((*parent)->m_black)
            {
                // hta n3awd ntcheki wash les (*parent) != null
                if (((*parent)->m_isLeftChild && (*parent)->m_parent->m_right && (*parent)->m_parent->m_right->m_black == false) ||
                    (!(*parent)->m_isLeftChild && (*parent)->m_parent->m_left && (*parent)->m_parent->m_left->m_black == false))
                    caseTwo((*parent)); // f7alat makan sibling [RED]
                else
                    caseThree((*parent));
            }
            *parent = NULL;
            // delete ((*parent));
            return;
        }
        if (key > (*parent)->m_pair.first)
            deleteNode(key, &(*parent)->m_right);
        else if (key < (*parent)->m_pair.first)
            deleteNode(key, &(*parent)->m_left);
        else
        {
            if (height((*parent)->m_left) >= height((*parent)->m_right))
            {
                q = inorderPredecessor((*parent)->m_left);
                (*parent)->m_pair.first = q->m_pair.first;
                (*parent)->m_pair.second = q->m_pair.second;
                deleteNode(q->m_pair.first, &(*parent)->m_left);
            }
            else
            {
                q = inorderSuccessor((*parent)->m_right);
                (*parent)->m_pair.first = q->m_pair.first;
                (*parent)->m_pair.second = q->m_pair.second;
                deleteNode(q->m_pair.first, &(*parent)->m_right);
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
        **                     [R] (delete a red node)
        */
        Node *tmp = node;
        if (!node->m_right && !node->m_left)
        {
            // std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << std::endl;
        }
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
    }

    void caseTwo(Node *node)
    {
        Node *tmp = node;

        if (tmp->m_isLeftChild)
        {
            tmp->m_parent->m_left = tmp->m_left; // hadi mamt2kdsh manha : ma3raftsh wash anakhud left ola right
            if (tmp->m_left)
                tmp->m_left->m_parent = tmp->m_parent;
            leftRotation(tmp->m_parent);
            tmp->m_parent->m_black = false;
            colorToRed(tmp->m_parent->m_right); // hadi 7a9ash ga3 les child li kayduzu l jiha lakhra khashum ikunu red
            tmp->m_parent->m_parent->m_black = true;
            tmp->m_parent->m_parent->m_right->m_black = false;
        }
        else if (!tmp->m_isLeftChild)
        {
            tmp->m_parent->m_right = tmp->m_right; // hadi mamt2kdsh manha : ma3raftsh wash anakhud left ola right
            if (tmp->m_right)
                tmp->m_right->m_parent = tmp->m_parent;
            rightRotation(tmp->m_parent);
            tmp->m_parent->m_black = false;
            colorToRed(tmp->m_parent->m_left); // hadi 7a9ash ga3 les child li kayduzu l jiha lakhra khashum ikunu red
            tmp->m_parent->m_parent->m_black = true;
            tmp->m_parent->m_parent->m_left->m_black = false;
        }
        delete (node);
    }
    void colorToRed(Node *node)
    {
        if (node == NULL)
            return;
        colorToRed(node->m_left);
        node->m_black = false;
        checkColor(node); // t9dar takhud liya time bzaf
        colorToRed(node->m_right);
    }
    void caseThree(Node *node)
    {
        Node *tmp = node;
        Node *tmpParent = node->m_parent;

        if (tmp->m_isLeftChild)
        {
            if ((!tmp->m_parent->m_right->m_left && !tmp->m_parent->m_right->m_right) ||
                (tmp->m_parent->m_right->m_left->m_black && tmp->m_parent->m_right->m_right->m_black)) // kan checki wash childs dyal sibling wash b2 black
            {
                tmp->m_parent->m_right->m_black = false;
                tmp->m_parent->m_black = true;
                delete (node);
                tmp->m_parent->m_left = tmp->m_left; // hadi mamt2kdsh manha : ma3raftsh wash anakhud left ola right
                if (tmp->m_left)
                    tmp->m_left->m_parent = tmp->m_parent;
                checkColor(tmp->m_parent);
            }
            else
            {
                if (tmp->m_parent->m_right->m_right && !tmp->m_parent->m_right->m_right->m_black)
                {
                    tmp->m_parent->m_left = tmp->m_left; // hadi mamt2kdsh manha : ma3raftsh wash anakhud left ola right
                    if (tmp->m_left)
                        tmp->m_left->m_parent = tmp->m_parent;
                    leftRotation(tmp->m_parent);
                    tmp->m_parent->m_black = false;
                    tmp->m_parent->m_parent->m_black = true;
                    tmp->m_parent->m_parent->m_right->m_black = false;
                }
                else if (tmp->m_parent->m_right->m_left && !tmp->m_parent->m_right->m_left->m_black)
                {
                    tmp->m_parent->m_left = tmp->m_left; // hadi mamt2kdsh manha : ma3raftsh wash anakhud left ola right
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
                (tmp->m_parent->m_left->m_left->m_black && tmp->m_parent->m_left->m_right->m_black))
            {
                tmp->m_parent->m_left->m_black = false;
                tmp->m_parent->m_black = true;
                delete (node);
                tmp->m_parent->m_right = tmp->m_right; // hadi mamt2kdsh manha : ma3raftsh wash anakhud left ola right
                if (tmp->m_right)
                    tmp->m_right->m_parent = tmp->m_parent;
                checkColor(tmp->m_parent);
            }
            else
            {
                if (tmp->m_parent->m_left->m_left && !tmp->m_parent->m_left->m_left->m_black)
                {
                    tmp->m_parent->m_right = tmp->m_right; // hadi mamt2kdsh manha : ma3raftsh wash anakhud right ola right
                    if (tmp->m_right)
                        tmp->m_right->m_parent = tmp->m_parent;
                    rightRotation(tmp->m_parent);
                    tmp->m_parent->m_black = false;
                    tmp->m_parent->m_parent->m_black = true;
                    tmp->m_parent->m_parent->m_left->m_black = false;
                }
                else if (tmp->m_parent->m_left->m_right && !tmp->m_parent->m_left->m_right->m_black)
                {
                    tmp->m_parent->m_right = tmp->m_right; // hadi mamt2kdsh manha : ma3raftsh wash anakhud left ola right
                    if (tmp->m_right)
                        tmp->m_right->m_parent = tmp->m_parent;
                    leftRightRotation(tmp->m_parent);
                    tmp->m_parent->m_black = false;
                    tmp->m_parent->m_parent->m_black = true;
                    tmp->m_parent->m_parent->m_left->m_black = false;
                }
                delete (node);
            }
        }
    }
    Node *getRoot() const
    {
        return (m_root);
    }

    void print(Node *parent)
    {
        if (parent)
        {
            print(parent->m_left);
            std::cout << "-------------------------------------------" << std::endl;
            if (parent == m_root)
                std::cout << YELLOW << "************ ROOT ************" << DEFAULT << std::endl;
            std::cout << parent->m_pair.first << ": " << parent->m_pair.second << std::endl;
            if (parent->m_isLeftChild)
                std::cout << "Which Child: " << GREEN << "LEFT" << DEFAULT << std::endl;
            else if (!parent->m_isLeftChild)
                std::cout << "Which Child: " << GREEN << "RIGHT" << DEFAULT << std::endl;
            if (parent->m_black)
                std::cout << "Color: " << BLACK << "black" << DEFAULT << std::endl;
            else if (!parent->m_black)
                std::cout << "Color: " << RED << "Red" << DEFAULT << std::endl;
            if (parent->m_right)
                std::cout << "Right Child: [" << parent->m_right->m_pair.second << "]" << std::endl;
            if (parent->m_left)
                std::cout << "Left Child: [" << parent->m_left->m_pair.second << "]" << std::endl;
            print(parent->m_right);
        }
    }
};

#endif