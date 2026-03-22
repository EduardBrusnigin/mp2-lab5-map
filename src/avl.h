// AVL
// Brusnigin
#include <vector>
#include <stack>
#include <iostream>
#include "bst.h"

using namespace std;


template <typename TKey, typename TValue>
struct AVLNode : public BSTNode<TKey, TValue> {
    int balance;

    AVLNode(TKey k, TValue v, AVLNode* l, AVLNode* r, AVLNode* p) : BSTNode<TKey, TValue>(k, v, l, r, p), balance(0) {}
};


template <typename TKey, typename TValue>
class AVL : public BST<TKey, TValue, AVLNode<TKey, TValue>> {
private:
	using Node = AVLNode<TKey, TValue>;
	
	// возвращают новый "корень"
	Node* LL(Node* A) {
	    if ((A == nullptr) || (A->left == nullptr)) 
	    	return A;
	    
	    Node* parent = static_cast<Node*>(A->parent);
	    Node* B = static_cast<Node*>(A->left);
	    Node* t2 = static_cast<Node*>(B->right);
	    
	    if (parent != nullptr) {
	        if (parent->left == A)
	            parent->left = B;

	        else
	            parent->right = B;
	    }
	    
	    B->parent = parent;
	    B->right = A;
	    A->parent = B;
	    A->left = t2;
	    
	    if (t2)
	        t2->parent = A;

	    A->balance = 0;
		B->balance = 0;

		return B;
	}
	
	
	Node* RR(Node* A) {
	    if ((A == nullptr) || (A->right == nullptr)) 
	    	return A;
	    
	    Node* parent = static_cast<Node*>(A->parent);
	    Node* B = static_cast<Node*>(A->right);
	    Node* t2 = static_cast<Node*>(B->left);
	    
	    if (parent != nullptr) {
	        if (parent->left == A)
	            parent->left = B;

	        else
	            parent->right = B;
	    }
	    
	    B->parent = parent;
	    B->left = A;
	    A->parent = B;
	    A->right = t2;
	    
	    if (t2 != nullptr)
	        t2->parent = A;

	    A->balance = 0;
		B->balance = 0;

		return B;
	}
	

	Node* LR(Node* A) {
	    if ((A == nullptr) || (A->left == nullptr)) 
	    	return A;
	    
	    Node* parent = static_cast<Node*>(A->parent);
	    Node* B = static_cast<Node*>(A->left);
	    Node* C = static_cast<Node*>(B->right);
	    Node* t2 = static_cast<Node*>(C->left);
	    Node* t3 = static_cast<Node*>(C->right);
	    
	    if (parent != nullptr) {
	        if (parent->left == A)
	            parent->left = C;

	        else
	            parent->right = C;
	    }
	    
	    C->left = B;
		B->parent = C;
		C->right = A;
		A->parent = C;
		B->right = t2;
		A->left = t3;
	    
	    if (t2)
	        t2->parent = B;

	    if (t3)
	        t3->parent = A;

	    if (C->balance == 0) {
	    	A->balance = 0;
	    	B->balance = 0;
	    }

	    else if (C->balance == 1) {
	    	A->balance = 0;
	    	B->balance = -1;
	    }

	    else if (C->balance == -1) {
	    	A->balance = 1;
	    	B->balance = 0;
	    }

	    C->balance = 0;

	    return C;
	}

	
	Node* RL(Node* A) {
	    if ((A == nullptr) || (A->right == nullptr)) 
	    	return A;
	    
	    Node* parent = static_cast<Node*>(A->parent);
	    Node* B = static_cast<Node*>(A->right);
	    Node* C = static_cast<Node*>(B->left);
	    Node* t2 = static_cast<Node*>(C->left);
	    Node* t3 = static_cast<Node*>(C->right);
	    
	    if (parent != nullptr) {
	        if (parent->left == A)
	            parent->left = C;

	        else
	            parent->right = C;
	    }
	    
	    C->left = A;
		A->parent = C;
		C->right = B;
		B->parent = C;
		A->right = t2;
		B->left = t3;
	    
	    if (t2)
	        t2->parent = A;

	    if (t3)
	        t3->parent = B;

	    if (C->balance == 0) {
	    	A->balance = 0;
	    	B->balance = 0;
	    }

	    else if (C->balance == 1) {
	    	A->balance = -1;
	    	B->balance = 0;
	    }

	    else if (C->balance == -1) {
	    	A->balance = 0;
	    	B->balance = 1;
	    }

	    C->balance = 0;

	    return C;
	}


	Node* GetNext(Node* x) const {
		return BST<TKey, TValue, Node>::GetNext(x);
	}


	Node* GetMinimal() const {
		return BST<TKey, TValue, Node>::GetMinimal();
	}


