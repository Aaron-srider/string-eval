//
// Created by c w on 2022/6/26.
//

#ifndef REVERSE_POLISH_NOTATION_RIGHTBRACKET_H
#define REVERSE_POLISH_NOTATION_RIGHTBRACKET_H

#include "Operator.h"

class RightBracket: public Operator {
public:
    RightBracket();

    virtual char ToChar() const override;

};


#endif //REVERSE_POLISH_NOTATION_RIGHTBRACKET_H
