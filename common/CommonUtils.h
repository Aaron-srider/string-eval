//
// Created by c w on 2022/6/30.
//

#ifndef REVERSE_POLISH_NOTATION_COMMONUTILS_H
#define REVERSE_POLISH_NOTATION_COMMONUTILS_H

#include "iostream"

/**
* Delete white char(\n \t \r ' ') from a std::string.
* @param str [in] target str to be processed.
* @param result [out] result string.
*/
void DeleteWhite(const std::string *str, std::string *result);

#endif //REVERSE_POLISH_NOTATION_COMMONUTILS_H
