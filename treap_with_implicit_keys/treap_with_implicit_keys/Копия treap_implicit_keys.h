
#ifndef treap_implicit_keys_h
#define treap_implicit_keys_h
#include <iostream> 
#include "next_permutation.h"

// Структура для вершины дерева
struct Node {
    int cost; // значение в вершине
    Node* left; // левый сын
    Node* right; // правый сын
    int leftmost; // значение в самом левом потомке, за который отвечает данная вершина
    int rightmost;  // значение в самом правом потомке, за который отвечает данная вершина
    int sorted_suffix; // количество элементов в убывающем суффиксе
    int sorted_prefix; // количество элементов в возрастающем префиксе
    int priority; // приоритет
    int size; // размер поддерева включая саму вершину
    int sum_segment; // сумма на отрезке, за который отвечает данная вершина
    bool reversed; // флаг, отвечающий на вопрос, переворачивали ли мы отрезок, за который отвечает данная вершина, или нет
    
    // Конструктор с присваиванием левого и правого сыновей
    Node(int _cost, Node* _left, Node* _right) {
        cost = _cost;
        left = _left;
        right = _right;
        leftmost = left->cost;
        rightmost = right->cost;
        sorted_suffix = 1;
        sorted_prefix = 1;
        priority = rand() % 1000;
        size = 1;
        sum_segment = _cost;
        reversed = false;
    }
    
    // Еще один конструтор, только в сыновей записываем nullptr
    Node(int _cost) {
        cost = _cost;
        left = nullptr;
        right = nullptr;
        leftmost = _cost;
        rightmost = _cost;
        sorted_suffix = 1;
        sorted_prefix = 1;
        priority = rand() % 1000;
        size = 1;
        sum_segment = _cost;
        reversed = false;
    }
    
    // Конструтор для пустой вершины
    Node() {
        left = nullptr;
        right = nullptr;
        sorted_suffix = 0;
        sorted_prefix = 0;
        size = 0;
        sum_segment = 0;
        reversed = false;
    }
    
    // Деструктор
    ~Node() {
        if (left) {
            delete left;
        }
        if (right) {
            delete right;
        }
    }
};

// Класс декартова дерева по неявному ключу
class ImplicitTreap : public InterfaceImplicitKeyTree{
 private:
    Node* root;
 public:
    
    ImplicitTreap(int _cost); // Конструктор для дерева с одной вершиной
    
    ImplicitTreap(); // Конструктор дял пустого дерева
    
    ~ImplicitTreap(); // Деструтор
    
    Node* Merge(Node* left, Node* right); // Слияние двух деревьев
    
    void Split(Node* v, int x, Node* &left, Node* &right); // Сплит дерева по индексу
    
    void Insert(int _cost, int pos); // Вставка элемента на позицию
    
    void SetUp(int _cost, int pos); // Установка нужного значение в позицию
    
    Node* Remove(Node* v, int pos); // Удаление элемента с позиции
    
    int SumSegment(int a, int b); // Сумма на подотрезке
    
    Node* Reverse(Node* &v, int a, int b); // Переворот подотрезка
    
    int SizeOf(Node* v); // Возвращает размер поддерева данной вершины
    
    int SumOf(Node* v); // Возвращает сумму на отрезке, за который отвечает данная вершина
    
    int SizeOfSortedSuffix(Node* v); // Возвращает размер невозрастающего суффикса данной вершины
    
    int SizeOfSortedPrefix(Node *v); // Возвращает размер неубывающего префикса данной вершины
    
    void Push(Node* v); // Проталкивание обещаний
    
    void Recalc(Node* v); // Пересчет всех значений
    
    void RecalcSortedSuffix(Node* v); // Пересчет невозрастающего суффикса
    
    void RecalcSortedPrefix(Node* v); // Пересчет неубывающего префикса
    
    void NextPermutation(int a, int b); // Следующая перестановка на подотрезке
    
    int find(Node* v, int key);
    
