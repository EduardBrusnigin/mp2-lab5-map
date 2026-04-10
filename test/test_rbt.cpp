
#include <gtest.h>
#include <vector>
#include <string>
#include <algorithm>
#include "rbt.h"

TEST(RBTTest, EmptyTree) {
    RBT<int, std::string> tree;

    EXPECT_TRUE(tree.isRBT());
}

TEST(RBTTest, SingleInsert) {
    RBT<int, std::string> tree;

    tree.Insert(10, "ten");

    EXPECT_TRUE(tree.isRBT());
}

TEST(RBTTest, MultipleInsert) {
    RBT<int, std::string> tree;

    tree.Insert(10, "ten");
    tree.Insert(20, "twenty");
    tree.Insert(30, "thirty");
    tree.Insert(15, "fifteen");
    tree.Insert(25, "twenty five");

    EXPECT_TRUE(tree.isRBT());
}

TEST(RBTTest, UpdateExistingKey) {
    RBT<int, std::string> tree;

    tree.Insert(10, "ten");
    tree.Insert(10, "TEN");

    EXPECT_TRUE(tree.isRBT());
}

TEST(RBTTest, InsertAscending) {
    RBT<int, int> tree;

    for (int i = 1; i <= 100; ++i) {
        tree.Insert(i, i * 10);
        EXPECT_TRUE(tree.isRBT());
    }
}

TEST(RBTTest, InsertDescending) {
    RBT<int, int> tree;

    for (int i = 100; i >= 1; --i) {
        tree.Insert(i, i * 10);
        EXPECT_TRUE(tree.isRBT());
    }
}

TEST(RBTTest, DeleteLeaf) {
    RBT<int, std::string> tree;

    tree.Insert(10, "ten");
    tree.Insert(20, "twenty");
    tree.Insert(30, "thirty");

    EXPECT_TRUE(tree.isRBT());

    tree.Delete(30);

    EXPECT_TRUE(tree.isRBT());
}

TEST(RBTTest, DeleteNodeWithOneChild) {
    RBT<int, std::string> tree;

    tree.Insert(20, "twenty");
    tree.Insert(10, "ten");
    tree.Insert(30, "thirty");
    tree.Insert(5, "five");

    EXPECT_TRUE(tree.isRBT());

    tree.Delete(10);

    EXPECT_TRUE(tree.isRBT());
}

TEST(RBTTest, DeleteNodeWithTwoChildren) {
    RBT<int, std::string> tree;

    tree.Insert(20, "twenty");
    tree.Insert(10, "ten");
    tree.Insert(30, "thirty");
    tree.Insert(5, "five");
    tree.Insert(15, "fifteen");

    EXPECT_TRUE(tree.isRBT());

    tree.Delete(10);

    EXPECT_TRUE(tree.isRBT());
}

TEST(RBTTest, DeleteRoot) {
    RBT<int, std::string> tree;

    tree.Insert(20, "twenty");
    tree.Insert(10, "ten");
    tree.Insert(30, "thirty");

    EXPECT_TRUE(tree.isRBT());

    tree.Delete(20);

    EXPECT_TRUE(tree.isRBT());
}

TEST(RBTTest, DeleteAll) {
    RBT<int, int> tree;

    for (int i = 1; i <= 50; ++i) {
        tree.Insert(i, i * 10);
    }

    EXPECT_TRUE(tree.isRBT());

    for (int i = 2; i <= 50; i += 2) {
        tree.Delete(i);
        EXPECT_TRUE(tree.isRBT());
    }

    for (int i = 1; i <= 50; i += 2) {
        tree.Delete(i);
        EXPECT_TRUE(tree.isRBT());
    }
}

TEST(RBTTest, DeleteNonExistent) {
    RBT<int, std::string> tree;

    tree.Insert(10, "ten");
    tree.Insert(20, "twenty");

    EXPECT_TRUE(tree.isRBT());

    tree.Delete(30); 

    EXPECT_TRUE(tree.isRBT());
}

