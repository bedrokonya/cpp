
#include "tests2.h"
#include "naive_next_permutation.h"
#include "treap_implicit_keys.h"

#include <iostream>
/*
int main() {
    // Количество операций, минимум диапазона значений, максимум диапащона значений
    int n, minInt, maxInt;
    std::cin >> n >> minInt >> maxInt;
    // Cчитаем диапазон возможных значений
    int gap = maxInt - minInt + 1;
    // Генерируем первое число, которое затоклнем в массивы
    int start = rand() % gap + minInt;
    // Заталкиваем первое число
    InterfaceImplicitKeyTree* test1 = new ImplicitTreap(start);
    InterfaceImplicitKeyTree* test2 = new Vect(start);
    // Запускаем тестирование
    testing(test1, test2, n, minInt, maxInt);
    return 0;
}
*/

int main() {
    // Количество операций, минимум диапазона значений, максимум диапащона значений
    int N, min_int, max_int;
    std::cin >> N >> min_int >> max_int;
    
    // Генерируем тесты
    Tester test(N, min_int, max_int);
    Vect naive_realisation;
    ImplicitTreap treap;
    
    InterfaceImplicitKeyTree* first = &treap;
    InterfaceImplicitKeyTree* second = &naive_realisation;
    
    // Запускаем тестирования
    clock_t treap_time = clock();
    std::vector<int> treap_res = test.run_tests(first);
    treap_time = clock() - treap_time;
    
    clock_t naive_time = clock();
    std::vector<int> naive_res = test.run_tests(second);
    naive_time = clock() - naive_time;
    
    std::cout << "IKTreap's time : " << (static_cast<double>(treap_time) / CLOCKS_PER_SEC) << "seconds" << "\n";
    std::cout << "Naive realisation's time : " << (static_cast<double>(naive_time) / CLOCKS_PER_SEC) << "seconds" << "\n";
    
    // Проверяем, корректно ли все отработало
    int errors = 0;
    for (int i = 0; i < treap_res.size(); i++) {
        if (treap_res[i] != naive_res[i]) {
            errors++;
        }
    }
    
    std::cout << "Amount of errors : " << errors << "\n";
    return 0;
}

