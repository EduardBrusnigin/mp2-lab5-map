// Red-Black Tree
// Zaplatkin
#include <vector>
#include <iostream>
#include <utility>

using namespace std;

enum class Color { RED, BLACK };

template <typename TKey, typename TValue>
struct RBNode : public BSTNode<TKey, TValue>
{
    Color color;

    RBNode(TKey k, TValue v, RBNode* l, RBNode* r, RBNode* p, Color c = Color::RED)
        : BSTNode<TKey, TValue>(k, v, l, r, p), color(c) {}
};

template <typename TKey, typename TValue>
class RBTree : public BST<TKey, TValue, RBNode<TKey, TValue>>
{
private:
    using Node = RBNode<TKey, TValue>;

    Color GetColor(Node* node) const
    {
        if (node == nullptr)
            return Color::BLACK;
        return node->color;
    }

    void SetColor(Node* node, Color color)
    {
        if (node != nullptr)
            node->color = color;
    }

    void LeftRotate(Node* x)
    {
        Node* y = static_cast<Node*>(x->right);
        x->right = y->left;

        if (y->left != nullptr)
            static_cast<Node*>(y->left)->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr) 
            this->root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void RightRotate(Node* y)
    {
        Node* x = static_cast<Node*>(y->left);
        y->left = x->right;

        if (x->right != nullptr)
            static_cast<Node*>(x->right)->parent = y;

        x->parent = y->parent;

        if (y->parent == nullptr)
            this->root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;

        x->right = y;
        y->parent = x;
    }

    void InsertFixup(Node* z)
    {
        while (z != this->root && GetColor(static_cast<Node*>(z->parent)) == Color::RED)
        {
            Node* parent = static_cast<Node*>(z->parent);
            Node* grandparent = static_cast<Node*>(parent->parent);

            if (parent == grandparent->left)
            {
                Node* uncle = static_cast<Node*>(grandparent->right);

                if (GetColor(uncle) == Color::RED)
                {
                    SetColor(parent, Color::BLACK);
                    SetColor(uncle, Color::BLACK);
                    SetColor(grandparent, Color::RED);
                    z = grandparent;
                }
                else
                {
                    if (z == parent->right)
                    {
                        z = parent;
                        LeftRotate(z);
                        parent = static_cast<Node*>(z->parent);
                        grandparent = static_cast<Node*>(parent->parent);
                    }

                    SetColor(parent, Color::BLACK);
                    SetColor(grandparent, Color::RED);
                    RightRotate(grandparent);
                }
            }
            else 
            {
                Node* uncle = static_cast<Node*>(grandparent->left);

                if (GetColor(uncle) == Color::RED)
                {
                    SetColor(parent, Color::BLACK);
                    SetColor(uncle, Color::BLACK);
                    SetColor(grandparent, Color::RED);
                    z = grandparent;
                }
                else
                {
                    if (z == parent->left)
                    {
                        z = parent;
                        RightRotate(z);
                        parent = static_cast<Node*>(z->parent);
                        grandparent = static_cast<Node*>(parent->parent);
                    }

                    SetColor(parent, Color::BLACK);
                    SetColor(grandparent, Color::RED);
                    LeftRotate(grandparent);
                }
            }
        }

        SetColor(static_cast<Node*>(this->root), Color::BLACK);
    }

    void DeleteFixup(Node* x)
    {
        while (x != this->root && GetColor(x) == Color::BLACK)
        {
            Node* parent = static_cast<Node*>(x->parent);



            if (x == parent->left)
            {
                Node* w = static_cast<Node*>(parent->right);

                if (GetColor(w) == Color::RED)
                {
                    SetColor(w, Color::BLACK);
                    SetColor(parent, Color::RED);
                    LeftRotate(parent);
                    w = static_cast<Node*>(parent->right);
                }

                if (GetColor(static_cast<Node*>(w->left)) == Color::BLACK &&
                    GetColor(static_cast<Node*>(w->right)) == Color::BLACK)
                {
                    SetColor(w, Color::RED);
                    x = parent;
                }
                else
                {
                    if (GetColor(static_cast<Node*>(w->right)) == Color::BLACK)
                    {
                        SetColor(static_cast<Node*>(w->left), Color::BLACK);
                        SetColor(w, Color::RED);
                        RightRotate(w);
                        w = static_cast<Node*>(parent->right);
                    }

                    SetColor(w, GetColor(parent));
                    SetColor(parent, Color::BLACK);
                    SetColor(static_cast<Node*>(w->right), Color::BLACK);
                    LeftRotate(parent);
                    x = static_cast<Node*>(this->root);
                }
            }
            else 
            {
                Node* w = static_cast<Node*>(parent->left); 

                if (GetColor(w) == Color::RED)
                {
                    SetColor(w, Color::BLACK);
                    SetColor(parent, Color::RED);
                    RightRotate(parent);
                    w = static_cast<Node*>(parent->left);
                }

                if (GetColor(static_cast<Node*>(w->right)) == Color::BLACK &&
                    GetColor(static_cast<Node*>(w->left)) == Color::BLACK)
                {
                    SetColor(w, Color::RED);
                    x = parent;
                }
                else
                {
                    if (GetColor(static_cast<Node*>(w->left)) == Color::BLACK)
                    {
                        SetColor(static_cast<Node*>(w->right), Color::BLACK);
                        SetColor(w, Color::RED);
                        LeftRotate(w);
                        w = static_cast<Node*>(parent->left);
                    }

                    SetColor(w, GetColor(parent));
                    SetColor(parent, Color::BLACK);
                    SetColor(static_cast<Node*>(w->left), Color::BLACK);
                    RightRotate(parent);
                    x = static_cast<Node*>(this->root);
                }
            }
        }

        SetColor(x, Color::BLACK);
    }

