

#include <iostream>
#include "avl-tree.h"


int main() {
    AVLTree tree;
    int N;
    std::cin >> N;
    int key;
    int k;
    for (int i = 0; i < N; i++) {
        std::cin >> key >> k;
        if (key >= 0) {
            tree.head = tree.insert(tree.head, key);
        }
        else {
            key = -key;
            tree.head = tree.remove(tree.head, key);
        }
        int tmp = tree.get_Kth_element(k);
        std::cout << tmp << "\n";
     
    }
    return 0;
}