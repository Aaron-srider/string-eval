//
// Created by c w on 2022/6/28.
//

#ifndef REVERSE_POLISH_NOTATION_EXCEPTION_H
#define REVERSE_POLISH_NOTATION_EXCEPTION_H


#include <exception>
#include "string"

class UnexpectedOperatorException :public std::exception{

public:
    explicit UnexpectedOperatorException(std::string op);

private:
    //std::string what_ = "Unexpected Operator Found";

    std::string op_;

    const char * what() const _NOEXCEPT override ;

};


#endif //REVERSE_POLISH_NOTATION_EXCEPTION_H
