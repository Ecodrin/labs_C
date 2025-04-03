#include "../include/big_int.hpp"
#include <gtest/gtest.h>

class BigIntTest : public ::testing::Test {
protected:
    BigInt a = BigInt("123456789012345678901234567890");
    BigInt b = BigInt("-987654321098765432109876543210");
    BigInt zero = BigInt(0);
};

TEST_F(BigIntTest, DefaultConstructor) {
    BigInt num;
    EXPECT_EQ(num.to_string(), "0");
}

TEST_F(BigIntTest, LongLongConstructor) {
    EXPECT_EQ(BigInt(0).to_string(), "0");
    EXPECT_EQ(BigInt(123456789).to_string(), "123456789");
    EXPECT_EQ(BigInt(-123456789).to_string(), "-123456789");
}

TEST_F(BigIntTest, StringConstructorValidation) {
    EXPECT_THROW(BigInt("12a34"), std::invalid_argument);
    EXPECT_THROW(BigInt("-"), std::invalid_argument);
    EXPECT_NO_THROW(BigInt("0000012345"));
}

TEST_F(BigIntTest, CopyMoveSemantics) {
    BigInt copy(a);
    EXPECT_EQ(copy.to_string(), a.to_string());

    BigInt moved(std::move(copy));
    EXPECT_EQ(moved.to_string(), a.to_string());
    EXPECT_TRUE(copy == zero);
}

TEST_F(BigIntTest, ComparisonOperators) {
    BigInt a2("123456789012345678901234567890");
    BigInt small("123");

    EXPECT_EQ(a, a2);
    EXPECT_NE(a, b);
    EXPECT_GT(a, b);
    EXPECT_LT(b, zero);
    EXPECT_GT(a, small);
}

TEST_F(BigIntTest, AdditionOperations) {
    EXPECT_EQ(a + zero, a);
    EXPECT_EQ(a + b, BigInt("-864197532086419753208641975320"));
    EXPECT_EQ(a + BigInt("99999999999999999999"),
              BigInt("123456789112345678901234567889"));
}

TEST_F(BigIntTest, SubtractionOperations) {
    EXPECT_EQ(a - a, zero);
    EXPECT_EQ(b - b, zero);
    EXPECT_EQ(a - BigInt("100000000000"),
              BigInt("123456789012345678801234567890"));
}

TEST_F(BigIntTest, MultiplicationOperations) {
    BigInt big1("12345678901234567890");
    BigInt big2("98765432109876543210");

    EXPECT_EQ(a * zero, zero);
    EXPECT_EQ(big1 * big2, BigInt("1219326311370217952237463801111263526900"));
}

TEST_F(BigIntTest, DivisionOperations) {
    BigInt dividend("12345678901234567890123490");
    BigInt divisor("12345678900000000000000");

    EXPECT_EQ(dividend / divisor, BigInt("1000"));
    EXPECT_THROW(a / zero, std::invalid_argument);
}

TEST_F(BigIntTest, CompoundOperations) {
    BigInt num("1000000000000000000");
    num += BigInt("500000000000000000");
    EXPECT_EQ(num.to_string(), "1500000000000000000");

    num -= BigInt("300000000000000000");
    EXPECT_EQ(num.to_string(), "1200000000000000000");
}

TEST_F(BigIntTest, UnaryOperators) {
    EXPECT_EQ((-a).to_string(), "-123456789012345678901234567890");
    EXPECT_EQ((-b).to_string(), "987654321098765432109876543210");

    BigInt x(10);
    EXPECT_EQ(++x, BigInt(11));
    EXPECT_EQ(x++, BigInt(11));
    EXPECT_EQ(x, BigInt(12));
}

TEST_F(BigIntTest, LargeNumberOperations) {
    BigInt num1("9999999999999999999999999999999999999999");
    BigInt num2("1111111111111111111111111111111111111111");

    EXPECT_EQ(num1 + num2, BigInt("11111111111111111111111111111111111111110"));
    EXPECT_EQ(num1 - num2, BigInt("8888888888888888888888888888888888888888"));
    EXPECT_EQ(num1 / num2, BigInt("9"));
}

