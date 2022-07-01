//
// Created by c w on 2022/7/1.
//

#include "gtest/gtest.h"
#include "iostream"
#include "BigNumberCalculation/BigNumberCalculation.h"

TEST(POSITIVE_ADD, NORMAL) {

    std::string result;
    BigNumberCalculation::PositiveAdd("92534999", "992349", &result);
    EXPECT_EQ(result, "93527348");

    BigNumberCalculation::PositiveAdd("999", "1", &result);
    EXPECT_EQ(result, "1000");

    BigNumberCalculation::PositiveAdd("999", "999", &result);
    EXPECT_EQ(result, "1998");

    BigNumberCalculation::PositiveAdd("999", "0", &result);
    EXPECT_EQ(result, "999");

    BigNumberCalculation::PositiveAdd("1", "0", &result);
    EXPECT_EQ(result, "1");

    BigNumberCalculation::PositiveAdd("0", "0", &result);
    EXPECT_EQ(result, "0");

}

TEST(PositiveSub, NORMAL) {

    std::string result;

    BigNumberCalculation::PositiveSub("1000", "0", result);
    EXPECT_EQ(result, "1000");

    BigNumberCalculation::PositiveSub("990", "19", result);
    EXPECT_EQ(result, "971");

    BigNumberCalculation::PositiveSub("19", "990", result);
    EXPECT_EQ(result, "-971");

    BigNumberCalculation::PositiveSub("0", "1", result);
    EXPECT_EQ(result, "-1");

    BigNumberCalculation::PositiveSub("0", "990", result);
    EXPECT_EQ(result, "-990");

    BigNumberCalculation::PositiveSub("999", "999", result);
    EXPECT_EQ(result, "0");

    BigNumberCalculation::PositiveSub("0", "0", result);
    EXPECT_EQ(result, "0");
}
//
//
//
TEST(DeleteZero, NORMAL) {

    std::string result;

    BigNumberCalculation::DeleteZero("034", result);
    EXPECT_EQ(result, "34");

    BigNumberCalculation::DeleteZero("1000", result);
    EXPECT_EQ(result, "1000");

    BigNumberCalculation::DeleteZero("000", result);
    EXPECT_EQ(result, "0");

    BigNumberCalculation::DeleteZero("0", result);
    EXPECT_EQ(result, "0");

}
//
TEST(ABS, NORMAL) {

    std::string result;

    BigNumberCalculation::Abs("-123", result);
    EXPECT_EQ(result, "123");

    BigNumberCalculation::Abs("123", result);
    EXPECT_EQ(result, "123");

    BigNumberCalculation::Abs("0", result);
    EXPECT_EQ(result, "0");
}
//
//
TEST(COMPARE, NORMAL) {

    int rv = 0;
    rv = BigNumberCalculation::Compare("928342", "0");
    EXPECT_TRUE(rv > 0);
    rv = BigNumberCalculation::Compare("928342", "234");
    EXPECT_TRUE(rv > 0);
    rv = BigNumberCalculation::Compare("129", "321");
    EXPECT_TRUE(rv < 0);
    rv = BigNumberCalculation::Compare("-928342", "234");
    EXPECT_TRUE(rv < 0);
    rv = BigNumberCalculation::Compare("928342", "-234");
    EXPECT_TRUE(rv > 0);
    rv = BigNumberCalculation::Compare("-928342", "0");
    EXPECT_TRUE(rv < 0);
    rv = BigNumberCalculation::Compare("0", "-234");
    EXPECT_TRUE(rv > 0);
    rv = BigNumberCalculation::Compare("928342", "928342");
    EXPECT_TRUE(rv == 0);
    rv = BigNumberCalculation::Compare("0", "0");
    EXPECT_TRUE(rv == 0);
    rv = BigNumberCalculation::Compare("-1", "-1");
    EXPECT_TRUE(rv == 0);
}
//
//
TEST(Opposite, NORMAL) {

    std::string input, result;

    input = "-234";
    BigNumberCalculation::Opposite(&input, &result);
    EXPECT_EQ(result, "234");

    input = "234";
    BigNumberCalculation::Opposite(&input, &result);
    EXPECT_EQ(result, "-234");

    input = "0";
    BigNumberCalculation::Opposite(&input, &result);
    EXPECT_EQ(result, "0");
}

