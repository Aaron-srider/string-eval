//
// Created by c w on 2022/6/24.
//

#ifndef REVERSE_POLISH_NOTATION_SUBTRACTIONOPERATOR_H
#define REVERSE_POLISH_NOTATION_SUBTRACTIONOPERATOR_H

#include "BinocularOperator.h"

class SubtractionOperator : public BinocularOperator {
public:
    SubtractionOperator();

    int Calculate(int operand1, int operand2) const override;


    char ToChar() const override;

};


#endif //REVERSE_POLISH_NOTATION_SUBTRACTIONOPERATOR_H
