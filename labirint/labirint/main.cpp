
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#define INF 100500

struct vertex {
    bool visited;
    bool passable;
    std::pair<int, int> coordinates;
    int val;
};

int get_num(int decades) {
    int result = 1;
    for (int i = 0; i < decades; i++) {
        result *= 10;
    }
    return result;
}

void mark_visited(vertex& v, int sum) {
    if (v.visited) {
        if (v.val > sum)
            v.val = sum;
    }
    else {
        v.val = sum;
        v.visited = true;
    }
}

void bfs(std::vector<std::vector<vertex>>& m, int x_start, int y_start) {
    std::queue<vertex> q;
    vertex u;
    
    q.push(m[x_start][y_start]);
    m[x_start][y_start].visited = true;
    while (!q.empty()) {
        u = q.front();
        q.pop();
        if (m[u.coordinates.first - 1][u.coordinates.second].passable) {
            if(!(m[u.coordinates.first - 1][u.coordinates.second].visited)) {
                m[u.coordinates.first - 1][u.coordinates.second].visited = true;
                m[u.coordinates.first - 1][u.coordinates.second].val = u.val + 1;
                q.push(m[u.coordinates.first - 1][u.coordinates.second]);
            }
            else {
                if (u.val + 1 < m[u.coordinates.first - 1][u.coordinates.second].val)
                    m[u.coordinates.first - 1][u.coordinates.second].val = u.val + 1;
            }
        }
        if (m[u.coordinates.first + 1][u.coordinates.second].passable) {
            if(!(m[u.coordinates.first + 1][u.coordinates.second].visited)) {
                m[u.coordinates.first + 1][u.coordinates.second].visited = true;
                m[u.coordinates.first + 1][u.coordinates.second].val = u.val + 1;
                q.push(m[u.coordinates.first + 1][u.coordinates.second]);
            }
            else {
                if (u.val + 1 < m[u.coordinates.first + 1][u.coordinates.second].val)
                    m[u.coordinates.first + 1][u.coordinates.second].val = u.val + 1;
            }
        }
        if (m[u.coordinates.first][u.coordinates.second + 1].passable) {
            if(!(m[u.coordinates.first][u.coordinates.second + 1].visited)) {
                m[u.coordinates.first][u.coordinates.second + 1].visited = true;
                m[u.coordinates.first][u.coordinates.second + 1].val = u.val + 1;
                q.push(m[u.coordinates.first][u.coordinates.second + 1]);
            }
            else {
                if (u.val + 1 < m[u.coordinates.first][u.coordinates.second + 1].val)
                    m[u.coordinates.first][u.coordinates.second + 1].val = u.val + 1;
            }
        }
        if (m[u.coordinates.first][u.coordinates.second - 1].passable) {
            if(!(m[u.coordinates.first][u.coordinates.second - 1].visited)) {
                m[u.coordinates.first][u.coordinates.second - 1].visited = true;
                m[u.coordinates.first][u.coordinates.second - 1].val = u.val - 1;
                q.push(m[u.coordinates.first][u.coordinates.second - 1]);
            }
            else {
                if (u.val + 1 < m[u.coordinates.first][u.coordinates.second - 1].val)
                    m[u.coordinates.first][u.coordinates.second - 1].val = u.val - 1;
            }

        }
    }
}

int main() {
    int N;
    char c;
    std::cout << "Enter the size of the square maze: > ";
    std::cin >> N;
    c = getchar();
    
    
    std::pair<int, int> wall;
    std::vector<std::vector<vertex>> maze;
    maze.resize(N + 2);
    
    // инициализируем клетки лабиринта (все изначально проходимы)
    for (int i = 0; i < N + 2; i++) {
        maze[i].resize(N + 2);
        for (int j = 1; j < N + 1; j++) {
            maze[i][j].passable = true;
            maze[i][j].val = 0;
            maze[i][j].visited = false;
            maze[i][j].coordinates.first = i;
            maze[i][j].coordinates.second = j;
        }
        
    }
    for (int i = 0, j = 0; j < N + 2; j++) {
        maze[i][j].passable = false;
    }
    for (int i = N + 1, j = 0; j < N + 2; j++) {
        maze[i][j].passable = false;
    }
    for (int j = 0, i = 0; i < N + 2; i++) {
        maze[i][j].passable = false;
    }
    for (int j = N + 1, i = 0; i < N + 2; i++) {
        maze[i][j].passable = false;
    }
    
    for (int i = 1; i < N + 1; i++) {
        bool f = false;
        int counter = 0;
        int num = 0;
        
        c = getchar();
        while (c != '\n') {
            if (c != ' ') {
                num = (num*get_num(counter)) + atoi(&c);
                counter++;
            }
            else {
                counter = 0;
                if (f) {
                    wall.second = num;
                    f = false;
                    for (int k = wall.first; k < wall.second; k++) {
                        maze[i][k].passable = false;
                        //maze[i][k].val = INF;
                    }
                }
                else {
                    wall.first = num;
                    f = true;
                }
                num = 0;
            }
            c = getchar();
        }
        wall.second = num;
        for (int k = wall.first; k < wall.second; k++) {
            maze[i][k].passable = false;
            //maze[i][k].val = INF;
        }
    }
    
    std::pair<int, int> start;
    std::pair<int, int> finish;
    std::cout << "\nEnter the coordinates of the beginning and end points:\n";
    std::cin >> start.first >> start.second >> finish.first >> finish.second;
    
    std::vector<std::vector<vertex>>& ref = maze;
    bfs(ref, start.first, start.second);
    
    std::cout << "The shortest way is: > " << maze[finish.first][finish.second].val << "\n";
    
    for (int i = 0; i < N + 2; i++) {
        for (int j = 0; j < N + 2; j++) {
            if (maze[i][j].passable)
                std::cout /*<< maze[i][j].val */<< "_ ";
            else
                std::cout << "# ";
        }
        std::cout << "\n";
    }
    return 0;
}