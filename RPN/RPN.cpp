//
// Created by c w on 2022/6/28.
//

#include "RPN.h"
#include "exception"


RPN::RPN(std::string infix_str) : infix_str_(std::move(infix_str)) {

}

int RPN::Resolve(char ch) const {
    if (ch == '+' ||
        ch == '-' ||
        ch == '*' ||
        ch == '/' ||
        ch == '(' ||
        ch == ')'
            ) {
        return 1;
    }
    return 0;
}

void RPN::ResolveOperand(char cur_char_from_infix) {
    Number *new_number = new Number(std::string("") + cur_char_from_infix);
    rpn_queue_.push(new_number);
}

void RPN::ResolveOperator(const std::string &input, int cur_idx, char cur_char_from_infix,
                          std::stack<Operator *> &operator_stack) {

    Operator *cur_op = nullptr;
    Operator::Build(input, cur_idx, &cur_op);

    if (operator_stack.empty()) {
        operator_stack.push(cur_op);
        return;
    }

    if (*cur_op == Operator::OperatorLabel::LEFTBRACKET) {
        operator_stack.push(cur_op);
        return;
    }

    if (*cur_op == Operator::OperatorLabel::RIGHTBRACKET) {
        // until '('
        while (!(*operator_stack.top() == Operator::OperatorLabel::LEFTBRACKET)) {
            rpn_queue_.push(operator_stack.top());
            operator_stack.pop();
        }
        // pop '('
        operator_stack.pop();
        return;
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

        return;
    }

    operator_stack.push(cur_op);

}

void RPN::ConvertInfix2Suffix() {

    std::stack<Operator *> operator_stack;
    for (int i = 0; i < infix_str_.length(); i++) {
        const char cur_char_from_infix = infix_str_[i];
        switch (Resolve(cur_char_from_infix)) {
            // 操作数
            case 0:
                ResolveOperand(cur_char_from_infix);
                break;
                // 操作符
            case 1:
                ResolveOperator(infix_str_, i, cur_char_from_infix, operator_stack);
                break;
        }
    }

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