TEST(Add, NORMAL) {
    std::string operand1, operand2;
    std::string result;

    operand1 = "999";
    operand2 = "1";
    BigNumberCalculation::Add(operand1, operand2, &result);
    EXPECT_EQ(result, "1000");

    operand1 = "1000";
    operand2 = "-1";
    BigNumberCalculation::Add(operand1, operand2, &result);
    EXPECT_EQ(result, "999");

    operand1 = "-1000";
    operand2 = "1";
    BigNumberCalculation::Add(operand1, operand2, &result);
    EXPECT_EQ(result, "-999");

    operand1 = "-999";
    operand2 = "-1";
    BigNumberCalculation::Add(operand1, operand2, &result);
    EXPECT_EQ(result, "-1000");

    operand1 = "999";
    operand2 = "1";
    BigNumberCalculation::Add(operand1, operand2, &result);
    EXPECT_EQ(result, "1000");

    operand1 = "0";
    operand2 = "0";
    BigNumberCalculation::Add(operand1, operand2, &result);
    EXPECT_EQ(result, "0");

    operand1 = "999";
    operand2 = "-999";
    BigNumberCalculation::Add(operand1, operand2, &result);
    EXPECT_EQ(result, "0");

}

TEST(Sub, NORMAL) {
    std::string operand1, operand2;
    std::string result;

    operand1 = "1000";
    operand2 = "1";
    BigNumberCalculation::Sub(operand1, operand2, &result);
    EXPECT_EQ(result, "999");

    operand1 = "129";
    operand2 = "321";
    BigNumberCalculation::Sub(operand1, operand2, &result);
    EXPECT_EQ(result, "-192");

    operand1 = "999";
    operand2 = "-1";
    BigNumberCalculation::Sub(operand1, operand2, &result);
    EXPECT_EQ(result, "1000");

    operand1 = "-999";
    operand2 = "1";
    BigNumberCalculation::Sub(operand1, operand2, &result);
    EXPECT_EQ(result, "-1000");

    operand1 = "-999";
    operand2 = "1";
    BigNumberCalculation::Sub(operand1, operand2, &result);
    EXPECT_EQ(result, "-1000");

    operand1 = "0";
    operand2 = "0";
    BigNumberCalculation::Sub(operand1, operand2, &result);
    EXPECT_EQ(result, "0");

    operand1 = "-999";
    operand2 = "-999";
    BigNumberCalculation::Sub(operand1, operand2, &result);
    EXPECT_EQ(result, "0");

}

TEST(PositiveMultiply, NORMAL) {
    std::string operand1, operand2;
    std::string result;

    operand1 = "1000";
    operand2 = "1";
    BigNumberCalculation::PositiveMultiply(operand1, operand2, &result);
    EXPECT_EQ(result, "1000");

    operand1 = "999";
    operand2 = "999";
    BigNumberCalculation::PositiveMultiply(operand1, operand2, &result);
    EXPECT_EQ(result, std::to_string(999 * 999));

    operand1 = "1";
    operand2 = "999";
    BigNumberCalculation::PositiveMultiply(operand1, operand2, &result);
    EXPECT_EQ(result, "999");

    operand1 = "0";
    operand2 = "999";
    BigNumberCalculation::PositiveMultiply(operand1, operand2, &result);
    EXPECT_EQ(result, "0");

    operand1 = "999";
    operand2 = "0";
    BigNumberCalculation::PositiveMultiply(operand1, operand2, &result);
    EXPECT_EQ(result, "0");

    operand1 = "0";
    operand2 = "0";
    BigNumberCalculation::PositiveMultiply(operand1, operand2, &result);
    EXPECT_EQ(result, "0");

}

