#include "../include/my_map.hpp"


#include <gtest/gtest.h>
#include <string>
#include <vector>


class MyMapTest : public ::testing::Test {
   protected:
	void SetUp() override {
		map.insert(10, "ten");
		map.insert(5, "five");
		map.insert(15, "fifteen");
		map.insert(3, "three");
		map.insert(7, "seven");
		map.insert(12, "twelve");
		map.insert(17, "seventeen");
	}

	MyMap<int, std::string, Tree::BSTree> map;
};

TEST_F(MyMapTest, InsertAndFind) {
	auto* val = map.find(10);
	ASSERT_NE(val, nullptr);
	EXPECT_EQ(*val, "ten");

	EXPECT_EQ(map.find(100), nullptr);
}

TEST_F(MyMapTest, Contains) {
	EXPECT_TRUE(map.contains(5));
	EXPECT_TRUE(map.contains(15));
	EXPECT_FALSE(map.contains(100));
}

TEST_F(MyMapTest, Remove) {
	map.remove(5);
	EXPECT_FALSE(map.contains(5));
	EXPECT_EQ(map.size(), 6);

	map.remove(15);
	EXPECT_FALSE(map.contains(15));
	EXPECT_EQ(map.size(), 5);
}

TEST_F(MyMapTest, SizeAndClear) {
	EXPECT_EQ(map.size(), 7);
	map.clear();
	EXPECT_EQ(map.size(), 0);
	EXPECT_FALSE(map.contains(10));
}

TEST_F(MyMapTest, Iterator) {
	std::vector<int> expected{3, 5, 7, 10, 12, 15, 17};
	std::vector<int> keys;

	for (auto it = map.begin(); it != map.end(); ++it) {
		keys.push_back((*it)->key);
	}
	EXPECT_EQ(keys, expected);
}

TEST_F(MyMapTest, RangeBasedFor) {
	std::vector<int> expected{3, 5, 7, 10, 12, 15, 17};
	std::vector<int> keys;

	for (const auto& pair : map) {
		keys.push_back(pair->key);
	}
	EXPECT_EQ(keys, expected);
}

TEST_F(MyMapTest, EmptyMap) {
	MyMap<int, std::string, Tree::BSTree> emptyMap;
	EXPECT_EQ(emptyMap.size(), 0);
	EXPECT_EQ(emptyMap.begin(), emptyMap.end());
	EXPECT_FALSE(emptyMap.contains(0));
}