TEST(RBTTest, InsertDeleteSequence) {
    RBT<int, int> tree;

    for (int i = 0; i < 20; ++i) {
        tree.Insert(i, i);
    }

    EXPECT_TRUE(tree.isRBT());

    for (int i = 0; i < 20; i += 2) {
        tree.Delete(i);
        EXPECT_TRUE(tree.isRBT());
    }

    for (int i = 20; i < 30; ++i) {
        tree.Insert(i, i);
        EXPECT_TRUE(tree.isRBT());
    }
}
TEST(RBTTest, ConstructorWithVector) {
    std::vector<std::pair<int, std::string>> data = {
        {5, "five"}, {3, "three"}, {7, "seven"}, {2, "two"},
        {4, "four"}, {6, "six"}, {8, "eight"}
    };

    RBT<int, std::string> tree(data);

    EXPECT_TRUE(tree.isRBT());
}

TEST(RBTTest, ComplexOperations) {
    RBT<int, int> tree;

    int values[] = { 50, 25, 75, 10, 30, 60, 90, 5, 15, 27, 35, 55, 65, 80, 95 };
    for (int v : values) {
        tree.Insert(v, v);
    }

    EXPECT_TRUE(tree.isRBT());

    tree.Delete(50);
    EXPECT_TRUE(tree.isRBT());

    tree.Delete(25);
    EXPECT_TRUE(tree.isRBT());

    tree.Delete(75);
    EXPECT_TRUE(tree.isRBT());

    int newValues[] = { 12, 28, 52, 72, 92 };
    for (int v : newValues) {
        tree.Insert(v, v);
        EXPECT_TRUE(tree.isRBT());
    }
}

TEST(RBTTest, DifferentTypes) {
    RBT<std::string, int> strTree;
    strTree.Insert("banana", 1);
    strTree.Insert("apple", 2);
    strTree.Insert("cherry", 3);

    EXPECT_TRUE(strTree.isRBT());

    RBT<double, std::string> doubleTree;
    doubleTree.Insert(3.14, "pi");
    doubleTree.Insert(2.71, "e");

    EXPECT_TRUE(doubleTree.isRBT());
}

TEST(RBTTest, GetNext) {
    RBT<int, std::string> tree;

    tree.Insert(5, "five");
    tree.Insert(3, "three");
    tree.Insert(7, "seven");
    tree.Insert(2, "two");
    tree.Insert(4, "four");
    tree.Insert(6, "six");
    tree.Insert(8, "eight");

    EXPECT_TRUE(tree.isRBT());

    EXPECT_EQ(tree.GetNext(2), 3);
    EXPECT_EQ(tree.GetNext(3), 4);
    EXPECT_EQ(tree.GetNext(4), 5);
    EXPECT_EQ(tree.GetNext(5), 6);
    EXPECT_EQ(tree.GetNext(6), 7);
    EXPECT_EQ(tree.GetNext(7), 8);
    EXPECT_THROW(tree.GetNext(8), const char*);
}

TEST(RBTTest, DeleteAllNodes) {
    RBT<int, int> tree;

    tree.Insert(10, 100);
    tree.Delete(10);

    EXPECT_TRUE(tree.isRBT());

    tree.Insert(20, 200);
    EXPECT_TRUE(tree.isRBT());
}

TEST(RBTTest, MultipleInsertDelete) {
    RBT<int, int> tree;

    for (int i = 1; i <= 100; ++i) {
        tree.Insert(i, i);
    }

    EXPECT_TRUE(tree.isRBT());

    for (int i = 3; i <= 100; i += 3) {
        tree.Delete(i);
    }

    EXPECT_TRUE(tree.isRBT());

    for (int i = 101; i <= 150; ++i) {
        tree.Insert(i, i);
    }

    EXPECT_TRUE(tree.isRBT());

    for (int i = 2; i <= 150; i += 2) {
        tree.Delete(i);
    }

    EXPECT_TRUE(tree.isRBT());
}

TEST(RBTTest, DuplicateKeys) {
    RBT<int, std::string> tree;

    for (int i = 0; i < 50; ++i) {
        tree.Insert(10, "value" + std::to_string(i));
        EXPECT_TRUE(tree.isRBT());
    }
}
