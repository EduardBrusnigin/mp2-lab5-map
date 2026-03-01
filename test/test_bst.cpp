#include "gtest.h"
#include "bst.cpp"
#include <vector>
#include <utility>


TEST(BST, is_valid_default_constructor) 
{
    BST<int, double> bst;

    ASSERT_NO_THROW(bst);
}


TEST(BST, is_valid_constructor_by_vector) 
{
    vector<pair<int, double>> v = {{2, 2.1}, {1, 1.3}, {3, 3.4}, {4, 1.5}};
    BST<int, double> bst(v);

    EXPECT_NO_THROW(bst.Print());
}


TEST(BST, can_insert_node) 
{
    BST<int, double> bst;

    EXPECT_NO_THROW(bst.Insert(0, 3.14));
    EXPECT_NO_THROW(bst.Insert(1, 2.718));
    EXPECT_NO_THROW(bst.Insert(2, -9.123));
}


TEST(BST, can_print_nodes) 
{
    BST<int, double> bst;

    bst.Insert(0, 3.14);
    bst.Insert(1, 2.718);
    bst.Insert(2, -9.123);

    EXPECT_NO_THROW(bst.Print());
}


TEST(BST, can_get_next_node) 
{
    vector<pair<int, double>> v = {{3, 0}, {1, 0}, {5, 0}, {2, 0}, {7, 0}};

    BST<int, double> bst(v);
    EXPECT_NO_THROW(bst.Print());
    EXPECT_EQ(bst.GetNext(1), 2);
    EXPECT_EQ(bst.GetNext(5), 7);
    EXPECT_EQ(bst.GetNext(3), 5);
    EXPECT_EQ(bst.GetNext(2), 3);
    EXPECT_ANY_THROW(bst.GetNext(7));
}
