//
// Created by c w on 2022/6/24.
//

#include "SubtractionOperator.h"

int SubtractionOperator::Calculate(int operand1, int operand2) const {
    return operand1 - operand2;
}

SubtractionOperator::SubtractionOperator() : BinocularOperator(OperatorLabel::SUBTRACTION) {

}

char SubtractionOperator::ToChar() const {
    return '-';
}
