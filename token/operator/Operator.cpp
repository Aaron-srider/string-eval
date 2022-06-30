//
// Created by c w on 2022/6/24.
//

#include "Operator.h"
#include "LeftBracket.h"
#include "RightBracket.h"
#include "PlusOperator.h"
#include "SubtractionOperator.h"
#include "DivisionOperator.h"
#include "MultiplicationOperator.h"
#include "NegativeOperator.h"
#include "map"

std::map<Operator::OperatorLabel, std::string> Operator::label_str_map_ = {
        {Operator::OperatorLabel::NEGATIVE,       "-"},
        {Operator::OperatorLabel::SUBTRACTION,    "-"},
        {Operator::OperatorLabel::PLUS,           "+"},
        {Operator::OperatorLabel::MULTIPLICATION, "*"},
        {Operator::OperatorLabel::DIVISION,       "/"},
        {Operator::OperatorLabel::LEFTBRACKET,    "("},
        {Operator::OperatorLabel::RIGHTBRACKET,   ")"},
};;


int Operator::Build(Operator::OperatorLabel label, Operator **new_operator) {
    switch (label) {

        case PLUS:
            *new_operator = new PlusOperator();
            break;
        case SUBTRACTION:
            *new_operator = new SubtractionOperator();
            break;
        case DIVISION:
            *new_operator = new DivisionOperator();
            break;
        case MULTIPLICATION:
            *new_operator = new MultiplicationOperator();
            break;
        case NEGATIVE:
            *new_operator = new NegativeOperator();
            break;
        case LEFTBRACKET:
            *new_operator = new LeftBracket();
            break;
        case RIGHTBRACKET:
            *new_operator = new RightBracket();
            break;
        case UNKNOWN:
        default:
            *new_operator = nullptr;

    }
}

int Operator::Build(const std::string &input, int idx,  Operator **new_operator) {
    Operator::OperatorLabel label;
    IdentifyLabel(input, idx, &label);

    switch (label) {

        case PLUS:
            *new_operator = new PlusOperator();
            break;
        case SUBTRACTION:
            *new_operator = new SubtractionOperator();
            break;
        case DIVISION:
            *new_operator = new DivisionOperator();
            break;
        case MULTIPLICATION:
            *new_operator = new MultiplicationOperator();
            break;
        case NEGATIVE:
            *new_operator = new NegativeOperator();
            break;
        case LEFTBRACKET:
            *new_operator = new LeftBracket();
            break;
        case RIGHTBRACKET:
            *new_operator = new RightBracket();
            break;
        case UNKNOWN:
        default:
            *new_operator = nullptr;

    }
}

void Operator::IdentifyLabel(const std::string &input, int idx, Operator::OperatorLabel *label) {
    char cur_ch = input.at(idx);

    if (!IsOperator(cur_ch)) {
        *label = UNKNOWN;
    }

    if (cur_ch != '-') {
        switch (cur_ch) {
            case '+':
                *label = OperatorLabel::PLUS;
                break;
            case '*':
                *label = OperatorLabel::MULTIPLICATION;
                break;
            case '/' :
                *label = OperatorLabel::DIVISION;
                break;

            case '(' :
                *label = OperatorLabel::LEFTBRACKET;
                break;

            case ')' :
                *label = OperatorLabel::RIGHTBRACKET;
                break;
        }
        return;
    }

    if (idx == 0) {
        *label = OperatorLabel::NEGATIVE;
        return;
    }

    char before = input.at(idx - 1);
    if (before == '+' ||
        before == '-' ||
        before == '*' ||
        before == '/') {
        *label = OperatorLabel::NEGATIVE;
        return;
    }

    if (before == ')' ||
        IsOperand(before)) {
        *label = OperatorLabel::SUBTRACTION;
        return;
    }

    *label = NEGATIVE;

}

bool Operator::IsOperator(char ch) {
    if (ch == '+' ||
        ch == '-' ||
        ch == '*' ||
        ch == '/' ||
        ch == '(' ||
        ch == ')'
            ) {
        return true;
    }
    return false;
}

bool Operator::IsOperand(char ch) {
    if ('0' + 0 <= ch && ch <= '0' + 9) {
        return true;
    }
    return false;
}

int Operator::Compare(const Operator *stack_top_op, const Operator *cur_op) {
    // err
    if ((*cur_op == OperatorLabel::RIGHTBRACKET) || (*stack_top_op == OperatorLabel::RIGHTBRACKET)) {
        return 0;
    }

    // not include right brackets
    if (
            (((*stack_top_op == OperatorLabel::PLUS) || (*stack_top_op == OperatorLabel::SUBTRACTION)) &&
             ((*cur_op == OperatorLabel::MULTIPLICATION) || (*cur_op == OperatorLabel::MULTIPLICATION))) ||
            *cur_op == OperatorLabel::LEFTBRACKET ||
            *stack_top_op == OperatorLabel::LEFTBRACKET
            ) {
        return 1;
    }

    if ((*cur_op == OperatorLabel::NEGATIVE) &&
        ((*stack_top_op == OperatorLabel::PLUS) ||
         (*stack_top_op == OperatorLabel::SUBTRACTION) ||
         (*stack_top_op == OperatorLabel::MULTIPLICATION) ||
         (*stack_top_op == OperatorLabel::DIVISION)
        )
            ) {
        return 1;
    }

    return -1;
}

bool Operator::operator==(Operator::OperatorLabel operator_label) const {
    return label_ == operator_label;
}

bool Operator::IsOperator() const {
    return true;
}

bool Operator::IsOperand() const {
    return false;
}

Operator::Operator(Operator::OperatorType operator_type, Operator::OperatorLabel label) {
    this->label_ = label;
    this->operator_type_ = operator_type;
}

std::string Operator::ToString() const {
    return Operator::label_str_map_[label_];
}

Operator::OperatorLabel Operator::GetOperatorLabel() const {
    return label_;
}

bool Operator::operator==(const Operator &other_op) const {
    if ((other_op.operator_type_ == this->operator_type_) &&
        other_op.label_ == this->label_
            ) {
        return true;
    }

    return false;
}

bool Operator::operator!=(const Operator &other_op) const {
    return !(*this == other_op);
}


Operator::OperatorType Operator::GetOperatorType() const {
    return operator_type_;
}




