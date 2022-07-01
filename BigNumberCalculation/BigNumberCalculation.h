//
// Created by c w on 2022/6/30.
//

#ifndef REVERSE_POLISH_NOTATION_BIGNUMBERCALCULATION_H
#define REVERSE_POLISH_NOTATION_BIGNUMBERCALCULATION_H

#include "iostream"

class BigNumberCalculation {
public:
    BigNumberCalculation() {}                                  //默认构造函数
    bool cmp(std::string a, std::string b);                   //比较两个“数字”的大小
    void Carry(std::string &c, int t);                   //进位操作，当某一位超过十是使用此函数进位
    std::string Add(std::string a, std::string b);                 //大数加法
    std::string Less(std::string a, std::string b);                //大数减法
    std::string Multiply(std::string a, std::string b);            //大数乘法
    std::string Except_Judge(std::string a, std::string b, int n); //大数除法模式选择（大数小或小除大）
    std::string Except_A(std::string a, std::string b, int n);     //大除小
    std::string Except_B(std::string a, std::string b, int n);     //小除大高精度除法，其中n为自定义的小数位数
    std::string Module(std::string a, std::string b);              //大数求模

public:
    static void Add(std::string a, std::string b, std::string *c);

public:
    static bool IsNegative(const std::string *basicString);

    static bool PositiveOrZero(const std::string *basicString);

    static int PositiveOrZeroCompare(std::string a, std::string b);

    static void DeleteZero(std::string number, std::string &result);

    static void Abs(std::string a, std::string &result);

    static int Compare(std::string a, std::string b);

    static void PositiveAdd(std::string a, std::string b, std::string *c);

    static void PositiveSub(std::string a, std::string b, std::string &c);

    static void Opposite(const std::string *original, std::string *opposite);

    static bool Positive(const std::string *a);

    static bool Zero(const std::string *a);
};


#endif //REVERSE_POLISH_NOTATION_BIGNUMBERCALCULATION_H
