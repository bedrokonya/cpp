#pragma once

#include <string>

// Класс, переводящий инфиксное выражение в постфиксное и вычисляющий его значение.
class Calculator {
 public:
    // Конструкторы.
    Calculator();
    Calculator(const std::string& line);
    // Деструктор,
    ~Calculator();
    
    void ToReversePolish();  // Переводит инфиксную запись в постфиксную.
    void CalculateReversePolish();  // Вычисляет значение выражения в постфиксной записи.
    double value() const; // Возвращает посчитанное значение выражения.
    std::string infix_line;
    std::string postfix_line;
   
    
 private:
    
    double value_; // Переменная, в которую запишется окончательное значения выражения.
    
    double count_operation(const char& operation, double a, double b);  // Считает значение элементарного выражения.
    bool is_operator(const char& c); // Проверяет, является ли символ оператором.
    std::string associativity(const char& c); // Возврашает "значение" ассоциативности оператора.
    int priority(const char & c);  // Возвращает приоритет оператора.
};