	int get_height(const Node* n) {
	    if (n == nullptr)
	        return 0;
	    
	    int left = get_height(static_cast<Node*>(n->left));
	    int right = get_height(static_cast<Node*>(n->right));
	    
	    if (left > right)
	    	return 1 + left;

	    else
	    	return 1 + right;
	}

	int get_balance(const Node* n) {
	    if (n == nullptr)
	        return 0;
	    
	    return get_height(static_cast<Node*>(n->right)) - get_height(static_cast<Node*>(n->left));
	}


public:
	AVL() : BST<TKey, TValue, AVLNode<TKey, TValue>>() {}
	AVL(vector<pair<TKey, TValue>> v) : BST<TKey, TValue, AVLNode<TKey, TValue>>(v) {}


	void Insert(const TKey& key, const TValue& value) override {
		std::stack<Node*> nodes;

		if (this->root == nullptr) {
			this->root = new Node(key, value, nullptr, nullptr, this->fictional);
			this->fictional->left = this->root;

			return;
		}

		Node* current = this->root;

		while (current != nullptr) {
			nodes.push(current);

			if (key < current->key)
				current = static_cast<Node*>(current->left);

			else if (key > current->key)
				current = static_cast<Node*>(current->right);

			else {
				current->value = value;
				return;
			}
		}

		Node* new_node = new Node(key, value, nullptr, nullptr, nodes.top());

		if (key < nodes.top()->key)
	        nodes.top()->left = new_node;

	    else
	        nodes.top()->right = new_node;


	    while (!nodes.empty()) {
	    	current = nodes.top();
	    	nodes.pop();

	    	if (current->key > key)
	    		current->balance--;

	    	else if (current->key < key)
	    		current->balance++;


	    	if (current->balance == -2) {
	    		Node* new_root;

	    		if (static_cast<Node*>(current->left)->balance == -1)
	    			new_root = LL(current);

	    		else if (static_cast<Node*>(current->left)->balance == 1)
	    			new_root = LR(current);

	    		if (current == this->root) {
	    			this->fictional->left = new_root;
	    			this->root = new_root;
	    		}
	    	}

	    	else if (current->balance == 2) {
	    		Node* new_root;

	    		if (static_cast<Node*>(current->right)->balance == 1)
	    			new_root = RR(current);

	    		else if (static_cast<Node*>(current->right)->balance == -1)
	    			new_root = RL(current);

	    		if (current == this->root) {
	    			this->fictional->left = new_root;
	    			this->root = new_root;
	    		}
	    	}
	    }
	}


	void Delete(const TKey& key) override {
		if (this->root == nullptr)
			throw "No node with this key";

		Node* current = this->root;

		while ((current != nullptr) && (current->key != key)) {
			if (key < current->key)
				current = static_cast<Node*>(current->left);

			else if (key > current->key)
				current = static_cast<Node*>(current->right);
		}

		if (!current || (current->key != key))
			throw "No node with this key";


		TKey deleted_key;

		// случай: удаляемый узел - лист
		if (!current->left && !current->right) {
			Node* parent = static_cast<Node*>(current->parent);
			deleted_key = current->key;

			delete current;
			current = parent;
		}

		// не лист
		else {
			Node* next = GetNext(current);
			current->key = next->key;
			current->value = next->value;

			current = static_cast<Node*>(next->parent);

			deleted_key = next->key;
			delete next;
		}

		while (current != this->fictional) {
	    	if (current->key > deleted_key)
	    		current->balance--;

	    	else if (current->key < deleted_key)
	    		current->balance++;


	    	if (current->balance == -2) {
	    		Node* new_root;

	    		if (static_cast<Node*>(current->left)->balance == -1)
	    			new_root = LL(current);

	    		else if (static_cast<Node*>(current->left)->balance == 1)
	    			new_root = LR(current);

	    		if (current == this->root) {
	    			this->fictional->left = new_root;
	    			this->root = new_root;
	    		}

	    		current = new_root;
	    	}

	    	else if (current->balance == 2) {
	    		Node* new_root;

	    		if (static_cast<Node*>(current->right)->balance == 1)
	    			new_root = RR(current);

	    		else if (static_cast<Node*>(current->right)->balance == -1)
	    			new_root = RL(current);

	    		if (current == this->root) {
	    			this->fictional->left = new_root;
	    			this->root = new_root;
	    		}

	    		current = new_root;
	    	}

	    	current = static_cast<Node*>(current->parent);
	    }
	}


	const TKey& GetNext(const TKey& key) const {
	    return BST<TKey, TValue, Node>::GetNext(key);
	}


	bool is_avl() {
		if (this->root == nullptr)
			return true;

		if (!this->is_bst())
			return false;


		Node* current = GetMinimal();
	 
		while (current != static_cast<Node*>(this->fictional)) {
			int b = get_balance(current);

			if (current->balance != b)
				return false;

			if ((b != -1) && (b != 0) && (b != 1))
				return false;

			current = GetNext(current);
		}

		return true;
	}
};
