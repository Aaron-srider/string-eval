//
// Created by c w on 2022/6/27.
//

#include "gtest/gtest.h"
#include "token/Tokenizer.h"
#include "token/operator/NegativeOperator.h"
#include "token/operator/MultiplicationOperator.h"
#include "token/operator/PlusOperator.h"
#include "token/operator/LeftBracket.h"
#include "token/operator/DivisionOperator.h"
#include "token/operator/SubtractionOperator.h"
#include "token/operator/RightBracket.h"


TEST(PeekNextToken, NORMAL) {
    std::string input = "-3*5+(-7/3-4)";
    Tokenizer tokenizer(input);
    Token *token = nullptr;
    EN_RV rv = tokenizer.PeekNext(&token);

    EXPECT_EQ(rv, ENR_OK);
    EXPECT_TRUE(token->IsOperator());
    EXPECT_TRUE(((Operator *) token)->GetOperatorLabel() == Operator::OperatorLabel::NEGATIVE);
}


TEST(PeekNextToken, PEEK_END) {
    std::string input = "-3*5+(-7/3-4)";
    Tokenizer tokenizer(input);
    Token *token = nullptr;
    EN_RV rv = ENR_OK;

    //get all tokens
    while (rv != ENR_END) {
        rv = tokenizer.NextToken(&token);
        EXPECT_TRUE(rv == ENR_END || rv == ENR_OK);
        if (rv == ENR_UNRECOGNIZED_TOKEN) {
            exit(rv);
        }
    }
    rv = tokenizer.PeekNext(&token);

    EXPECT_EQ(rv, ENR_END);


}


TEST(NextToken, NORMAL) {

    //expect token list
    std::vector<Token *> expect_token_list;
    expect_token_list = {
            new NegativeOperator(),
            new Number("3"),
            new MultiplicationOperator(),
            new Number("5"),
            new PlusOperator(),
            new LeftBracket(),
            new NegativeOperator(),
            new Number("7"),
            new DivisionOperator(),
            new Number("3"),
            new SubtractionOperator(),
            new Number("4"),
            new RightBracket(),
    };

    std::string input = "-3*5+(-7/3-4)";
    Tokenizer tokenizer(input);
    Token *token;
    EN_RV rv = ENR_OK;
    //get all tokens
    while (rv != ENR_END) {
        rv = tokenizer.NextToken(&token);
        std::cout << token->ToString() << std::endl;
        EXPECT_TRUE(rv == ENR_END || rv == ENR_OK);
        if (rv == ENR_UNRECOGNIZED_TOKEN) {
            exit(rv);
        }
    }

    std::vector<Token *> internal_token_list;
    //get internal token list
    rv = tokenizer.GetInternalTokenList(&internal_token_list);
    EXPECT_EQ(rv, ENR_OK);
    //check token count
    EXPECT_EQ(internal_token_list.size(), expect_token_list.size());


    //check each token
    for (int i = 0; i < internal_token_list.size(); i++) {
        Token *expect = expect_token_list.at(i);
        Token *internal_token = internal_token_list.at(i);

        if (expect->IsOperator()) {
            EXPECT_TRUE(internal_token->IsOperator());
            Operator *ex = (Operator *) expect;
            Operator *in = (Operator *) internal_token;

            EXPECT_TRUE(*ex == *in);
        }

        if (expect->IsOperand()) {
            EXPECT_TRUE(internal_token->IsOperand());
            Number *ex = (Number *) expect;
            Number *in = (Number *) internal_token;
            EXPECT_EQ(ex->ToString(), in->ToString());
        }
    }

}

