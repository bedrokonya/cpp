//
//  main.cpp
//  G_k'th_string(BOR)
//
//  Created by Ирина Дмитриева on 14.12.16.
//  Copyright © 2016 Ирина Дмитриева. All rights reserved.
//
#include <vector>
#include <iostream>

const int NUMBER_OF_SYMBOLS_IN_THE_ALPHABET = 26;

struct vertex {
    std::vector<vertex*> following_vertices;
    //std::vector<char> append;
    bool is_it_terminal;
    int number_of_terminal_vertices_in_tree;
    
    vertex() : is_it_terminal(false), number_of_terminal_vertices_in_tree(0) {
        following_vertices.resize(NUMBER_OF_SYMBOLS_IN_THE_ALPHABET);
    }
};

vertex* trie_root; // корень бора


void add_string(std::string& str) {
    vertex* current_vertex = trie_root;
    current_vertex->number_of_terminal_vertices_in_tree++;
    size_t index_of_last_symbol = str.size() - 1;
    for (size_t i = 0; i < str.size(); i++) {
        int index = str[i] - 'a';
        if (current_vertex->following_vertices[index] == nullptr) {
            current_vertex->following_vertices[index] = new vertex();
            current_vertex = current_vertex->following_vertices[index];
        } else {
            current_vertex = current_vertex->following_vertices[index];
        }
        current_vertex->number_of_terminal_vertices_in_tree++;
        
        if (i == index_of_last_symbol) {
            current_vertex->is_it_terminal = true;
        }
    }
}

void get_k_th_string(vertex* current_vertex, int k, std::string& str) {
    
    if (current_vertex->is_it_terminal) {
        k--;
    }
    if (current_vertex->is_it_terminal && k == 0) {
        return;
    }
    for (size_t i = 0; i < current_vertex->following_vertices.size(); i++) {
        if (current_vertex->following_vertices[i] == nullptr)
            continue;
        if (current_vertex->following_vertices[i]->number_of_terminal_vertices_in_tree >= k) {
            char symbol = 'a' + i;
            str += symbol;
            get_k_th_string(current_vertex->following_vertices[i], k, str);
            return;
        } else {
            k -= current_vertex->following_vertices[i]->number_of_terminal_vertices_in_tree;
        }
    }
}

int str_to_int(std::string &str) {
    int a = 0;
    for(size_t i = 0; i < str.size(); ++i) {
        a *= 10;
        a += str[i] - '0';
    }
    return a;
}



int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    trie_root = new vertex();
    int n;
    std::cin >> n;
    for(size_t t = 0; t < n; ++t) {
        std::string str;
        std::cin >> str;
        if(str[0] >= '0' && str[0] <= '9') {
            int k = str_to_int(str);
            std::string result = "";
            get_k_th_string(trie_root, k, result);
            for(int i = 0; i < result.size(); i++) {
                std::cout << result[i];
            }
            std::cout<<std::endl;
        } else {
            add_string(str);
        }
    }
    return 0;
}
