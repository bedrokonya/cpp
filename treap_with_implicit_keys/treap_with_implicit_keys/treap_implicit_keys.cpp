
#include "treap_implicit_keys.h"
#include <queue>
#include <iostream>

void ImplicitTreap::Recalc(Node* v) {
    if (v == nullptr) {
        return;
    }
    v->size = SizeOf(v->left) + SizeOf(v->right) + 1;
    v->sum_segment = SumOf(v->left) + v->cost + SumOf(v->right);
    v->leftmost = v->cost;
    v->rightmost = v->cost;
    RecalcSortedSuffix(v);
    RecalcSortedPrefix(v);
    if (v->left) {
        v->leftmost = v->left->leftmost;
    }
    if (v->right) {
        v->rightmost = v->right->rightmost;
    }
    
}

int ImplicitTreap::SizeOf(Node* v) {
    if (v == nullptr) {
        return 0;
    }
    return v->size;
}

int ImplicitTreap::SumOf(Node* v) {
    if (v == nullptr) {
        return 0;
    }
    return v->sum_segment;
}

int ImplicitTreap::SizeOfSortedSuffix(Node* v) {
    if (v == nullptr) {
        return 0;
    }
    return v->sorted_suffix;
}

int ImplicitTreap::SizeOfSortedPrefix(Node *v) {
    if (v == nullptr) {
        return 0;
    }
    return v->sorted_prefix;

}

ImplicitTreap::ImplicitTreap(int _cost) {
    root = new Node(_cost);
}

ImplicitTreap::ImplicitTreap() {
    //root = new Node();
}

void ImplicitTreap::Print(Node* v) {
    if (v == nullptr)
        return;
    Print(v->left);
    std::cout << v->cost << " ";
    Print(v->right);
}

ImplicitTreap::~ImplicitTreap() {
    if (root)
        delete root;
}


Node* ImplicitTreap::Merge(Node* left, Node* right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    // Смотрим, какой элемент станет корнем будущего дерева.
    if (left->priority > right->priority) {
        // Если приоритет левого корня оказался больше приоритета правого, то корнем нового дерева становится корень left. Левым поддеревом нового дерева становится left->left. А для правого дерева нового поддерева рекурсивно вызываем merge от right и left->right.
        left->right = Merge(left->right, right);
        Recalc(left);
        return left;
    }
    else { // Симметричная ситуация.
        right->left = Merge(left, right->left);
        Recalc(right);
        return right;
    }
}

void ImplicitTreap::Split(Node* v, int x, Node* &L, Node* &R) {
    
    if(!v) {
        L = nullptr;
        R = nullptr;
        return;
    }
    
    Push(v);
    int curIndex = SizeOf(v->left) + 1;
    if (curIndex > x)
    {
        R = v;
        Split(v->left, x, L, R->left);
    }
    else
    {
        L = v;
        Split(v->right, x - curIndex, L->right, R);
    }
    
    Recalc(L);
    Recalc(R);
}


Node* ImplicitTreap::Insert(Node* v, int pos, int _cost) {
    
    Node* l;
    Node* r;
    
    Split(v, pos, l, r);
    Node* m = new Node(_cost);
    return Merge(Merge(l, m), r);
}

Node* ImplicitTreap::Remove(Node* v, int pos) {
    
    Node* l;
    Node* m;
    Node* r;
    
    Split(v, pos, l, r);
    Split(r, 1, m, r);
    return Merge(l, r);
}

int ImplicitTreap::SumOnSubsegment(Node* v, int a, int b) {
    
    Node* l;
    Node* m;
    Node* r;
    
    Split(v, a, l, r);
    Split(r, b - a, m, r);
    return SumOf(m);
}


void ImplicitTreap::Push(Node* v) {
    if (v == nullptr)
        return;
    
    // не установленное обещание не проталкивается
    if (!v->reversed)
        return;
    std::swap(v->sorted_suffix, v->sorted_prefix);
    std::swap(v->leftmost, v->rightmost);
    std::swap(v->left, v->right);
    //Node* temp = v->left;
    //v->left = v->right;
    //v->reversed = temp;
    v->reversed = false;
    if (v->left != nullptr)
        v->left->reversed ^= true;
    if (v->right != nullptr)
        v->right->reversed ^= true;
}


Node* ImplicitTreap::Reverse(Node* &v, int a, int b) {
    Node* l;
    Node* m;
    Node* r;
    
    Split(v, a, l, r);
    Split(r, b - a, m, r);
    m->reversed ^= true;
    return Merge(Merge(l, m), r);
}


void ImplicitTreap::RecalcSortedSuffix(Node* v) {
    v->sorted_suffix = 0;
    // Если правый сын существует
    if (v->right) {
        v->sorted_suffix = v->right->sorted_suffix;
    }
    
    // Если правого сына нет или его суффикс является убывающим отрезком, а значение в вершине больше или равно значению в правом сыне
    if (v->right == nullptr || (SizeOfSortedSuffix(v->right) == SizeOf(v->right) && v->cost >= v->right->leftmost)) {
        v->sorted_suffix++;
        // Если суффикс левого сына является убывающим отрезком и ...
        if (v->left && v->left->rightmost >= v->cost) {
            v->sorted_suffix += v->left->sorted_suffix;
        }
    }
}

void ImplicitTreap::RecalcSortedPrefix(Node* v) {
    v->sorted_prefix = 0;
    
    if (v->left) {
        v->sorted_prefix = v->left->sorted_prefix;
    }
    if (v->left == nullptr || (SizeOfSortedPrefix(v->left) == SizeOf(v->left) && v->left->rightmost <= v->cost) ) {
        v->sorted_prefix++;
        if (v->left && v->cost <= v->right->leftmost) {
            v->sorted_prefix += v->right->sorted_prefix;
        }
    }
}
/*
int main() {
    int N;
    std::cin >> N;
    //ImplicitTreap* trp = new ImplicitTreap(rand() % 100);
 
    trp->root = trp->Add(trp->root, 0, 7);
    trp->root = trp->Add(trp->root, 1, 23);
    trp->root = trp->Add(trp->root, 2, 4);
    trp->root = trp->Add(trp->root, 3, 44);
    trp->root = trp->Add(trp->root, 4, 54);
    for (int i = 0; i < N; i++) {
        trp->root = trp->Insert(trp->root, i, rand()% 100);
    }
    trp->Print(trp->root);
    trp->root = trp->Remove(trp->root, 4);
    std::cout << "\n";
    trp->Print(trp->root);
    trp->root = trp->Reverse(trp->root, 6, 9);
     std::cout << "\n";
    trp->Print(trp->root);
    return 0;
} */
