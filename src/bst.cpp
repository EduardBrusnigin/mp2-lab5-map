template <typename T>
class BST<TKey, TVal> {
private:
	struct Node {
		TKey k;
		TVal val;
		Node* left;
		Node* right;
		Node* parent;
	}

	Node* root;

public:
	Insert(const TKey& key, const TVal& value);
	Delete(const TKey& val)
	{
		Node cur = &root;
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
	TVal& Search(const TKey& key);
}

