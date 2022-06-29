//
// Created by c w on 2022/6/26.
//

#include "LeftBracket.h"

char LeftBracket::ToChar()  const{
    return '(';
}

LeftBracket::LeftBracket(): Operator(OperatorType::unknown, OperatorLabel::LEFTBRACKET){}
