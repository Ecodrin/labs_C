#include "ex7.h"

void Product::is_correct_product() const {
	if (name.empty() or weight <= 0 or price < 0) {
		throw incorrect_data_product();
	}
}
Product::Product(const std::string& _name, size_t _id, double _weight, double _price, unsigned int _shelf_life_in_days)
    : name(_name), id(_id), weight(_weight), price(_price) , shelf_life_in_days(_shelf_life_in_days) {
	is_correct_product();
}
Product::Product(const Product& product) {
	name = product.name;
	id = product.id;
	weight = product.weight;
	price = product.weight;
	shelf_life_in_days = product.shelf_life_in_days;
	is_correct_product();
}
Product& Product::operator=(const Product& product) {
	name = product.name;
	id = product.id;
	weight = product.weight;
	price = product.weight;
	shelf_life_in_days = product.shelf_life_in_days;
	is_correct_product();
	return *this;
}
Product::~Product() {
	id = 0;
	weight = 0;
	price = 0;
	shelf_life_in_days = 0;
	std::destroy(name.begin(), name.end());
}
void Product::displayInfo() const {
	std::cout << "Product: " << name << std::endl;
	std::cout << "Id: " << id << std::endl;
	std::cout << "Weight: " << weight << std::endl;
	std::cout << "Price: " << price << std::endl;
	std::cout << "Shelf life in days: " << shelf_life_in_days << std::endl;
}
double Product::calculateStorageFee() const { return weight * price * shelf_life_in_days; }

void Date::is_correct_date() const {
	if (month < 1 || month > 12 || year < 0) {
		throw incorrect_date();
	}

	switch (month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (day < 1 || day > 31) {
				throw incorrect_date();
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if (day < 1 || day > 30) {
				throw incorrect_date();
			}
			break;
		case 2:
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
				if (day < 1 || day > 29) {
					throw incorrect_date();
				}
			} else {
				if (day < 1 || day > 28) {
					throw incorrect_date();
				}
			}
			break;
		default:
			throw incorrect_date();
	}
}
Date::Date(size_t day, size_t month, size_t year) {
	this->day = day;
	this->month = month;
	this->year = year;
	is_correct_date();
}
Date::Date(size_t days) {
	year = 1970;
	month = 1;
	day = 1;

	const size_t days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	while (days > 0) {
		bool is_leap_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		size_t days_in_current_month = days_in_month[month - 1];
		if (month == 2 && is_leap_year) {
			days_in_current_month = 29;
		}

		if (days >= days_in_current_month) {
			days -= days_in_current_month;
			month++;
			if (month > 12) {
				month = 1;
				year++;
			}
		} else {
			day += days;
			days = 0;
		}
	}
}
int Date::operator<=>(const Date& other) const {
	if (other.year != year) {
		return year - other.year;
	}
	if (month != other.month) {
		return month - other.month;
	}
	return day - other.day;
}

double PerishableProduct::calculateStorageFee() const {
	// TODO
}

PerishableProduct::PerishableProduct(const std::string& name, size_t id, double weight, double price,
                                     unsigned int shelfLifeInDays)
    : Product(name, id, weight, price, shelfLifeInDays) {
	expirationDate = {shelfLifeInDays};
}

std::ostream& operator<<(std::ostream& ostream, const Date& date) {
	ostream << date.day << "." << date.month << "." << date.year;
	return ostream;
}