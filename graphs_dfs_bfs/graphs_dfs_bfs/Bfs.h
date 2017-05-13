
#ifndef Bfs_h
#define Bfs_h
#include "GraphTraverse.h"
#include "CGraph.h"
#include <queue>
// Breadth first search
template <typename Tid, typename Tweight>
class CBfs : public CGraphTraverse<Tid, Tweight> {
public:
    // Конструктор, на вход даем размер графа, который собираемся обходить и указатель на стартовую вершину.
    CBfs(size_t size, CVertex<Tid, Tweight>* _start) {
        vect.resize(size, WHITE);
        start = _start;
    }
    
    // Покраска вершины.
    void MarkVisited(CVertex<Tid, Tweight>* v) {
        size_t num = v->GetNumber();
        vect.at(num) = BLACK;
    }
    
    // Breadth first search
    void RunCBfs() {
        q.push(start);
        MarkVisited(start);
        while (!q.empty()) {
            CVertex<Tid, Tweight>* tmp = q.front();
            q.pop();
            adjacent_vertices = tmp->GetAdjacentVertex();
            size_t num_of_adjacent_vertices = adjacent_vertices.size();
            for (size_t i = 0; i < num_of_adjacent_vertices; i++) {
                CEdge<Tid, Tweight> edge = adjacent_vertices.front();
                adjacent_vertices.pop_front();
                CVertex<Tid, Tweight>* adj_vertex = edge.GetDest();
                if (vect.at(adj_vertex->GetNumber()) != BLACK) {
                    MarkVisited(adj_vertex);
                    q.push(adj_vertex);
                }
            }
            adjacent_vertices.clear();
        }
    }
    
    // Проверка на то, что все вершины покрашены.
    void CheckCBfs() {
        for (size_t i = 0; i < vect.size(); i++) {
            if (vect.at(i) == BLACK)
                continue;
            else {
                printf("BFS has worked not correctly! (((((\n");
                return;
            }
        }
        //printf("BFS has worked correctly, everything seems to be okay ))))\n");
    }
    
    virtual ~CBfs() {}
private:
    // Возможные цвета покраски вершины.
    enum colour {
        WHITE,
        BLACK
    };
    
    std::queue<CVertex<Tid, Tweight>*> q;
    std::vector<int> vect; // Вектор, в котором хранится, в какой цвет покрашена каждая вершина графа.
    std::list<CEdge<Tid, Tweight>> adjacent_vertices;
    CVertex<Tid, Tweight>* start; // Стартовая вершина.
};

#endif /* Bfs_h */