TEST_F(BigIntTest, EdgeCaseOperations) {
    BigInt max_val("999999999999999999999999999999");
    EXPECT_EQ(max_val * max_val,
              BigInt("999999999999999999999999999998000000000000000000000000000001"));

    BigInt min_val("-999999999999999999999999999999");
    EXPECT_EQ(min_val * min_val,
              BigInt("999999999999999999999999999998000000000000000000000000000001"));
}

TEST_F(BigIntTest, StreamOperations) {
    std::stringstream ss;
    ss << a;
    EXPECT_EQ(ss.str(), "123456789012345678901234567890");

    BigInt num;
    ss >> num;
    EXPECT_EQ(num, a);
}


TEST_F(BigIntTest, InvalidBaseConversion) {
    BigInt num("12345");
    EXPECT_THROW(num.change_base(999), std::invalid_argument);
    EXPECT_THROW(num.change_base(0), std::invalid_argument);
}

TEST_F(BigIntTest, IncrementDecrementEdgeCases) {
    BigInt neg("-5");
    EXPECT_EQ(++neg, BigInt("-4"));
    EXPECT_EQ(--neg, BigInt("-5"));

    BigInt zero(0);
    EXPECT_EQ(zero++, BigInt(0));
    EXPECT_EQ(zero--, BigInt(1));
}

TEST_F(BigIntTest, DivisionByOne) {
    BigInt a("1234");
    EXPECT_EQ(a / BigInt(1), a);
    EXPECT_EQ((-a) / BigInt(1), -a);
}

TEST_F(BigIntTest, MixedSignOperations) {
    BigInt pos("100");
    BigInt neg("-50");

    EXPECT_EQ(pos + neg, BigInt(50));
    EXPECT_EQ(neg - pos, BigInt(-150));
    EXPECT_EQ(pos * neg, BigInt(-5000));
    EXPECT_EQ(neg / pos, BigInt(0));
}

TEST_F(BigIntTest, ZeroHandling) {
    BigInt z1;
    BigInt z2("00000");

    EXPECT_EQ(z1 * z2, BigInt(0));
    EXPECT_EQ(z1 / BigInt(1), BigInt(0));
    EXPECT_EQ(z2 - z1, BigInt(0));
}

TEST_F(BigIntTest, BoundaryValueMultiplication) {
    BigInt max("999999999");
    EXPECT_EQ(max * max, BigInt("999999998000000001"));
}

TEST_F(BigIntTest, ReloadEdgeCases) {
    BigInt num;
    EXPECT_NO_THROW(num.reload_from_string("-0"));
    EXPECT_EQ(num.to_string(), "0");
}

TEST_F(BigIntTest, FullDivisionCoverage) {
    BigInt a("100"), b("3");
    EXPECT_EQ(a / b, BigInt("33"));

    BigInt c("999"), d("999");
    EXPECT_EQ(c / d, BigInt("1"));
}

TEST_F(BigIntTest, AdditionWithNegativeNumbers) {
    BigInt a("-500");
    BigInt b("-300");
    a += b;
    EXPECT_EQ(a.to_string(), "-800");

    BigInt c("-100");
    BigInt d("200");
    c += d;
    EXPECT_EQ(c.to_string(), "100");
}

TEST_F(BigIntTest, SubtractionEdgeCases) {
    BigInt a("500");
    a -= a;
    EXPECT_EQ(a.to_string(), "0");

    BigInt b("1000");
    BigInt c("999");
    b -= c;
    EXPECT_EQ(b.to_string(), "1");
}

TEST_F(BigIntTest, MultiplicationSignHandling) {
    BigInt pos("100");
    BigInt neg("-5");
    pos *= neg;
    EXPECT_EQ(pos.to_string(), "-500");

    BigInt neg2("-10");
    neg2 *= BigInt("-3");
    EXPECT_EQ(neg2.to_string(), "30");
}

TEST_F(BigIntTest, DivisionSignHandling) {
    BigInt a("-1000");
    BigInt b("200");
    a /= b;
    EXPECT_EQ(a.to_string(), "-5");

    BigInt c("999");
    BigInt d("-3");
    c /= d;
    EXPECT_EQ(c.to_string(), "-333");
}

TEST_F(BigIntTest, IncrementDecrement) {
    BigInt neg("-1");
    ++neg;
    EXPECT_EQ(neg.to_string(), "0");
    --neg;
    EXPECT_EQ(neg.to_string(), "-1");
}

