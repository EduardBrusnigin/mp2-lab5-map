
#include "bst.h"

enum class Color { RED, BLACK };

template <typename TKey, typename TValue>
struct RBTNode : public BSTNode<TKey, TValue>
{
    Color color;

    RBTNode(TKey k, TValue v, RBTNode* l = nullptr, RBTNode* r = nullptr, RBTNode* p = nullptr, Color c = Color::RED)
        : BSTNode<TKey, TValue>(k, v, l, r, p), color(c) {}
};

template <typename TKey, typename TValue>
class RBT : public BST<TKey, TValue, RBTNode<TKey, TValue>>
{
private:
    using Node = RBTNode<TKey, TValue>;
    using Base = BST<TKey, TValue, Node>;

    Node* nil;  
    Node*& root;

    void leftRotate(Node* x)
    {
        Node* y = static_cast<Node*>(x->right);  
        x->right = y->left;                       

        if (y->left != nil)
            y->left->parent = x;

        y->parent = x->parent;                    

        if (x->parent == nil)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;                              
        x->parent = y;
    }

    void rightRotate(Node* y)
    {
        Node* x = static_cast<Node*>(y->left);    
        y->left = x->right;                        

        if (x->right != nil)
            x->right->parent = y;

        x->parent = y->parent;                     

        if (y->parent == nil)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;

        x->right = y;                              
        y->parent = x;
    }

    void rbInsertFixup(Node* z)
    {
        while (static_cast<Node*>(z->parent)->color == Color::RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                Node* y = static_cast<Node*>(z->parent->parent->right);

                if (y->color == Color::RED)
                {
                    static_cast<Node*>(z->parent)->color = Color::BLACK;      
                    y->color = Color::BLACK;                                   
                    static_cast<Node*>(z->parent->parent)->color = Color::RED; 
                    z = static_cast<Node*>(z->parent->parent);                 
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = static_cast<Node*>(z->parent);  
                        leftRotate(z);                       
                    }

                    static_cast<Node*>(z->parent)->color = Color::BLACK;       
                    static_cast<Node*>(z->parent->parent)->color = Color::RED; 
                    rightRotate(static_cast<Node*>(z->parent->parent));       
                }
            }
            else
            {
                Node* y = static_cast<Node*>(z->parent->parent->left);

                if (y->color == Color::RED)
                {
                    static_cast<Node*>(z->parent)->color = Color::BLACK;      
                    y->color = Color::BLACK;                                   
                    static_cast<Node*>(z->parent->parent)->color = Color::RED; 
                    z = static_cast<Node*>(z->parent->parent);                 
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = static_cast<Node*>(z->parent);  
                        rightRotate(z);                      
                    }

                    static_cast<Node*>(z->parent)->color = Color::BLACK;      
                    static_cast<Node*>(z->parent->parent)->color = Color::RED; 
                    leftRotate(static_cast<Node*>(z->parent->parent));         
                }
            }
        }

        root->color = Color::BLACK;
    }

    void rbDeleteFixup(Node* x)
    {
        while (x != root && x->color == Color::BLACK)
        {
            if (x == x->parent->left)
            {
                Node* w = static_cast<Node*>(x->parent->right);

                if (w->color == Color::RED)
                {
                    w->color = Color::BLACK;                                   
                    static_cast<Node*>(x->parent)->color = Color::RED;         
                    leftRotate(static_cast<Node*>(x->parent));                 
                    w = static_cast<Node*>(x->parent->right);                  
                }

                if (static_cast<Node*>(w->left)->color == Color::BLACK &&
                    static_cast<Node*>(w->right)->color == Color::BLACK)
                {
                    w->color = Color::RED;                                     
                    x = static_cast<Node*>(x->parent);                         
                }
                else
                {
                    if (static_cast<Node*>(w->right)->color == Color::BLACK)
                    {
                        static_cast<Node*>(w->left)->color = Color::BLACK;     
                        w->color = Color::RED;                                 
                        rightRotate(w);                                        
                        w = static_cast<Node*>(x->parent->right);              
                    }

                    w->color = static_cast<Node*>(x->parent)->color;           
                    static_cast<Node*>(x->parent)->color = Color::BLACK;       
                    static_cast<Node*>(w->right)->color = Color::BLACK;        
                    leftRotate(static_cast<Node*>(x->parent));                 
                    x = root;                                                  
                }
            }
            else 
            {
                Node* w = static_cast<Node*>(x->parent->left);

                if (w->color == Color::RED)
                {
                    w->color = Color::BLACK;                                   
                    static_cast<Node*>(x->parent)->color = Color::RED;         
                    rightRotate(static_cast<Node*>(x->parent));                
                    w = static_cast<Node*>(x->parent->left);                   
                }

                if (static_cast<Node*>(w->right)->color == Color::BLACK &&
                    static_cast<Node*>(w->left)->color == Color::BLACK)
                {
                    w->color = Color::RED;                                     
                    x = static_cast<Node*>(x->parent);                         
                }
                else
                {
                    if (static_cast<Node*>(w->left)->color == Color::BLACK)
                    {
                        static_cast<Node*>(w->right)->color = Color::BLACK;    
                        w->color = Color::RED;                                 
                        leftRotate(w);                                         
                        w = static_cast<Node*>(x->parent->left);               
                    }

                    w->color = static_cast<Node*>(x->parent)->color;           
                    static_cast<Node*>(x->parent)->color = Color::BLACK;       
                    static_cast<Node*>(w->left)->color = Color::BLACK;         
                    rightRotate(static_cast<Node*>(x->parent));                
                    x = root;                                                  
                }
            }
        }

        x->color = Color::BLACK;
    }

    Node* treeMinimum(Node* x) const
    {
        while (x->left != nil)
            x = static_cast<Node*>(x->left);
        return x;
    }

    int checkBlackHeight(Node* node) const
    {
        if (node == nil)
            return 1;

        int leftHeight = checkBlackHeight(static_cast<Node*>(node->left));
        int rightHeight = checkBlackHeight(static_cast<Node*>(node->right));

        if (leftHeight == -1 || rightHeight == -1 || leftHeight != rightHeight)
            return -1;

        return leftHeight + (node->color == Color::BLACK ? 1 : 0);
    }

    bool checkRedProperty(Node* node) const
    {
        if (node == nil)
            return true;

        if (node->color == Color::RED)
        {
            if (static_cast<Node*>(node->left)->color == Color::RED ||
                static_cast<Node*>(node->right)->color == Color::RED)
                return false;
        }

        return checkRedProperty(static_cast<Node*>(node->left)) &&
            checkRedProperty(static_cast<Node*>(node->right));
    }

    bool checkBSTProperty(Node* node, const TKey* minKey, const TKey* maxKey) const
    {
        if (node == nil)
            return true;

        if ((minKey != nullptr && node->key <= *minKey) ||
            (maxKey != nullptr && node->key >= *maxKey))
            return false;

        return checkBSTProperty(static_cast<Node*>(node->left), minKey, &(node->key)) &&
            checkBSTProperty(static_cast<Node*>(node->right), &(node->key), maxKey);
    }

    void deleteTree(Node* node)
    {
        if (node == nil)
            return;
        deleteTree(static_cast<Node*>(node->left));
        deleteTree(static_cast<Node*>(node->right));
        delete node;
    }

