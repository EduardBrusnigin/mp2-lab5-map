// AVL
// Brusnigin
#include <vector>
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
	    if ((A == nullptr) || (static_cast<Node*>(A->left) == nullptr)) 
	    	return A;
	    
	    Node* parent = static_cast<Node*>(A->parent);
	    Node* B = static_cast<Node*>(A->left);
	    Node* t2 = static_cast<Node*>(B->right);
	    
	    if (parent != nullptr) {
	        if (parent->left == A)
	            parent->left = B;

	        else
	            parent->right = B;

	        B->parent = parent;
	    }
	    
	    B->parent = parent;
	    B->right = A;
	    A->parent = B;
	    A->left = t2;
	    
	    if (t2)
	        t2->parent = A;

	    //A->balance = 0;
		//B->balance = 0;
		if (B->balance == 0) {
		    A->balance = 1;
		    B->balance = -1;
		} 

		else {
		    A->balance = 0;
		    B->balance = 0;
		}

		return B;
	}
	
	
	Node* RR(Node* A) {
	    if ((A == nullptr) || (static_cast<Node*>(A->right) == nullptr)) 
	    	return A;
	    
	    Node* parent = static_cast<Node*>(A->parent);
	    Node* B = static_cast<Node*>(A->right);
	    Node* t2 = static_cast<Node*>(B->left);
	    
	    if (parent != nullptr) {
	        if (parent->left == A)
	            parent->left = B;

	        else
	            parent->right = B;

	        B->parent = parent;
	    }
	    
	    B->parent = parent;
	    B->left = A;
	    A->parent = B;
	    A->right = t2;
	    
	    if (t2 != nullptr)
	        t2->parent = A;

	    //A->balance = 0;
		//B->balance = 0;

		if (B->balance == 0) {
		    A->balance = -1;
		    B->balance = 1;
		} 

		else {
		    A->balance = 0;
		    B->balance = 0;
		}

		return B;
	}
	

	Node* LR(Node* A) {
	    if ((A == nullptr) || (static_cast<Node*>(A->left) == nullptr)) 
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

	        C->parent = parent;
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

	    if (!t2 && !t3)
	    	parent->balance++;

	    return C;
	}

	
	Node* RL(Node* A) {
	    if ((A == nullptr) || (static_cast<Node*>(A->right) == nullptr)) 
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

	        C->parent = parent;
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

	    if (!t2 && !t3)
	    	parent->balance++;
	    //parent->balance = get_balance(parent);																																																	

	    //this->Print();

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

	virtual void print(Node* n) {
		if (n == nullptr) 
			return;

		print(static_cast<Node*>(n->left));
		//cout << "[" << n->key << ", " << n->value << "]" << endl;  // release
		if (n == static_cast<Node*>(this->root)) {
			if (n->left && n->right)
				cout << "(Key: " << n->key << ", Value: " << n->value << ", left: " << n->left->key << ", right: " << n->right->key << ", balance: " << n->balance << ") - root" << endl;
			
			else if (n->right)
				cout << "(Key: " << n->key << ", Value: " << n->value << ", left: -, right: " << n->right->key << ", balance: " << n->balance << ") - root" << endl;
			
			else if (n->left)
    			cout << "(Key: " << n->key << ", Value: " << n->value << ", left: " << n->left->key << ", right: -, balance: " << n->balance << ") - root" << endl;

			else
				cout << "(Key: " << n->key << ", Value: " << n->value << ", left: -, right: -, balance: " << n->balance << ") - root" << endl;
		} 
		
		else {
			if (n->left && n->right)
				cout << "(Key: " << n->key << ", Value: " << n->value << ", Parent (key): " << n->parent->key << ", left: " << n->left->key << ", right: " << n->right->key << ", balance: " << n->balance << ")" << endl;

			else if (n->right)
				cout << "(Key: " << n->key << ", Value: " << n->value << ", Parent (key): " << n->parent->key << ", left: -, right: " << n->right->key << ", balance: " << n->balance << ")" << endl;
			
			else if (n->left)
    			cout << "(Key: " << n->key << ", Value: " << n->value << ", Parent (key): " << n->parent->key << ", left: " << n->left->key << ", right: -, balance: " << n->balance << ")" << endl;

			else
				cout << "(Key: " << n->key << ", Value: " << n->value << ", Parent (key): " << n->parent->key << ", left: -, right: -, balance: " << n->balance << ")" << endl;
		}  
		print(static_cast<Node*>(n->right));
	}


public:
	AVL() : BST<TKey, TValue, AVLNode<TKey, TValue>>() {}

	AVL(vector<pair<TKey, TValue>> v) {
		this->root = nullptr;
		this->fictional = new Node(TKey(), TValue(), this->root, nullptr, nullptr);

		for (auto p: v)
			Insert(p.first, p.second);
	}


	void Insert(const TKey& key, const TValue& value) override {
		if (this->root == nullptr) {
			this->root = new Node(key, value, nullptr, nullptr, static_cast<Node*>(this->fictional));
			this->fictional->left = this->root;

			return;
		}

		Node* current = this->root;
		Node* parent = nullptr;

		while (current != nullptr) {
			parent = current;

			if (key < current->key)
				current = static_cast<Node*>(current->left);

			else if (key > current->key)
				current = static_cast<Node*>(current->right);

			else {
				current->value = value;
				return;
			}
		}

		Node* new_node = new Node(key, value, nullptr, nullptr, parent);

		bool flag = false;
		bool flag2 = false;
		bool side;

		if (key < parent->key) {
			parent->left = new_node;
			side = false;

			if (parent->right)
				flag = true;
		}

		else {
			parent->right = new_node;
			side = true;

			if (parent->left)
				flag = true;
		}

		Node* prev = new_node;
		current = parent;


		if (flag) {
	    	if (current->key > key)
	    		current->balance--;

	    	else if (current->key < key)
	    		current->balance++;
    	}
    	

	    while (current != static_cast<Node*>(this->fictional)) {
	    	if (side == false) {
	    		if (current->right == prev) {
	    			if (current->balance == -1) {
	    				current->balance = 0;
	    				flag2 = true;
	    			}
	    		}

	    	}

	    	else {
	    		if (current->left == prev) {
	    			if (current->balance == 1) {
	    				current->balance = 0;
	    				flag2 = true;
	    			}
	    		}
	    	}

	    	if (!flag && !flag2) {
		    	if (current->key > key)
		    		current->balance--;

		    	else if (current->key < key)
		    		current->balance++;
	    	}



	    	if (current->balance == -2) {
	    		Node* new_root;

	    		if (static_cast<Node*>(current->left)->balance <= 0)
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

	    		if (static_cast<Node*>(current->right)->balance >= 0)
	    			new_root = RR(current);

	    		else if (static_cast<Node*>(current->right)->balance == -1)
	    			new_root = RL(current);

	    		if (current == this->root) {
	    			this->fictional->left = new_root;
	    			this->root = new_root;
	    		}

	    		current = new_root;
	    	}

	    	prev = current;
	    	current = static_cast<Node*>(current->parent);
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


		Node* target = current;

		if (target->left && target->right) { 
			Node* to_delete = static_cast<Node*>(target->right);

			while (to_delete->left)
				to_delete = static_cast<Node*>(to_delete->left);

			target->key = to_delete->key;
			target->value = to_delete->value;

			if (!target->right->right || !target->right->left)
				target->balance--;																																																																																																																																								

			Node* child = static_cast<Node*>(to_delete->right);

			if (child)
			    child->parent = static_cast<Node*>(to_delete->parent);

			if (static_cast<Node*>(to_delete->parent)->left == to_delete)
			    static_cast<Node*>(to_delete->parent)->left = child;

			else
			    static_cast<Node*>(to_delete->parent)->right = child;

			current = static_cast<Node*>(to_delete->parent);
			delete to_delete;
		}

		else {
		    Node* to_delete = target;
		    Node* parent = static_cast<Node*>(to_delete->parent);
		    Node* child; 

		    if (to_delete->left) {
		    	if (parent != static_cast<Node*>(this->fictional))
		    		parent->balance++;
		    	child = static_cast<Node*>(to_delete->left);
		    }

		    else {
		    	if (parent != static_cast<Node*>(this->fictional))
		    		parent->balance--;
		    	child = static_cast<Node*>(to_delete->right);
		    }
		    
		    if (to_delete == static_cast<Node*>(this->root))
		    	this->root = child;

		    if (child)
		        child->parent = parent;
		    
		    if (parent->left == to_delete)
		        parent->left = child;

		    else
		        parent->right = child;
		    
		    current = parent;
		    delete to_delete;
		}


		while (current != static_cast<Node*>(this->fictional)) {
			if (current->balance == -2) {						
				Node* new_root;

				if (static_cast<Node*>(current->left)->balance <= 0) {
					//cout << "LL\n";
					new_root = LL(current);
				}

				else {
					//cout << "LR\n";
					new_root = LR(current);
				}

				if (current == this->root) {
					this->root = new_root;
					this->fictional->left = new_root;
				}

				//current = new_root;
			}

			else if (current->balance == 2) {
				Node* new_root;

				if (static_cast<Node*>(current->right)->balance >= 0) {
					//cout << "RR\n";
					new_root = RR(current);
				}

				else {
					//cout << "RL\n";
					new_root = RL(current);
				}

				if (current == this->root) {
					this->root = new_root;
					this->fictional->left = new_root;
				}

				//current = new_root;
			}
			//this->Print();
			
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
