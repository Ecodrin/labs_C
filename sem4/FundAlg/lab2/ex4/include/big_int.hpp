#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <complex>
#include <cmath>

class BigInt {
private:
    unsigned long long base = 1000000;
    std::vector<unsigned long long> data;
    bool is_negative = false;

    void remove_leading_zeros();
    static void remove_leading_zeros(std::vector<long double> & vector);
    static bool is_correct_string(const std::string &str);

    static std::vector<std::complex<long double>> fft_transform(const std::vector<unsigned long long>& input, size_t n);
    static std::vector<unsigned long long> fft_reset(const std::vector<std::complex<long double>>& input, size_t base);

    void shift_left(int k);

    static std::vector<long double> big_int_to_polynomial(const BigInt &f);

    static BigInt polynomial_to_big_int(const std::vector<long double> &f, unsigned long long int base);

    static std::vector<long double> polynomial_multiply(const std::vector<long double>& f, const std::vector<long double>& g);
    static std::vector<long double> polynomial_subtract(const std::vector<long double>& f, const std::vector<long double>& g);


public:
    static std::pair<BigInt, BigInt> divide(const BigInt &lhs, const BigInt &rhs);
    BigInt();
    BigInt(const BigInt &other);
    BigInt(BigInt &&other) noexcept;
    explicit BigInt(long long l);
    explicit BigInt(const std::string &in);
    ~BigInt() = default;

    BigInt &operator=(const BigInt &other);
    BigInt &operator=(BigInt &&other) noexcept;

    [[nodiscard]] std::string to_string() const;
    void reload_from_string(const std::string & in);
    friend std::ostream &operator<<(std::ostream &out, const BigInt &num);
    friend std::istream &operator>>(std::istream &in, BigInt &num);

    void change_base(unsigned long long new_base);
    BigInt operator-();

    friend std::strong_ordering operator<=>(const BigInt & lhs, const BigInt & rhs);
    friend bool operator==(const BigInt & lhs, const BigInt & rhs);

    BigInt operator+(const BigInt & num) const;
    BigInt operator-(const BigInt & num) const;
    BigInt operator*(const BigInt & num) const;
    BigInt operator/(const BigInt & num) const;
    BigInt operator%(const BigInt & num) const;
    BigInt & operator+=(const BigInt & num);
    BigInt & operator-=(const BigInt & num);
    BigInt & operator*=(const BigInt & num);
    BigInt & operator/=(const BigInt & num);
    BigInt & operator%=(const BigInt & num);
    BigInt& operator++();
    BigInt& operator--();
    BigInt operator++(int);
    BigInt operator--(int);
    std::vector<unsigned long long > &get_data();
    void normalize();


    [[nodiscard]] bool is_null() const;

    static BigInt mod_exp(const BigInt& base, const BigInt& exp, const BigInt& mod);

    BigInt fft_multiply(const BigInt& a) const;
    BigInt ntt_multiply(const BigInt &a, unsigned long long m) const;
    static unsigned long long find_primitive_root(unsigned long long m);

    [[nodiscard]] static bool is_correct_mod(unsigned long long m);
    static bool is_prime_power(unsigned long long n);
    static unsigned long long euler_phi(unsigned long long m);
    static std::vector<unsigned long long > get_factors(unsigned long long n);
    static unsigned long long mod_pow(unsigned long long a, unsigned long long n, unsigned long long mod);
    static unsigned long long mod_inverse( long long w,  long long m);
    static std::vector<long long> extended_gcd(long long a, long long b);

    static std::complex<long double> omega(int n, int k);
    static std::vector<std::complex<long double>> fft(size_t n, std::vector<std::complex<long double>> f, std::complex<long double> w);
    static std::vector<unsigned long long > nnt(size_t n, std::vector<unsigned long long > f, unsigned long long w, unsigned long long m);

    [[nodiscard]] BigInt karatsuba_multiply(const BigInt &a) const;
    static BigInt karatsuba(BigInt f, BigInt g);


    static std::vector<long double> newton_reverse(std::vector<long double> f, size_t l);
    static std::pair<BigInt, BigInt> newton_divide(const BigInt &lhs, const BigInt &rhs);
    static std::vector<long double> reverse(std::vector<long double> f, size_t R);


};


