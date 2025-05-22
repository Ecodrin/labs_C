#include <gtest/gtest.h>

#include <random>

#include "../include/bst_tree.hpp"
#include "../include/comparator.hpp"

using namespace Tree;

class BSTreeTest : public ::testing::Test {
   protected:
	void SetUp() override {
		tree.add(5, "five");
		tree.add(3, "three");
		tree.add(7, "seven");
		tree.add(1, "one");
		tree.add(4, "four");
		tree.add(6, "six");
	}

	BSTree<int, std::string, LessIntComparator> tree;
};

TEST_F(BSTreeTest, DefaultConstructor) {
	BSTree<int, std::string> t;
	auto d = t.find(0);
	EXPECT_EQ(d, t.end());
}

TEST_F(BSTreeTest, KeyValueConstructor) {
	BSTree<int, std::string> t(10, "ten");
	auto value = t.find(10);
	ASSERT_NE(value, t.end());
	EXPECT_EQ((*value)->value, "ten");
}

TEST_F(BSTreeTest, AddAndFind) {
	auto value = tree.find(5);
	ASSERT_NE(value, tree.end());
	EXPECT_EQ((*value)->value, "five");

	value = tree.find(3);
	ASSERT_NE(value, tree.end());
	EXPECT_EQ((*value)->value, "three");

	value = tree.find(7);
	ASSERT_NE(value, tree.end());
	EXPECT_EQ((*value)->value, "seven");

	EXPECT_EQ(tree.find(0), tree.end());
}

TEST_F(BSTreeTest, InOrderTraversal) {
	std::vector<int> keys;
	tree.inorder([&keys](BSTree<int, std::string, LessIntComparator>::Node* node){ keys.push_back(node->key); });
	ASSERT_EQ(keys, (std::vector<int>{1, 3, 4, 5, 6, 7}));
}

TEST_F(BSTreeTest, EmpyTreeTraversal) {
	std::vector<int> keys;
	BSTree<int, int> b;
	b.inorder([&keys](BSTree<int, int>::Node* node){ keys.push_back(node->key); });
	ASSERT_EQ(keys, (std::vector<int>{}));

	b.preorder([&keys](BSTree<int, int>::Node* node){ keys.push_back(node->key); });
	ASSERT_EQ(keys, (std::vector<int>{}));

	b.postorder([&keys](BSTree<int, int>::Node* node){ keys.push_back(node->key); });
	ASSERT_EQ(keys, (std::vector<int>{}));
}

TEST_F(BSTreeTest, PreOrderTraversal) {
	std::vector<int> keys;
	tree.preorder([&keys](BSTree<int, std::string, LessIntComparator>::Node* node){ keys.push_back(node->key); });
	ASSERT_EQ(keys, (std::vector<int>{5, 3, 1, 4, 7, 6}));
}

TEST_F(BSTreeTest, PostOrderTraversal) {
	std::vector<int> keys;
	tree.postorder([&keys](BSTree<int, std::string, LessIntComparator>::Node* node){ keys.push_back(node->key); });
	ASSERT_EQ(keys, (std::vector<int>{1, 4, 3, 6, 7, 5}));
}

TEST_F(BSTreeTest, Iterator) {
	std::vector<int> keys;
	for(auto it = tree.begin(); it != tree.end(); ++it) {
		keys.push_back((*it)->key);
	}
	ASSERT_EQ(keys, (std::vector<int>{1, 3, 4, 5, 6, 7}));

	for (auto el : tree) {
		std::cout << el << " ";
	}
	std::cout << std::endl;
}

TEST_F(BSTreeTest, ConstIterator) {
	std::vector<int> keys;
	const auto& ctree = tree;
	for(auto it = ctree.cbegin(); it != ctree.cend(); ++it) {
		keys.push_back((*it)->key);
	}
	ASSERT_EQ(keys, (std::vector<int>{1, 3, 4, 5, 6, 7}));
}
TEST_F(BSTreeTest, IteratorEquality) {
	auto it1 = tree.begin();
	auto it2 = tree.begin();
	EXPECT_TRUE(it1 == it2);
	++it2;
	EXPECT_TRUE(it1 != it2);
}


TEST_F(BSTreeTest, IteratorIncrement) {
	auto it = tree.begin();
	EXPECT_EQ((*it)->key, 1);
	++it;
	EXPECT_EQ((*it)->key, 3);
	it++;
	EXPECT_EQ((*it)->key, 4);
}

