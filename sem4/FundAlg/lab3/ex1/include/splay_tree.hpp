#pragma once

#include "bst_tree.hpp"
#include "comparator.hpp"

namespace Tree {

template <typename Key, typename Value, typename Comparator = DefaultComparator<Key>>
class SplayTree : public Tree::BSTree<Key, Value, Comparator> {
   public:
	using Node = typename BSTree<Key, Value, Comparator>::Node;
	using iterator = typename BSTree<Key, Value, Comparator>::iterator;

   private:
	void rotate_left(Node* cur, Node** parent);
	void rotate_right(Node* cur, Node** parent);
	void splay(Node* current, std::stack<Node*> stack);
	Node* merge_subtrees(SplayTree::Node* tree1, SplayTree::Node* tree2);

   public:
	SplayTree();
	SplayTree(const Key& key, const Value& value);

	SplayTree(const SplayTree& other);
	SplayTree(SplayTree&& other) noexcept;
	SplayTree& operator=(const SplayTree& other);
	SplayTree& operator=(SplayTree&& other) noexcept;

	size_t get_height(Node* node);

	void add(const Key& key, const Value& value) override;
	void remove(const Key& key) override;
	iterator find(const Key & key);

};

template <typename Key, typename Value, typename Comparator>
SplayTree<Key, Value, Comparator>::iterator SplayTree<Key, Value, Comparator>::find(const Key& key) {
	Node* tmp =  BSTree<Key, Value, Comparator>::head;
	std::stack<Node*> stack;
	while (tmp) {
		if (tmp->key == key) {
			break;
		}
		stack.push(tmp);
		if (Comparator()(tmp->key, key)) {
			tmp = tmp->right;
		} else {
			tmp = tmp->left;
		}
	}
	if(tmp == nullptr) {
		return iterator();
	}
	splay(tmp, stack);
	return iterator( BSTree<Key, Value, Comparator>::head, false);
}

template <typename Key, typename Value, typename Comparator>
SplayTree<Key, Value, Comparator>& SplayTree<Key, Value, Comparator>::operator=(const SplayTree& other) {
	if (this != &other) {
		BSTree<Key, Value, Comparator>::operator=(other);
	}
	return *this;
}

template <typename Key, typename Value, typename Comparator>
SplayTree<Key, Value, Comparator>& SplayTree<Key, Value, Comparator>::operator=(SplayTree&& other) noexcept {
	if (this != &other) {
		BSTree<Key, Value, Comparator>::operator=(std::move(other));
	}
	return *this;
}

template <typename Key, typename Value, typename Comparator>
SplayTree<Key, Value, Comparator>::SplayTree(SplayTree&& other) noexcept : BSTree<Key, Value, Comparator>{std::move(other)} {}
template <typename Key, typename Value, typename Comparator>
SplayTree<Key, Value, Comparator>::SplayTree(const SplayTree& other) : BSTree<Key, Value, Comparator>{other} {}

template <typename Key, typename Value, typename Comparator>
void SplayTree<Key, Value, Comparator>::remove(const Key& key) {
	if(BSTree<Key, Value, Comparator>::size_ == 0) {
		throw std::runtime_error("remove from empty tree");
	}
	std::stack<Node*> stack;
	Node* current = BSTree<Key, Value, Comparator>::head;
	Node* parent = nullptr;

	while (current) {
		parent = current;
		stack.push(parent);

		if (key == parent->key) break;
		if (Comparator{}(key, parent->key)) {
			current = current->left;
		} else {
			current = current->right;
		}
	}

	if (current == nullptr) {
		return;
	}
	stack.pop();
	splay(current, stack);

	Node* left_tree = BSTree<Key, Value, Comparator>::head->left;
	Node* right_tree = BSTree<Key, Value, Comparator>::head->right;
	delete BSTree<Key, Value, Comparator>::head;
	BSTree<Key, Value, Comparator>::head = merge_subtrees(left_tree, right_tree);
	BSTree<Key, Value, Comparator>::size_ -= 1;
}

template <typename Key, typename Value, typename Comparator>
SplayTree<Key, Value, Comparator>::Node* SplayTree<Key, Value, Comparator>::merge_subtrees(SplayTree::Node* tree1,
                                                                                  SplayTree::Node* tree2) {
	if (tree1 == nullptr or tree2 == nullptr) {
		return nullptr;
	}
	Node* current = tree1;
	std::stack<Node*> stack;
	Node* prev = nullptr;
	while (current) {
		stack.push(current);
		prev = current;
		current = current->right;
	}
	if (prev) {
		stack.pop();
		splay(prev, stack);
	}
	tree1 = BSTree<Key, Value, Comparator>::head;
	tree1->right = tree2;
	return tree1;
}

template <typename Key, typename Value, typename Comparator>
void SplayTree<Key, Value, Comparator>::splay(SplayTree::Node* current, std::stack<Node*> stack) {
	while (stack.size() > 2) {
		Node* parent = stack.top();
		stack.pop();
		Node* grand_parent = stack.top();
		stack.pop();
		Node* grand_grand_parent = stack.top();
		stack.pop();

		Node** grand_grand_parent_ref;

		if (grand_grand_parent->left == grand_parent) {
			grand_grand_parent_ref = &grand_grand_parent->left;
		} else {
			grand_grand_parent_ref = &grand_grand_parent->right;
		}

		if (current == parent->left) {
			if (parent == grand_parent->left) {
				// Zig-Zig (левый-левый)
				rotate_right(grand_parent, grand_grand_parent_ref);
				rotate_right(parent, grand_grand_parent_ref);
			} else {
				// Zig-Zag (правый-левый)
				rotate_right(parent, &grand_parent->right);
				rotate_left(grand_parent, grand_grand_parent_ref);
			}
		} else {
			if (parent == grand_parent->right) {
				// Zig-Zig (правый-правый)
				rotate_left(grand_parent, grand_grand_parent_ref);
				rotate_left(parent, grand_grand_parent_ref);
			} else {
				// Zig-Zag (левый-правый)
				rotate_left(parent, &grand_parent->left);
				rotate_right(grand_parent, grand_grand_parent_ref);
			}
		}
		stack.push(grand_grand_parent);
	}

	if (stack.size() == 2) {
		Node* parent = stack.top();
		stack.pop();
		Node* grand_parent = stack.top();
		stack.pop();

		Node** parent_ref;
		if (grand_parent->left == parent) {
			parent_ref = &grand_parent->left;
		} else {
			parent_ref = &grand_parent->right;
		}

		if (parent->left == current) {
			rotate_right(parent, parent_ref);  // Zig
		} else {
			rotate_left(parent, parent_ref);  // Zag
		}
		stack.push(grand_parent);
	}

	if (stack.size() == 1) {
		Node* parent = stack.top();
		stack.pop();

		Node** parent_ref = &(BSTree<Key, Value, Comparator>::head);
		if (parent->left == current) {
			rotate_right(parent, parent_ref);
		} else {
			rotate_left(parent, parent_ref);
		}
	}

	BSTree<Key, Value, Comparator>::head = current;
}
template <typename Key, typename Value, typename Comparator>
size_t SplayTree<Key, Value, Comparator>::get_height(SplayTree::Node* node) {
	if (node == nullptr) {
		return 0;
	}
	return 1 + std::max(get_height(node->left), get_height(node->right));
}

template <typename Key, typename Value, typename Comparator>
void SplayTree<Key, Value, Comparator>::add(const Key& key, const Value& value) {
	if (BSTree<Key, Value, Comparator>::head == nullptr) {
		BSTree<Key, Value, Comparator>::head = new Node{key, value};
		BSTree<Key, Value, Comparator>::size_ = 1;
		return;
	}

	Node* current = BSTree<Key, Value, Comparator>::head;
	Node* prev_current;
	std::stack<Node*> stack;
	while (current) {
		prev_current = current;
		if (Comparator()(current->key, key)) {
			stack.push(current);
			current = current->right;
			if (current == nullptr) {
				current = prev_current->right = new Node{key, value};
				break;
			}
		} else {
			stack.push(current);
			current = current->left;
			if (current == nullptr) {
				current = prev_current->left = new Node{key, value};
				break;
			}
		}
	}
	BSTree<Key, Value, Comparator>::size_ += 1;

	splay(current, stack);
}

template <typename Key, typename Value, typename Comparator>
SplayTree<Key, Value, Comparator>::SplayTree(const Key& key, const Value& value)
    : Tree::BSTree<Key, Value, Comparator>(key, value) {}

template <typename Key, typename Value, typename Comparator>
SplayTree<Key, Value, Comparator>::SplayTree() : Tree::BSTree<Key, Value, Comparator>() {}

template <typename Key, typename Value, typename Comparator>
void SplayTree<Key, Value, Comparator>::rotate_right(Node* cur, Node** parent) {
	if (cur == nullptr or parent == nullptr) {
		return; // LCOV_EXCL_LINE
	}
	Node* new_cur = cur->left;
	cur->left = new_cur->right;
	new_cur->right = cur;
	*parent = new_cur;
}
template <typename Key, typename Value, typename Comparator>
void SplayTree<Key, Value, Comparator>::rotate_left(Node* cur, Node** parent) {
	if (cur == nullptr or parent == nullptr) {
		return; // LCOV_EXCL_LINE
	}
	Node* new_cur = cur->right;
	cur->right = new_cur->left;
	new_cur->left = cur;
	*parent = new_cur;
}



}  // namespace Tree
