#pragma once

#include <iostream>
#include <stack>

#include "bst_tree.hpp"
#include "comparator.hpp"

namespace Tree {
template <typename Key, typename Value, typename Comparator = DefaultComparator<Key>>
class RedBlackTree : public BSTree<Key, Value, Comparator> {
   public:
	struct Node : public BSTree<Key, Value, Comparator>::Node {
		unsigned char color = 1;
		// red - 1
		// black - 0

		Node(const Key& key, const Value& value, unsigned char color = 1);
	};

	RedBlackTree() = default;
	RedBlackTree(const Key& key, const Value& value);
	RedBlackTree(const RedBlackTree& other);
	RedBlackTree(RedBlackTree&& other) noexcept;
	RedBlackTree& operator=(const RedBlackTree& other);
	RedBlackTree& operator=(RedBlackTree&& other) noexcept;

	void add(const Key& key, const Value& value) override;

	void remove(const Key& key) override;

	size_t get_height(BSTree<Key, Value, Comparator>::Node* node);

   private:
	void balance_insert(std::stack<std::pair<Node*, unsigned char>>& stack);
	void balance_remove(std::stack<std::pair<Node*, unsigned char>>& stack);

	Node* small_rotate_right(Node* node);
	Node* small_rotate_left(Node* node);

