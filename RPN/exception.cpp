//
// Created by c w on 2022/6/28.
//

#include "exception.h"
#include "iostream"

const char *UnexpectedOperatorException::what() const _NOEXCEPT {
    std::cout << "Unexpected Operator Found: " << op_ << std::endl;
}

UnexpectedOperatorException::UnexpectedOperatorException(std::string op):op_(std::move(op)) {

}
