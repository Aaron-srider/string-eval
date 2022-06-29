//
// Created by c w on 2022/6/24.
//

#include "PlusOperator.h"

int PlusOperator::Calculate(int operand1, int operand2) const {
    return operand1 + operand2;
}

char PlusOperator::ToChar() const {
    return '+';
}

PlusOperator::PlusOperator() : BinocularOperator(Operator::OperatorLabel::PLUS) {

}
