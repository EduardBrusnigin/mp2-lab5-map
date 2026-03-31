
#include <vector>
#include <iostream>
#include <utility>
#include <string>

using namespace std;

enum class Color { RED, BLACK };

template <typename TKey, typename TValue>
struct BSTNode
{
    TKey key;
    TValue value;
    BSTNode* left;
    BSTNode* right;
    BSTNode* parent;

    BSTNode(TKey k, TValue v, BSTNode* l, BSTNode* r, BSTNode* p)
    {
        key = k;
        value = v;
        left = l;
        right = r;
        parent = p;
    }

    virtual ~BSTNode() {}
};

template <typename TKey, typename TValue, typename TNode = BSTNode<TKey, TValue>>
class BST
{
protected:
    TNode* fictional;
    TNode* root;

    void print(TNode* n)
    {
        if (n == nullptr || n == fictional)
            return;

        print(static_cast<TNode*>(n->left));
        if (n == root) { cout << "(Key: " << n->key << ", Value: " << n->value << ") - root" << endl; }
        else { cout << "(Key: " << n->key << ", Value: " << n->value << ", Parent: " << n->parent->key << ")" << endl; }
        print(static_cast<TNode*>(n->right));
    }

    TNode* Search(const TKey& key) const
    {
        TNode* current = root;
        while (current != nullptr && current != fictional && current->key != key)
        {
            if (key < current->key)
                current = static_cast<TNode*>(current->left);
            else
                current = static_cast<TNode*>(current->right);
        }
        return (current == fictional) ? nullptr : current;
    }

    TNode* GetNext(TNode* x) const
    {
        if (x == nullptr || x == fictional) return fictional;
        TNode* y = nullptr;
        if (x->right != nullptr && x->right != fictional)
        {
            y = static_cast<TNode*>(x->right);
            while (y->left != nullptr && y->left != fictional)
                y = static_cast<TNode*>(y->left);
            return y;
        }
        else
        {
            y = static_cast<TNode*>(x->parent);
            while (y != nullptr && y != fictional && x == y->right)
            {
                x = y;
                y = static_cast<TNode*>(y->parent);
            }
            return (y == nullptr) ? fictional : y;
        }
    }

    TNode* GetMinimal(TNode* node) const
    {
        if (node == nullptr || node == fictional) return fictional;
        TNode* current = node;
        while (current->left != nullptr && current->left != fictional)
            current = static_cast<TNode*>(current->left);
        return current;
    }

public:
    BST()
    {
        root = nullptr;
        fictional = new TNode(TKey(), TValue(), nullptr, nullptr, nullptr);
    }

    virtual ~BST()
    {
        DeleteSubtree(root);
        delete fictional;
    }

    void DeleteSubtree(TNode* node)
    {
        if (node == nullptr || node == fictional) return;
        DeleteSubtree(static_cast<TNode*>(node->left));
        DeleteSubtree(static_cast<TNode*>(node->right));
        delete node;
    }

    virtual void Insert(const TKey& key, const TValue& value)
    {
        if (root == nullptr)
        {
            root = new TNode(key, value, nullptr, nullptr, fictional);
            fictional->left = root;
            return;
        }
        TNode* current = root;
        TNode* parent = fictional;
        while (current != nullptr && current != fictional)
        {
            parent = current;
            if (key < current->key) current = static_cast<TNode*>(current->left);
            else if (key > current->key) current = static_cast<TNode*>(current->right);
            else { current->value = value; return; }
        }
        TNode* newNode = new TNode(key, value, nullptr, nullptr, parent);
        if (key < parent->key) parent->left = newNode;
        else parent->right = newNode;
    }

    virtual void Delete(const TKey& key)

