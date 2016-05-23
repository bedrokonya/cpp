

#include "AStar.h"
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <stdlib.h>
#include <queue>

struct comp {
    bool operator() (State* x, State* y) {
        return (*y) < (*x);
    }
};

int State::h()
{
    int res = 0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(field[i][j] != 0) {
                res += (abs(i - (field[i][j]-1)/size) + abs(j - (field[i][j]-1)%size));
            }
        }
    }
    return res;
}


std::string State::run(State &st) {
    std::string result;
    result.clear();
    if(!checkSolutionExist(st)) {
        std::cout << "Not solvable" << std::endl;
        return result;
    }
    std::priority_queue<State*, std::vector<State*>, comp> queue;
    std::vector<State*> positions;
    positions.push_back(&st);
    queue.push(&st);
    std::map<State, int> f;
    st.f = st.h();
    f.insert(f.begin(), std::pair<State, int>(st, st.f));
    
    while(!queue.empty()) {
        State* current = queue.top();
        queue.pop();
        if(current->f == 0) {
            while(current != nullptr) {
                result = current->op + result;
                current = current->parent;
            }
            return result;
            
        }
        for(int i = -1; i <= 1; i++) {
            for(int j = -1; j <= 1; j++) {
                int newx = current->zeroX + i;
                int newy = current->zeroY + j;
                if(newx >= 0 && newx < st.size && newy >= 0 && newy < st.size &&
                   !(i == 0 && j == 0) && !(abs(i) == 1 && abs(j) == 1)) {
                    std::vector<std::vector<short>> new_field(current->field);
                    std::swap(new_field[current->zeroY][current->zeroX], new_field[newy][newx]);
                    State* new_st = new State(st.size, new_field);
                    int new_f =  new_st->h();
                    if(f.find(*new_st) == f.end()) {
                        f.insert(f.begin(), std::pair<State, int>(*new_st, new_f));
                        new_st->parent = current;
                        new_st->f = new_f;
                        if (i == -1)
                            new_st->op = 'L';
                        if (i == 1)
                            new_st->op = 'R';
                        if (j == 1)
                            new_st->op = 'D';
                        if (j == -1)
                            new_st->op = 'U';
                        positions.push_back(new_st);
                        queue.push(new_st);
                    }
                }
            }
        }
    }
    for(size_t i = 1; i < positions.size(); i++) {
        delete positions[i];
    }
    return result;
}

bool State::checkSolutionExist(State &st) {
    int inv = 0;
    std::vector<short> data(st.size*st.size, -1);
    for(short i = 0; i < st.size; i++) {
        for(short j = 0; j < st.size; j++) {
            data[i*st.size+j] = st.field[i][j];
        }
    }
    
    for(short i = 0; i < data.size(); i++) {
        if(data[i]) {
            for(short j = 0; j < i; j++) {
                if(data[i] < data[j]) {
                    ++inv;
                }
            }
        }
        else {
            inv += 1 + i/st.size;
        }
    }
    
    return (inv+st.size)%2 == 0;
}

