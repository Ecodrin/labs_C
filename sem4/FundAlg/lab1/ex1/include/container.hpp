//
// Created by matvey on 3/7/25.
//

#pragma once

template <typename T>
class Container {
   public:
	using value_type = T;
	using reference = T&;
	using const_reference = const T&;
	using iterator = T*;
	using const_iterator = const T*;
	using difference_type = ptrdiff_t;

	Container() = default;
	Container(const Container& container) = default;
	Container& operator=(const Container& container) = default;
	virtual ~Container() = default;

	virtual iterator begin() noexcept = 0;
	virtual const_iterator cbegin() const  noexcept  = 0;
	virtual iterator end() noexcept  = 0;
	virtual const_iterator cend() const noexcept = 0;

	bool operator==(const Container& other) const = default;
	bool operator!=(const Container& other) const = default;

	virtual size_t size() const = 0;
	virtual size_t max_size() const = 0;
	virtual bool empty() const = 0;
};