TEST_F(BigIntTest, SelfAssignmentMove) {
    BigInt a("12345");
    EXPECT_EQ(std::move(a).to_string(), "12345");
}

TEST_F(BigIntTest, CarryPropagation) {
    BigInt a("999999999");
    BigInt b("1");
    a += b;
    EXPECT_EQ(a.to_string(), "1000000000");
}

TEST_F(BigIntTest, SubtractionCarryPropagation) {
    BigInt a("1000000000");
    BigInt b("1");
    a -= b;
    EXPECT_EQ(a.to_string(), "999999999");
}

TEST_F(BigIntTest, NegativeMultiplication) {
    BigInt a("-100");
    BigInt b("50");
    a *= b;
    EXPECT_EQ(a.to_string(), "-5000");
}

TEST_F(BigIntTest, ZeroResizeInSubtraction) {
    BigInt a("500");
    BigInt b("500");
    a -= b;
    EXPECT_EQ(a.to_string(), "0");
}

TEST_F(BigIntTest, LargeBaseConversion) {
    BigInt num("12345678901234567890");
    num.change_base(1000000000);
    EXPECT_EQ(num.to_string(), "12345678901234567890");
}

TEST_F(BigIntTest, DivisionWhenDividendLessThanDivisor) {
    BigInt a("50");
    BigInt b("100");
    EXPECT_EQ(a / b, BigInt("0"));
}

TEST_F(BigIntTest, AdditionWithCarryOverMultipleDigits) {
    BigInt a("999999999999999999999999");
    BigInt b("1");
    a += b;
    EXPECT_EQ(a.to_string(), "1000000000000000000000000");
}

TEST_F(BigIntTest, SubtractionWithMultipleBorrows) {
    BigInt a("1000000000000000000000000");
    BigInt b("1");
    a -= b;
    EXPECT_EQ(a.to_string(), "999999999999999999999999");
}

TEST_F(BigIntTest, MultiplyByZeroAfterSignChange) {
    BigInt a("-123");
    BigInt b("0");
    a *= b;
    EXPECT_EQ(a.to_string(), "0");
    EXPECT_FALSE(a < BigInt());
}

TEST_F(BigIntTest, ReloadFromStringWithMaxBase) {
    BigInt num("12345678901234567890");
    num.change_base(1000000000);
    EXPECT_EQ(num.to_string(), "12345678901234567890");
}

TEST_F(BigIntTest, OperatorDivideByNegativeOne) {
    BigInt a("-123456");
    BigInt b("-1");
    EXPECT_EQ(a / b, BigInt("123456"));
}

TEST_F(BigIntTest, PostfixIncrementDecrementEdge) {
    BigInt a("0");
    BigInt b = a++;
    EXPECT_EQ(a.to_string(), "1");
    EXPECT_EQ(b.to_string(), "0");

    BigInt c = a--;
    EXPECT_EQ(a.to_string(), "0");
    EXPECT_EQ(c.to_string(), "1");
}

TEST_F(BigIntTest, SubtractDifferentBases) {
    BigInt a("1000");
    a.change_base(1000);
    BigInt b("500");
    a -= b;
    EXPECT_EQ(a.to_string(), "500");
}

TEST_F(BigIntTest, SubtractNegativeThis) {
    BigInt a("-2000");
    BigInt b("500");
    a -= b;
    EXPECT_EQ(a.to_string(), "-2500");
}

TEST_F(BigIntTest, SubtractThisLessThanNum) {
    BigInt a("500");
    BigInt b("1000");
    a -= b;
    EXPECT_EQ(a.to_string(), "-500");
}

TEST_F(BigIntTest, SubtractWithCarryPropagation) {
    BigInt a("1000000000");
    BigInt b("1");
    a -= b;
    EXPECT_EQ(a.to_string(), "999999999");
}

TEST_F(BigIntTest, SubtractWithZeroResize) {
    BigInt a("500");
    BigInt b("500");
    a -= b;
    EXPECT_EQ(a.to_string(), "0");
}

TEST_F(BigIntTest, SubtractWithCarryPropagationInHighDigits) {
    BigInt a;
    a.change_base(1000);
    a.reload_from_string("100");

    BigInt b("1");
    a -= b;

    EXPECT_EQ(a.to_string(), "99");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}