//
// Created by c w on 2022/6/28.
//

#ifndef REVERSE_POLISH_NOTATION_RPN_H
#define REVERSE_POLISH_NOTATION_RPN_H

#include "iostream"
#include <queue>
#include <stack>
#include <utility>

#include "token/Token.h"
#include "token/operator/Operator.h"
#include "token/operand/Number.h"
#include "token/operator/BinocularOperator.h"
#include "token/operator/UnaryOperator.h"

#include "token/Tokenizer.h"

class RPN {

public:
    explicit RPN(std::string infix_str);

private:
    std::string infix_str_;

    std::queue<Token *> rpn_queue_;

    Tokenizer tokenizer_;

private:
    int Resolve(char ch) const;

    EN_RV ResolveOperand();

    //void ResolveOperator(const std::string &input, int cur_idx, char cur_char_from_infix,
    //                     std::stack<Operator *> &operator_stack);

    EN_RV ResolveOperator(
            std::stack<Operator *> &operator_stack);

public:
    void ConvertInfix2Suffix();

    Number *EvalRPN();

    void ResetInfixStr(std::string infix_str);

    std::string GetInternalRPNExpression() const;

};


#endif //REVERSE_POLISH_NOTATION_RPN_H
