// AVL
// Brusnigin
#include <vector>
#include <iostream>
#include "bst.h"

using namespace std;


template <typename TKey, typename TValue>
struct AVLNode : public BSTNode<TKey, TValue> {
    size_t balance;

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

public:
	void Insert(const TKey& key, const TValue& value) override {

	}


	void Delete(const TKey& key) override {

	}
};
