//
// Created by c w on 2022/6/26.
//

#ifndef REVERSE_POLISH_NOTATION_OPERAND_H
#define REVERSE_POLISH_NOTATION_OPERAND_H

#include "../Token.h"
class Operand:public Token {

    bool IsOperator()  const override;

    bool IsOperand()  const override;
};


#endif //REVERSE_POLISH_NOTATION_OPERAND_H