    Node* findNextElement(Node* v, int key); // Возвращает указатель на вершину, в которой записан первый элемент с конца отрезка, такой, что он большe key
    Node* nextElement(Node* v, Node* successor, int key);
    
    void Print(std::vector<int> &ans);
    
    void Print_(Node* v, std::vector<int> &ans);

};



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
    root = new Node();
}

ImplicitTreap::~ImplicitTreap() {
    if (root)
        delete root;
}


/*
void ImplicitTreap::print(Node* v) {
    if (v == nullptr)
        return;
    Print(v->left);
    std::cout << v->cost << " ";
    Print(v->right);
} 
*/

void ImplicitTreap::Print(std::vector<int> &ans) {
    Print_(root, ans);
    //std::cout << "\n";
}

void ImplicitTreap::Print_(Node*v, std::vector<int> &ans) {
    if (v == nullptr)
        return;
    Push(v);
    Print_(v->left, ans);
    ans.push_back(v->cost);
    //std::cout << v->cost << " ";
    Print_(v->right, ans);
}

Node* ImplicitTreap::Merge(Node* left, Node* right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    Push(left);
    Push(left->left);
    Push(left->right);
    Push(right);
    Push(right->left);
    Push(right->right);
    // Смотрим, какой элемент станет корнем будущего дерева.
    if (left->priority > right->priority) {
        // Если приоритет левого корня оказался больше приоритета правого, то корнем нового дерева становится корень left.
        // Левым поддеревом нового дерева становится left->left.
        // А для правого дерева нового поддерева рекурсивно вызываем merge от right и left->right.
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
    Push(v->left);
    Push(v->right);
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


void ImplicitTreap::Insert(int _cost, int pos) {
    
    Node* l;
    Node* r;
    
    Split(root, pos, l, r);
    Node* m = new Node(_cost);
    root = Merge(Merge(l, m), r);
}

void ImplicitTreap::SetUp(int _cost, int pos){
    
    root = Remove(root, pos);
    Insert(_cost, pos);
}

Node* ImplicitTreap::Remove(Node* v, int pos) {
    
    Node* l;
    Node* m;
    Node* r;
    
    Split(v, pos, l, r);
    Split(r, 1, m, r);
    return Merge(l, r);
}

int ImplicitTreap::SumSegment(int a, int b) {
    
    Node* l = nullptr;
    Node* m = nullptr;
    Node* r = nullptr;
    
    Split(root, a, l, r);
    Split(r, b - a + 1, m, r);
    int result = SumOf(m);
    root = Merge(l, Merge(m, r));
    return result;
}

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

void ImplicitTreap::RecalcSortedSuffix(Node* v) {
    v->sorted_suffix = 0;
    // Если правый сын существует
    if (v->right) {
        v->sorted_suffix = v->right->sorted_suffix;
    }
    
    // Если правого сына нет или его суффикс является убывающим отрезком, а значение в вершине больше или равно значению в правом сыне
    if (v->right == nullptr ||
        (SizeOfSortedSuffix(v->right) == SizeOf(v->right) && v->cost >= v->right->leftmost)) {
        v->sorted_suffix++;
        // Если суффикс левого сына является убывающим отрезком и ...
        if (v->left && v->left->rightmost >= v->cost) {
            v->sorted_suffix += v->left->sorted_suffix;
        }
    }
}

// Cимметрично случаю пересчета суффикса
void ImplicitTreap::RecalcSortedPrefix(Node* v) {
    v->sorted_prefix = 0;
    
    if (v->left) {
        v->sorted_prefix = v->left->sorted_prefix;
    }
    if (v->left == nullptr ||
        (SizeOfSortedPrefix(v->left) == SizeOf(v->left) && v->left->rightmost <= v->cost) ) {
        v->sorted_prefix++;
        if (v->right && v->cost <= v->right->leftmost) {
            v->sorted_prefix += v->right->sorted_prefix;
        }
    }
}


void ImplicitTreap::Push(Node* v) {
    if (v == nullptr)
        return;
    
    // не установленное обещание не проталкивается
    if (!v->reversed)
        return;
    std::swap(v->leftmost, v->rightmost);
    std::swap(v->sorted_suffix, v->sorted_prefix);
    std::swap(v->left, v->right);
    //Node* temp = v->left;
    //v->left = v->right;
    //v->reversed = temp;
    if (v->left != nullptr)
        v->left->reversed ^= true;
    if (v->right != nullptr)
        v->right->reversed ^= true;
    v->reversed = false;
}

// Разворот на подотрезке
Node* ImplicitTreap::Reverse(Node* &v, int a, int b) {
    Node* l;
    Node* m;
    Node* r;
    
    Split(v, a, l, r);
    Split(r, b - a, m, r);
    m->reversed ^= true;
    Push(m);
    return Merge(Merge(l, m), r);
}



void ImplicitTreap::NextPermutation(int a, int b) {
    Node* L;
    Node* M;
    Node* R;
    // 'Выспличиваем' наш подотрезок
    Split(root, a, L, R);
    Split(R, b - a + 1, M, R);
    int suff = M->sorted_suffix;
    // Дальше на этом подотрезке делаем все необходимое, а именно
    Node* l;
    Node* r;
    // Сплитим подотрезок на убывающий суффикс и все остальное
    Split(M, M->size - suff, l, r);
    
    if (l != nullptr) {
        // Запоминаем последний элемент, который предшествовал убывающему суффиксу
        int last = l->rightmost;
        // Находим указатель на ноду, в которой записан первый элемент с конца убывающего суффикса, такой, что он больше last
        Node* tmp = findNextElement(r, last);
        // Находим индекс в массиве этого элемента
        int pos_of_next_element = find(r, tmp->cost);
        
        Node* one = nullptr;
        Node* two = nullptr;
        Node* seg1 = nullptr;
        Node* seg2 = nullptr;
        Node* seg3 = nullptr;
        /*
                l            r
         _______︿______ ____︿___
         |             ||        |
              seg1      seg2  seg3
          _____︿____   _︿_  _︿_
         [           ] [   ] [   ]
         |_|_|_|_|_|_|_|_|_|_|_|_|
                      ↑     ↑
                    one     two
         */
        
        // Выспличиваем найденные ноды и сливаем их так, как нам надо
        Split(l, l->size - 1, seg1, one);
        Split(r, pos_of_next_element - 1, seg2, seg3);
        Split(seg3, 1, two, seg3);
        l = Merge(seg1, two);
        seg2 = Merge(seg2, one);
        r = Merge(seg2, seg3);
        // Делаем пересчёт
        Recalc(one);
        Recalc(two);
        // Разворачиваем наш убывающий суффикс
        r->reversed = true;
        Push(r);
        // Сливаем все обратно
        M = Merge(l, r);
        L = Merge(L, M);
        root = Merge(L, R);
    } else
        return;
}

int ImplicitTreap::find(Node* v, int key) {
    int counter = 0;
    Node* tmp = v;
    
        if (tmp == nullptr) {
            return counter;
        }
        while (tmp->cost != key) {
            if (tmp->cost < key) {
                tmp = tmp->left;
            }
            else {
                counter += SizeOf(tmp->left) + 1;
                tmp = tmp->right;
            }
        }
        counter += SizeOf(tmp->left) + 1;
        return counter;
}

Node* ImplicitTreap::findNextElement(Node* v, int key) {
    return nextElement(v, nullptr, key);
}

Node* ImplicitTreap::nextElement(Node* v, Node* successor, int key) {
    Node* tmp = v;
    if (tmp == nullptr)
        return successor;
    while (tmp != nullptr) {
        Push(tmp);
        //Push(tmp->left);
        //Push(tmp->right);
        if (tmp->cost > key) {
            successor = tmp;
            tmp = tmp->right;
        }
        else {
            tmp = tmp->left;
        }
    }
    return successor;
}

#endif /* treap_implicit_keys_h */
