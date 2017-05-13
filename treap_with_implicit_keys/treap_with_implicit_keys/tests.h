
#ifndef tests_h
#define tests_h
#include <vector>
#include "treap_implicit_keys.h"
#include "naive_next_permutation.h"
#include "interface.h"

// Проверяет, правильно ли отработала конкретная операция; в случае ошибке выводит, что именно случилось
void check_operation(InterfaceImplicitKeyTree* test1, InterfaceImplicitKeyTree* test2, size_t num_op) {
    std::vector<int> test;
    std::vector<int> right;
    test.clear();
    test1->Print(test);
    right.clear();
    test2->Print(right);
    if(test.size() != right.size()){
        std::cout << "error! After " << num_op << "'th operation test.size doesn't equal right.size!\n";
        return;
    }
    for (size_t i = 0; i < test.size(); i++) {
        if (test[i] != right[i]) {
            std::cout << "error! After " << num_op <<  "'th operation vectors don't match!" << std::endl;
            std::cout << i <<"'th element is wrong!\n";
            return;
        }
    }
    //std::cout << "OKAY, at least vectors do match!\n";
}

// Тестирование, на вход получает указатель на нашу реализацию и на наивную, количество операций, минимум диапазона значений, максимум диапазона значений
void testing(InterfaceImplicitKeyTree* test1, InterfaceImplicitKeyTree* test2, int n, int minInt, int maxInt) {

    int gap = maxInt - minInt + 1; // Cчитаем диапазон возможных значений
    int cnt = 1; // Текущий индекс в массиве

    std::vector<int> test; // Вектор, в который мы будем заталкивать массив, на котором отработала наша реализация
    std::vector<int> right; // Вектор, в который мы будем заталкивать массив, на котором отработала наивная реализация
    
    for (size_t i = 0; i < n; ++i)
    {
        int t = 0, a = 0, b = 0;
        t = rand() % 4; // Генерируем номер операции
        if (t == 0) // INSERT
        {
            a = rand() % gap + minInt; // Генерируем значение, которое затолкнем в массив
            b = rand() % (cnt + 1); // Генерируем позицию, на которой будет записано это значение
            test1->Insert(a, b);
            test2->Insert(a, b);
            check_operation(test1, test2, i);
            ++cnt;
        }
        if (t == 1) //SETUP
        {
            a = rand() % gap + minInt; // Генерируем значение, которое затолкнем в массив
            b = rand() % cnt; // Генерируем позицию, на которой будет записано это значение
            test1->SetUp(a, b);
            test2->SetUp(a, b);
            check_operation(test1, test2, i);
        }
        if (t == 2) //SUMSEGMENT
        {
            a = rand() % cnt; // Генерируем левый конец подотрезка
            b = rand() % cnt; // Генерируем правый конец подотрезка
            if (a > b)
                std::swap(a, b);
            //std::cout << test1->SumSegment(a, b) << "  " << test2->SumSegment(a, b) << "\n";
            if (test1->SumSegment(a, b) != test2->SumSegment(a, b)){
                std::cout << "error! SumSegment's don't match!" << ' ' << i << ' '<< t << std::endl;
            }
            check_operation(test1, test2, i);
        }
        
        if (t == 3) //NEXT PERMUTATION
        {
            a = rand() % cnt;  // Генерируем левый конец подотрезка
            b = rand() % cnt;  // Генерируем правый конец подотрезка
            if (a > b)
                std::swap(a, b);
            right.clear();
            test2->Print(right);
            // Проверяем, можно ли вообще выполнить NextPermutation на данном подотрезке
            for (size_t i = a; i < b; ++i)
            {
                if (right[i] < right[i + 1])
                {
                    test1->NextPermutation(a, b);
                    test2->NextPermutation(a, b);
                    break;
                }
            }
            check_operation(test1, test2, i);
        }
        //std::cout << t << ' ' << a << ' ' << b << ' ';
        //std::cout << std::endl;
    }
    
    /*test1->Print(test);
    right.clear();
    test2->Print(right);
    if (test.size() != right.size())
        std::cout << "error" << std::endl;
    for (size_t i = 0; i < test.size(); ++i)
        if (test[i] != right[i])
            std::cout << "error" << std::endl; */
}

#endif /* tests_h */