    void Transplant(Node* u, Node* v)
    {
        if (u->parent == nullptr)
            this->root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        if (v != nullptr)
            v->parent = u->parent;
    }

    Node* FindMinimum(Node* node) const
    {
        while (node->left != nullptr)
            node = static_cast<Node*>(node->left);
        return node;
    }

    void PrintNode(Node* n, int depth = 0)
    {
        if (n == nullptr)
            return;

        PrintNode(static_cast<Node*>(n->right), depth + 1);

        for (int i = 0; i < depth; i++)
            cout << " ";

        string color_str = (n->color == Color::RED) ? "R" : "B";
        cout << "[" << n->key << ", " << n->value << "] " << color_str;

        if (n == this->root)
            cout << " (root)";
        else if (n->parent != nullptr)
            cout << " (parent: " << n->parent->key << ")";

        cout << endl;

        PrintNode(static_cast<Node*>(n->left), depth + 1);
    }

    int CheckRBProperties(Node* node) const
    {
        if (node == nullptr)
            return 0;



        if (GetColor(node) == Color::RED)
        {
            if (GetColor(static_cast<Node*>(node->left)) == Color::RED ||
                GetColor(static_cast<Node*>(node->right)) == Color::RED)
                return -1;
        }

        int left_height = CheckRBProperties(static_cast<Node*>(node->left));
        int right_height = CheckRBProperties(static_cast<Node*>(node->right));

        if (left_height == -1 || right_height == -1)
            return -1;

        if (left_height != right_height)
            return -1;

        return left_height + (GetColor(node) == Color::BLACK ? 1 : 0);
    }

public:
    RBTree() : BST<TKey, TValue, RBNode<TKey, TValue>>()
    {
        delete this->fictional;
        this->fictional = nullptr;
        this->root = nullptr;
    }

    RBTree(vector<pair<TKey, TValue>> v) : BST<TKey, TValue, RBNode<TKey, TValue>>()
    {
        delete this->fictional;
        this->fictional = nullptr;
        this->root = nullptr;

        for (auto p : v)
        {
            Insert(p.first, p.second);
        }
    }

    ~RBTree()
    {
        DeleteSubtree(static_cast<Node*>(this->root));
    }

    void DeleteSubtree(Node* node)
    {
        if (node == nullptr)
            return;

        DeleteSubtree(static_cast<Node*>(node->left));
        DeleteSubtree(static_cast<Node*>(node->right));
        delete node;
    }

    void Insert(const TKey& key, const TValue& value) override
    {
        Node* z = new Node(key, value, nullptr, nullptr, nullptr, Color::RED);
        Node* y = nullptr;
        Node* x = static_cast<Node*>(this->root);

        while (x != nullptr)
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

        if (y == nullptr)
            this->root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;

        InsertFixup(z);
    }

    void Delete(const TKey& key) override
    {
        Node* z = static_cast<Node*>(this->Search(key));

        if (z == nullptr)
            return;

        Node* y = z;
        Node* x = nullptr;
        Color y_original_color = y->color;

        if (z->left == nullptr)
        {
            x = static_cast<Node*>(z->right);
            Transplant(z, static_cast<Node*>(z->right));
        }
        else if (z->right == nullptr)
        {
            x = static_cast<Node*>(z->left);
            Transplant(z, static_cast<Node*>(z->left));
        }
        else
        {
            y = FindMinimum(static_cast<Node*>(z->right));
            y_original_color = y->color;
            x = static_cast<Node*>(y->right);

            if (y->parent == z)
            {
                if (x != nullptr)
                    x->parent = y;
            }
            else
            {
                Transplant(y, static_cast<Node*>(y->right));
                y->right = z->right;
                y->right->parent = y;
            }

            Transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (y_original_color == Color::BLACK)
            DeleteFixup(x);
    }

    void Print()
    {
        cout << "Red-Black Tree (NIL leaves are black):" << endl;
        if (this->root == nullptr)
            cout << " Empty tree" << endl;
        else
            PrintNode(static_cast<Node*>(this->root));
    }

    bool is_rbt() const
    {
        if (static_cast<Node*>(this->root) == nullptr)
            return true;

        if (GetColor(static_cast<Node*>(this->root)) != Color::BLACK)
            return false;

        int black_height = CheckRBProperties(static_cast<Node*>(this->root));

        return black_height != -1;
    }



    int GetBlackHeight() const
    {
        if (this->root == nullptr)
            return 0;

        return CheckRBProperties(static_cast<Node*>(this->root));
    }
};