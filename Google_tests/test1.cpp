//
// Created by c w on 2022/6/27.
//

#include "gtest/gtest.h"
#include "token/operator/Operator.h"

TEST(OperatorTest, Build_Label_Operator) {

    Operator *op;
    Operator::Build(Operator::OperatorLabel::UNKNOWN, &op);
    EXPECT_TRUE(op == nullptr);

    Operator::Build(Operator::OperatorLabel::SUBTRACTION, &op);
    EXPECT_TRUE(op != nullptr);
    EXPECT_TRUE(op->GetOperatorLabel() == Operator::OperatorLabel::SUBTRACTION);

}

TEST(OperatorTest, Build_Input_Idx_NewOperator) {

    std::string input = "-3*5+(-7/3-4)";

    Operator *op;
    Operator::Build(input, 0, &op);
    EXPECT_TRUE(op->GetOperatorLabel() == Operator::NEGATIVE);

    Operator::Build(input, 2, &op);
    EXPECT_TRUE(op->GetOperatorLabel() == Operator::MULTIPLICATION);

    Operator::Build(input, 10, &op);
    EXPECT_TRUE(op->GetOperatorLabel() == Operator::SUBTRACTION);

}

TEST(OperatorTest, IdentifyLabel) {

    std::string input = "-3*5+(-7/3-4)";
    Operator::OperatorLabel operator_label;
    Operator::IdentifyLabel(input, 6, &operator_label);
    EXPECT_TRUE(operator_label == Operator::OperatorLabel::NEGATIVE);

    Operator::IdentifyLabel(input, 0, &operator_label);
    EXPECT_TRUE(operator_label == Operator::OperatorLabel::NEGATIVE);

    Operator::IdentifyLabel(input, 10, &operator_label);
    EXPECT_TRUE(operator_label == Operator::OperatorLabel::SUBTRACTION);

    Operator::IdentifyLabel(input, 2, &operator_label);
    EXPECT_TRUE(operator_label == Operator::OperatorLabel::MULTIPLICATION);

}
