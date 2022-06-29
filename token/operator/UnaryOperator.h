//
// Created by c w on 2022/6/24.
//

#ifndef REVERSE_POLISH_NOTATION_UNARYOPERATOR_H
#define REVERSE_POLISH_NOTATION_UNARYOPERATOR_H

#include "Operator.h"

class UnaryOperator : public Operator {
public:
    explicit UnaryOperator(OperatorLabel label);

    virtual int Calculate(int operand) const = 0;
};


#endif //REVERSE_POLISH_NOTATION_UNARYOPERATOR_H
