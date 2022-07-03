#include <iostream>
#include"BigNumberCalculation/BigNumberCalculation.h"
int main() {

    std::string a = "9347563749273604563";
    std::string b = "37384";
    std::string c;

    BigNumberCalculation::Divide(&a,&b,&c);
    std::cout << c << std::endl;
}
