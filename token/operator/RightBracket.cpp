//
// Created by c w on 2022/6/26.
//

#include "RightBracket.h"

char RightBracket::ToChar()  const{
    return ')';
}

RightBracket::RightBracket() : Operator(Operator::OperatorType::unknown, Operator::OperatorLabel::RIGHTBRACKET) {

}
