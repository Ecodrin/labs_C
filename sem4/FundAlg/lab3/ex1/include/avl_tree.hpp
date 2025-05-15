
#pragma once

#include "bst_tree.hpp"

namespace Tree {

template <typename Key, typename Value, typename Comparator = std::less<Key>>
class AVLTree : public BSTree<Key, Value, Comparator> {
   public:
	using Node = typename BSTree<Key, Value, Comparator>::Node;

   private:
	void small_rotate_left(Node** node);
	void small_rotate_right(Node** node);
	void big_rotate_left(Node** node);
	void big_rotate_right(Node** node);


	void balance(std::stack<Node*> & stack);

   public:
	AVLTree();
	AVLTree(const Key& key, const Value& value);
	void add(const Key& key, const Value& value) override;
	void remove(const Key & key) override;

	std::pair<size_t, size_t> get_height_subtrees(Node* node);
	size_t get_height(Node* node);
};

template <typename Key, typename Value, typename Comparator>
void AVLTree<Key, Value, Comparator>::balance(std::stack<Node*>& stack) {
	while (!stack.empty()) {
		Node* t = stack.top();
		Node *copy_t = t;
		stack.pop();
		std::pair<int, int> subtree_heights = get_height_subtrees(t);
		if (std::abs((int)subtree_heights.first - (int)subtree_heights.second) <= 1) {
			continue;
		}
		if (subtree_heights.first - subtree_heights.second > 1) {
			std::pair<size_t, size_t> subtree_left_heights = get_height_subtrees(t->left);
			if(subtree_left_heights.first >= subtree_left_heights.second) {
				small_rotate_right(&t);
			} else {
				big_rotate_right(&t);
			}
		} else {
			std::pair<int, int> subtree_right_heights = get_height_subtrees(t->right);
			if(subtree_right_heights.first <= subtree_right_heights.second) {
				small_rotate_left(&t);
			} else {
				big_rotate_left(&t);
			}
		}
		if(!stack.empty()) {
			Node * s_parent = stack.top();
			if(s_parent->left == copy_t) {
				s_parent->left = t;
			} else {
				s_parent->right = t;
			}
		} else {
			BSTree<Key, Value, Comparator>::head = t;
		}
	}
}
template <typename Key, typename Value, typename Comparator>
void AVLTree<Key, Value, Comparator>::remove(const Key& key) {
	if(BSTree<Key, Value, Comparator>::size_ == 0) {
		throw std::runtime_error("remove from empty bst");
	}
	Node* tmp = BSTree<Key, Value, Comparator>::head;
	Node* parent = nullptr;
	Node* current = tmp;
	std::stack<Node*> stack;

	while (current != nullptr && current->key != key) {
		parent = current;
		stack.push(parent);
		if (Comparator()(key, current->key)) {
			current = current->left;
		} else {
			current = current->right;
		}
	}

	if (current == nullptr) {
		return;
	}
	if (current->left != nullptr && current->right != nullptr) {
		Node* successor_parent = current;
		Node* successor = current->right;
		while (successor->left != nullptr) {
			successor_parent = successor;
			successor = successor->left;
		}

		current->key = successor->key;
		current->value = successor->value;

		if (successor_parent == current) {
			successor_parent->right = successor->right;
		} else {
			successor_parent->left = successor->right;
		}
		delete successor;
		BSTree<Key, Value, Comparator>::size_--;
	} else {
		Node* child = (current->left != nullptr) ? current->left : current->right;

		if (current ==  BSTree<Key, Value, Comparator>::head) {
			BSTree<Key, Value, Comparator>::head = child;
		} else {
			if (parent->left == current) {
				parent->left = child;
			} else {
				parent->right = child;
			}
		}
		delete current;
		BSTree<Key, Value, Comparator>::size_--;
	}

	balance(stack);

}

template <typename Key, typename Value, typename Comparator>
void AVLTree<Key, Value, Comparator>::add(const Key& key, const Value& value) {
	if (BSTree<Key, Value, Comparator>::head == nullptr) {
		BSTree<Key, Value, Comparator>::head = new Node{key, value};
		BSTree<Key, Value, Comparator>::size_ = 1;
		return;
	}
	Node* tmp = BSTree<Key, Value, Comparator>::head;
	Node* prev;
	std::stack<Node*> stack;
	while (tmp) {
		prev = tmp;
		if (Comparator()(tmp->key, key)) {
			stack.push(tmp);
			tmp = tmp->right;
			if (tmp == nullptr) {
				prev->right = new Node{key, value};
			}
		} else {
			stack.push(tmp);
			tmp = tmp->left;
			if (tmp == nullptr) {
				prev->left = new Node{key, value};
			}
		}
	}
	BSTree<Key, Value, Comparator>::size_ += 1;

	balance(stack);
}

template <typename Key, typename Value, typename Comparator>
void AVLTree<Key, Value, Comparator>::big_rotate_right(AVLTree::Node** node) {
	if (node == nullptr) {
		return; // LCOV_EXCL_LINE
	}
	Node* tmp = *node;
	if (tmp == nullptr or tmp->left == nullptr or tmp->left->right == nullptr) {
		return; // LCOV_EXCL_LINE
	}
	small_rotate_left(&(tmp->left));
	small_rotate_right(node);
}

template <typename Key, typename Value, typename Comparator>
void AVLTree<Key, Value, Comparator>::big_rotate_left(AVLTree::Node** node) {
	if (node == nullptr) {
		return; // LCOV_EXCL_LINE
	}
	Node* tmp = *node;
	if (tmp == nullptr or tmp->right == nullptr or tmp->right->left == nullptr) {
		return; // LCOV_EXCL_LINE
	}
	small_rotate_right(&(tmp->right));
	small_rotate_left(node);
}

template <typename Key, typename Value, typename Comparator>
void AVLTree<Key, Value, Comparator>::small_rotate_right(Node** node) {
	if (node == nullptr) {
		return; // LCOV_EXCL_LINE
	}
	Node* tmp = *node;
	if (tmp->left) {
		Node* t = tmp->left;
		tmp->left = t->right;
		t->right = tmp;
		*node = t;
	}
}

template <typename Key, typename Value, typename Comparator>
void AVLTree<Key, Value, Comparator>::small_rotate_left(Node** node) {
	if (node == nullptr or *node == nullptr) {
		return; // LCOV_EXCL_LINE
	}
	Node* tmp = *node;
	if (tmp->right) {
		Node* t = tmp->right;
		tmp->right = t->left;
		t->left = tmp;
		*node = t;
	}
}
template <typename Key, typename Value, typename Comparator>
std::pair<size_t, size_t> AVLTree<Key, Value, Comparator>::get_height_subtrees(
    BSTree<Key, Value, Comparator>::Node* node) {
	if (node == nullptr) {
		return {}; // LCOV_EXCL_LINE
	}
	return {get_height(node->left), get_height(node->right)};
}

template <typename Key, typename Value, typename Comparator>
size_t AVLTree<Key, Value, Comparator>::get_height(BSTree<Key, Value, Comparator>::Node* node) {
	if (node == nullptr) {
		return 0;
	}
	return 1 + std::max(get_height(node->left), get_height(node->right));
}

template <typename Key, typename Value, typename Comparator>
AVLTree<Key, Value, Comparator>::AVLTree(const Key& key, const Value& value)
    : BSTree<Key, Value, Comparator>(key, value) {}

template <typename Key, typename Value, typename Comparator>
AVLTree<Key, Value, Comparator>::AVLTree() : BSTree<Key, Value, Comparator>() {}
}  // namespace Tree