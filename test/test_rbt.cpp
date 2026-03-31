
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <functional>
#include "rbt.h"

TEST(RBTreeTest, RootIsAlwaysBlack) {
    RBTree<int, int> tree;
    EXPECT_TRUE(tree.is_rbt());

    tree.Insert(10, 10);
    EXPECT_EQ(static_cast<RBNode<int, int>*>(tree.GetRoot())->color, Color::BLACK);
    EXPECT_TRUE(tree.is_rbt());
}

TEST(RBTreeTest, DuplicateKeyUpdatesValue) {
    RBTree<int, std::string> tree;
    tree.Insert(10, "old");
    tree.Insert(20, "other");
    tree.Insert(10, "new");

    RBNode<int, std::string>* found_node = static_cast<RBNode<int, std::string>*>(tree.Search(10));
    ASSERT_NE(found_node, nullptr);
    EXPECT_EQ(found_node->value, "new");
    EXPECT_TRUE(tree.is_rbt());
}

TEST(RBTreeTest, SequentialInsertBalance) {
    RBTree<int, int> tree;
    for (int i = 1; i <= 50; ++i) {
        tree.Insert(i, i);
        ASSERT_TRUE(tree.is_rbt()) << "Failed RBT property at insertion of " << i;
    }
    EXPECT_TRUE(tree.is_bst());
}

TEST(RBTreeTest, ReverseSequentialInsert) {
    RBTree<int, int> tree;
    for (int i = 50; i >= 1; --i) {
        tree.Insert(i, i);
        ASSERT_TRUE(tree.is_rbt()) << "Failed RBT property at reverse insertion of " << i;
    }
    EXPECT_TRUE(tree.is_bst());
}

TEST(RBTreeTest, ParentPointerIntegrity) {
    RBTree<int, int> tree;
    std::vector<int> vals = { 40, 20, 60, 10, 30, 50, 70 };
    for (int v : vals) tree.Insert(v, v);

    std::function<void(BSTNode<int, int>*)> check_parents =
        [&](BSTNode<int, int>* node) {
        if (!node || node == tree.fictional) return;

        if (node->left && node->left != tree.fictional) {
            EXPECT_EQ(node->left->parent, node) << "Left child " << node->left->key << " has wrong parent";
            check_parents(node->left);
        }
        if (node->right && node->right != tree.fictional) {
            EXPECT_EQ(node->right->parent, node) << "Right child " << node->right->key << " has wrong parent";
            check_parents(node->right);
        }
        };
    check_parents(tree.GetRoot());
}

TEST(RBTreeTest, ComplexDeletion) {
    RBTree<int, int> tree;
    std::vector<int> vals = { 13, 8, 17, 1, 11, 15, 25, 6, 22, 27 };
    for (int v : vals) tree.Insert(v, v);

    tree.Delete(6);
    EXPECT_TRUE(tree.is_rbt());

    tree.Delete(1);
    EXPECT_TRUE(tree.is_rbt());

    tree.Delete(17);
    EXPECT_TRUE(tree.is_rbt());

    tree.Delete(13);
    EXPECT_TRUE(tree.is_rbt());
    EXPECT_TRUE(tree.is_bst());
}

TEST(RBTreeTest, ClearTreeByDeletion) {
    RBTree<int, int> tree;
    std::vector<int> vals = { 10, 20, 30, 40, 50 };
    for (int v : vals) tree.Insert(v, v);

    for (int v : vals) {
        tree.Delete(v);
        EXPECT_TRUE(tree.is_rbt());
    }
    EXPECT_EQ(tree.GetRoot(), nullptr);
}

TEST(RBTreeTest, RandomMixedOperations) {
    RBTree<int, int> tree;
    std::vector<int> data;
    const int count = 200;

    std::mt19937 rng(42);

    for (int i = 0; i < count; ++i) {
        int val = rng() % 1000;
        data.push_back(val);
        tree.Insert(val, val);
    }
    ASSERT_TRUE(tree.is_rbt());

    std::shuffle(data.begin(), data.end(), rng);

    for (int i = 0; i < count / 2; ++i) {
        tree.Delete(data[i]);
        ASSERT_TRUE(tree.is_rbt()) << "Failed RBT property after deleting " << data[i];
    }
    EXPECT_TRUE(tree.is_bst());
}

TEST(RBTreeTest, GetNextConsistency) {
    RBTre

        e<int, int> tree;
    std::vector<int> vals = { 15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9 };
    for (int v : vals) tree.Insert(v, v);

    std::sort(vals.begin(), vals.end());

    for (size_t i = 0; i < vals.size() - 1; ++i) {
        EXPECT_EQ(tree.GetNext(vals[i]), vals[i + 1]) << "GetNext failed for key " << vals[i];
    }
    EXPECT_EQ(tree.GetNext(vals.back()), TKey());
}