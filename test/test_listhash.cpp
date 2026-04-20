
#include <gtest.h>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include "hash2.h"

// Тест 1: Конструктор по умолчанию
TEST(HashTableTest, Test01_DefaultConstructor) {
    Hash_Table<int, std::string> ht;
    EXPECT_EQ(ht.Find(42), nullptr);
}

// Тест 2: Конструктор с заданным размером
TEST(HashTableTest, Test02_ConstructorWithSize) {
    Hash_Table<int, int> ht(32);
    EXPECT_EQ(ht.Find(100), nullptr);
}

// Тест 3: Вставка и поиск одного элемента
TEST(HashTableTest, Test03_InsertAndFindSingle) {
    Hash_Table<int, std::string> ht;
    ht.Insert(1, "one");

    std::string* result = ht.Find(1);
    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_EQ(*result, "one");
    }
}

// Тест 4: Вставка нескольких элементов
TEST(HashTableTest, Test04_InsertAndFindMultiple) {
    Hash_Table<int, std::string> ht;

    ht.Insert(1, "one");
    ht.Insert(2, "two");
    ht.Insert(3, "three");
    ht.Insert(4, "four");

    std::string* r1 = ht.Find(1);
    std::string* r2 = ht.Find(2);
    std::string* r3 = ht.Find(3);
    std::string* r4 = ht.Find(4);

    if (r1) EXPECT_EQ(*r1, "one");
    if (r2) EXPECT_EQ(*r2, "two");
    if (r3) EXPECT_EQ(*r3, "three");
    if (r4) EXPECT_EQ(*r4, "four");
    EXPECT_EQ(ht.Find(5), nullptr);
}

// Тест 5: Обновление существующего значения
TEST(HashTableTest, Test05_UpdateExistingValue) {
    Hash_Table<int, std::string> ht;

    ht.Insert(1, "one");
    ht.Insert(1, "ONE_UPDATED");

    std::string* result = ht.Find(1);
    if (result) {
        EXPECT_EQ(*result, "ONE_UPDATED");
    }
}

// Тест 6: Поиск несуществующего ключа
TEST(HashTableTest, Test06_FindNonExistentKey) {
    Hash_Table<int, std::string> ht;

    ht.Insert(1, "one");
    ht.Insert(2, "two");

    EXPECT_EQ(ht.Find(3), nullptr);
    EXPECT_EQ(ht.Find(100), nullptr);
}

// Тест 7: Удаление существующего элемента
TEST(HashTableTest, Test07_RemoveExistingElement) {
    Hash_Table<int, std::string> ht;

    ht.Insert(1, "one");
    ht.Insert(2, "two");

    EXPECT_TRUE(ht.Remove(1));
    EXPECT_EQ(ht.Find(1), nullptr);
    EXPECT_NE(ht.Find(2), nullptr);
}

// Тест 8: Удаление несуществующего элемента
TEST(HashTableTest, Test08_RemoveNonExistentElement) {
    Hash_Table<int, std::string> ht;

    ht.Insert(1, "one");

    EXPECT_FALSE(ht.Remove(2));
    EXPECT_NE(ht.Find(1), nullptr);
}

// Тест 9: Последовательное удаление и вставка
TEST(HashTableTest, Test09_RemoveAndReinsert) {
    Hash_Table<int, std::string> ht;

    ht.Insert(1, "one");
    EXPECT_TRUE(ht.Remove(1));
    EXPECT_FALSE(ht.Remove(1));

    ht.Insert(1, "new_one");
    std::string* result = ht.Find(1);
    if (result) {
        EXPECT_EQ(*result, "new_one");
    }
}

// Тест 10: Очистка таблицы
TEST(HashTableTest, Test10_ClearTable) {
    Hash_Table<int, std::string> ht;

    ht.Insert(1, "one");
    ht.Insert(2, "two");
    ht.Insert(3, "three");

    ht.Clear();

    EXPECT_EQ(ht.Find(1), nullptr);
    EXPECT_EQ(ht.Find(2), nullptr);
    EXPECT_EQ(ht.Find(3), nullptr);

    ht.Insert(4, "four");
    EXPECT_NE(ht.Find(4), nullptr);
}

// Тест 11: Работа со строковыми ключами
TEST(HashTableTest, Test11_StringKeys) {
    Hash_Table<std::string, int> ht;

    ht.Insert("apple", 5);
    ht.Insert("banana", 8);
    ht.Insert("orange", 12);

    int* r1 = ht.Find("apple");
    int* r2 = ht.Find("banana");
    int* r3 = ht.Find("orange");

    if (r1) EXPECT_EQ(*r1, 5);
    if (r2) EXPECT_EQ(*r2, 8);
    if (r3) EXPECT_EQ(*r3, 12);
    EXPECT_EQ(ht.Find("grape"), nullptr);
}

// Тест 12: Работа с отрицательными ключами
TEST(HashTableTest, Test12_NegativeKeys) {
    Hash_Table<int, std::string> ht;

    ht.Insert(-5, "minus five");
    ht.Insert(-10, "minus ten");
    ht.Insert(5, "five");

    std::string* r1 = ht.Find(-5);
    std::string* r2 = ht.Find(-10);
    std::string* r3 = ht.Find(5);

    if (r1) EXPECT_EQ(*r1, "minus five");
    if (r2) EXPECT_EQ(*r2, "minus ten");
    if (r3) EXPECT_EQ(*r3, "five");
}

// Тест 13: Работа с указателями в качестве значений
TEST(HashTableTest, Test13_PointerValues) {
    Hash_Table<int, int*> ht;

    int value1 = 100;
    int value2 = 200;

    ht.Insert(1, &value1);
    ht.Insert(2, &value2);

    int** result1 = ht.Find(1);
    int** result2 = ht.Find(2);

    if (result1) EXPECT_EQ(**result1, 100);
    if (result2) EXPECT_EQ(**result2, 200);
}
