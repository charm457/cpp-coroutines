#include <gtest/gtest.h>
#include "../src/doubly_linked_list.hpp"

using namespace bdk;

class LinkedListTest : public ::testing::Test {
protected:
    DoublyLinkedList<int> list;
};

TEST_F(LinkedListTest, EmptyListSize) {
    EXPECT_EQ(list.get_size(), 0);
}

TEST_F(LinkedListTest, PushBack) {
    list.push_back(1);
    list.push_back(2);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_TRUE(list.has_item(1));
    EXPECT_TRUE(list.has_item(2));
}

TEST_F(LinkedListTest, RemoveFirst) {
    list.push_back(100);
    list.push_back(200);
    EXPECT_TRUE(list.remove_first(100));
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_FALSE(list.has_item(100));
    EXPECT_TRUE(list.has_item(200));
}

TEST_F(LinkedListTest, RemoveNonExistent) {
    list.push_back(10);
    EXPECT_FALSE(list.remove_first(20));
    EXPECT_EQ(list.get_size(), 1);
}