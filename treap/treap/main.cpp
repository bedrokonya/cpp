//
//  main.cpp
//  treap
//
//  Created by macbook on 13.12.15.
//  Copyright © 2015 macbook. All rights reserved.
//
#include "treap.h"
#include "binary tree.h"

#include <iostream>


int main() {
    Treap* trp = new Treap();
    BinaryTree bt;
    int N;
    int x, y;
    cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> x >> y;
        trp = trp->add(x,y);
        bt.add(x);
    }
    int binary_tree_height = bt.get_height(bt.root);
    int treap_height = trp->height;
    std::cout << binary_tree_height - treap_height;
    return 0;
    
}
