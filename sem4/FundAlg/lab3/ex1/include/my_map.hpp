#pragma once

#include <iostream>

#include "bst_tree.hpp"
#include "comporator.hpp"

template <typename Key, typename Value, template <typename, typename, typename> class TreeType,
          typename Comparator = DefaultComparator<Key>>
class MyMap {
	TreeType<Key, Value, Comparator> tree_;

   public:
	MyMap() = default;
	void insert(const Key& key, const Value& value);
	Value * find(const Key & key);
	bool contains(const Key & key);
	void remove(const Key & key);

	void clear();
	[[nodiscard]] size_t size() const;

	TreeType<Key, Value, Comparator>::iterator begin() noexcept;
	TreeType<Key, Value, Comparator>::iterator end() noexcept;
	TreeType<Key, Value, Comparator>::iterator begin() const noexcept;
	TreeType<Key, Value, Comparator>::iterator end() const noexcept;
	TreeType<Key, Value, Comparator>::iterator cbegin() const noexcept;
	TreeType<Key, Value, Comparator>::iterator cend() const noexcept;

};

template <typename Key, typename Value, template <typename, typename, typename> class TreeType, typename Comparator>
TreeType<Key, Value, Comparator>::iterator MyMap<Key, Value, TreeType, Comparator>::cend() const noexcept {
	return tree_.end();
}

template <typename Key, typename Value, template <typename, typename, typename> class TreeType, typename Comparator>
TreeType<Key, Value, Comparator>::iterator MyMap<Key, Value, TreeType, Comparator>::cbegin() const noexcept {
	return tree_.begin();
}

template <typename Key, typename Value, template <typename, typename, typename> class TreeType, typename Comparator>
TreeType<Key, Value, Comparator>::iterator MyMap<Key, Value, TreeType, Comparator>::end() const noexcept {
	return tree_.end();
}

template <typename Key, typename Value, template <typename, typename, typename> class TreeType, typename Comparator>
TreeType<Key, Value, Comparator>::iterator MyMap<Key, Value, TreeType, Comparator>::begin() const noexcept {
	return tree_.begin();
}

template <typename Key, typename Value, template <typename, typename, typename> class TreeType, typename Comparator>
TreeType<Key, Value, Comparator>::iterator MyMap<Key, Value, TreeType, Comparator>::end() noexcept {
	return tree_.end();
}

template <typename Key, typename Value, template <typename, typename, typename> class TreeType, typename Comparator>
TreeType<Key, Value, Comparator>::iterator MyMap<Key, Value, TreeType, Comparator>::begin() noexcept {
	return tree_.begin();
}

template <typename Key, typename Value, template <typename, typename, typename> class TreeType, typename Comparator>
size_t MyMap<Key, Value, TreeType, Comparator>::size() const {
	return tree_.size();
}

template <typename Key, typename Value, template <typename, typename, typename> class TreeType, typename Comparator>
void MyMap<Key, Value, TreeType, Comparator>::remove(const Key& key) {
	tree_.remove(key);
}

template <typename Key, typename Value, template <typename, typename, typename> class TreeType, typename Comparator>
bool MyMap<Key, Value, TreeType, Comparator>::contains(const Key& key) {
	return tree_.contains(key);
}

template <typename Key, typename Value, template <typename, typename, typename> class TreeType, typename Comparator>
void MyMap<Key, Value, TreeType, Comparator>::clear() {
	tree_.clear();
}

template <typename Key, typename Value, template <typename, typename, typename> class TreeType, typename Comparator>
Value* MyMap<Key, Value, TreeType, Comparator>::find(const Key& key) {
	return tree_.find(key);
}

template <typename Key, typename Value, template <typename, typename, typename> class TreeType, typename Comparator>
void MyMap<Key, Value, TreeType, Comparator>::insert(const Key& key, const Value& value) {
	tree_.add(key, value);
}