TEST_F(BSTreeTest, FindNonExistentKey) { EXPECT_EQ(tree.find(100), tree.end()); }

TEST_F(BSTreeTest, PostOrderEdgeCase) {
	BSTree<int, std::string> t;
	t.add(5, "root");
	std::vector<int> keys;
	t.postorder([&keys](BSTree<int, std::string>::Node* node){ keys.push_back(node->key); });
	ASSERT_EQ(keys, (std::vector<int>{5}));
}

TEST_F(BSTreeTest, PreOrderSingleNode) {
	BSTree<int, std::string> t;
	t.add(10, "ten");
	std::vector<int> keys;
	t.preorder([&keys](BSTree<int, std::string>::Node* node){ keys.push_back(node->key); });
	ASSERT_EQ(keys, (std::vector<int>{10}));
}

TEST_F(BSTreeTest, IteratorEndCondition) {
	auto it = tree.begin();
	for(int i = 0; i < 6; ++i) ++it;
	EXPECT_EQ(it, tree.end());
}


TEST_F(BSTreeTest, DestructorClearsMemory) {
	auto* tree = new BSTree<int, std::string>();
	tree->add(1, "one");
	tree->add(2, "two");
	ASSERT_NO_THROW(delete tree);
}


TEST_F(BSTreeTest, ContainsExistingKeys) {
	EXPECT_TRUE(tree.contains(5));
	EXPECT_TRUE(tree.contains(3));
	EXPECT_TRUE(tree.contains(7));
	EXPECT_TRUE(tree.contains(1));
	EXPECT_TRUE(tree.contains(4));
	EXPECT_TRUE(tree.contains(6));
}

TEST_F(BSTreeTest, ContainsNonExistentKeys) {
	EXPECT_FALSE(tree.contains(0));
	EXPECT_FALSE(tree.contains(100));
	EXPECT_FALSE(tree.contains(-5));
}

TEST_F(BSTreeTest, RemoveLeafNode) {
	tree.remove(1);
	EXPECT_FALSE(tree.contains(1));
	std::vector<int> keys;
	tree.inorder([&keys](BSTree<int, std::string, LessIntComparator>::Node* node){ keys.push_back(node->key); });
	ASSERT_EQ(keys, (std::vector<int>{3, 4, 5, 6, 7}));
}

TEST_F(BSTreeTest, RemoveNodeWithOneChild) {
	tree.remove(7);
	EXPECT_FALSE(tree.contains(7));
	std::vector<int> keys;
	tree.inorder([&keys](BSTree<int, std::string, LessIntComparator>::Node* node){ keys.push_back(node->key); });
	ASSERT_EQ(keys, (std::vector<int>{1, 3, 4, 5, 6}));
}

TEST_F(BSTreeTest, RemoveNodeWithTwoChildren) {
	tree.remove(5);
	EXPECT_FALSE(tree.contains(5));
	std::vector<int> keys;
	tree.inorder([&keys](BSTree<int, std::string, LessIntComparator>::Node* node){ keys.push_back(node->key); });
	ASSERT_EQ(keys, (std::vector<int>{1, 3, 4, 6, 7}));
}

TEST_F(BSTreeTest, RemoveRootMultipleTimes) {
	tree.remove(5);
	tree.remove(6);
	tree.remove(7);
	std::vector<int> keys;
	tree.inorder([&keys](BSTree<int, std::string, LessIntComparator>::Node* node){ keys.push_back(node->key); });
	ASSERT_EQ(keys, (std::vector<int>{1, 3, 4}));
}

TEST_F(BSTreeTest, RemoveNonExistentKey) {
	ASSERT_NO_THROW(tree.remove(100));
	std::vector<int> keys;
	tree.inorder([&keys](BSTree<int, std::string, LessIntComparator>::Node* node){ keys.push_back(node->key); });
	ASSERT_EQ(keys, (std::vector<int>{1, 3, 4, 5, 6, 7}));
}

TEST_F(BSTreeTest, RemoveAllElements) {
	tree.remove(1);
	tree.remove(3);
	tree.remove(4);
	tree.remove(5);
	tree.remove(6);
	tree.remove(7);
	EXPECT_FALSE(tree.contains(5));
	EXPECT_EQ(tree.begin(), tree.end());
}


TEST_F(BSTreeTest, RemoveException) {
	BSTree<int, int> b;
	EXPECT_THROW(b.remove(12), std::runtime_error);
}