    {
        TNode* z = Search(key);
        if (!z) return;
        TNode* y = z;
        TNode* x = nullptr;
        if (z->left == nullptr || z->left == fictional) {
            x = static_cast<TNode*>(z->right);
            Transplant(z, x);
        }
        else if (z->right == nullptr || z->right == fictional) {
            x = static_cast<TNode*>(z->left);
            Transplant(z, x);
        }
        else {
            y = GetMinimal(static_cast<TNode*>(z->right));
            if (y->parent != z) {
                Transplant(y, static_cast<TNode*>(y->right));
                y->right = z->right;
                y->right->parent = y;
            }
            Transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
        }
        delete z;
    }

    void Transplant(TNode* u, TNode* v)
    {
        if (u->parent == fictional) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if (v != nullptr && v != fictional) v->parent = u->parent;
        if (u->parent == fictional) fictional->left = root;
    }

    bool is_bst()
    {
        if (!root) return true;
        TNode* curr = GetMinimal(root);
        TKey prevKey = curr->key;
        curr = GetNext(curr);
        while (curr != fictional) {
            if (curr->key <= prevKey) return false;
            prevKey = curr->key;
            curr = GetNext(curr);
        }
        return true;
    }

    TNode* GetRoot() const { return root; }
};

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
    using Node = RBNode<TKey, TValue>;
private:
    Color GetColor(Node* n) { return (n == nullptr || n == this->fictional) ? Color::BLACK : n->color; }

    void LeftRotate(Node* x)
    {
        Node* y = static_cast<Node*>(x->right);
        x->right = y->left;
        if (y->left != nullptr && y->left != this->fictional) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == this->fictional) { this->root = y; this->fictional->left = y; }
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void RightRotate(Node* y)
    {
        Node* x = static_cast<Node*>(y->left);
        y->left = x->right;
        if (x->right != nullptr && x->right != this->fictional) x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == this->fictional) { this->root = x; this->fictional->left = x; }
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void InsertFixup(Node* z)
    {
        while (GetColor(static_cast<Node*>(z->parent)) == Color::RED)
        {
            Node* p = static_cast<Node*>(z->parent);
            Node* g = static_cast<Node*>(p->parent);
            if (p == g->left)
            {
                Node* u = static_cast<Node*>(g->right);
                if (GetColor(u) == Color::RED) {
                    p->color = Color::BLACK; u->color = Color::BLACK; g->color = Color::RED; z = g;
                }
                else {
                    if (z == p->right) { z = p; LeftRotate(z); p = static_cast<Node*>(z->parent); g = static_cast<Node*>(p->parent); }
                    p->color = Color::BLACK; g->color = Color::RED; RightRotate(g);
                }
            }
            else {
                Node* u = static_cast<Node*>(g->left);
                if (GetColor(u) == Color::RED) {

                    p->color = Color::BLACK; u->color = Color::BLACK; g->color = Color::RED; z = g;
                }
                else {
                    if (z == p->left) { z = p; RightRotate(z); p = static_cast<Node*>(z->parent); g = static_cast<Node*>(p->parent); }
                    p->color = Color::BLACK; g->color = Color::RED; LeftRotate(g);
                }
            }
        }
        static_cast<Node*>(this->root)->color = Color::BLACK;
    }

    void DeleteFixup(Node* x, Node* xp)
    {
        while (x != this->root && GetColor(x) == Color::BLACK)
        {
            if (x == xp->left) {
                Node* w = static_cast<Node*>(xp->right);
                if (GetColor(w) == Color::RED) { w->color = Color::BLACK; xp->color = Color::RED; LeftRotate(xp); w = static_cast<Node*>(xp->right); }
                if (GetColor(static_cast<Node*>(w->left)) == Color::BLACK && GetColor(static_cast<Node*>(w->right)) == Color::BLACK) {
                    w->color = Color::RED; x = xp; xp = static_cast<Node*>(x->parent);
                }
                else {
                    if (GetColor(static_cast<Node*>(w->right)) == Color::BLACK) {
                        if (w->left) static_cast<Node*>(w->left)->color = Color::BLACK;
                        w->color = Color::RED; RightRotate(w); w = static_cast<Node*>(xp->right);
                    }
                    w->color = xp->color; xp->color = Color::BLACK;
                    if (w->right) static_cast<Node*>(w->right)->color = Color::BLACK;
                    LeftRotate(xp); x = static_cast<Node*>(this->root);
                }
            }
            else {
                Node* w = static_cast<Node*>(xp->left);
                if (GetColor(w) == Color::RED) { w->color = Color::BLACK; xp->color = Color::RED; RightRotate(xp); w = static_cast<Node*>(xp->left); }
                if (GetColor(static_cast<Node*>(w->right)) == Color::BLACK && GetColor(static_cast<Node*>(w->left)) == Color::BLACK) {
                    w->color = Color::RED; x = xp; xp = static_cast<Node*>(x->parent);
                }
                else {
                    if (GetColor(static_cast<Node*>(w->left)) == Color::BLACK) {
                        if (w->right) static_cast<Node*>(w->right)->color = Color::BLACK;
                        w->color = Color::RED; LeftRotate(w); w = static_cast<Node*>(xp->left);
                    }
                    w->color = xp->color; xp->color = Color::BLACK;
                    if (w->left) static_cast<Node*>(w->left)->color = Color::BLACK;
                    RightRotate(xp); x = static_cast<Node*>(this->root);
                }
            }
        }
        if (x) x->color = Color::BLACK;
    }

