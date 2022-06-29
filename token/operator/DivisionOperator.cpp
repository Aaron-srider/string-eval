//
// Created by c w on 2022/6/24.
//

#include "DivisionOperator.h"

int DivisionOperator::Calculate(int operand1, int operand2) const {
    return operand1 / operand2;
}

char DivisionOperator::ToChar() const {
    return '/';
}


DivisionOperator::DivisionOperator():BinocularOperator(OperatorLabel::DIVISION) {

}

