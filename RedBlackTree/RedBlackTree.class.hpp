#ifndef REDBLACKTREE_CLASS_HPP
#define REDBLACKTREE_CLASS_HPP

template <class K, class T>
class RedBlackTree
{
public:
    typedef K key_type;
    typedef T mapped_type;

private:
    class Node
    {

    public:
        key_type m_key;
        mapped_type m_value;
        Node *m_left;
        Node *m_right;
        Node *m_parent;
        bool m_isLeftChild;
        bool m_black;
        Node(key_type key, mapped_type value) : m_key(key), m_value(value), m_left(0),
                                                m_right(0), m_parent(0), m_isLeftChild(false), m_black(false)
        {
        }
    };

    Node *m_root;
    int m_size;

    // methodes;
    void add(Node *parent, Node *node, std::less<key_type> less = std::less<key_type>())
    {
        if (less(parent->m_key, node->m_key))
        {
            if (parent->m_right == NULL)
            {
                parent->m_right = node;
                node->m_parent = parent;
                node->m_isLeftChild = false;
                return;
            }
            return add(parent->m_right, node);
        }
        // else if (less(node->m_key, parent->m_key))
        // {
        if (parent->m_left == NULL)
        {
            parent->m_left = node;
            node->m_parent = parent;
            node->m_isLeftChild = true;
            return;
        }
        add(parent->m_left, node);
        // }
        checkColor(node);
    }

    void checkColor(Node *node)
    {
        if (node == m_root)
            return;
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
            // if(node->m_parent->m_parent->m_right)
            // {
            node->m_parent->m_parent->m_right->m_black = true;
            node->m_parent->m_parent->m_black = false;
            node->m_parent->m_black = true;
            // }
            return;
        }
        //  Uncle ==> node->m_parent->m_parent->m_left
        if (!node->m_parent->m_parent->m_left || node->m_parent->m_parent->m_left->m_black)
            return rotation(node);
        // if(node->m_parent->m_parent->m_left)
        // {
        node->m_parent->m_parent->m_left->m_black = true;
        node->m_parent->m_parent->m_black = false;
        node->m_parent->m_black = true;
        // }
        return;
    }

    void rotation(Node *node)
    {
        if (node->m_isLeftChild)
        {
            if (node->m_parent->m_isLeftChild)
            {
                rightRotation(&node->m_parent->m_parent);
                node->m_black = false;
                node->m_parent->m_black = true;
                // hta nzid wahad condion dyal hna f 7alat makant null
                node->m_parent->m_right->m_black = false;
                return;
            }
            rightLeftRotation(&node->m_parent->m_parent);
            node->m_black = true;
            node->m_right->m_black = false;
            node->m_left->m_black = false;
            return;
        }
        if (node->m_parent->m_isLeftChild)
        {
            leftRotation(&node->m_parent->m_parent);
            node->m_black = false;
            node->m_parent->m_black = true;
            // hta nzid wahad condion dyal hna f 7alat makant null
            node->m_parent->m_right->m_black = false;
            return;
        }
        leftRightRotation(&node->m_parent->m_parent);
        node->m_black = true;
        node->m_right->m_black = false;
        node->m_left->m_black = false;
        return;
    }

    void leftRotation(Node **node)
    {
        Node *tmp;
        tmp = (*node)->m_right;

        (*node)->m_right = tmp->m_left;
        if ((*node)->m_right != NULL)
        {
            (*node)->m_right->m_parent = *node;
            (*node)->m_right->m_isLeftChild = false;
        }

        if ((*node)->m_parent == NULL) // *node is root
        {
            m_root = tmp;
            tmp->m_parent = NULL;
        }
        else
        {
            tmp->m_parent = (*node)->m_parent;
            if ((*node)->m_isLeftChild)
            {
                tmp->m_isLeftChild = true;
                (*node)->m_parent->m_left = tmp;
            }
            else
            {
                tmp->m_isLeftChild = false;
                (*node)->m_parent->m_right = tmp;
            }
        }
        (*node)->m_isLeftChild = true;
        (*node)->m_parent = tmp;
    }
    void rightRotation(Node **node)
    {
        Node *tmp;
        tmp = (*node)->m_left;

        (*node)->m_left = tmp->m_right;
        if ((*node)->m_left != NULL)
        {
            (*node)->m_left->m_parent = *node;
            (*node)->m_left->m_isLeftChild = true;
        }

        if ((*node)->m_parent == NULL) // *node is root
        {
            m_root = tmp;
            tmp->m_parent = NULL;
        }
        else
        {
            tmp->m_parent = (*node)->m_parent;
            if ((*node)->m_isLeftChild)
            {
                tmp->m_isLeftChild = true;
                (*node)->m_parent->m_left = tmp;
            }
            else
            {
                tmp->m_isLeftChild = false;
                (*node)->m_parent->m_right = tmp;
            }
        }
        (*node)->m_isLeftChild = false;
        (*node)->m_parent = tmp;
    }

    void leftRightRotation(Node **node)
    {
        leftRotation(&(*node)->m_left);
        rightRotation(&(*node));
    }

    void rightLeftRotation(Node **node)
    {
        rightRotation(&(*node)->m_right);
        leftRotation(&(*node));
    }

public:
    RedBlackTree() : m_root(0), m_size(0){};
    void insert(key_type key, mapped_type value)
    {
        Node *node = new Node(key, value);
        if (m_root == NULL)
        {
            m_root = node;
            m_root->m_black = true;
            m_size++;
            return;
        }
        add(m_root, node);
        m_size++;
        return;
    }

    void delete(key_type key, mapped_type value)
    {
        
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
            std::cout << parent->m_value << std::endl;
            print(parent->m_right);
        }
    }
};

#endif