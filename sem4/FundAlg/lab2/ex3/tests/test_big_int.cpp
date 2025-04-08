#include "../include/big_int.hpp"


int main() {
    BigInt a{"23123123123231231231322"}, b{-2123213213};
    a.change_base(10);
    BigInt res = a.fft_multiply(b);
    std::cout << res << std::endl;
    std::cout << a * b;
}
