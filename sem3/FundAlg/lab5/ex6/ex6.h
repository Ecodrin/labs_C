
#ifndef LAB5_EX6_H
#define LAB5_EX6_H

#include <iostream>
#include <cstring>

class memory_allocated : std::exception {};

class incorrect_index : std::exception {};

class Vector {
   private:
	double* _data;
	size_t _size;
	size_t _capacity;



   public:
	Vector(size_t n = 10, double default_value = 0);
	~Vector();

	size_t size() const;
	size_t capacity() const;
	void reverse(size_t num = 0);
	void shrink_to_fit();
	void clear();
	void insert(size_t index, double elem);
	void erase(size_t index);

	double & at(size_t index);
	double & operator[](size_t index);
	double & front();
	double & back();
	double * data();


	const double & at(size_t index) const;
	const double & operator[](size_t index) const;
	const double & front() const;
	const double & back() const;
	const double * data() const;

};


std::ostream & operator<<(std::ostream &ostream, const Vector & vector);

#endif  // LAB5_EX6_H
