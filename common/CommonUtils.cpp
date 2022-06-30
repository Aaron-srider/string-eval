//
// Created by c w on 2022/6/30.
//
#include "CommonUtils.h"

void DeleteWhite(std::string str, std::string *result) {
    result->clear();
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n') {
            continue;
        }
        result->push_back(str[i]);
    }
}
