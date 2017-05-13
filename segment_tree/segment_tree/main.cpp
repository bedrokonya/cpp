//
//  main.cpp
//  segment_tree
//
//  Created by macbook on 20.12.15.
//  Copyright © 2015 macbook. All rights reserved.
//

#include <iostream>
#include "segment_tree.h"
int main() {
    int N;
    std::cin >> N;
    std::vector<int> vect(N);
    int _R;
    int _G;
    int _B;
    for (int i = 0; i < N; i++) {
        int tmp;
        std::cin >> _R >> _G >> _B;
        tmp = _R + _G + _B;
        vect.at(i) = tmp;
    }
    segmentTree tr;
    tr.buid_tree(vect);
    int K;
    std::cin >> K;
    int C, D, E, F;
    for (int i = 0; i < K; i++) {
        std::cin >> C >> D >> _R >> _G >> _B >> E >> F;
        for (int j = C; j <= D; j++) {
            int tmp = _R + _G + _B;
            tr.update(vect, j, tmp);
        }
        int segment_min = tr.rmq_up(vect, E, F);
        std::cout << segment_min << "\n";
    }
    return 0;
}
