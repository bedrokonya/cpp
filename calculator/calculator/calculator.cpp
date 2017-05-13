#include "calculator.h"
#include <stack>
#include <cassert>
#include <cmath>
#include <vector>
#include <cctype>

using std::string;

Calculator::Calculator() :
    value_(0)
{
}

Calculator::Calculator(const string& line) :
    value_(0)
{
    infix_line = line;
}

Calculator::~Calculator() {}



double Calculator::value() const
{
    return value_;
}



// Проверяет, является ли символ оператором.
bool Calculator::is_operator(const char& c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

// Возвращает значение ассоциотивности оператора,
string Calculator::associativity(const char& c) {
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
            return "left";
        case '^':
            return "right";
        default:
            assert(false);
    }
}

// Возвращает приоритет оператора.
int Calculator::priority(const char& c) {
    switch (c) {
        case '(':
        case ')':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default: assert(false);
    }
}

//Считает значение элементарного выражения.
double Calculator::count_operation(const char &operation, double a, double b) {
    double result = 0.0;
    switch (operation) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = b - a;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = b / a;
            break;
        case '^':
            result = pow(b, a);
            break;

    }
    return result;
}



// Перевод инфиксной записи в постфикусную.
void Calculator::ToReversePolish() {
    std::stack<char> stack;
    //stack.push('(');
    for (int i = 0; i < infix_line.length() ; i++){
        char current = infix_line[i];
        
        // Если пробел, то игнорируем.
        if (isspace(current)) {
            continue;
        }
        // Если символ является числом, то добавляем его к выходной строке.
        if (isalnum(current) || current == '.') {
            postfix_line += current;
        } else
            // Если символ является открывающей скобкой, помещаем его в стек.
            if (current == '(') {
                stack.push(current);
            } else
                // Если символ является оператором 'о1'
                if (is_operator(current)) {
                    if (associativity(current) == "left") { // Если оператор о1 лево-ассоциированный,
                        // то пока приоритет 'o1' меньше или равен приоритету оператора, находящегося на вершине стека,  выталкиваем верхний элемент стека в выходную строку.
                        while (priority(current) <= priority(stack.top())) {
                            postfix_line = postfix_line + ' ' + stack.top();
                            stack.pop();
                        }
                        postfix_line += ' ';
                        stack.push(current); // Помещаем оператор o1 в стек.
                    }
                    //Если оператор о1 право-ассоциированный,
                    if (associativity(current) == "right") {
                        // то пока приоритет o1 меньше приоритета оператора, находящегося на вершине стека, выталкиваем верхний элемент стека в выходную строку.
                        while (priority(current) < priority(stack.top())) {
                            postfix_line = postfix_line + ' ' + stack.top();
                            stack.pop();
                        }
                        postfix_line += ' ';
                        stack.push(current); // Помещаем оператор о1 в стек.
                    }
                } else
                    // Если символ является закрывающей скобкой: до тех пор, пока верхним элементом стека не станет открывающая скобка, выталкиваем элементы из стека в выходную строку. При этом открывающая скобка удаляется из стека, но в выходную строку не добавляется.
                    if (current == ')') {
                        while (!stack.empty() && stack.top() != '(') {
                            postfix_line = postfix_line + ' ' + stack.top();
                            stack.pop();
                        }
                        // Если в стеке не осталось открывающейся скобки, значит в выражении не согласованы скобки.
                        if (stack.empty())
                            throw std::runtime_error("Некорректный ввод");
                        stack.pop();
                    }
    }
    // Когда входная строка закончилась, выталкиваем все символы из стека в выходную строку.
    while (!stack.empty() && stack.top() != '(') {
        postfix_line = postfix_line + ' ' + stack.top();
        stack.pop();
    }
    postfix_line += ' ';
    if (stack.empty())
        throw std::runtime_error("Некорректный ввод");
    // Удалить скобку, добавленную вначале.
    //stack.pop();
}

// Вычисление выражения в постфиксной записи.
void Calculator::CalculateReversePolish() {
    std::stack<double> stack; // Стек операндов.
    string temp; // Для считывания числа из постфиксной строки.
    
    for (int i = 0; i < postfix_line.length(); ++i) {
        char current = postfix_line[i];
        if (isalnum(current) || current == '.') {
            temp += current;
        } else
            if (isspace(current) && (isalnum(postfix_line[i - 1]))) {
                stack.push(stod(temp));
                temp = "";
            } else
                if (is_operator(current)) {
                    
                    double a, b;
                    a = stack.top();
                    stack.pop();
                    b = stack.top();
                    stack.pop();
                    stack.push(count_operation(current, a, b));
                }
    }
    value_ = stack.top();
}
