
#ifndef LAB5_EX7_H
#define LAB5_EX7_H

#include <iostream>
#include <string>
#include <vector>

class incorrect_data_product : std::exception {};

class incorrect_date : std::exception {};

class Date {
   private:
	void is_correct_date() const;

   public:
	size_t day;
	size_t month;
	size_t year;

	Date(size_t day, size_t month, size_t year);
	Date(size_t days = 0);


	int operator<=>(const Date& other) const;
};

std::ostream& operator<<(std::ostream& ostream, const Date& date);

class Product {
   private:
	void is_correct_product() const;

   public:
	std::string name;
	size_t id;
	double weight;
	double price;
	unsigned int shelf_life_in_days;

	Product(const std::string& _name, size_t _id, double _weight, double _price, unsigned int _shelf_life_in_days);
	Product(const Product& product);
	~Product();

	Product& operator=(const Product& product);

	virtual void displayInfo() const;
	virtual double calculateStorageFee() const;
};

class PerishableProduct : public Product {
   public:
	Date expirationDate;

	PerishableProduct(const std::string& name, size_t id, double weight, double price, unsigned int shelfLifeInDays);
	double calculateStorageFee() const override;
};
#endif  // LAB5_EX7_H
