//
// Created by c w on 2022/6/26.
//

#ifndef REVERSE_POLISH_NOTATION_LEFTBRACKET_H
#define REVERSE_POLISH_NOTATION_LEFTBRACKET_H

#include "Operator.h"

class LeftBracket : public Operator {
public:
    LeftBracket();

    char ToChar() const override;

};


#endif //REVERSE_POLISH_NOTATION_LEFTBRACKET_H
