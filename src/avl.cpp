// AVL
// Brusnigin
#include <vector>
#include <iostream>

using namespace std;


template <typename TKey, typename TValue>
class AVL 
{
protected:
	struct AVLNode
	{
		TKey key;
		TValue value;
		AVLNode* left;
		AVLNode* right;
		AVLNode* parent;

		AVLNode(TKey k, TValue v, AVLNode* l, AVLNode* r, AVLNode* p) 
		{
			key = k;
			value = v;
			left = l;
			right = r;
			parent = p;
		}
	};

	AVLNode* fictional;
	AVLNode* root;

	void print(AVLNode* n) 
	{
		if (n == nullptr) 
			return;

		print(n->left);
		//cout << "[" << n->key << ", " << n->value << "]" << endl;  // release
		if (n == root) {cout << "(Key: " << n->key << ", Value: " << n->value << ") - root" << endl;} else if (n == fictional) {cout << "(Key: " << n->key << ", Value: " << n->value << ") - fictional" << endl;} else {cout << "(Key: " << n->key << ", Value: " << n->value << ", Parent (key): " << n->parent->key << ")" << endl;}  // debug
		print(n->right);
	}


	AVLNode* Search(const TKey& key) const
	{
		AVLNode* current = root;

		while (current != nullptr && current->key != key)
		{
			if (key < current->key)
				current = current->left;

			else if (key > current->key)
				current = current->right;
		}

		if (!current)
			throw "No node with this key";

		return current;
	}


	AVLNode* GetNext(AVLNode* x) const
	{
		AVLNode* y = nullptr;

		if (x->right == nullptr)
		{
			y = x->parent;

			while ((y != fictional) && (y->key < x->key))
			{
				x = y;
				y = x->parent;
			}

			if (y == fictional)
				throw "No next node for this node";

			return y;
		}

		else 
		{
			y = x->right;

			while (y->left != nullptr)
				y = y->left;

			return y;
		}
	}


	AVLNode* GetMinimal() const  // спуск к минимальной ноде
	{
		if (root == nullptr) 
			return nullptr;

		AVLNode* current = root;
		AVLNode* parent = nullptr;
		
		while (current != nullptr)
		{
			parent = current;
			current = current->left;
		}

		return parent;
	}


public:
	BST() 
	{	
		root = nullptr;
		fictional = new AVLNode(TKey(), TValue(), root, nullptr, nullptr);
	}


	BST(vector<pair<TKey, TValue>> v) 
	{
		root = nullptr;
		fictional = new AVLNode(TKey(), TValue(), root, nullptr, nullptr);

		for (auto p: v) 
		{	
			Insert(p.first, p.second);
		}
	}


	void Print() 
	{
		cout << "BST:" << endl;
		print(root);
	}


	void Insert(const TKey& key, const TValue& value) 
	{
		if (root == nullptr)
		{
			root = new AVLNode(key, value, nullptr, nullptr, fictional);
			fictional->left = root;

			return;
		}

		else
		{
			AVLNode* current = root;
			AVLNode* parent = nullptr;

			while (current != nullptr)
			{
				if (key < current->key)
				{
					parent = current;
					current = current->left;
				}

				else if (key > current->key)
				{
					parent = current;
					current = current->right;
				}

				else  // ключ совпал => просто перезаписываем значение, не создавая новый узел
				{
					current->value = value;

					return;
				}
			}

			AVLNode* new_node = new AVLNode(key, value, nullptr, nullptr, parent);

			if (key < parent->key)
		        parent->left = new_node;

		    else
		        parent->right = new_node;

			return;
		}
	}


	const TKey& GetNext(const TKey& key) const
	{
		AVLNode* x = Search(key);

		x = GetNext(x);

		return x->key;
	}


	TValue& operator[](const TKey& key) 
	{
		AVLNode* x = GetMinimal();

		if (x == nullptr)
			throw "No node with this key";

		// обход от минимального
		while (x->key != key) 
		{
			x = GetNext(x);
		}

		return x->value;
	}


	void Delete(const TKey& key)
	{
		AVLNode* x = Search(key);
		

		// случай 1 (отсутствуют дети)
		if (!(x->left) && !(x->right))
		{
			if (x->parent->left == x)
				x->parent->left = nullptr;

			else
				x->parent->right = nullptr;

			delete x;

			return;
		}


		// случай 2.1 (есть left child, нет right child)
		else if (x->left && !(x->right))
		{
			if (x->parent->left == x)
				x->parent->left = x->left;

			else
				x->parent->right = x->left;

			x->left->parent = x->parent;
			delete x;

			return;
		}


		// случай 2.2 (нет left child, есть right child)
		else if (!(x->left) && x->right)
		{
			if (x->parent->left == x)
				x->parent->left = x->right;

			else
				x->parent->right = x->right;

			x->right->parent = x->parent;
			delete x;

			return;
		}


		// случай 3 (есть оба потомка)
		// ищем successor (наименьший в правом поддереве)
		else
		{
			AVLNode* successor = x->right;

			while (successor->left != nullptr)
				successor = successor->left;

			x->key = successor->key;  // меняем значения "удаляемой" ноды 
		    x->value = successor->value;

		    Delete(successor->key);  // удаляем successor (случай 1 или 2)

			return;
		}
	}


	bool is_bst()  // проверка правильности
	{
	    if (root == nullptr)
	        return true;
	    
	    AVLNode* current = GetMinimal();
	    TKey prev_key = current->key;
	    
	    while (true) 
	    {	
	    	try 
	    	{
	        	current = GetNext(current);
	        }

	        catch (...) 
	        {
	        	return true;  // GetNext() даёт исключение, когда доходим до фиктивной ноды
	        }
	        
	        if (current->key <= prev_key)
	            return false;
	        
	        prev_key = current->key;
	    }
	}
};
