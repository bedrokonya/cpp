
#ifndef treap_h
#define treap_h
#pragma once
#include <stdlib.h>
#include <algorithm>

// Декартово дерево.
class Treap {
private:
    int key; // x
    int priority; // y
    Treap* left; // Указатель на левое поддерево
    Treap* right; // Указатель на правое поддерево.
    int size; // Размер (необязательная характеристика, ввела для проверки
public:
    int height; // Высота дерева.
    // Конструктор для пустого дерева.
    Treap() : left(nullptr), right(nullptr), size(0), height(0), key() {}
    // Конструктор для одноэлементного дерева.
    Treap(int _x, int _y) {
        key = _x;
        priority = _y;
        left = nullptr;
        right = nullptr;
        size = 1;
        height = 0;
    }
    
    // Деструктор.
    ~Treap() {
        if (left) {
            delete left;
        }
        if (right) {
            delete right;
        }
    }
    
    Treap* merge(Treap* _left, Treap* _right);
    void split(int x, Treap* T, Treap* &L, Treap* &R);
    void update_size();
    void update_height();
    Treap* add(int key, int priority);
    
};

inline void Treap::update_size() {
    size = (left ? left->size : 0) + (right ? right->size : 0) + 1;
}

inline void Treap::update_height() {
    height = std::max(left ? left->height : 0, right ? right->height : 0) + 1;
}

// Объединяет два поддерева left и right, и возвращает это новое дерево. Следует заметить, что работать операция merge может не с любыми парами деревьев, а только с теми, у которых все ключи одного дерева left не превышают ключей второго right.
Treap* Treap::merge(Treap* left, Treap* right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    // Смотрим, какой элемент станет корнем будущего дерева.
    if (left->priority > right->priority) {
        // Если приоритет левого корня оказался больше приоритета правого, то корнем нового дерева становится корень left. Левым поддеревом нового дерева становится left->left. А для правого дерева нового поддерева рекурсивно вызываем merge от right и left->right.
        left->right = merge(left->right, right);
        left->update_size();
        left->update_height();
        return left;
    }
    else { // Симметричная ситуация.
        right->left = merge(left, right->left);
        right->update_size();
        right->update_height();
        return right;
    }
}

//Split (x, T, L, R) - разделяет дерево T на два дерева L и R (которые являются возвращаемым значением) таким образом, что L содержит все элементы, меньшие по ключу x, а R содержит все элементы, большие x.
void Treap::split(int x, Treap* T, Treap* &L, Treap* &R) {
    // Если дерево пустое -- выходим из рекурсии.
    if (T == nullptr) {
        L = R = nullptr;
    }
    // Смотрим, где окажется корень нового дерева. Если его ключ меньше x, то в L, иначе в R.
    else if (x < T->key) {
        // Если ключ корня оказался больше х, то все элементы правого поддерева T также окажутся в R — их ключи ведь тоже все будут больше x. Более того, корень T будет и корнем R, поскольку его приоритет наибольший во всем дереве. Правое поддерево корня полностью сохранится без изменений, а вот левое уменьшится — из него придется убрать элементы с ключами, меньшими x, и вынести в дерево L. А остаток ключей сохранить как новое левое поддерево R.
        split(x, T->left, L, T->left);
        R = T;
        R->update_size();
        R->update_height();
    }
    else { // Симметричная ситуация.
        split(x, T->right, T->right, R);
        L = T;
        L->update_size();
        L->update_height();
    }
}

// Добавление элемента.
Treap* Treap::add(int _key, int _priority) {
    Treap* L;
    Treap* R;
    if (this->size == 0) { // Если добавляем элемент в пустую кучу.
        Treap* tmp = new Treap(_key, _priority);
        return tmp;
    }
    split(_key, this, L, R); // Разделим дерево по ключу _key на дерево L, с ключами меньше _key, и дерево R, с большими.
    Treap* M = new Treap(_key, _priority); // Создадим из данного ключа дерево M из единственной вершины (_key, _priority)
    return merge(merge(L, M), R); // Объединим по очереди L с M, а то что получилось — с R.

}

#endif /* treap_h */
