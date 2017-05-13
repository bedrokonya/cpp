//
//  main.cpp
//  merge_sort
//
//  Created by Ирина Дмитриева on 30.01.17.
//  Copyright © 2017 Ирина Дмитриева. All rights reserved.
//

#include <iostream>
#include <vector>
#include <climits>
#include <random>
#include <cstdlib>
using std::vector;

const int INF = INT_MAX;


void merge(std::vector<int>& A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    std::vector<int> L(n1);
    std::vector<int> R(n2);
    // initializing L and R
    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
    }
    for (int i = 0; i < n2; i++ ) {
        R[i] = A[q + i + 1];
    }
    int i = 0;
    int j = 0;
    int k = p;
    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
    
        }
        else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < L.size()) {
        A[k] = L[i];
        k++;
        i++;
    }
    while (j < R.size()) {
        A[k] = R[j];
        k++;
        j++;
    }
}

void merge_sort(std::vector<int>& A, int p, int r) {
    if (p < r) {
        int q = (p + r)/2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int minimal_scalar_product(vector<int>& v1, vector<int>& v2) {
    int vector_size = v1.size();
    merge_sort(v1, 0, vector_size - 1);
    merge_sort(v2, 0, vector_size - 1);
    int result = 0;
    
    for (int i = 0; i < vector_size; i++) {
        result += v1[i]*v2[vector_size - 1 - i];
    }
    return result;
}

int main(int argc, const char * argv[]) {
    int T;
    int n;
    std::cin >> T;
    vector<int> v1;
    std::string str;
    vector<int> v2;
    
    for (int i = 0; i < T; i++) {
        std::cin >> n;
        v1.clear();
        v2.clear();
        for (int j = 0; j < n; j++) {
            int tmp;
            std::cin >> tmp;
            v1.push_back(tmp);
        }
        for (int j = 0; j < n; j++) {
            int tmp;
            std::cin >> tmp;
            v2.push_back(tmp);
        }
        int result = minimal_scalar_product(v1, v2);
        std::cout << result << std::endl;
    }
    
    
    return 0;
}
