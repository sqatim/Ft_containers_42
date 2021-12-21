#ifndef REDBLACKTREE_CLASS_HPP
#define REDBLACKTREE_CLASS_HPP

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
    std::string m_end;  // hta nhaydha
    std::string m_root; // hta nhaydha
    NodeBase() : m_left(0), m_right(0), m_parent(0), m_isLeftChild(false), m_black(false), m_end("Not the end"), m_root("not root")
    {
    }
    NodeBase(value_type pair) : m_pair(pair), m_left(0),
                                m_right(0), m_parent(0), m_isLeftChild(false), m_black(false), m_end("Not the end"), m_root("not root")
    {
    }
};

// template<typename Tp>
template <class Iter, class Pair>
class RedBlackTreeIterator
{
public:
    typedef Iter iterator_type;
    typedef typename std::bidirectional_iterator_tag iterator_category;
    typedef typename Iterator_traits<iterator_type>::value_type value_type;
    typedef typename Iterator_traits<iterator_type>::difference_type difference_type;
    typedef typename Iterator_traits<Pair *>::pointer pointer;
    typedef typename Iterator_traits<Pair *>::reference reference;
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
            m_current = m_current->m_parent;
        }
        return *this;
    };
    RedBlackTreeIterator &operator--()
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

template <class Iter, class Pair>
bool operator==(const RedBlackTreeIterator<Iter, Pair> &lhs,
                const RedBlackTreeIterator<Iter, Pair> &rhs)
{
    return lhs.base() == rhs.base();
}

template <class Iter, class Pair>
bool operator!=(const RedBlackTreeIterator<Iter, Pair> &lhs,
                const RedBlackTreeIterator<Iter, Pair> &rhs)
{
    return lhs.base() != rhs.base();
}

template <class Key, class T, class Compare, class Alloc>
class RedBlackTree
{
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef ft::pair<const key_type, mapped_type> value_type;
    typedef NodeBase<value_type> Node;
    typedef Alloc allocator_type;
    typedef Compare key_compare;

private:
    Node *m_root;
    Node *m_end;
    size_t m_size;
    allocator_type m_allocator;
    key_compare m_compare;

    // methodes;
    ft::pair<Node *, bool> add(Node *parent, Node *node, key_compare &compare)
    {
        if (compare(parent->m_pair.first, node->m_pair.first))
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
        else if (compare(node->m_pair.first, parent->m_pair.first))
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
        if (node == NULL || m_root == m_end) // had f7alatma badalt  tbadal root kan protecti biha
        {
            return;
        }
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
            // if (!node->m_parent->m_parent->m_left)
            // {
            return rotation(node);
            // }
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
        std::cout << GREEN << "                                 [" << RED << "RIGHT ROTATION" << GREEN << "]" << DEFAULT << std::endl;
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
        std::cout << RED << "Inorder predecessor" << ptr->m_pair.second << DEFAULT << std::endl;
        return ptr;
    }

