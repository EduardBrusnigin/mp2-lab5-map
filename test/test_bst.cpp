#include "gtest.h"
#include "bst.cpp"
#include <utility>


TEST(BST, is_valid_default_constructor) 
{
    BST<int, double> bst;

    ASSERT_NO_THROW(bst);
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
