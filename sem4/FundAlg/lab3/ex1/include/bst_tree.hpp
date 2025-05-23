#pragma once

#include <functional>
#include <iostream>
#include <stack>

#include "comparator.hpp"

namespace Tree {

template <typename Key, typename Value, typename Comparator = DefaultComparator<int>>
class BSTree {
   protected:
	size_t size_ = 0;

   public:
	struct Node {
		Key key;
		Value value;
		Node* left = nullptr;
		Node* right = nullptr;
	};
	using CallBack = std::function<void(Node* node)>;

	Node* head = nullptr;

	BSTree() = default;
	explicit BSTree(const Key& key, const Value& value);
	BSTree(const BSTree& other);
	BSTree(BSTree&& other) noexcept;
	BSTree& operator=(const BSTree& other);
	BSTree& operator=(BSTree&& other) noexcept;

	virtual ~BSTree();

	[[nodiscard]] size_t size() const;

	class iterator {
	   private:
		std::stack<Node*> s;

	   public:
		using value_type = Node*;

		explicit iterator(Node* t, bool init_stack = true);
		iterator() = default;
		~iterator() = default;
		value_type operator*();

		iterator& operator++();
		iterator operator++(int);

		bool operator==(const BSTree::iterator& other) const;
		bool operator!=(const BSTree::iterator& other) const;
	};

	virtual void add(const Key& key, const Value& value);
	virtual iterator find(const Key& key) const;
	bool contains(const Key& key) const;
	virtual void remove(const Key& key);

	void inorder(CallBack call_back);
	void preorder(CallBack call_back);
	void postorder(CallBack call_back);

	iterator begin() noexcept;
	iterator begin() const noexcept;
	iterator cbegin() const noexcept;
	iterator end() noexcept;
	iterator end() const noexcept;
	iterator cend() const noexcept;

	void clear();

