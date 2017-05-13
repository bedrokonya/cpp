#pragma once

// Структура для представления узлов дерева.
struct Node {
    int key; // ключ узла
    int degree; // размер поддерева (включая саму вершину)
    int height; // высота поддерева с корнем в данном узле
    Node* left; // указатель на левое поддерево
    Node* right; // указатель на правое поддерево
    // Конструктор, создающий новый узел с заданным ключом _key.
    Node(int _key) {
        key = _key;
        left = right = nullptr;
        height = 1;
        degree = 1;
    }
};


class AVLTree {
private:
    //Node* head;
public:
    Node* head; // Корень дерева.
    AVLTree() : head(nullptr) {} // Конструктор для пустого дерева.
    // Конструктор для одноэлементного дерева с ключом _key.
    AVLTree(int _key) {
        Node* temp = new Node(_key);
        head = temp;
    }
    // Деструктор
    ~AVLTree() {
        if (head) {
            if (head->left) {
                delete head->left;
                }
            if (head->right) {
                delete head->right;
            }
        }
    }
    
    int get_height(Node* p); // Возвращает значение высоты узла (раотает и с нулевыми указателями).
    int get_balance_factor(Node* p); // Вычисляет balance factor заданного узла (и работает только с ненулевыми указателями).
    void fix_height(Node* p); // Восстанавливает корректное значение поля height заданного узла.
    int get_degree(Node* p); // Возвращает значение degree узла (работает и с нулевыми указателями).
    void fix_degree(Node* p); // Восстанавливает корректное значение поля degree заданного узла.
    Node* right_rotate(Node* p); // Правый поворот вокруг p.
    Node* left_rotate(Node* p); // Левый поворот вокруг p.
    Node* balance(Node* p); // Балансировка узла p.
    Node* insert(Node* p, int _key); // Вставка ключа _key в дерево с корнем p.
    Node* find_min(Node* p); // Поиск узла с минимальным ключом в дереве p.
    Node* remove_min(Node* p); // Удаление узла с минимальным ключом из дерева p
    Node* remove(Node* p, int _key); // Удаление ключа _key из дерева p.
    int get_Kth_element(int k); // Вычисление k-ой порядковой статистики.
};


// Возвращает значение высоты узла (раотает и с нулевыми указателями).
int AVLTree::get_height(Node* p) {
    return p ? p->height : 0;
}

// Вычисляет balance factor заданного узла (и работает только с ненулевыми указателями).
int AVLTree::get_balance_factor(Node* p) {
    return get_height(p->right) - get_height(p->left);
}

// Восстанавливает корректное значение поля height заданного узла.
void AVLTree::fix_height(Node* p)
{
    int hl = get_height(p->left);
    int hr = get_height(p->right);
    p->height = (hl>hr? hl : hr) + 1;
}

// Возвращает значение degree узла (работает и с нулевыми указателями).
int AVLTree::get_degree(Node* p) {
    return p? p->degree : 0;
}

// Восстанавливает корректное значение поля degree заданного узла.
void AVLTree::fix_degree(Node* p) {
    int hl = get_degree(p->left);
    int hr = get_degree(p->right);
    p->degree = hl + hr + 1;
}

// Правый поворот вокруг p.
Node* AVLTree::right_rotate(Node* p) {
    Node* new_tree = p->left;
    p->left = new_tree->right;
    new_tree->right = p;
    fix_height(p);
    fix_height(new_tree);
    fix_degree(p);
    fix_degree(new_tree);
    return new_tree;
}

// Левый поворот вокруг p.
Node* AVLTree::left_rotate(Node* q) {
    Node* new_tree = q->right;
    q->right = new_tree->left;
    new_tree->left = q;
    fix_height(q);
    fix_height(new_tree);
    fix_degree(q);
    fix_degree(new_tree);
    return new_tree;
}

/*   p
    / \
   /   \
  A     q
       / \
      /   \
     s     D
    / \
   /   \
  B     C
 
 */

