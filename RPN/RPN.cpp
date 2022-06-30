//
// Created by c w on 2022/6/28.
//

#include "RPN.h"
#include "exception"
#include "common/CommonUtils.h"


RPN::RPN(std::string infix_str)  {
    std::string result;
    DeleteWhite(infix_str, &result);
    infix_str_ = std::move(result);
    tokenizer_.SetInput(infix_str_);
}

EN_RV RPN::ResolveOperand() {
    Token *cur_token;
    tokenizer_.PeekCurToken(&cur_token);
    if (cur_token == nullptr || !cur_token->IsOperand()) {
        return ENR_GENERAL_ERR;
    }

    Number *new_number = new Number(cur_token->ToString());
    rpn_queue_.push(new_number);
}
//
//void RPN::ResolveOperator(const std::string &input, int cur_idx, char cur_char_from_infix,
//                          std::stack<Operator *> &operator_stack) {
//
//    Operator *cur_op = nullptr;
//    Operator::Build(input, cur_idx, &cur_op);
//
//    if (operator_stack.empty()) {
//        operator_stack.push(cur_op);
//        return;
//    }
//
//    if (*cur_op == Operator::OperatorLabel::LEFTBRACKET) {
//        operator_stack.push(cur_op);
//        return;
//    }
//
//    if (*cur_op == Operator::OperatorLabel::RIGHTBRACKET) {
//        // until '('
//        while (!(*operator_stack.top() == Operator::OperatorLabel::LEFTBRACKET)) {
//            rpn_queue_.push(operator_stack.top());
//            operator_stack.pop();
//        }
//        // pop '('
//        operator_stack.pop();
//        return;
//    }
//
//    if (Operator::Compare(operator_stack.top(), cur_op) < 0) {
//        while (!operator_stack.empty()) {
//            if (Operator::Compare(operator_stack.top(), cur_op) < 0) {
//                rpn_queue_.push(operator_stack.top());
//                operator_stack.pop();
//                continue;
//            }
//            operator_stack.push(cur_op);
//            break;
//        }
//        if (operator_stack.empty()) {
//            operator_stack.push(cur_op);
//        }
//
//        return;
//    }
//
//    operator_stack.push(cur_op);
//
//}

EN_RV RPN::ResolveOperator(std::stack<Operator *> &operator_stack) {

    Token *cur_token;
    tokenizer_.PeekCurToken(&cur_token);
    if (cur_token == nullptr || !cur_token->IsOperator()) {
        return ENR_GENERAL_ERR;
    }

    Operator *cur_op = (Operator *) cur_token;

    if (operator_stack.empty()) {
        operator_stack.push(cur_op);
        return ENR_OK;
    }

    if (*cur_op == Operator::OperatorLabel::LEFTBRACKET) {
        operator_stack.push(cur_op);
        return ENR_OK;

    }

    if (*cur_op == Operator::OperatorLabel::RIGHTBRACKET) {
        // until '('
        while (!(*operator_stack.top() == Operator::OperatorLabel::LEFTBRACKET)) {
            rpn_queue_.push(operator_stack.top());
            operator_stack.pop();
        }
        // pop '('
        operator_stack.pop();
        return ENR_OK;

    }

    if (Operator::Compare(operator_stack.top(), cur_op) < 0) {
        while (!operator_stack.empty()) {
            if (Operator::Compare(operator_stack.top(), cur_op) < 0) {
                rpn_queue_.push(operator_stack.top());
                operator_stack.pop();
                continue;
            }
            operator_stack.push(cur_op);
            break;
        }
        if (operator_stack.empty()) {
            operator_stack.push(cur_op);
        }

        return ENR_OK;
    }

    operator_stack.push(cur_op);

}

void RPN::ConvertInfix2Suffix() {

    std::stack<Operator *> operator_stack;
    EN_RV rv = ENR_OK;
    while (rv != ENR_END) {
        Token *next_token;

        rv = tokenizer_.NextToken(&next_token);

        //if (rv == ENR_END) {
        //    break;
        //}

        switch (next_token->IsOperator()) {
            case true:
                ResolveOperator(operator_stack);
                break;
            case false:
                ResolveOperand();
                break;
        }
    }
    //for (int i = 0; i < infix_str_.length(); i++) {
    //    const char cur_char_from_infix = infix_str_[i];
    //    Token * next_token;
    //    tokenizer_.NextToken(&next_token);
    //    switch (Resolve(cur_char_from_infix)) {
    //        // 操作数
    //        case 0:
    //            ResolveOperand();
    //            break;
    //            // 操作符
    //        case 1:
    //            ResolveOperator(infix_str_, i, cur_char_from_infix, operator_stack);
    //            break;
    //    }
    //}

    while (!operator_stack.empty()) {
        rpn_queue_.push(operator_stack.top());
        operator_stack.pop();
    }
}

Number *RPN::EvalRPN() {

    std::stack<Number *> operand_stack;   // 存放操作数，操作数使用整形

    while (!rpn_queue_.empty()) {
        Token *cur_token = rpn_queue_.front();
        rpn_queue_.pop();

        bool is_operand = cur_token->IsOperand();

        if (is_operand) {
            std::string cur_token_str = cur_token->ToString();
            operand_stack.push(new Number(cur_token_str));
            continue;
        }

        Operator *cur_op = (Operator *) cur_token;

        if (cur_op->GetOperatorType() == Operator::OperatorType::unary) {
            Number *left = operand_stack.top();
            operand_stack.pop();
            int result = ((UnaryOperator *) cur_token)->Calculate(left->ToIntValue());
            operand_stack.push(new Number(std::to_string(result)));
            continue;
        }

        if (cur_op->GetOperatorType() == Operator::OperatorType::binocular) {
            Number *right = operand_stack.top();
            operand_stack.pop();
            Number *left = operand_stack.top();
            operand_stack.pop();
            int result = ((BinocularOperator *) cur_token)->Calculate(left->ToIntValue(), right->ToIntValue());
            operand_stack.push(new Number(std::to_string(result)));
            continue;
        }

    }

    return operand_stack.top();
}

void RPN::ResetInfixStr(std::string infix_str) {
    this->infix_str_ = std::move(infix_str);
    this->tokenizer_.SetInput(infix_str_);
    this->rpn_queue_ = std::queue<Token *>();
}

std::string RPN::GetInternalRPNExpression() const {
    std::queue<Token *> copy_rpn_queue = rpn_queue_;
    std::string result;
    while (!copy_rpn_queue.empty()) {
        result += copy_rpn_queue.front()->ToString();
        copy_rpn_queue.pop();
    }
    return std::move(result);
}