	BSTree<Key, Value, Comparator>::Node* copy_nodes_recursive(RedBlackTree::Node* other_node);
};

template <typename Key, typename Value, typename Comparator>
Tree::RedBlackTree<Key, Value, Comparator>::Node::Node(const Key& key, const Value& value, unsigned char color)
    : BSTree<Key, Value, Comparator>::Node(key, value), color{color} {}

template <typename Key, typename Value, typename Comparator>
void RedBlackTree<Key, Value, Comparator>::balance_remove(std::stack<std::pair<Node*, unsigned char>>& stack) {
	Node *current = nullptr, *parent = nullptr, *grand_parent = nullptr;
	unsigned char dir = 0, parent_dir = 0;
	bool current_is_left;

	while (!stack.empty()) {
		std::tie(current, dir) = stack.top();
		stack.pop();



		if (stack.empty()) {
			break;
		}
		std::tie(parent, dir) = stack.top();
		stack.pop();
		current_is_left = (dir == 0);
		Node* brother;

		if (current_is_left) {
			brother = static_cast<Node*>(parent->right);
		} else {
			brother = static_cast<Node*>(parent->left);
		}

		if (brother && brother->color == 1) {
			parent->color = 1;
			brother->color = 0;
			Node* old_parent = parent; // Сохраняем исходный родитель
			bool old_current_is_left = current_is_left; // Сохраняем направление до поворота
			if (current_is_left) {
				parent = small_rotate_left(parent);
			} else {
				parent = small_rotate_right(parent);
			}
			if (!stack.empty()) {
				std::tie(grand_parent, parent_dir) = stack.top();
				if (parent_dir == 0)
					grand_parent->left = parent;
				else
					grand_parent->right = parent;
			} else {
				this->head = parent;
			}
			if (old_current_is_left) {
				brother = static_cast<Node*>(old_parent->right);
				stack.emplace(parent, 0);
			} else {
				brother = static_cast<Node*>(old_parent->left);
				stack.emplace(parent, 1);
			}
			parent = old_parent;
		}

		bool left_black = !brother->left || static_cast<Node*>(brother->left)->color == 0;
		bool right_black = !brother->right || static_cast<Node*>(brother->right)->color == 0;

		if (left_black && right_black) {
			brother->color = 1;
			if (parent->color == 0) {
				stack.emplace(parent, dir);
				continue;
			}
			parent->color = 0;
			break;
		}
		if (current_is_left) {
			if (right_black) {
				static_cast<Node*>(brother->left)->color = 0;
				brother->color = 1;
				parent->right = small_rotate_right(brother);
				brother = static_cast<Node*>(parent->right);
				brother->color = 0;
			}
			brother->color = parent->color;
			parent->color = 0;
			static_cast<Node*>(brother->right)->color = 0;
			parent = small_rotate_left(parent);
		} else {
			if (!brother->left || static_cast<Node*>(brother->left)->color == 0) {
				static_cast<Node*>(brother->right)->color = 0;
				brother->color = 1;
				parent->left = small_rotate_left(brother);
				brother = static_cast<Node*>(parent->left);
			}

			brother->color = parent->color;
			parent->color = 0;
			static_cast<Node*>(brother->left)->color = 0;
			parent = small_rotate_right(parent);
		}

		if (!stack.empty()) {
			std::tie(grand_parent, dir) = stack.top();
			if (dir == 0)
				grand_parent->left = parent;
			else
				grand_parent->right = parent;
		} else {
			this->head = parent;
		}
		break;
	}

	if (this->head) static_cast<Node*>(this->head)->color = 0;
}

template <typename Key, typename Value, typename Comparator>
void RedBlackTree<Key, Value, Comparator>::remove(const Key& key) {
	if (this->size_ == 0) {
		throw std::runtime_error("remove from empty tree");
	}
	std::stack<std::pair<Node*, unsigned char>> stack;
	Node* current = static_cast<Node*>(this->head);
	while (current) {
		if (current->key == key) {
			break;
		}
		if (Comparator()(key, current->key)) {
			stack.emplace(current, 0);
			current = static_cast<Node*>(current->left);
		} else {
			stack.emplace(current, 1);
			current = static_cast<Node*>(current->right);
		}
	}
	if (current == nullptr) {
		throw std::runtime_error("remove not exist element");
	}
	this->size_ -= 1;
	Node* parent;
	unsigned char dir;
	if (current->left == nullptr and current->right == nullptr) {
		if (current == this->head) {
			this->head = nullptr;
		} else {
			std::tie(parent, dir) = stack.top();
			if (dir == 0) {
				parent->left = nullptr;
			} else {
				parent->right = nullptr;
			}
			if(current->color == 0) {
				stack.push({nullptr, dir});
				balance_remove(stack);
			}
		}
		delete current;
	} else if (current->left == nullptr or current->right == nullptr) {
		Node* ref;
		std::tie(parent, dir) = stack.top();
		if (current->left == nullptr) {
			ref = static_cast<Node*>(current->right);
		} else {
			ref = static_cast<Node*>(current->left);
		}
		if (dir == 0) {
			parent->left = ref;
		} else {
			parent->right = ref;
		}
		stack.emplace(ref, dir);
		if (current->color == 0) {
			balance_remove(stack);
		}
		delete current;
	} else {
		Node* tmp = static_cast<Node*>(current->right);
		stack.emplace(current, 1);
		while (tmp->left) {
			stack.emplace(tmp, 0);
			tmp = static_cast<Node*>(tmp->left);
		}
		std::tie(parent, dir) = stack.top();
		current->key = tmp->key;
		current->value = tmp->value;
		if (dir == 0) {
			parent->left = tmp->right;
			stack.emplace(static_cast<Node*>(tmp->right), 1);
		} else {
			parent->right = tmp->right;
			stack.emplace(static_cast<Node*>(tmp->right), 1);
		}


		if (tmp->color == 0) {
			balance_remove(stack);
		}
		delete tmp;
	}
}

template <typename Key, typename Value, typename Comparator>
RedBlackTree<Key, Value, Comparator>& RedBlackTree<Key, Value, Comparator>::operator=(RedBlackTree&& other) noexcept {
	if (this != &other) {
		this->clear();
		this->head = other.head;
		this->size_ = other.size_;
		other.head = nullptr;
		other.size_ = 0;
	}
	return *this;
}

template <typename Key, typename Value, typename Comparator>
RedBlackTree<Key, Value, Comparator>& RedBlackTree<Key, Value, Comparator>::operator=(const RedBlackTree& other) {
	if (&other != this) {
		BSTree<Key, Value, Comparator>::clear();
		BSTree<Key, Value, Comparator>::head = copy_nodes_recursive(static_cast<Node*>(other.head));
		;
		BSTree<Key, Value, Comparator>::size_ = other.size_;
	}
	return *this;
}

template <typename Key, typename Value, typename Comparator>
RedBlackTree<Key, Value, Comparator>::RedBlackTree(RedBlackTree&& other) noexcept : BSTree<Key, Value, Comparator>() {
	std::swap(this->head, other.head);
	std::swap(this->size_, other.size_);
}
template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::Node* RedBlackTree<Key, Value, Comparator>::copy_nodes_recursive(
    RedBlackTree::Node* other_node) {
	if (!other_node) {
		return nullptr;
	}
	Node* new_node = new Node{other_node->key, other_node->value, other_node->color};
	new_node->left = copy_nodes_recursive(static_cast<Node*>(other_node->left));
	new_node->right = copy_nodes_recursive(static_cast<Node*>(other_node->right));
	return new_node;
}
template <typename Key, typename Value, typename Comparator>
RedBlackTree<Key, Value, Comparator>::RedBlackTree(const RedBlackTree& other) : BSTree<Key, Value, Comparator>() {
	this->size_ = other.size_;
	this->head = copy_nodes_recursive(static_cast<Node*>(other.head));
}

template <typename Key, typename Value, typename Comparator>
void RedBlackTree<Key, Value, Comparator>::balance_insert(std::stack<std::pair<Node*, unsigned char>>& stack) {
	Node *current, *parent, *grand_parent, *grand_grand_parent;
	unsigned char dir, parent_dir, grand_parent_dir;
	std::tie(current, dir) = stack.top();
	stack.pop();
	while (!stack.empty()) {
		std::tie(parent, dir) = stack.top();
		stack.pop();

		if (parent->color == 0) {
			stack.emplace(parent, dir);
			break;
		}

		if (stack.empty()) {
			parent->color = 0;
			break;
		}

		std::tie(grand_parent, parent_dir) = stack.top();
		stack.pop();

		Node* uncle;
		if (parent_dir == 0) {
			uncle = static_cast<Node*>(grand_parent->right);
		} else {
			uncle = static_cast<Node*>(grand_parent->left);
		}

		if (uncle && uncle->color == 1) {
			grand_parent->color = 1;
			parent->color = 0;
			uncle->color = 0;
		} else {
			if (dir != parent_dir) {
				if (parent_dir == 0) {
					grand_parent->left = small_rotate_left(parent);
				} else {
					grand_parent->right = small_rotate_right(parent);
				}
			}

			grand_parent->color = 1;
			Node* new_grand_parent;

			if (parent_dir == 0) {
				new_grand_parent = small_rotate_right(grand_parent);
				static_cast<Node*>(new_grand_parent->right)->color = 1;
			} else {
				new_grand_parent = small_rotate_left(grand_parent);
				static_cast<Node*>(new_grand_parent->left)->color = 1;
			}

			new_grand_parent->color = 0;

			if (!stack.empty()) {
				std::tie(grand_grand_parent, grand_parent_dir) = stack.top();
				if (grand_parent_dir == 0) {
					grand_grand_parent->left = new_grand_parent;
				} else {
					grand_grand_parent->right = new_grand_parent;
				}
			} else {
				this->head = new_grand_parent;
			}
			break;
		}
	}
	static_cast<Node*>(this->head)->color = 0;
}

template <typename Key, typename Value, typename Comparator>
void RedBlackTree<Key, Value, Comparator>::add(const Key& key, const Value& value) {
	if (this->contains(key)) {
		throw std::runtime_error("such key already exist");
	}
	std::stack<std::pair<Node*, unsigned char>> stack;
	Node* current = static_cast<Node*>(BSTree<Key, Value, Comparator>::head);
	unsigned char d;
	while (current) {
		if (Comparator()(key, current->key)) {
			stack.push({current, 0});
			if (!current->left) {
				d = 0;
				break;
			}
			current = static_cast<Node*>(current->left);
		} else {
			stack.push({current, 1});
			if (!current->right) {
				d = 1;
				break;
			}
			current = static_cast<Node*>(current->right);
		}
	}
	Node* new_node = new Node{key, value};
	if (stack.empty()) {
		new_node->color = 0;
		this->size_ = 1;
		BSTree<Key, Value, Comparator>::head = static_cast<BSTree<Key, Value, Comparator>::Node*>(new_node);
		return;
	}
	if (d) {
		current->right = new_node;
	} else {
		current->left = new_node;
	}
	stack.push({new_node, d});

	balance_insert(stack);
	this->size_ += 1;
}

template <typename Key, typename Value, typename Comparator>
size_t RedBlackTree<Key, Value, Comparator>::get_height(BSTree<Key, Value, Comparator>::Node* node) {
	if (node == nullptr) {
		return 0;
	}
	return 1 + std::max(get_height(node->left), get_height(node->right));
}

template <typename Key, typename Value, typename Comparator>
RedBlackTree<Key, Value, Comparator>::RedBlackTree(const Key& key, const Value& value)
    : BSTree<Key, Value, Comparator>(key, value) {}

template <typename Key, typename Value, typename Comparator>
RedBlackTree<Key, Value, Comparator>::Node* RedBlackTree<Key, Value, Comparator>::small_rotate_right(Node* node) {
	if (node == nullptr) {
		return nullptr;  // LCOV_EXCL_LINE
	}
	Node* tmp = node;
	Node* t;
	if (tmp->left) {
		t = static_cast<Node*>(tmp->left);
		tmp->left = t->right;
		t->right = tmp;
	}
	return t;
}

template <typename Key, typename Value, typename Comparator>
RedBlackTree<Key, Value, Comparator>::Node* RedBlackTree<Key, Value, Comparator>::small_rotate_left(Node* node) {
	if (node == nullptr) {
		return nullptr;  // LCOV_EXCL_LINE
	}
	Node* tmp = (node);
	Node* t;
	if (tmp->right) {
		t = static_cast<Node*>(tmp->right);
		tmp->right = t->left;
		t->left = tmp;
	}
	return t;
}

}  // namespace Tree
