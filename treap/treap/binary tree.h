
#ifndef binary_tree_h
#define binary_tree_h

class Node {
public:
    int key;
    int height;
    Node* left;
    Node* right;
    Node* parent;
    Node() {
        height = 0;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
    Node(int _key) : left(NULL), right(NULL), parent(NULL), height(0) {
        key = _key;
    }
    ~Node() {
        if (left) {
            delete left;
        }
        if (right) {
            delete right;
        }
    }
};

class BinaryTree {
    
public:
    Node* root;
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() {
        if (root) {
            delete root;
        }
    }
    void add(int key);
    int get_height(Node* x);
};

/* inline void Node::update_height(Node* x) {
    x->height = std::max(x->left ? x->left->height : 0, x->right ? x->right->height : 0) + 1;
} */
int BinaryTree::get_height(Node* x) {
    if (x->left == nullptr && x->right == nullptr) {
        x->height = 0;
    }
    if (x->left != nullptr && x->right == nullptr) {
        x->height = 1 + get_height(x->left);
    }
    if (x-> left == nullptr && x->right != nullptr) {
        x->height = 1 + get_height(x->right);
    }
    if (x->left != nullptr && x->right != nullptr) {
        x->height = 1 + std::max(get_height(x->left), get_height(x->right));
    }
    return x->height;
}

void BinaryTree::add(int _key) {
    Node* tmp = new Node(_key);
    Node* ptr;
    Node* ptr1 = nullptr;
    if (root == nullptr) {
        root = tmp;
        return;
    }
    ptr = root; /* идем от корня и ищем подходящее место для нашего нового элемента, оно должно быть свободно */
    {
    while (ptr != nullptr) {
        ptr1 = ptr; /* будущий родитель нового узла */
        if (_key < ptr->key) { /* по определению нашего дерева - слева значение ключа меньше родителя, */
            ptr = ptr->left;
        }
        else ptr = ptr->right;
    }
    tmp->parent = ptr1;
    if (ptr1 == nullptr) { /* дерево было пусто? */
        root = tmp;
    }
    else {
        if (_key < ptr1->key) {
            ptr1->left = tmp;
        }
        else {
            ptr1->right = tmp;
        }
    }
    return;
}

#endif /* binary_tree_h */