// Балансировка узла p.
Node* AVLTree::balance(Node* p) {
    fix_height(p);
    fix_degree(p);
    // Когда высота правого поддерева узла p больше высота левого поддерева (обратный случай является симметричным).
    if (get_balance_factor(p) == 2) {
        //Большой поворот применяется при условии h(s)>h(D) и сводится в данном случае к двум простым — сначала правый поворот вокруг q и затем левый вокруг p
        if (get_balance_factor(p->right) < 0) {
            p->right = right_rotate(p->right);
        }
        // Простой поворот выполняется при условии, что высота левого поддерева q больше высоты его правого поддерева
        return left_rotate(p);
    } // Симметричный случай
    if (get_balance_factor(p) == -2) {
        if (get_balance_factor(p->left) > 0) {
            p->left = left_rotate(p->left);
        }
        return right_rotate(p);
    }
    return p;
}

// Спускаемся вниз по дереву, выбирая правое или левое направление движения в зависимости от результата сравнения ключа в текущем узле и вставляемого ключа. При возвращении из рекурсии (т.е. после того, как ключ вставлен либо в правое, либо в левое поддерево, и это дерево сбалансировано) выполняется балансировка текущего узла.
Node* AVLTree::insert(Node* p, int _key) {
    if(!p) {
        head = new Node(_key);
        return head;
    }
    if (_key < p->key) {
        p->left = insert(p->left, _key);
    }
    else {
        p->right = insert(p->right, _key);
    }
    return balance(p);
}

// По свойству двоичного дерева поиска минимальный ключ находится в конце левой ветки, начиная от корня дерева.
Node* AVLTree::find_min(Node* p) {
    return p->left? find_min(p->left) : p;
}

// По свойству АВЛ-дерева у минимального элемента справа либо подвешен единственный узел, либо там пусто. В обоих случаях надо просто вернуть указатель на правый узел и по пути назад (при возвращении из рекурсии) выполнить балансировку.
Node* AVLTree::remove_min(Node *p) {
    if (p->left == nullptr)
        return p->right;
    p->left = remove_min(p->left);
    return balance(p);
}


Node* AVLTree::remove(Node* p, int _key) {
    if (!p) return 0;
    // Находим нужный узел, выполняя те же действия, что и при вставке ключа
    if (_key < p->key) {
        p->left = remove(p->left, _key);
    }
    else if (_key > p->key) {
        p->right = remove(p->right, _key);
    }
    // Как только ключ _key найден
    else {
        // Запоминаем корни q и r левого и правого поддеревьев узла p
        Node* q = p->left;
        Node* r = p->right;
        // удаляем узел p
        delete p;
        // если правое поддерево пустое, то возвращаем указатель на левое поддерево
        if (!r) return q;
        // если правое поддерево не пустое, то находим там минимальный элемент min,
        Node* min = find_min(r);
        // потом его извлекаем оттуда, слева к min подвешиваем q, справа — то, что получилось из r.
        min->right = remove_min(r);
        min->left = q;
        // Возвращаем min после его балансировки.
        return balance(min);
    }
    // При выходе из рекурсии выполняем балансировку
    return balance(p);
}

// Находит k-ую порядковую статистику.
int AVLTree::get_Kth_element(int k) {
    // Смотрим в корень дерева и на размер его левого поддерева
    Node* cur = this->head;
    while (cur != nullptr) {
        int degreeLeft = get_degree(cur->left);
        // Если размер левого поддерева равен k, то искомый элемент мы нашли, и это — корень.
        if (degreeLeft == k) {
            return cur->key;
        }
        // Если размер левого поддерева больше k, то искомый элемент находится где-то в левом поддереве, спускаемся туда и повторяем процесс.
        cur = degreeLeft > k? cur->left : cur->right;
        // Если размер левого поддерева меньше k, то искомый элемент находится где-то в правом поддереве. Уменьшим k на число degreeLeft+1, чтобы корректно реагировать на размеры поддеревьев справа, и повторим процесс для правого поддерева.
        if (degreeLeft < k) {
            k -= degreeLeft + 1;
        }
    }
    return NULL;
}

