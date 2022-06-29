//
// Created by c w on 2022/6/24.
//

#ifndef REVERSE_POLISH_NOTATION_BINOCULAROPERATOR_H
#define REVERSE_POLISH_NOTATION_BINOCULAROPERATOR_H

#include "Operator.h"

class BinocularOperator : public Operator {

public:
    explicit BinocularOperator(OperatorLabel label);

    virtual int Calculate(int operand1, int operand2) const = 0;
};


#endif //REVERSE_POLISH_NOTATION_BINOCULAROPERATOR_H
