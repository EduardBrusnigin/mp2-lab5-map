#include "gtest.h"
#include "hash1.h"
#include <vector>
#include <utility>


TEST(OAHashTable, is_valid_default_constructor) {
	OAHashTable<int, double> hashtable;

	ASSERT_NO_THROW(hashtable);
	EXPECT_TRUE(hashtable.is_hash_table());
}


TEST(OAHashTable, is_valid_constructor_by_vector) {
	vector<pair<int, double>> v = {{2, 2.1}, {1, 1.3}, {3, 3.4}, {4, 1.5}};
	OAHashTable<int, double> hashtable(v);

	EXPECT_TRUE(hashtable.is_hash_table());
}


TEST(OAHashTable, can_insert) {
	OAHashTable<int, double> hashtable;

	EXPECT_NO_THROW(hashtable.Insert(7, 0));
	EXPECT_NO_THROW(hashtable.Insert(10, 0));
	EXPECT_NO_THROW(hashtable.Insert(1, 0));
	EXPECT_NO_THROW(hashtable.Insert(5, 0));
	EXPECT_NO_THROW(hashtable.Insert(9, 0));
	EXPECT_NO_THROW(hashtable.Insert(-3, 0));
	EXPECT_NO_THROW(hashtable.Insert(8, 0));
	EXPECT_NO_THROW(hashtable.Insert(3, 0));
	EXPECT_NO_THROW(hashtable.Insert(-11, 0));
	EXPECT_NO_THROW(hashtable.Insert(4, 0));

	EXPECT_TRUE(hashtable.is_hash_table());
}


TEST(OAHashTable, can_print_nodes) {
	OAHashTable<int, double> hashtable;

	hashtable.Insert(0, 3.14);
	hashtable.Insert(1, 2.718);
	hashtable.Insert(2, -9.123);

	EXPECT_TRUE(hashtable.is_hash_table());
	EXPECT_NO_THROW(hashtable.Print());
}


TEST(OAHashTable, can_delete_node1) {
	vector<pair<int, double>> v = {{0, 3.14}, {1, -2.7}, {2, 5.1}, {3, 9.9}, {4, -6.3}, {5, 10.13}};
	OAHashTable<int, double> hashtable(v);
	EXPECT_TRUE(hashtable.is_hash_table());
	EXPECT_NO_THROW(hashtable.Delete(1));
	EXPECT_NO_THROW(hashtable.Delete(3));
	EXPECT_NO_THROW(hashtable.Delete(5));
	EXPECT_NO_THROW(hashtable.Delete(2));
	EXPECT_NO_THROW(hashtable.Delete(4));
	EXPECT_TRUE(hashtable.is_hash_table());
}

TEST(OAHashTable, can_delete_node2) {
	vector<pair<int, double>> v = {{15, 0}, {13, 0}, {1, 0}, {3, 0}, {2, 0}, {5, 0}, {6, 0}, {4, 0}, {14, 0}, {12, 0}, {10, 0}, {7, 0}, {9, 0}, {11, 0}, {8, 0}};
	OAHashTable<int, double> hashtable(v);
	EXPECT_TRUE(hashtable.is_hash_table());
	EXPECT_NO_THROW(hashtable.Delete(15));
	EXPECT_NO_THROW(hashtable.Delete(11));
	EXPECT_NO_THROW(hashtable.Delete(1));
	EXPECT_NO_THROW(hashtable.Delete(3));
	EXPECT_NO_THROW(hashtable.Delete(5));
	EXPECT_NO_THROW(hashtable.Delete(2));
	EXPECT_NO_THROW(hashtable.Delete(4));
	EXPECT_TRUE(hashtable.is_hash_table());
}


TEST(OAHashTable, search) {
	OAHashTable<int, double> hashtable;
	hashtable.Insert(5, 3.14);
	hashtable.Insert(10, 2.718);
	hashtable.Insert(15, 1.618);

	EXPECT_DOUBLE_EQ(hashtable.Search(5), 3.14);
	EXPECT_DOUBLE_EQ(hashtable.Search(10), 2.718);
	EXPECT_DOUBLE_EQ(hashtable.Search(15), 1.618);
	EXPECT_TRUE(hashtable.is_hash_table());
}


TEST(OAHashTable, search_non_existing) {
	OAHashTable<int, double> hashtable;
	hashtable.Insert(1, 1.1);
	hashtable.Insert(2, 2.2);

	EXPECT_THROW(hashtable.Search(999), const char*);
	EXPECT_TRUE(hashtable.is_hash_table());
}


TEST(OAHashTable, delete_non_existing) {
	OAHashTable<int, double> hashtable;
	hashtable.Insert(1, 1.1);
	hashtable.Insert(2, 2.2);

	EXPECT_THROW(hashtable.Delete(999), const char*);
	EXPECT_TRUE(hashtable.is_hash_table());
}


TEST(OAHashTable, insert_duplicate) {
	OAHashTable<int, double> hashtable;
	hashtable.Insert(7, 1.1);
	hashtable.Insert(7, 9.9);
	
	EXPECT_DOUBLE_EQ(hashtable.Search(7), 9.9);
	EXPECT_TRUE(hashtable.is_hash_table());
}


TEST(OAHashTable, rehashing_works) {
	OAHashTable<int, double> hashtable;
	
	for (int i = 0; i < 20; i++) {
		hashtable.Insert(i, i * 1.5);
	}
	
	for (int i = 0; i < 20; i++) {
		EXPECT_DOUBLE_EQ(hashtable.Search(i), i * 1.5);
	}
	
	EXPECT_TRUE(hashtable.is_hash_table());
}


TEST(OAHashTable, negative_keys_works) {
	OAHashTable<int, double> hashtable;
	
	hashtable.Insert(-5, 1.1);
	hashtable.Insert(-10, 2.2);
	hashtable.Insert(-15, 3.3);
	hashtable.Insert(-1, 4.4);
	
	EXPECT_DOUBLE_EQ(hashtable.Search(-5), 1.1);
	EXPECT_DOUBLE_EQ(hashtable.Search(-10), 2.2);
	EXPECT_DOUBLE_EQ(hashtable.Search(-15), 3.3);
	EXPECT_DOUBLE_EQ(hashtable.Search(-1), 4.4);
	
	hashtable.Delete(-5);
	EXPECT_THROW(hashtable.Search(-5), const char*);
	
	EXPECT_TRUE(hashtable.is_hash_table());
}