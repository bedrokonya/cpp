#include "implicit_treap.h"
#include <iostream>

ImplicitTreap::ImplicitTreap(int _cost, ) {
    int cost = _cost;
    left = nullptr;
    right = nullptr;
    leftmost = left;
    rightmost = right;
    int sorted_suffix = 1;
    int priority = rand() % 1000;
    int size = 1;
    int sum_segment = _cost;
    bool reversed = false;
}

ImplicitTreap::~ImplicitTreap() {
        if (left) {
            delete left;
        }
        if (right) {
            delete right;
        }
}

ImplicitTreap* ImplicitTreap::Merge(ImplicitTreap* L, ImplicitTreap* R) {
    
    Push(L);
    Push(R);
    
    if (L == nullptr) {
        return R;
    }
    if (R == nullptr) {
        return L;
    }
    if (L->priority > R->priority) {
        L->right = Merge(L->right, R);
        L->Recalc();
        return L;
    }
    else {
        R->left = Merge(L, R->left);
        R->Recalc();
        return R;
    }
}

void ImplicitTreap::Split(int x, ImplicitTreap* &L, ImplicitTreap* &R) {
    
    Push(this);
    
    ImplicitTreap* newTreap = nullptr;
    int curIndex = SizeOf(left) + 1;
    
    if (curIndex <= x) {
        if (right == nullptr) {
            R = nullptr;
        }
        else {
            right->Split(x - curIndex, newTreap, R);
        }
        L = new ImplicitTreap(cost, priority, left, newTreap);
        L->Recalc();
    }
    else {
        if (left == nullptr) {
            L = nullptr;
        }
        else {
            left->Split(x, L, newTreap);
        }
        R = new ImplicitTreap(cost, priority, newTreap, right);
        R->Recalc();
    }
}
