//
// Created by c w on 2022/6/26.
//

#include "Number.h"

std::string Number::ToString()  const{
    return std::string(value_text_);
}

Number::Number(std::string value_text) {
    this->value_text_ = std::move(value_text);
}
