#include "calculator.h"
#include <iostream>
#include <string>

int main() {
    std::string line;
    std::getline(std::cin, line);
    Calculator calc(line);
    calc.ToReversePolish();
    calc.CalculateReversePolish();
    std::cout << calc.infix_line << "\n";
    std::cout << calc.postfix_line << "\n";
    std::cout << calc.value() << "\n";
    return 0;
}
