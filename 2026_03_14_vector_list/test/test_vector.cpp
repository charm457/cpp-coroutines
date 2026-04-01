#include <gtest/gtest.h>
#include "../src/vector.hpp"

using namespace bdk;

class VectorTest : public ::testing::Test {
protected:
    Vector<int> v;
};

TEST_F(VectorTest, PushBackAndSize) {
    v.push_back(10);
    v.push_back(20);
    EXPECT_EQ(v.get_size(), 2);
}

TEST_F(VectorTest, HasItem) {
    v.push_back(10);
    EXPECT_TRUE(v.has_item(10));
    EXPECT_FALSE(v.has_item(50));
}

TEST_F(VectorTest, Insert) {
    v.push_back(1);
    v.push_back(3);
    EXPECT_TRUE(v.insert(1, 2)); // Вставляем 2 между 1 и 3
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(2));
}

TEST_F(VectorTest, RemoveFirst) {
    v.push_back(10);
    v.push_back(20);
    v.push_back(10);
    EXPECT_TRUE(v.remove_first(10));
    EXPECT_EQ(v.get_size(), 2);
    // Проверяем, что удалилось только первое вхождение
    EXPECT_TRUE(v.has_item(10)); 
}