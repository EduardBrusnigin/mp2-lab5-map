#include "gtest.h"
#include "avl.h"
#include <vector>
#include <utility>


TEST(AVL, is_valid_default_constructor) {
    AVL<int, double> avl;

    ASSERT_NO_THROW(avl);
    EXPECT_TRUE(avl.is_avl());
}


TEST(AVL, is_valid_constructor_by_vector) {
    vector<pair<int, double>> v = {{2, 2.1}, {1, 1.3}, {3, 3.4}, {4, 1.5}};
    AVL<int, double> avl(v);
    
    EXPECT_TRUE(avl.is_avl());
}


TEST(AVL, can_insert_node) {
    AVL<int, double> avl;

    EXPECT_NO_THROW(avl.Insert(0, 3.14));
    EXPECT_NO_THROW(avl.Insert(1, 2.718));
    EXPECT_NO_THROW(avl.Insert(2, -9.123));

    EXPECT_TRUE(avl.is_avl());
}


TEST(AVL, can_print_nodes) {
    AVL<int, double> avl;

    avl.Insert(0, 3.14);
    avl.Insert(1, 2.718);
    avl.Insert(2, -9.123);

    EXPECT_TRUE(avl.is_avl());
    EXPECT_NO_THROW(avl.Print());
}


TEST(AVL, can_get_next_node) {
    vector<pair<int, double>> v = {{3, 0}, {1, 0}, {5, 0}, {2, 0}, {7, 0}};

    AVL<int, double> avl(v);
    EXPECT_TRUE(avl.is_avl());
    EXPECT_EQ(avl.GetNext(1), 2);
    EXPECT_EQ(avl.GetNext(5), 7);
    EXPECT_EQ(avl.GetNext(3), 5);
    EXPECT_EQ(avl.GetNext(2), 3);
    EXPECT_ANY_THROW(avl.GetNext(7));
    EXPECT_TRUE(avl.is_avl());
}


TEST(AVL, can_delete) {
    vector<pair<int, double>> v = {{0, 3.14}, {1, -2.7}, {2, 5.1}, {3, 9.9}, {4, -6.3}, {5, 10.13}};
    AVL<int, double> avl(v);
    EXPECT_TRUE(avl.is_avl());
    EXPECT_NO_THROW(avl.Delete(1));
    EXPECT_NO_THROW(avl.Delete(3));
    EXPECT_TRUE(avl.is_avl());
}