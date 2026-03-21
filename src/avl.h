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

    AVLNode(TKey k, TValue v, AVLNode* l, AVLNode* r, AVLNode* p) {
    	balance = 0;
		key = k;
		value = v;
		left = l;
		right = r;
		parent = p;
	}
};


template <typename TKey, typename TValue>
class AVL : public BST<TKey, TValue, AVLNode<TKey, TValue>> {
private:
	using Node = AVLNode<TKey, TValue>;
	
	// возвращают новый "корень"
	AVLNode* LL(AVLNode* A) {
	    if ((A == nullptr) || (A->left == nullptr)) 
	    	return A;
	    
	    AVLNode* parent = A->parent;
	    AVLNode* B = A->left;
	    AVLNode* t2 = B->right;
	    
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
	
	
	AVLNode* RR(AVLNode* A) {
	    if ((A == nullptr) || (A->right == nullptr)) 
	    	return A;
	    
	    AVLNode* parent = A->parent;
	    AVLNode* B = A->right;
	    AVLNode* t2 = B->left;
	    
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
	

	AVLNode* LR(AVLNode* A) {
	    if ((A == nullptr) || (A->left == nullptr)) 
	    	return A;
	    
	    AVLNode* parent = A->parent;
	    AVLNode* B = A->left;
	    AVLNode* C = B->right;
	    AVLNode* t2 = C->left;
	    
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
		A->left = t2;
	    
	    if (t2)
	        t2->parent = A;

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

	
	AVLNode* RL(AVLNode* A) {
	    if ((A == nullptr) || (A->right == nullptr)) 
	    	return A;
	    
	    AVLNode* parent = A->parent;
	    AVLNode* B = A->right;
	    AVLNode* C = B->left;
	    AVLNode* t2 = C->left;
	    
	    if (parent != nullptr) {
	        if (parent->left == A)
	            parent->left = C;

	        else
	            parent->right = C;
	    }
	    
	    C->left = A;
		B->parent = C;
		C->right = B;
		A->parent = C;
		A->right = t2;
	    
	    if (t2)
	        t2->parent = A;

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


public:
	void Insert(const TKey& key, const TValue& value) override {
		std::stack<AVLNode*> nodes;

		if (root == nullptr) {
			root = new AVLNode(key, value, nullptr, nullptr, fictional);
			fictional->left = root;

			return;
		}

		AVLNode* current = root;

		while (current != nullptr) {
			nodes.push(current);

			if (key < current->key)
				current = current->left;

			else if (key > current->key)
				current = current->right;

			else {
				current->value = value;
				return;
			}
		}

		AVLNode* new_node = new AVLNode(key, value, nullptr, nullptr, nodes.top());

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
	    		AVLNode* new_root;

	    		if (current->left->balance == -1)
	    			new_root = LL(current);

	    		else if (current->left->balance == 1)
	    			new_root = LR(current);

	    		if (current == root) {
	    			fictional->left = new_root;
	    			root = new_root;
	    		}
	    	}

	    	else if (current->balance == 2) {
	    		AVLNode* new_root;

	    		if (current->right->balance == 1)
	    			new_root = RR(current);

	    		else if (current->right->balance == -1)
	    			new_root = RL(current);

	    		if (current == root) {
	    			fictional->left = new_root;
	    			root = new_root;
	    		}
	    	}
	    }
	}


	void Delete(const TKey& key) override {
		if (root == nullptr)
			throw "No node with this key";

		AVLNode* current = root;

		while ((current != nullptr) && (current->key != key)) {
			if (key < current->key)
				current = current->left;

			else if (key > current->key)
				current = current->right;
		}

		if (!current || (current->key != key))
			throw "No node with this key";


		TKey deleted_key;

		// случай: удаляемый узел - лист
		if (!current->left && !current->right) {
			AVLNode* parent = current->parent;
			deleted_key = current->key;

			delete current;
			current = parent;
		}

		// не лист
		else {
			AVLNode* next = GetNext(current);
			current->key = next->key;
			current->value = next->value;

			current = next->parent;

			deleted_key = next->key;
			delete next;
		}

		while (current != fictional) {
	    	if (current->key > deleted_key)
	    		current->balance--;

	    	else if (current->key < deleted_key)
	    		current->balance++;


	    	if (current->balance == -2) {
	    		AVLNode* new_root;

	    		if (current->left->balance == -1)
	    			new_root = LL(current);

	    		else if (current->left->balance == 1)
	    			new_root = LR(current);

	    		if (current == root) {
	    			fictional->left = new_root;
	    			root = new_root;
	    		}

	    		current = new_root;
	    	}

	    	else if (current->balance == 2) {
	    		AVLNode* new_root;

	    		if (current->right->balance == 1)
	    			new_root = RR(current);

	    		else if (current->right->balance == -1)
	    			new_root = RL(current);

	    		if (current == root) {
	    			fictional->left = new_root;
	    			root = new_root;
	    		}

	    		current = new_root;
	    	}

	    	current = current->parent;
	    }
	}
};
