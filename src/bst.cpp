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
	Delete(const TKey& val);
	TVal& Search(const TKey& key);
}