    Node *inorderSuccessor(Node *ptr)
    {
        while (ptr && ptr->m_left != NULL)
            ptr = ptr->m_left;
        std::cout << RED << "Inorder succesor " << ptr->m_pair.second << DEFAULT << std::endl;
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
    RedBlackTree() : m_root(0), m_end(0), m_size(0){};
    RedBlackTree(allocator_type &allocator, key_compare &compare) : m_root(0), m_end(0), m_size(0), m_allocator(allocator), m_compare(compare){};
    RedBlackTree(const RedBlackTree &x)
    {
        *this = x;
        return;
    }
    ft::pair<Node *, bool> insert(const ft::pair<key_type, mapped_type> &value, key_compare &compare, allocator_type &allocator)
    {
        ft::pair<Node *, bool> k;
        Node *node = allocator.allocate(1);
        allocator.construct(node, Node(value));
        if (m_root == NULL)
        {
            m_end = allocator.allocate(1);
            allocator.construct(m_end, Node(ft::make_pair<key_type, mapped_type>(key_type(), mapped_type())));
            m_end->m_black = true;
            m_end->m_end = "the end";
            m_root = node;
            m_root->m_root = "i am the root";
            m_end->m_left = m_root;
            m_root->m_parent = m_end;
            m_root->m_black = true;
            m_root->m_isLeftChild = true;
            m_size++;
            return ft::make_pair(node, true);
        }
        k = add(m_root, node, compare);
        return (k);
    }

    Node *reallocation(Node *node, Node *x, Node *parent)
    {
        if (!x)
            return NULL;
        else
        {
            node = m_allocator.allocate(1);
            m_allocator.construct(node, Node(x->m_pair));
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
    RedBlackTree &operator=(const RedBlackTree &x)
    {
        if (this != &x)
        {
            if (m_size > 0)
                this->~RedBlackTree();
            m_size = 0;
            m_end = reallocation(m_end, x.getEnd(), NULL);
            if (m_end != NULL)
            {
                m_size--;
                m_root = m_end->m_left;
                m_root->m_parent = m_end;
                // std::cout << RED << "------------------warning**********************" << DEFAULT << std::endl;
                // std::cout << m_root->m_right->m_pair.second << std::endl;
                // std::cout << RED << "------------------warning**********************" << DEFAULT << std::endl;
            }
            else
            {
                m_root = NULL;
            }
        }
        return *this;
    }

    void deleteNode(Node **node)
    {
        if ((*node) == NULL)
            return ;
        if ((*node)->m_black)
            std::cout << "[delete] a BLACK node --- " << (*node)->m_pair.second << std::endl;
        else
            std::cout << "[delete] a RED node --- " << (*node)->m_pair.second << std::endl;
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
            // hta n3awd ntcheki wash les (*node) != null
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

    // void erase(value_type value)
    // {
    //     erase(value.first, &m_root);
    // }
    void erase(key_type key, Node **parent)
    {
        Node *q;
        if ((*parent) == NULL)
            return;
        if (!(*parent)->m_left && !(*parent)->m_right)
            deleteNode(&(*parent));
        else if (*parent && m_compare((*parent)->m_pair.first, key))
            erase(key, &(*parent)->m_right);
        else if (*parent && m_compare(key, (*parent)->m_pair.first))
            erase(key, &(*parent)->m_left);
        else if (*parent && key == (*parent)->m_pair.first)
        {
            // if height is 0 in parent left we cant chose inorderPredecessor  and the opposite is tree this is why we calcul the height
            if (height((*parent)->m_left) >= height((*parent)->m_right))
            {
                q = inorderPredecessor((*parent)->m_left);
                const_cast<key_type &>((*parent)->m_pair.first) = q->m_pair.first;
                (*parent)->m_pair.second = q->m_pair.second;
                erase(q->m_pair.first, &(*parent)->m_left);
            }
            else
            {
                q = inorderSuccessor((*parent)->m_right);
                const_cast<key_type &>((*parent)->m_pair.first) = q->m_pair.first;
                (*parent)->m_pair.second = q->m_pair.second;
                erase(q->m_pair.first, &(*parent)->m_right);
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
        std::cout << GREEN << "                    [" << SMILE << RED << "CaseOne" << GREEN << SMILE << "]" << DEFAULT << std::endl;
        Node *tmp = node;
        if (!node->m_right && !node->m_left)
        {
            // std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << std::endl;
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
        std::cout << GREEN << "                    [" << SMILE << RED << "CaseTwo" << GREEN << SMILE << "]" << DEFAULT << std::endl;
        Node *tmp = node;

        if (tmp->m_isLeftChild)
        {
            tmp->m_parent->m_left = tmp->m_left; // hadi mamt2kdsh manha : ma3raftsh wash anakhud left ola right
            if (tmp->m_left)
                tmp->m_left->m_parent = tmp->m_parent;
            leftRotation(tmp->m_parent);
            tmp->m_parent->m_black = false;
            tmp->m_parent->m_parent->m_black = true;
            tmp->m_parent->m_parent->m_right->m_black = false;
            colorToRed(tmp->m_parent->m_right); // hadi 7a9ash ga3 les child li kayduzu l jiha lakhra khashum ikunu red
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
        // std::cout << YELLOW <<"wa shamir ra dkhalt l colortored "<< DEFAULT << std::endl;
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

        std::cout << GREEN << "                    [" << SMILE << RED << "CaseThree" << GREEN << SMILE << "]" << DEFAULT << std::endl;
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
                ((tmp->m_parent->m_left->m_left && tmp->m_parent->m_left->m_left->m_black) && (tmp->m_parent->m_left->m_right && tmp->m_parent->m_left->m_right->m_black)))
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

    ~RedBlackTree()
    {
        // if (m_size > 0)
        // {
        //     freeNodes(&this->m_end);
        //     m_root = NULL;
        //     m_end = NULL;
        //     m_size = 0;
        // }
    }
};

#endif