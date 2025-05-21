#include <gtest/gtest.h>

#include "../include/avl_tree.hpp"

using namespace std;

class AVLTreeTest : public ::testing::Test {
   protected:
	Tree::AVLTree<int, int, LessIntComparator> avl;

	void SetUp() override {}

	void TearDown() override { avl.clear(); }

	bool isBalanced(typename Tree::AVLTree<int, int, LessIntComparator>::Node* node) {
		if (!node) return true;
		auto heights = avl.get_height_subtrees(node);
		int balance = heights.first - heights.second;
		if (balance < -1 || balance > 1) return false;
		return isBalanced(node->left) && isBalanced(node->right);
	}
};

TEST_F(AVLTreeTest, EmptyTree) {
	EXPECT_EQ(avl.size(), 0);
	EXPECT_EQ(avl.get_height(avl.head), 0);
}

TEST_F(AVLTreeTest, SingleNode) {
	avl.add(10, 100);
	EXPECT_EQ(avl.head->key, 10);
	EXPECT_EQ(avl.get_height(avl.head), 1);
	auto heights = avl.get_height_subtrees(avl.head);
	EXPECT_EQ(heights.first, 0);
	EXPECT_EQ(heights.second, 0);
	EXPECT_TRUE(isBalanced(avl.head));
}

TEST_F(AVLTreeTest, SmallLeftRotation) {
	avl.add(10, 0);
	avl.add(20, 0);
	avl.add(30, 0);

	EXPECT_EQ(avl.head->key, 20);
	EXPECT_EQ(avl.head->left->key, 10);
	EXPECT_EQ(avl.head->right->key, 30);
	EXPECT_TRUE(isBalanced(avl.head));
}

TEST_F(AVLTreeTest, BigRightRotation) {
	avl.add(30, 0);
	avl.add(20, 0);
	avl.add(25, 0);

	EXPECT_EQ(avl.head->key, 25);
	EXPECT_EQ(avl.head->left->key, 20);
	EXPECT_EQ(avl.head->right->key, 30);
	EXPECT_TRUE(isBalanced(avl.head));
}

TEST_F(AVLTreeTest, ComplexRemoval) {
	avl.add(50, 0);
	avl.add(30, 0);
	avl.add(70, 0);
	avl.add(20, 0);
	avl.add(40, 0);
	avl.add(60, 0);
	avl.add(80, 0);
	avl.add(10, 0);

	avl.remove(40);
	EXPECT_TRUE(isBalanced(avl.head));

	avl.remove(50);
	EXPECT_TRUE(isBalanced(avl.head));
	EXPECT_EQ(avl.head->key, 60);
}

TEST_F(AVLTreeTest, SubtreeHeights) {
	avl.add(50, 0);
	avl.add(30, 0);
	avl.add(70, 0);
	avl.add(20, 0);

	auto heights = avl.get_height_subtrees(avl.head);
	EXPECT_EQ(heights.first, 2);
	EXPECT_EQ(heights.second, 1);
}

TEST_F(AVLTreeTest, MixedOperations) {
	for (int i = 0; i < 10; ++i) {
		avl.add(i, i * 10);
		EXPECT_TRUE(isBalanced(avl.head));
	}

	for (int i = 0; i < 10; ++i) {
		avl.remove(i);
		EXPECT_TRUE(isBalanced(avl.head));
	}
}

TEST_F(AVLTreeTest, TreeHeight) {
	avl.add(50, 0);
	EXPECT_EQ(avl.get_height(avl.head), 1);
	avl.add(30, 0);
	avl.add(70, 0);
	EXPECT_EQ(avl.get_height(avl.head), 2);
}

TEST_F(AVLTreeTest, BigLeftRotation) {
	avl.add(10, 0);
	avl.add(30, 0);
	avl.add(20, 0);

	EXPECT_EQ(avl.head->key, 20);

	EXPECT_NE(avl.head->left, nullptr);
	EXPECT_EQ(avl.head->left->key, 10);
	EXPECT_EQ(avl.head->left->left, nullptr);
	EXPECT_EQ(avl.head->left->right, nullptr);

	EXPECT_NE(avl.head->right, nullptr);
	EXPECT_EQ(avl.head->right->key, 30);
	EXPECT_EQ(avl.head->right->left, nullptr);
	EXPECT_EQ(avl.head->right->right, nullptr);

	EXPECT_TRUE(isBalanced(avl.head));

	EXPECT_EQ(avl.get_height(avl.head), 2);

	auto root_heights = avl.get_height_subtrees(avl.head);
	EXPECT_EQ(root_heights.first, 1);
	EXPECT_EQ(root_heights.second, 1);
}

TEST_F(AVLTreeTest, RemoveException) {
	Tree::AVLTree<int, int> b;
	EXPECT_THROW(b.remove(1), std::runtime_error);
}

TEST_F(AVLTreeTest, RemoveNotExistElement) {
	avl.add(12, 13);
	avl.remove(-134);
	EXPECT_EQ(avl.size(), 1);
}
