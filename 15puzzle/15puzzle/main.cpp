#include "AStar.h"
#include <iostream>

int main()
{
    short N;
    std::string str;
    std::cout << "Enter the size of field:\n";
    std::cin >> N;
    std::vector<short> data;
    for(int i = 0; i < N*N; i++) {
        short val;
        std::cin >> val;
        data.push_back(val);
    }
    State st(N, data);
    str = st.run(st);
    std::cout << "The sequence of moves, which will let you win:\n";
    for (int i = 0; i < str.size(); i++) {
        std::cout << str[i] << "\n";
    }
    return 0;
}