TEST_F(BSTreeTest, LargeTreeRandomRemoval) {
	std::vector<int> keys;
	for (int i = 1; i <= 100; ++i) keys.push_back(i);
	std::shuffle(keys.begin(), keys.end(), std::mt19937{std::random_device{}()});

	BSTree<int, std::string> largeTree;
	for (int key : keys) {
		largeTree.add(key, "value_" + std::to_string(key));
	}

	std::vector<int> allKeys = keys;
	std::shuffle(keys.begin(), keys.end(), std::mt19937{std::random_device{}()});
	std::vector<int> keysToRemove(keys.begin(), keys.begin() + 30);

	for (int key : keysToRemove) {
		ASSERT_TRUE(largeTree.contains(key));
		largeTree.remove(key);
		ASSERT_FALSE(largeTree.contains(key));
	}

	std::vector<int> remainingKeys;
	for (int key : allKeys) {
		if (std::find(keysToRemove.begin(), keysToRemove.end(), key) == keysToRemove.end()) {
			remainingKeys.push_back(key);
		}
	}
	std::sort(remainingKeys.begin(), remainingKeys.end());

	std::vector<int> inorderKeys;
	largeTree.inorder([&inorderKeys](BSTree<int, std::string>::Node* node) {
		inorderKeys.push_back(node->key);
	});

	EXPECT_TRUE(std::is_sorted(inorderKeys.begin(), inorderKeys.end()));
	EXPECT_EQ(inorderKeys.size(), 70);
	EXPECT_EQ(inorderKeys, remainingKeys);
	if (!inorderKeys.empty()) {
		int firstKey = inorderKeys[0];
		int middleKey = inorderKeys[inorderKeys.size() / 2];
		int lastKey = inorderKeys.back();

		largeTree.remove(firstKey);
		largeTree.remove(middleKey);
		largeTree.remove(lastKey);

		std::vector<int> modifiedInorder;
		largeTree.inorder([&modifiedInorder](BSTree<int, std::string>::Node* node) {
			modifiedInorder.push_back(node->key);
		});

		EXPECT_TRUE(std::is_sorted(modifiedInorder.begin(), modifiedInorder.end()));
		EXPECT_EQ(modifiedInorder.size(), 67);
	}
}

TEST_F(BSTreeTest, CopyConstructor) {
	Tree::BSTree<int, std::string, LessIntComparator> new_t{tree};
	std::vector<int> keys;
	for (auto it = new_t.begin(); it != new_t.end(); ++it) {
		keys.push_back((*it)->key);
	}
	EXPECT_EQ(keys, (std::vector<int>{1, 3, 4, 5, 6, 7}));
}

TEST_F(BSTreeTest, MoveConstructor) {
	Tree::BSTree<int, std::string, LessIntComparator> new_t{std::move(tree)};
	std::vector<int> keys;
	for (auto it = new_t.begin(); it != new_t.end(); ++it) {
		keys.push_back((*it)->key);
	}
	ASSERT_EQ(tree.size(), 0);
	EXPECT_EQ(keys, (std::vector<int>{1, 3, 4, 5, 6, 7}));
}

TEST_F(BSTreeTest, CopyOperatorEq) {
	Tree::BSTree<int, std::string, LessIntComparator> new_t = tree;
	std::vector<int> keys;
	for (auto it = new_t.begin(); it != new_t.end(); ++it) {
		keys.push_back((*it)->key);
	}
	EXPECT_EQ(keys, (std::vector<int>{1, 3, 4, 5, 6, 7}));
}

TEST_F(BSTreeTest, MoveOperatorEq) {
	Tree::BSTree<int, std::string, LessIntComparator> new_t = std::move(tree);
	std::vector<int> keys;
	for (auto it = new_t.begin(); it != new_t.end(); ++it) {
		keys.push_back((*it)->key);
	}
	ASSERT_EQ(tree.size(), 0);
	EXPECT_EQ(keys, (std::vector<int>{1, 3, 4, 5, 6, 7}));
}

TEST(ComporatorTest, DefaultComporatorT) {
	bool res = DefaultComparator<int>()(12, 13);
	EXPECT_EQ(res, true);
}

TEST(ComporatorTest, LessComporatorT) {
	bool res = LessIntComparator()(12, 13);
	EXPECT_EQ(res, true);
}

TEST(ComporatorTest, GreaterComporatorT) {
	bool res = GreaterIntComparator()(14, 13);
	EXPECT_EQ(res, true);
}