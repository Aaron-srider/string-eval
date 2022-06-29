//
// Created by c w on 2022/6/24.
//

#include "NegativeOperator.h"

NegativeOperator::NegativeOperator() : UnaryOperator(OperatorLabel::NEGATIVE) {

}

int NegativeOperator::Calculate(int operand) const {
    return -operand;
}

char NegativeOperator::ToChar() const {
    return '-';
}



