#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bubble_sort.hpp"

TEST(ArraysEqual, AnyElementsCount) {
	std::vector<int> actual = {1, 8, 2, 5, 3, 11};
	bs::bubble_sort(actual);
	std::vector<int> expected = {1, 2, 3, 5, 8, 11};

	ASSERT_EQ(expected.size(), actual.size())
		<< "Разные размеры ожидаемого и отсортированного массивов";

	for (int i = 0; i < actual.size(); i++) {
		ASSERT_EQ(expected[i], actual[i]) 
			<< "Массив ожидаемый и отсортировнный отличаются в элементе с индексом "
			<< i;
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}