#include <gtest/gtest.h>

#include <random>
#include <stack>

#include "../include/red_black_tree.hpp"
using namespace Tree;

void print(Tree::RedBlackTree<int, int>& tree) {
	std::cout << "==============================================\n";
	tree.preorder([&](Tree::BSTree<int, int>::Node* node) {
		Tree::BSTree<int, int>::Node* tmp = tree.head;
		size_t h = 0;
		while (true) {
			if (tmp == node) {
				break;
			}
			if (tmp->key < node->key) {
				tmp = tmp->right;
			} else {
				tmp = tmp->left;
			}
			h++;
		}
		for (size_t i = 0; i < h; ++i) {
			std::cout << "\t";
		}
		std::cout << h << " " << node->key << " " << (int)static_cast<Tree::RedBlackTree<int, int>::Node*>(node)->color
		          << std::endl;
	});
	std::cout << "==============================================\n";
}

template <typename Key, typename Value>
class RedBlackTreeTest : public ::testing::Test {
   protected:
	using Node = typename RedBlackTree<Key, Value>::Node;

	void SetUp() override {
		// Общие настройки для всех тестов (при необходимости)
	}

	void TearDown() override { tree.clear(); }

	void ValidateTree() {
		Node* root = static_cast<Node*>(tree.head);
		if (root) {
			ASSERT_EQ(root->color, 0) << "Root must be black";
			CheckRedBlackProperties(root);
			CheckBlackHeight(root);
		}
	}

	void CheckRedBlackProperties(const Node* node) {
		if (!node) return;

		Node* left = static_cast<Node*>(node->left);
		Node* right = static_cast<Node*>(node->right);

		CheckRedBlackProperties(left);
		CheckRedBlackProperties(right);
	}

	int CheckBlackHeight(const Node* node) {
		if (!node) return 1;

		int left_height = CheckBlackHeight(static_cast<Node*>(node->left));
		int right_height = CheckBlackHeight(static_cast<Node*>(node->right));
		EXPECT_EQ(left_height, right_height) << "Black height mismatch at node " << node->key;
		return (node->color == 0) ? left_height + 1 : left_height;
	}

	RedBlackTree<Key, Value> tree;
};

using RedBlackTreeIntTest = RedBlackTreeTest<int, int>;
TEST_F(RedBlackTreeIntTest, InsertSingleNode) {
	tree.add(42, 100);
	Node* root = static_cast<Node*>(tree.head);
	ASSERT_NE(root, nullptr);
	EXPECT_EQ(root->key, 42);
	EXPECT_EQ(root->color, 0);
	ValidateTree();
}

TEST_F(RedBlackTreeIntTest, InsertAndRotateLeftRight) {
	tree.add(30, 0);
	tree.add(10, 0);
	tree.add(20, 0);

	Node* root = static_cast<Node*>(tree.head);
	ASSERT_NE(root, nullptr);
	EXPECT_EQ(root->key, 20);
	ValidateTree();
}

TEST_F(RedBlackTreeIntTest, InsertAndRotateRightLeft) {
	tree.add(10, 0);
	tree.add(30, 0);
	tree.add(20, 0);

	Node* root = static_cast<Node*>(tree.head);
	ASSERT_NE(root, nullptr);
	EXPECT_EQ(root->key, 20);
	ValidateTree();
}

TEST_F(RedBlackTreeIntTest, RemoveRootWithTwoChildren) {
	tree.add(10, 0);
	tree.add(5, 0);
	tree.add(15, 0);
	tree.remove(10);

	Node* root = static_cast<Node*>(tree.head);
	ASSERT_NE(root, nullptr);
	EXPECT_TRUE(root->key == 15 || root->key == 5);
	EXPECT_EQ(tree.size(), 2);
	ValidateTree();
}

TEST_F(RedBlackTreeIntTest, CopyConstructor) {
	tree.add(10, 0);
	tree.add(5, 0);
	RedBlackTree<int, int> copy(tree);

	Node* copyRoot = static_cast<Node*>(copy.head);
	ASSERT_NE(copyRoot, nullptr);
	EXPECT_NE(copyRoot, tree.head);
	ValidateTree();
}

TEST_F(RedBlackTreeIntTest, MoveConstructor) {
	tree.add(10, 0);
	RedBlackTree<int, int> moved(std::move(tree));

	Node* movedRoot = static_cast<Node*>(moved.head);
	ASSERT_NE(movedRoot, nullptr);
	ASSERT_EQ(tree.head, nullptr);
	ValidateTree();
}

TEST_F(RedBlackTreeIntTest, AssignmentOperator) {
	tree.add(10, 0);
	RedBlackTree<int, int> copy;
	copy = tree;

	Node* copyRoot = static_cast<Node*>(copy.head);
	ASSERT_NE(copyRoot, nullptr);
	EXPECT_NE(copyRoot, tree.head);
	ValidateTree();
}

TEST_F(RedBlackTreeIntTest, HeightCalculation) {
	tree.add(10, 0);
	tree.add(20, 0);
	tree.add(5, 0);
	size_t height = tree.get_height(tree.head);
	EXPECT_GE(height, 1);
}

TEST_F(RedBlackTreeIntTest, Insert1000ElementsAndValidate) {
	const int NUM_ELEMENTS = 1000;
	std::vector<int> keys;

	// Генерация уникальных случайных ключей
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, NUM_ELEMENTS * 10);
	while (keys.size() < NUM_ELEMENTS) {
		int key = dist(gen);
		if (std::find(keys.begin(), keys.end(), key) == keys.end()) {
			keys.push_back(key);
		}
	}
	//	keys.clear();
	//	keys.insert(keys.begin(), {80, 84, 45, 33, 40, 83, 71, 69, 31, });
	for (int key : keys) {
		//		std::cout << key <<std::endl;
		tree.add(key, 0);
		//		print(tree);
	}
	std::cout << std::endl;

	//	print(tree);
	EXPECT_EQ(tree.size(), NUM_ELEMENTS);
	ValidateTree();
}

TEST_F(RedBlackTreeIntTest, InsertAndDeleteRandomElements) {
	const int NUM_ELEMENTS = 1000;
	const int NUM_TO_DELETE = 500;
	std::vector<int> keys;

	std::set<int> unique_keys;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, NUM_ELEMENTS * 10);
	while (unique_keys.size() < NUM_ELEMENTS) {
		unique_keys.insert(dist(gen));
	}
	keys.assign(unique_keys.begin(), unique_keys.end());

//	keys.clear();
//	keys.insert(keys.begin(), {12, 1, 2, -12, 0, 13, 3, 5, 11, 14, 42, 100, 18, 17, -100, 11243, 112});

	for (int key : keys) {
		tree.add(key, 0);
	}
	std::shuffle(keys.begin(), keys.end(), gen);
	std::vector<int> keys_to_delete(keys.begin(), keys.begin() + NUM_TO_DELETE);
	std::vector<int> remaining_keys(keys.begin() + NUM_TO_DELETE, keys.end());

//	print(tree);
	for (int key : keys_to_delete) {
//		std::cout << key << std::endl;
		ASSERT_NO_THROW(tree.remove(key));
//		print(tree);
		ValidateTree();
	}

	EXPECT_EQ(tree.size(), NUM_ELEMENTS - NUM_TO_DELETE);

	for (int key : keys_to_delete) {
		EXPECT_FALSE(tree.contains(key));
	}

	for (int key : remaining_keys) {
		EXPECT_TRUE(tree.contains(key));
	}

	//	ValidateTree();
}