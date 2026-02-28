// BST
#include <vector>
#include <iostream>

using namespace std;


template <typename TKey, typename TValue>
class BST 
{
private:
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
	};

	BSTNode* fictional;
	BSTNode* root;

	void print(BSTNode* n) 
	{
		if (n == nullptr) 
			return;

		print(n->left);
		//cout << n->key << " - " << n->value << endl;  // release
		if (n == root) {cout << n->key << " - root" << endl;} else if (n == fictional) {cout << n->key << " - dummy" << endl;} else {cout << n->key << " - " << n->parent->key << endl;}   // debug
		print(n->right);
	}


public:
	BST() 
	{	
		root = nullptr;
		fictional = new BSTNode(TKey(), TValue(), root, nullptr, nullptr);
	}


	BST(vector<pair<TKey, TValue>> v) 
	{
		for (auto p: v) 
		{
			*this.Insert(p.first, p.second);
		}
	}


	void Print() 
	{
		cout << "BST:" << endl;
		print(root);
	}


	BSTNode* Insert(const TKey& key, const TValue& value) 
	{
		if (root == nullptr)
		{
			root = new BSTNode(key, value, nullptr, nullptr, fictional);
			fictional->left = root;

			return root;
		}

		else
		{
			BSTNode* current = root;
			BSTNode* parent = nullptr;

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

					return current;
				}
			}

			BSTNode* new_node = new BSTNode(key, value, nullptr, nullptr, parent);

			if (key < parent->key)
		        parent->left = new_node;

		    else
		        parent->right = new_node;

			return new_node;
		}
	}


	//BSTNode* GetNext(BSTNode* x) const
	//{
	//	if (x->right == nullptr)
	//	{
			//y = x->parent;

			//while (y != )
	//	}
	//}

	/*
	void Delete(const TKey& key)
	{
		Node* cur = root;

		while (cur->k != key && cur != nullptr)
		{
			if (key < cur->k)
			{
				cur = cur->left;
			}
			else
			{
				cur = cur->right;
			}
		}

		if (cur == nullptr)
		{
			throw "ne nashel :(";
		}

		if (cur.left == nullptr && cur.right == nullptr)
		{
			if (cur.parent.left == cur)
			{
				cur.parent.left = nullptr;
			}
			if (cur.parent.right == cur)
			{
				cur.parent.right = nullptr;
			}
		}

		if (cur.left != nullptr && cur.right == nullptr)
		{
			if (cur.parent.left == cur)
			{
				cur.parent.left = cur.left;
			}
			if (cur.parent.right == cur)
			{
				cur.parent.right = cur.left;
			}
		}

		if (cur.left == nullptr && cur.right != nullptr)
		{
			if (cur.parent.left == cur)
			{
				cur.parent.left = cur.right;
			}
			if (cur.parent.right == cur)
			{
				cur.parent.right = cur.right;
			}
		}

		if (cur.left != nullptr && cur.right != nullptr)
		{
			if (cur.parent.left == cur)
			{
				Node* somepart = cur.right;
				if (somepart.left == nullptr)
				{
					somepart.left = cur.left;
					cur.parent.left = somepart;
				}
				else
				{
					while (somepart.left != nullptr)
					{
						somepart = somepart.left;
					}
					somepart.left = cur.left;
					somepart.parent.left = somepart.right;
					somepart.right = cur.right;
					cur.parent.left = somepart;
				}
			}

			if (cur.parent.right == cur)
			{
				Node* somepart = cur.left
					if (somepart.right == nullptr)
					{
						somepart.right = cur.right;
						cur.parent.right = somepart;
					}
					else
					{
						while (somepart.right != nullptr)
						{
							somepart = somepart.right;
						}
						somepart.right = cur.right;
						somepart.parent.right = somepart.left;
						somepart.left = cur.left;
						cur.parent.right = somepart;
					}
			}
		}
	}

	TValue& operator[](const TKey& key) 
	{

	}*/
};
