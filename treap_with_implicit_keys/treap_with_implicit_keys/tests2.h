#ifndef tests2_h
#define tests2_h

#include "interface.h"
#include <utility>
#include <vector>
#include <ctime>
#include <random>
#include <iostream>


class Tester {
 private:
    // Возможные типы команд
    enum command_type {
        INSERT,
        SETUP,
        SUMSEGMENT,
        NEXTPERM
    };
    
    // Структура-тест
    struct test {
        command_type type;
        int left, right; // Границы отрезка; в случае обращения по индексу, индекс - это левая граница
        int key; // Ключ в случае Insert'a и SetUp'a
        
        test(int _left, int _right, int _key, command_type _type)
        : type(_type), left(_left), right(_right), key(_key) {}
    };
    
    std::vector<test> tests;
    
    int N;
    int gap;
    
public:
    //Генератор случайных тестов с параметрами “количество команд”, “диапазон случайных данных”
    Tester(int n, int min_int, int max_int) : N(n), gap(max_int - min_int + 1) {
        //srand(time(NULL));
        tests.push_back(test(0, 0, rand() % gap + min_int, INSERT));
        size_t size = 1;
        for (size_t i = 1; i < N; i++) {
            int operation = rand() % 4;
            switch (operation) {
                case 0: {
                    test example_of_test(rand() % (size + 1), 0, rand() % gap + min_int, INSERT);
                    tests.push_back(example_of_test);
                    size++;
                    break;
                }
                case 1: {
                    test example_of_test(rand() % size, 0, rand() % gap + min_int, SETUP);
                    tests.push_back(example_of_test);
                    break;
                }
                case 2: {
                    size_t l = rand() % size;
                    size_t r = rand() % size;
                    if (l > r)
                        std::swap(l, r);
                    test example_of_test(l, r, 0, SUMSEGMENT);
                    tests.push_back(example_of_test);
                    break;
                }
                case 3: {
                    size_t l = rand() % size; 
                    size_t r = rand() % size;
                    if (l > r)
                        std::swap(l, r);
                    test example_of_test(l, r, 0, NEXTPERM);
                    tests.push_back(example_of_test);
                    break;
                }
            }
        }
    }
    
    // Механизм запуска сгенерированного теста
    std::vector<int> run_tests(InterfaceImplicitKeyTree*& implement) {
        std::vector<int> result;
        for(size_t i = 0; i < N; i++) {
            switch (tests[i].type) {
                case INSERT:
                    implement->Insert(tests[i].key, tests[i].left);
                    break;
                case SETUP:
                    implement->SetUp(tests[i].key, tests[i].left);
                    break;
                case SUMSEGMENT:
                    result.push_back(implement->SumSegment(tests[i].left, tests[i].right));
                    break;
                case NEXTPERM:
                    implement->NextPermutation(tests[i].left, tests[i].right);
                    break;
            }
        }
        return result;
    }
};

#endif /* tests2_h */
