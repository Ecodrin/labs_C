
#include "ex4.hpp"
Complex Complex::operator+(const Complex& second) const {
	return Complex{real + second.get_real(), imaginary + second.get_imaginary()};
}
Complex Complex::operator-(const Complex& second) const {
	return Complex{real - second.get_real(), imaginary - second.get_imaginary()};
}
Complex Complex::operator*(const Complex& second) const {
	return Complex{real * second.get_real() - imaginary * second.get_imaginary(),
	               imaginary * second.get_real() + real * second.get_imaginary()};
}

Complex Complex::operator/(const Complex& second) const {
	if (std::fabs(second.absolute()) < 1e-20) {
		throw std::invalid_argument("div by null");
	}
	return Complex{(real * second.get_real() + imaginary * second.get_imaginary()) /
	                   (second.get_real() * second.get_real() + second.get_imaginary() * second.get_imaginary()),
	               (imaginary * second.get_real() - real * second.get_imaginary()) /
	                   (second.get_real() * second.get_real() + second.get_imaginary() * second.get_imaginary())};
}

double Complex::get_real() const { return real; }
double Complex::get_imaginary() const { return imaginary; }
Complex& Complex::operator+=(const Complex& second) & {
	*this = *this + second;
	return *this;
}
Complex& Complex::operator-=(const Complex& second) & {
	*this = *this - second;
	return *this;
}
Complex& Complex::operator*=(const Complex& second) & {
	*this = *this * second;
	return *this;
}
Complex& Complex::operator/=(const Complex& second) & {
	*this = *this / second;
	return *this;
}
Complex Complex::operator-() const { return Complex{-real, -imaginary}; }
double Complex::absolute() const { return std::sqrt(real * real + imaginary * imaginary); }
double Complex::argument() const { return std::atan2(imaginary, real); }
Complex::Complex(const Complex& complex) {
	real = complex.get_real();
	imaginary = complex.get_imaginary();
}
Complex& Complex::operator=(const Complex& complex){
	if(this != &complex){
		real = complex.get_real();
		imaginary = complex.get_imaginary();
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Complex& complex) {
	out << complex.get_real() << " " << complex.get_imaginary() << "i" << std::endl;
	return out;
}
