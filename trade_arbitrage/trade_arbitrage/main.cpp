
#include <iostream>
#include <vector>
#include <cassert>
//std::vector<std::vector<double>> adj_matrix;

void floyd(int n, std::vector<std::vector<double>>& matrix) {
    assert(matrix.size() == n);
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][k] != -1 && matrix[k][j] != -1) {
                    //if (matrix[i][j] < matrix[i][k]*matrix[k][j])
                    matrix[i][j] = std::max(matrix[i][j], matrix[i][k]*matrix[k][j]);
                }
            }
        }
    }
}

int main() {
    int N;
    double val;
    std::cout << "Enter the number of currency: \n";
    std::cin >> N;
    std::vector<std::vector<double>> adj_matrix;
    adj_matrix.resize(N);
    for (int i = 0; i < N; i++) {
        adj_matrix[i].resize(N);
        for (int j = 0; j < N; j++) {
            adj_matrix[i].resize(N);
            if (i == j) {
                adj_matrix[i].at(j) = 1.0;
            }
            else {
                std::cin >> val;
                adj_matrix[i].at(j) = val;
            }
        }
    }
    
    std::cout << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << adj_matrix[i][j];
            std::cout << " ";
        }
        std::cout << "\n";
    }
    std::vector<std::vector<double>>& ref = adj_matrix;
    floyd(N, ref);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << adj_matrix[i][j];
            std::cout << " ";
        }
        std::cout << "\n";
    }
    
    for (int i = 0; i < N; i++) {
        if (adj_matrix[i][i] > 1) {
            std::cout << "YES\n";
            return 0;
        }
    }
    std::cout << "NO\n";
    return 0;
}