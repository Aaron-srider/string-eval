//
// Created by c w on 2022/6/24.
//

#ifndef REVERSE_POLISH_NOTATION_NEGATIVEOPERATOR_H
#define REVERSE_POLISH_NOTATION_NEGATIVEOPERATOR_H

#include"Operator.h"
#include "UnaryOperator.h"

class NegativeOperator : public UnaryOperator {
public:
    NegativeOperator();

    int Calculate(int operand) const override;

    char ToChar() const override;
};


#endif //REVERSE_POLISH_NOTATION_NEGATIVEOPERATOR_H