TEST(Multiply, NORMAL) {
    std::string operand1, operand2;
    std::string result;

    operand1 = "999";
    operand2 = "999";
    BigNumberCalculation::Multiply(&operand1, &operand2, &result);
    EXPECT_EQ(result, "998001");

    operand1 = "42345";
    operand2 = "44234245";
    BigNumberCalculation::Multiply(&operand1, &operand2, &result);
    EXPECT_EQ(result, "1873099104525");

    operand1 = "-999";
    operand2 = "999";
    BigNumberCalculation::Multiply(&operand1, &operand2, &result);
    EXPECT_EQ(result, "-998001");

    operand1 = "999";
    operand2 = "-999";
    BigNumberCalculation::Multiply(&operand1, &operand2, &result);
    EXPECT_EQ(result, "-998001");

    operand1 = "-999";
    operand2 = "-999";
    BigNumberCalculation::Multiply(&operand1, &operand2, &result);
    EXPECT_EQ(result, "998001");

    operand1 = "999";
    operand2 = "0";
    BigNumberCalculation::Multiply(&operand1, &operand2, &result);
    EXPECT_EQ(result, "0");

    operand1 = "0";
    operand2 = "999";
    BigNumberCalculation::Multiply(&operand1, &operand2, &result);
    EXPECT_EQ(result, "0");

    operand1 = "0";
    operand2 = "0";
    BigNumberCalculation::Multiply(&operand1, &operand2, &result);
    EXPECT_EQ(result, "0");

}

TEST(PositiveDivide, NORMAL) {
    std::string operand1, operand2;
    std::string result;
    EN_RV rv;

    operand1 = "998";
    operand2 = "999";
    BigNumberCalculation::PositiveDivide(&operand1, &operand2, &result);
    EXPECT_EQ(result, "0");

    operand1 = "34524523452345";
    operand2 = "172837465";
    BigNumberCalculation::PositiveDivide(&operand1, &operand2, &result);
    EXPECT_EQ(result, "199751");

    operand1 = "234";
    operand2 = "2432342";
    BigNumberCalculation::PositiveDivide(&operand1, &operand2, &result);
    EXPECT_EQ(result, "0");

    operand1 = "0";
    operand2 = "245345";
    BigNumberCalculation::PositiveDivide(&operand1, &operand2, &result);
    EXPECT_EQ(result, "0");

    operand1 = "943";
    operand2 = "0";
    rv = BigNumberCalculation::PositiveDivide(&operand1, &operand2, &result);
    EXPECT_EQ(rv, ENR_DIVIDE_BY_ZERO);

    operand1 = "0";
    operand2 = "0";
    rv = BigNumberCalculation::PositiveDivide(&operand1, &operand2, &result);
    EXPECT_EQ(rv, ENR_DIVIDE_BY_ZERO);
}

TEST(Divide, NORMAL) {
    std::string operand1, operand2;
    std::string result;
    EN_RV rv;

    operand1 = "34524523452345";
    operand2 = "172837465";
    BigNumberCalculation::Divide(&operand1, &operand2, &result);
    EXPECT_EQ(result, "199751");

    operand1 = "-34524523452345";
    operand2 = "172837465";
    BigNumberCalculation::Divide(&operand1, &operand2, &result);
    EXPECT_EQ(result, "-199751");

    operand1 = "34524523452345";
    operand2 = "-172837465";
    BigNumberCalculation::Divide(&operand1, &operand2, &result);
    EXPECT_EQ(result, "-199751");

    operand1 = "-34524523452345";
    operand2 = "-172837465";
    BigNumberCalculation::Divide(&operand1, &operand2, &result);
    EXPECT_EQ(result, "199751");

    operand1 = "172837465";
    operand2 = "34524523452345";
    BigNumberCalculation::Divide(&operand1, &operand2, &result);
    EXPECT_EQ(result, "0");

    operand1 = "-172837465";
    operand2 = "34524523452345";
    BigNumberCalculation::Divide(&operand1, &operand2, &result);
    EXPECT_EQ(result, "0");

    operand1 = "0";
    operand2 = "172837465";
    BigNumberCalculation::Divide(&operand1, &operand2, &result);
    EXPECT_EQ(result, "0");

    operand1 = "172837465";
    operand2 = "0";
    rv = BigNumberCalculation::Divide(&operand1, &operand2, &result);
    EXPECT_EQ(rv, ENR_DIVIDE_BY_ZERO);

    operand1 = "0";
    operand2 = "0";
    rv = BigNumberCalculation::Divide(&operand1, &operand2, &result);
    EXPECT_EQ(rv, ENR_DIVIDE_BY_ZERO);
}
