#pragma once
#include <vector>
// Интерфейс структуры данных, инкапсулирующий дерево по неявному ключу
class InterfaceImplicitKeyTree {
public:
    virtual void Insert(int cost, int pos) = 0; // Вставка элемента на позицию
    virtual void SetUp(int cost, int pos) = 0; // Установка значения на позицию
    virtual int SumSegment(int l, int r) = 0; // Сумма на подотрезке
    virtual void NextPermutation(int l, int r) = 0; // Следующая перестановка на подотрезке
    virtual void Print(std::vector<int> &res) = 0;
    virtual ~InterfaceImplicitKeyTree() {};
};
