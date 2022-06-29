//
// Created by c w on 2022/6/24.
//

#include "MultiplicationOperator.h"

int MultiplicationOperator::Calculate(int operand1, int operand2) const {
    return operand2 * operand1;
}

char MultiplicationOperator::ToChar() const {
    return '*';
}

MultiplicationOperator::MultiplicationOperator() : BinocularOperator(OperatorLabel::MULTIPLICATION) {

}
