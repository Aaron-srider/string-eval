//
// Created by c w on 2022/6/26.
//

#ifndef REVERSE_POLISH_NOTATION_NUMBER_H
#define REVERSE_POLISH_NOTATION_NUMBER_H


#include <utility>

#include "../Token.h"
#include "iostream"
#include "Operand.h"

class Number : public Operand {
public:
    enum NumberType {
        INTEGER,
        DOUBLE,
        UNKNOWN
    };

    explicit Number(std::string value_text);

    //todo
    int ToIntValue() {
        return atoi(value_text_.c_str());
    }

    std::string ToString()  const;

    static bool IsPositiveInt(char ch);

private:
    std::string value_text_;

    NumberType number_type_ = UNKNOWN;
};


#endif //REVERSE_POLISH_NOTATION_NUMBER_H
