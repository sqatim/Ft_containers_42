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
        if (parent->m_left == NULL)
        {
            parent->m_left = node;
            node->m_parent = parent;
            node->m_isLeftChild = true;
            return;
        }
        return add(parent->m_left, node);
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