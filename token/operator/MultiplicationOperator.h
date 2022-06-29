//
// Created by c w on 2022/6/24.
//

#ifndef REVERSE_POLISH_NOTATION_MULTIPLICATIONOPERATOR_H
#define REVERSE_POLISH_NOTATION_MULTIPLICATIONOPERATOR_H


#include "BinocularOperator.h"
class MultiplicationOperator: public BinocularOperator{
public:
    MultiplicationOperator();

    int Calculate(int operand1, int operand2) const override;

    char ToChar() const override;


};


#endif //REVERSE_POLISH_NOTATION_MULTIPLICATIONOPERATOR_H