public:
    RBT() : Base(), root(Base::root)
    {
        nil = new Node(TKey(), TValue(), nullptr, nullptr, nullptr, Color::BLACK);
        Base::fictional = nil;
        root = nil;
    }

    RBT(std::vector<std::pair<TKey, TValue>> v) : Base(), root(Base::root)
    {
        nil = new Node(TKey(), TValue(), nullptr, nullptr, nullptr, Color::BLACK);
        Base::fictional = nil;
        root = nil;

        for (auto p : v)
        {
            Insert(p.first, p.second);
        }
    }

    ~RBT()
    {
        deleteTree(root);
        delete nil;
    }
void Insert(const TKey& key, const TValue& value) override
    {
        Node* z = new Node(key, value, nil, nil, nil, Color::RED);
        Node* y = nil;
        Node* x = root;

        while (x != nil)
        {
            y = x;
            if (z->key < x->key)
                x = static_cast<Node*>(x->left);
            else if (z->key > x->key)
                x = static_cast<Node*>(x->right);
            else
            {
                x->value = value;
                delete z;
                return;
            }
        }

        z->parent = y;

        if (y == nil)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;

        rbInsertFixup(z);
    }

    void Delete(const TKey& key) override
    {
        Node* z = static_cast<Node*>(Base::Search(key));

        if (z == nullptr || z == nil)
            return;

        Node* y = z;
        Node* x = nullptr;
        Color yOriginalColor = y->color;

        if (z->left == nil)
        {
            x = static_cast<Node*>(z->right);

            if (z->parent == nil)
                root = x;
            else if (z == z->parent->left)
                z->parent->left = x;
            else
                z->parent->right = x;

            x->parent = z->parent;

            delete z;
        }
        else if (z->right == nil)
        {
            x = static_cast<Node*>(z->left);

            if (z->parent == nil)
                root = x;
            else if (z == z->parent->left)
                z->parent->left = x;
            else
                z->parent->right = x;

            x->parent = z->parent;

            delete z;
        }
        else
        {
            y = treeMinimum(static_cast<Node*>(z->right));
            yOriginalColor = y->color;
            x = static_cast<Node*>(y->right);

            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                if (y->parent->left == y)
                    y->parent->left = x;
                else
                    y->parent->right = x;

                x->parent = y->parent;

                y->right = z->right;
                static_cast<Node*>(y->right)->parent = y;
            }

            if (z->parent == nil)
                root = y;
            else if (z == z->parent->left)
                z->parent->left = y;
            else
                z->parent->right = y;

            y->parent = z->parent;
            y->left = z->left;
            static_cast<Node*>(y->left)->parent = y;
            y->color = z->color;

            delete z;
        }

        if (yOriginalColor == Color::BLACK)
            rbDeleteFixup(x);
    }

    bool isRBT() const
    {

        if (root != nil && root->color != Color::BLACK)
            return false;

        if (nil->color != Color::BLACK)
            return false;

        if (!checkRedProperty(root))
            return false;

        if (checkBlackHeight(root) == -1)
            return false;

        if (!checkBSTProperty(root, nullptr, nullptr))
            return false;

        return true;
    }
};
