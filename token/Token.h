//
// Created by c w on 2022/6/26.
//

#ifndef REVERSE_POLISH_NOTATION_TOKEN_H
#define REVERSE_POLISH_NOTATION_TOKEN_H

#include "iostream"
class Token {

public:
    virtual bool IsOperand() const = 0;

    virtual bool IsOperator() const = 0;

    virtual std::string ToString() const = 0;

    virtual ~Token() = default;

};


#endif //REVERSE_POLISH_NOTATION_TOKEN_H
