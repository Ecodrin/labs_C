#pragma once

template <typename T>
class DefaultComparator {
   public:
	virtual bool operator()(const T & lhs, const T & rhs) const {
		return lhs < rhs;
	}
};

class LessIntComparator : public DefaultComparator<int>{
   public:
	bool operator()(const int & lhs, const int & rhs)const override {
		return lhs < rhs;
	}
};

class GreaterIntComparator : public DefaultComparator<int>{
   public:
	bool operator()(const int & lhs, const int & rhs)const override {
		return lhs > rhs;
	}
};