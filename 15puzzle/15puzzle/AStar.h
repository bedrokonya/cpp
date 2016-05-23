#ifndef AStar_h
#define AStar_h
#include <vector>

class State {
public:
    State(short N, std::vector<short> data):
    size(N), field(N, std::vector<short>(N, -1)), f(0),
    parent(nullptr)
    {
        for(short i = 0; i < N*N; i++) {
            field[i/size][i%size] = data[i];
            if(data[i] == 0) {
                zeroX = i%size;
                zeroY = i/size;
            }
        }
    }
    State(short N, std::vector<std::vector<short>> data):
    size(N), f(0), parent(nullptr), field(data) {
        for(short i = 0; i < N; i++) {
            for(short j = 0; j < N; j++) {
                if(field[i][j] == 0) {
                    zeroY = i;
                    zeroX = j;
                }
            }
        }
    }
    bool operator<(const State& another) const{
        if(this->f < another.f)
            return true;
        return this->field < another.field;
    }
    std::string run(State& pos);
private:
    int f;
    short zeroX;
    short zeroY;
    short size;
    char op;
    State* parent;
    std::vector<std::vector<short>> field;
    int h();
    static bool checkSolutionExist(State& pos);
};



#endif /* AStar_h */
