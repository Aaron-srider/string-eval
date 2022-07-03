//
// Created by c w on 2022/6/30.
//

#include "gtest/gtest.h"

#include "common/CommonUtils.h"
TEST(DELETE_WHITE, NORMAL) {
    std::string input = " 28 + - 9";
    std::string result;
    DeleteWhite(&input, &result);

    EXPECT_EQ(result, "28+-9");
}

TEST(DELETE_WHITE, WHOLE_WHITE) {
    std::string input = "   ";
    std::string result;
    DeleteWhite(&input, &result);

    EXPECT_EQ(result, "");
}