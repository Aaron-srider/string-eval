#include <iostream>
#include "RPN/RPN.h"

int main() {
    // 操作数只支持个位数， 只支持双目

    class RPN rpn("2*(9-2*3+5)/5-4/2");
    rpn.ConvertInfix2Suffix();
    int result = rpn.EvalRPN()->ToIntValue();
    std::cout << result << std::endl;
    return 0;
}