public:
    RBTree() : BST<TKey, TValue, RBNode<TKey, TValue>>() {}

    void Insert(const TKey& key, const TValue& value) override
    {
        Node* z = new Node(key, value, nullptr, nullptr, nullptr, Color::RED);
        Node* y = this->fictional;
        Node* x = static_cast<Node*>(this->root);
        while (x != nullptr && x != this->fictional) {
            y = x;
            if (z->key < x->key) x = static_cast<Node*>(x->left);
            else if (z->key > x->key) x = static_cast<Node*>(x->right);
            else { x->value = value; delete z; return; }
        }
        z->parent = y;
        if (y == this->fictional) { this->root = z; this->fictional->left = z; }
        else if (z->key < y->key) y->left = z;
        else y->right = z;
        InsertFixup(z);
    }

    void Delete(const TKey& key) override
    {
        Node* z = static_cast<Node*>(this->Search(key));
        if (!z) return;
        Node* x, * y = z;
        Node* xp;
        Color yoc = y->color;
        if (z->left == nullptr || z->left == this->fictional) {
            x = static_cast<Node*>(z->right); xp = static_cast<Node*>(z->parent); this->Transplant(z, x);

        }
        else if (z->right == nullptr || z->right == this->fictional) {
            x = static_cast<Node*>(z->left); xp = static_cast<Node*>(z->parent); this->Transplant(z, x);
        }
        else {
            y = static_cast<Node*>(this->GetMinimal(static_cast<Node*>(z->right)));
            yoc = y->color; x = static_cast<Node*>(y->right);
            if (y->parent == z) xp = y;
            else { xp = static_cast<Node*>(y->parent); this->Transplant(y, x); y->right = z->right; y->right->parent = y; }
            this->Transplant(z, y); y->left = z->left; y->left->parent = y; y->color = z->color;
        }
        delete z;
        if (yoc == Color::BLACK) DeleteFixup(x, xp);
    }

    bool is_rbt()
    {
        if (!this->root) return true;
        if (static_cast<Node*>(this->root)->color != Color::BLACK) return false;
        int bh = -1;
        return check_rbt(static_cast<Node*>(this->root), 0, bh);
    }

    bool check_rbt(Node* n, int cbh, int& ebh)
    {
        if (n == nullptr || n == this->fictional) {
            if (ebh == -1) ebh = cbh;
            return cbh == ebh;
        }
        if (n->color == Color::RED) {
            if (GetColor(static_cast<Node*>(n->left)) == Color::RED || GetColor(static_cast<Node*>(n->right)) == Color::RED) return false;
        }
        int nbh = cbh + (n->color == Color::BLACK ? 1 : 0);
        return check_rbt(static_cast<Node*>(n->left), nbh, ebh) && check_rbt(static_cast<Node*>(n->right), nbh, ebh);
    }
};