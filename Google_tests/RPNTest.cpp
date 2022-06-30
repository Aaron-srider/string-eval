//
// Created by c w on 2022/6/27.
//

#include "gtest/gtest.h"
#include "RPN/RPN.h"


TEST(ConvertInfix2Suffix, TEST_NEGATIVE) {
    RPN rpn("");
    std::string input;
    std::string rpn_exp;
    {
        input = "-3*5+(-7/3-4)";
        rpn.ResetInfixStr(input);

        rpn.ConvertInfix2Suffix();
        rpn_exp = rpn.GetInternalRPNExpression();

        std::cout << "infix: " << input << "\nrpn_exp: " << rpn_exp << std::endl;
        EXPECT_EQ(rpn_exp, "3-5*7-3/4-+");
    }

    {
        std::string input = "-3+-6";
        rpn.ResetInfixStr(input);

        rpn.ConvertInfix2Suffix();
        rpn_exp = rpn.GetInternalRPNExpression();

        std::cout << "infix: " << input << "\nrpn_exp: " << rpn_exp << std::endl;
        EXPECT_EQ(rpn_exp, "3-6-+");
    }

    {
        input = "-3+-(8*-8)";
        rpn.ResetInfixStr(input);

        rpn.ConvertInfix2Suffix();
        rpn_exp = rpn.GetInternalRPNExpression();

        std::cout << "infix: " << input << "\nrpn_exp: " << rpn_exp << std::endl;
        EXPECT_EQ(rpn_exp, "3-88-*-+");
    }

}

TEST(ConvertInfix2Suffix, TEST_INTEGER_WITH_MULTIPLE_LETTER){
    RPN rpn("");
    std::string input;
    std::string rpn_exp;
    {
        input = "-3*52334+-(-733/53--40)";
        rpn.ResetInfixStr(input);

        rpn.ConvertInfix2Suffix();
        rpn_exp = rpn.GetInternalRPNExpression();

        std::cout << "infix: " << input << "\nrpn_exp: " << rpn_exp << std::endl;
        EXPECT_EQ(rpn_exp, "3-52334*733-53/40---+");
    }
}


TEST(EvalRPN, TEST_NEGATIVE) {
    RPN rpn("");
    std::string input;
    std::string rpn_exp;
    std::string result;
    {
        input = "-3*52334+-(-733/53--40)";

        rpn.ResetInfixStr(input);
        rpn.ConvertInfix2Suffix();
        result = rpn.EvalRPN()->ToString();

        std::cout << "infix: " << input << "\nresult: " << result << std::endl;
        EXPECT_EQ(result, "-157029");
    }

}


TEST(EvalRPN, TEST_WHITE_CHAR) {
    RPN rpn("");
    std::string input;
    std::string rpn_exp;
    std::string result;
    {
        input = "-3* 5233 4+-(-73 3/ 5 3--4 0)";

        rpn.ResetInfixStr(input);
        rpn.ConvertInfix2Suffix();
        result = rpn.EvalRPN()->ToString();

        std::cout << "infix: " << input << "\nresult: " << result << std::endl;
        EXPECT_EQ(result, "-157029");
    }

}