   private:
	Node* copy_nodes_recursive(Node* other_node);
};

template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>& BSTree<Key, Value, Comparator>::operator=(BSTree&& other) noexcept {
	if (this == &other) {
		return *this;
	}
	clear();

	head = other.head;
	size_ = other.size_;

	other.head = nullptr;
	other.size_ = 0;

	return *this;
}

template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>& BSTree<Key, Value, Comparator>::operator=(const BSTree& other) {
	if (this == &other) {
		return *this;
	}
	clear();
	head = copy_nodes_recursive(other.head);
	size_ = other.size_;
	return *this;
}

template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::BSTree(BSTree&& other) noexcept : size_(other.size_), head(other.head) {
	other.head = nullptr;
	other.size_ = 0;
}

template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::BSTree(const BSTree& other) : size_(other.size_) {
	head = copy_nodes_recursive(other.head);
}
template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::Node* BSTree<Key, Value, Comparator>::copy_nodes_recursive(BSTree::Node* other_node) {
	if (!other_node) {
		return nullptr;
	}
	Node* new_node = new Node{other_node->key, other_node->value};
	new_node->left = copy_nodes_recursive(other_node->left);
	new_node->right = copy_nodes_recursive(other_node->right);
	return new_node;
}

template <typename Key, typename Value, typename Comparator>
void BSTree<Key, Value, Comparator>::remove(const Key& key) {
	if (size_ == 0) {
		throw std::runtime_error("remove from empty bst");
	}

	Node* parent = nullptr;
	Node* current = head;

	while (current != nullptr && current->key != key) {
		parent = current;
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
		size_--;
	} else {
		Node* child = (current->left != nullptr) ? current->left : current->right;

		if (current == head) {
			head = child;
		} else {
			if (parent->left == current) {
				parent->left = child;
			} else {
				parent->right = child;
			}
		}
		delete current;
		size_--;
	}
}
template <typename Key, typename Value, typename Comparator>
bool BSTree<Key, Value, Comparator>::contains(const Key& key) const {
	return find(key) != end();
}

template <typename Key, typename Value, typename Comparator>
void BSTree<Key, Value, Comparator>::clear() {
	postorder([](Node* node) { delete node; });
	size_ = 0;
	head = nullptr;
}

template <typename Key, typename Value, typename Comparator>
size_t BSTree<Key, Value, Comparator>::size() const {
	return size_;
}

template <typename Key, typename Value, typename Comparator>
bool Tree::BSTree<Key, Value, Comparator>::iterator::operator==(
    const Tree::BSTree<Key, Value, Comparator>::iterator& other) const {
	return s == other.s;
}

template <typename Key, typename Value, typename Comparator>
bool Tree::BSTree<Key, Value, Comparator>::iterator::operator!=(
    const Tree::BSTree<Key, Value, Comparator>::iterator& other) const {
	return s != other.s;
}

template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::iterator::value_type Tree::BSTree<Key, Value, Comparator>::iterator::operator*() {
	return s.top();
}

template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::iterator::iterator(Tree::BSTree<Key, Value, Comparator>::Node* t, bool init_stack) {
	if (init_stack) {
		while (t) {
			s.push(t);
			t = t->left;
		}
	} else if (t != nullptr) {
		s.push(t);
	}
}

template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::iterator& Tree::BSTree<Key, Value, Comparator>::iterator::operator++() {
	Node* p = s.top();
	s.pop();

	Node* ri = p->right;
	while (ri) {
		s.push(ri);
		ri = ri->left;
	}
	return *this;
}
template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::iterator Tree::BSTree<Key, Value, Comparator>::iterator::operator++(int) {
	BSTree::iterator iterator1 = *this;
	++(*this);
	return iterator1;
}

template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::iterator BSTree<Key, Value, Comparator>::end() const noexcept {
	return iterator{};
}
template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::iterator BSTree<Key, Value, Comparator>::end() noexcept {
	return iterator{};
}

template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::iterator BSTree<Key, Value, Comparator>::cend() const noexcept {
	return iterator{};
}
template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::iterator BSTree<Key, Value, Comparator>::begin() const noexcept {
	return iterator{head};
}
template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::iterator BSTree<Key, Value, Comparator>::begin() noexcept {
	return iterator{head};
}

template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::iterator BSTree<Key, Value, Comparator>::cbegin() const noexcept {
	return iterator{head};
}

template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::~BSTree() {
	clear();
}

template <typename Key, typename Value, typename Comparator>
void BSTree<Key, Value, Comparator>::postorder(BSTree::CallBack call_back) {
	if (head == nullptr) {
		return;
	}
	std::stack<Node*> stack;
	std::stack<Node*> stack2;
	Node* t = head;
	stack.push(t);
	while (!stack.empty()) {
		t = stack.top();
		stack.pop();
		stack2.push(t);
		if (t->left) stack.push(t->left);
		if (t->right) stack.push(t->right);
	}
	while (!stack2.empty()) {
		call_back(stack2.top());
		stack2.pop();
	}
}

template <typename Key, typename Value, typename Comparator>
void BSTree<Key, Value, Comparator>::preorder(BSTree::CallBack call_back) {
	if (head == nullptr) {
		return;
	}
	std::stack<Node*> stack;
	Node* t = head;
	stack.push(t);
	while (!stack.empty()) {
		t = stack.top();
		stack.pop();
		call_back(t);
		if (t->right) stack.push(t->right);
		if (t->left) stack.push(t->left);
	}
}

template <typename Key, typename Value, typename Comparator>
void BSTree<Key, Value, Comparator>::inorder(BSTree::CallBack call_back) {
	if (head == nullptr) {
		return;
	}
	std::stack<Node*> stack;
	Node* t = head;
	while (t || !stack.empty()) {
		while (t) {
			stack.push(t);
			t = t->left;
		}
		t = stack.top();
		stack.pop();
		call_back(t);
		t = t->right;
	}
}

template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::iterator BSTree<Key, Value, Comparator>::find(const Key& key) const {
	Node* tmp = head;
	while (tmp) {
		if (tmp->key == key) {
			return iterator{tmp, false};
		}
		if (Comparator()(tmp->key, key)) {
			tmp = tmp->right;
		} else {
			tmp = tmp->left;
		}
	}
	return end();
}

template <typename Key, typename Value, typename Comparator>
BSTree<Key, Value, Comparator>::BSTree(const Key& key, const Value& value) {
	head = new Node{key, value};
	size_ = 1;
}

template <typename Key, typename Value, typename Comparator>
void BSTree<Key, Value, Comparator>::add(const Key& key, const Value& value) {
	if (head == nullptr) {
		head = new Node{key, value};
		size_ = 1;
		return;
	}
	Node* tmp = head;
	Node* prev;
	while (tmp) {
		prev = tmp;
		if (Comparator()(tmp->key, key)) {
			tmp = tmp->right;
			if (tmp == nullptr) {
				prev->right = new Node{key, value};
			}
		} else {
			tmp = tmp->left;
			if (tmp == nullptr) {
				prev->left = new Node{key, value};
			}
		}
	}
	size_ += 1;
}

}  // namespace Tree