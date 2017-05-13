
#include "treap_implicit_keys.h"
#include <queue>
#include <iostream>

void ImplicitTreap::Recalc() {
    if (this == nullptr) {
        return;
    }
    this->size = SizeOf(this->left) + SizeOf(this->right) + 1;
    this->sum_segment += SumOf(this->left) + SumOf(this->right);
    RecalcSortedSuffix(this);
    if (this->left) {
        this->leftmost = this->left->leftmost;
    }
    if (this->right) {
        this->rightmost = this->right->rightmost;
    }
}

int ImplicitTreap::SizeOf(Node* &tmp) {
    if (tmp == nullptr) {
        return 0;
    }
    return tmp->size;
}

int ImplicitTreap::SumOf(Node* &tmp) {
    if (tmp == nullptr) {
        return 0;
    }
    return tmp->sum_segment;
}

int ImplicitTreap::SizeOfSortedSuffix(Node* &tmp) {
    if (tmp == nullptr) {
        return 0;
    }
    return tmp->sorted_suffix;
}


ImplicitTreap::ImplicitTreap(int _cost) {
    root = new Node(_cost);
}

ImplicitTreap::ImplicitTreap() {
    root = new Node();
}

void ImplicitTreap::Print() {

    std::queue<Node*> inProgress;
    inProgress.push(root);
    while (!inProgress.empty()) {
        Node* current = inProgress.front();
        inProgress.pop();
        if (current == nullptr) {
            continue;
        }
        std::cout << (current->cost) << "\n";
        inProgress.push(current->left);
        inProgress.push(current->right);
    }
}

ImplicitTreap::~ImplicitTreap() {
    if (root)
        delete root;
}



/* void ImplicitTreap::Recalc() {
    if (this == nullptr) {
        return;
    }
    this->size = SizeOf(this->left) + SizeOf(this->right) + 1;
    this->sum_segment += SumOf(this->left) + SumOf(this->right);
    RecalcSortedSuffix(this);
    if (this->left) {
        root->leftmost = root->left->leftmost;
    }
    if (root->right) {
        root->rightmost = root->right->rightmost;
    }
}

*/

Node* ImplicitTreap::Merge(Node* L, Node* R) {
    
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


void ImplicitTreap::Split(int x, Node* &L, Node* &R) {
    
    Push(this);
    
    Node* newTreap = nullptr;
    int curIndex = SizeOf(root->left) + 1;
    
    if (curIndex <= x) {
        if (root->right == nullptr) {
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

ImplicitTreap* ImplicitTreap::Add(int pos, int _cost) {
    
    ImplicitTreap* l;
    ImplicitTreap* r;
    
    Split(pos, l, r);
    ImplicitTreap* m = new ImplicitTreap(_cost, rand() % 1000, left = nullptr, right = nullptr);
    return Merge(Merge(l, m), r);
}

ImplicitTreap* ImplicitTreap::Remove(int pos) {
    
    ImplicitTreap* l;
    ImplicitTreap* m;
    ImplicitTreap* r;
    
    Split(pos, l, r);
    r->Split(1, m, r);
    return Merge(l, r);
}

int ImplicitTreap::SumOnSubsegment(int a, int b) {
    
    ImplicitTreap* l;
    ImplicitTreap* m;
    ImplicitTreap* r;
    
    this->Split(a, l, r);
    r->Split(b - a, m, r);
    return SumOf(m);
}


void ImplicitTreap::Push(Node& *tmp) {
    if (tmp == nullptr)
        return;
    
    // не установленное обещание не проталкивается
    if (!tmp->reversed)
        return;
    
    Node* temp = tmp->left;
    tmp->left = tmp->right;
    trmp->reversed = temp;
    
    tmp->reversed = false;
    if (tmp->left != nullptr)
        tmp->left->reversed ^= true;

    
    if (tmp->right != nullptr)
        tmp->right->reversed ^= true;
}


ImplicitTreap* ImplicitTreap::Reverse(int a, int b) {
    ImplicitTreap* l;
    ImplicitTreap* m;
    ImplicitTreap* r;
    
    this->Split(a, l, r);
    r->Split(b - a, m, r);
    m->reversed ^= true;
    return Merge(Merge(l, m), r);
}


void ImplicitTreap::RecalcSortedSuffix(Node* trp) {
    // Если правый сын существует
    if (trp->right) {
        trp->sorted_suffix = trp->right->sorted_suffix;
    }
    // Если правого сына нет или его суффикс является убывающим отрезком, а значение в вершине больше или равно значению в правом сыне
    if (trp->right == nullptr || (SizeOfSortedSuffix(trp->right) == SizeOf(trp->right) && trp->cost >= trp->right->leftmost->cost)) {
        trp->sorted_suffix++;
        // Если суффикс левого сына является убывающим отрезком и ...
        if (trp->left && trp->left->rightmost && trp->left->rightmost->cost >= trp->cost) {
            trp->sorted_suffix += trp->left->sorted_suffix;
        }
    }
}


int main() {
    int N;
    std::cin >> N;
    ImplicitTreap root;
    for (int i = 1; i < N; i++) {
        root.Add(i, rand() % 1000);
    }
    root.Print();
    return 0;
}
