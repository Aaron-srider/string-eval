//
// Created by c w on 2022/6/24.
//

#ifndef REVERSE_POLISH_NOTATION_PLUSOPERATOR_H
#define REVERSE_POLISH_NOTATION_PLUSOPERATOR_H

#include "Operator.h"
#include "BinocularOperator.h"

class PlusOperator : public BinocularOperator {

public:
    PlusOperator();

     int Calculate(int operand1, int operand2) const override;

     char ToChar() const override;

};


#endif //REVERSE_POLISH_NOTATION_PLUSOPERATOR_H
