#ifndef REDBLACKTREE_CLASS_HPP
#define REDBLACKTREE_CLASS_HPP

#define RED "\033[1;31m"
#define BLACK "\033[1;30m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define DEFAULT "\033[0m"

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
                // return;
            }
            add(parent->m_right, node);
        }
        else if (less(node->m_key, parent->m_key))
        {
            if (parent->m_left == NULL)
            {
                parent->m_left = node;
                node->m_parent = parent;
                node->m_isLeftChild = true;
                // return;
            }
            add(parent->m_left, node);
        }

        // }
        checkColor(node);
    }

    void checkColor(Node *node)
    {
        if (node == m_root)
        {
            node->m_black = true;
            return;
        }
        if (!node->m_black && !node->m_parent->m_black)
        {
            correctTree(node);
        }
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
            node->m_parent->m_left->m_black = false;
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

    Node *deleteNode(key_type key)
    {
        return (deleteNode(key, m_root));
    }
    Node *deleteNode(key_type key, Node *parent)
    {
        Node *q;
        if (parent == NULL)
        {
            return NULL;
        }
        if (!parent->m_left && !parent->m_right)
        {
            if (parent == m_root)
            {
                m_root = NULL;
            }
            if (parent->m_black)
                std::cout << "[delete] a BLACK node --- " << parent->m_value << std::endl;
            else
                std::cout << "[delete] a RED node --- " << parent->m_value << std::endl;
            if (!parent->m_black)
                caseOne(&parent);
            // // delete (*parent);
            if (parent->m_black)
            {
                // hta n3awd ntcheki wash les parent != null
                if ((parent->m_isLeftChild && parent->m_parent->m_right && parent->m_parent->m_right->m_black == false) ||
                    (!parent->m_isLeftChild && parent->m_parent->m_left && parent->m_parent->m_left->m_black == false))
                    caseTwo(&parent); // f7alat makan sibling [RED]
                else
                    caseThree(&parent);
            }
            // delete (parent);
            return (NULL);
        }
        if (key > parent->m_key)
            parent->m_right = deleteNode(key, parent->m_right);
        else if (key < parent->m_key)
            parent->m_left = deleteNode(key, parent->m_left);
        else
        {
            if (height(parent->m_left) > height(parent->m_right))
            {
                q = inorderPredecessor(parent->m_left);
                parent->m_key = q->m_key;
                parent->m_value = q->m_value;
                parent->m_left = deleteNode(q->m_key, parent->m_left);
            }
            else
            {
                q = inorderSuccessor(parent->m_right);
                parent->m_key = q->m_key;
                parent->m_value = q->m_value;
                parent->m_right = deleteNode(q->m_key, parent->m_right);
            }
        }
        return (parent);
    }
    void caseOne(Node **node)
    {
        /*
        **                [B]
        **               /   \
        **             [B]   [B]
        **                     \
        **                     [R] (delete a red node)
        */
        Node *tmp = *node;
        if (!(*node)->m_right && !(*node)->m_left)
            ;
        else if ((*node)->m_right)
        {
            if ((*node)->m_isLeftChild)
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
        else if ((*node)->m_left)
        {
            if ((*node)->m_isLeftChild)
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
        delete (*node);
    }

    void caseTwo(Node **node)
    {
        Node *tmp = *node;

        if (tmp->m_isLeftChild)
        {
            tmp->m_parent->m_left = tmp->m_left; // hadi mamt2kdsh manha : ma3raftsh wash anakhud left ola right
            if (tmp->m_left)
                tmp->m_left->m_parent = tmp->m_parent;
            leftRotation(&tmp->m_parent);
            tmp->m_parent->m_black = false;
            tmp->m_parent->m_parent->m_black = true;
            tmp->m_parent->m_parent->m_right->m_black = false;
        }
        else if (!tmp->m_isLeftChild)
        {
            tmp->m_parent->m_right = tmp->m_right; // hadi mamt2kdsh manha : ma3raftsh wash anakhud left ola right
            if (tmp->m_right)
                tmp->m_right->m_parent = tmp->m_parent;
            rightRotation(&tmp->m_parent);
            tmp->m_parent->m_black = false;
            tmp->m_parent->m_parent->m_black = true;
            tmp->m_parent->m_parent->m_left->m_black = false;
        }
        delete (*node);
    }

    void caseThree(Node **node)
    {
        Node *tmp = *node;

        if (tmp->m_isLeftChild)
        {
            if ((!tmp->m_parent->m_right->m_left && !tmp->m_parent->m_right->m_right) ||
                (tmp->m_parent->m_right->m_left->m_black && tmp->m_parent->m_right->m_right->m_black))
            {
                tmp->m_parent->m_right->m_black = false;
                tmp->m_parent->m_black = true;
                delete (*node);
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
                    leftRotation(&tmp->m_parent);
                    tmp->m_parent->m_black = false;
                    tmp->m_parent->m_parent->m_black = true;
                    tmp->m_parent->m_parent->m_right->m_black = false;
                }
                else if (tmp->m_parent->m_right->m_left && !tmp->m_parent->m_right->m_left->m_black)
                {
                    tmp->m_parent->m_left = tmp->m_left; // hadi mamt2kdsh manha : ma3raftsh wash anakhud left ola right
                    if (tmp->m_left)
                        tmp->m_left->m_parent = tmp->m_parent;
                    rightLeftRotation(&tmp->m_parent);
                    tmp->m_parent->m_black = false;
                    tmp->m_parent->m_parent->m_black = true;
                    tmp->m_parent->m_parent->m_right->m_black = false;
                }
                delete (*node);
            }
        }
        else if (!tmp->m_isLeftChild)
        {
            if ((!tmp->m_parent->m_left->m_left && !tmp->m_parent->m_left->m_right) ||
                (tmp->m_parent->m_left->m_left->m_black && tmp->m_parent->m_left->m_right->m_black))
            {
                tmp->m_parent->m_left->m_black = false;
                tmp->m_parent->m_black = true;
                delete (*node);
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
                    rightRotation(&tmp->m_parent);
                    tmp->m_parent->m_black = false;
                    tmp->m_parent->m_parent->m_black = true;
                    tmp->m_parent->m_parent->m_left->m_black = false;
                }
                else if (tmp->m_parent->m_left->m_right && !tmp->m_parent->m_left->m_right->m_black)
                {
                    tmp->m_parent->m_right = tmp->m_right; // hadi mamt2kdsh manha : ma3raftsh wash anakhud left ola right
                    if (tmp->m_right)
                        tmp->m_right->m_parent = tmp->m_parent;
                    leftRightRotation(&tmp->m_parent);
                    tmp->m_parent->m_black = false;
                    tmp->m_parent->m_parent->m_black = true;
                    tmp->m_parent->m_parent->m_left->m_black = false;
                }
                delete (*node);
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
            std::cout << parent->m_key << ": " << parent->m_value << std::endl;
            if (parent->m_isLeftChild)
                std::cout << "Which Child: " << GREEN << "LEFT" << DEFAULT << std::endl;
            else if (!parent->m_isLeftChild)
                std::cout << "Which Child: " << GREEN << "RIGHT" << DEFAULT << std::endl;
            if (parent->m_black)
                std::cout << "Color: " << BLACK << "black" << DEFAULT << std::endl;
            else if (!parent->m_black)
                std::cout << "Color: " << RED << "Red" << DEFAULT << std::endl;
            print(parent->m_right);
        }
    }
};

#endif