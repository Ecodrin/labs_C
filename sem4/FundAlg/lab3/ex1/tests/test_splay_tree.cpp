#include "../include/splay_tree.hpp"
#include <gtest/gtest.h>



#include <gtest/gtest.h>
#include "splay_tree.hpp"

using namespace Tree;

class SplayTreeTest : public testing::Test {
   protected:
	SplayTree<int, std::string> tree;

	void SetUp() override {
		tree.add(50, "50");
		tree.add(30, "30");
		tree.add(70, "70");
		tree.add(20, "20");
		tree.add(40, "40");
		tree.add(60, "60");
		tree.add(80, "80");
	}

	void TearDown() override {
		tree.clear();
	}
};

TEST_F(SplayTreeTest, BasicOperations) {
	EXPECT_EQ(tree.size(), 7);
	EXPECT_FALSE(tree.contains(100));
	EXPECT_TRUE(tree.contains(30));

	tree.remove(30);
	EXPECT_EQ(tree.size(), 6);
	EXPECT_FALSE(tree.contains(30));
}

TEST_F(SplayTreeTest, SplayingEffect) {
	auto it = tree.find(20);
	EXPECT_EQ((*it)->key, 20);
	EXPECT_EQ(tree.head->key, 20);

	it = tree.find(60);
	EXPECT_EQ(tree.head->key, 60);

	EXPECT_EQ(tree.find(10000), tree.end());
}

TEST_F(SplayTreeTest, Rotations) {
	tree.find(20);
	EXPECT_EQ(tree.head->right->key, 80);

	tree.find(80);
	EXPECT_EQ(tree.head->left->key, 20);
}

TEST_F(SplayTreeTest, MergeSubtrees) {
	tree.remove(50);
	EXPECT_EQ(tree.head->key, 40);
	EXPECT_EQ(tree.size(), 6);

	std::vector<int> keys;
	for(auto it = tree.begin(); it != tree.end(); ++it) {
		keys.push_back((*it)->key);
	}
	EXPECT_EQ(keys, (std::vector<int>{20, 30, 40, 60, 70, 80}));
}

TEST_F(SplayTreeTest, RemoveNotExistElement){
	size_t size = tree.size();
	tree.remove(1000000);
	EXPECT_EQ(size, tree.size());
}

TEST_F(SplayTreeTest, EdgeCases) {
	SplayTree<int, std::string> empty_tree;

	EXPECT_THROW(empty_tree.remove(10), std::runtime_error);

	empty_tree.add(10, "10");
	EXPECT_EQ(empty_tree.head->key, 10);
	empty_tree.remove(10);
	EXPECT_TRUE(empty_tree.size() == 0);
}

TEST_F(SplayTreeTest, Iterator) {
	std::vector<int> expected = {20, 30, 40, 50, 60, 70, 80};
	std::vector<int> actual;

	for(auto it = tree.begin(); it != tree.end(); ++it) {
		actual.push_back((*it)->key);
	}

	EXPECT_EQ(actual, expected);
}

TEST_F(SplayTreeTest, AccessPattern) {
	for(int i = 0; i < 10; ++i) {
		tree.find(40);
		EXPECT_EQ(tree.head->key, 40);

		tree.find(60);
		EXPECT_EQ(tree.head->key, 60);
	}
}

TEST_F(SplayTreeTest, CopyConstructor) {
	SplayTree<int, std::string> copy(tree);

	EXPECT_EQ(copy.size(), tree.size());
	for(auto it = tree.begin(); it != tree.end(); ++it) {
		EXPECT_TRUE(copy.contains((*it)->key));
	}

	tree.add(100, "100");
	EXPECT_FALSE(copy.contains(100));
}

TEST_F(SplayTreeTest, MoveConstructor) {
	SplayTree<int, std::string> temp(tree);
	size_t expected_size = temp.size();

	SplayTree<int, std::string> moved(std::move(temp));

	EXPECT_EQ(moved.size(), expected_size);
	EXPECT_EQ(temp.size(), 0);
	EXPECT_TRUE(temp.size() == 0);
}

TEST_F(SplayTreeTest, CopyAssignment) {
	SplayTree<int, std::string> copy;
	copy.add(-1, "-1");

	copy = tree;

	EXPECT_EQ(copy.size(), tree.size());
	EXPECT_TRUE(copy.contains(50));

	tree.remove(50);
	EXPECT_TRUE(copy.contains(50));

}

TEST_F(SplayTreeTest, MoveAssignment) {
	SplayTree<int, std::string> temp(tree);
	size_t expected_size = temp.size();

	SplayTree<int, std::string> moved;
	moved = std::move(temp);

	EXPECT_EQ(moved.size(), expected_size);
	EXPECT_EQ(temp.size(), 0);

	moved = SplayTree<int, std::string>();
	EXPECT_EQ(moved.size(), 0);
}

TEST_F(SplayTreeTest, EmptyOperations) {
	SplayTree<int, std::string> empty;

	SplayTree<int, std::string> copy(empty);
	EXPECT_TRUE(empty.size() == 0);

	SplayTree<int, std::string> moved(std::move(empty));
	EXPECT_TRUE(copy.size() == 0);

	SplayTree<int, std::string> target;
	target = empty;
	EXPECT_TRUE(target.size() == 0);
}