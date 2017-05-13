#ifndef Dfs_h
#define Dfs_h
#include "GraphTraverse.h"
#include "CGraph.h"
#include <stack>

// Depth first search
template <typename Tid, typename Tweight>
class CDfs : public CGraphTraverse<Tid, Tweight> {
    // Конструктор, на вход даем размер графа, котоырй собираемся обходить и указатель на стартовую вершину.
 public:
    CDfs(size_t size, CVertex<Tid, Tweight>* _start) {
        vect.resize(size, WHITE);
        start = _start;
    }
    
    //Покраска вершины
    void MarkVisited(CVertex<Tid, Tweight>* v) {
        size_t num = v->GetNumber();
        if (vect.at(num) == WHITE) {
            vect.at(num) = GREY;
        }
        if (vect.at(num) == GREY) {
            vect.at(num) = BLACK;
        }
    }
    
    // Depth first search
    void RunCDfs() {
        st.push(start);
        MarkVisited(start);
        while (!st.empty()) {
            CVertex<Tid, Tweight>* tmp = st.top();
            st.pop();
            adjacent_vertices = tmp->GetAdjacentVertex();
            size_t num_of_adjacent_vertices = adjacent_vertices.size();
            for (size_t i = 0; i < num_of_adjacent_vertices; i++) {
                CEdge<Tid, Tweight> edge = adjacent_vertices.front();
                adjacent_vertices.pop_front();
                CVertex<Tid, Tweight>* adj_vertex = edge.GetDest();
                if (vect.at(adj_vertex->GetNumber()) != BLACK) {
                    MarkVisited(adj_vertex);
                    st.push(adj_vertex);
                }
            }
            adjacent_vertices.clear();
        }
    }
    
    // Проверка на то, что все вершины покрашены. 
    void CheckCDfs() {
        for (size_t i = 0; i < vect.size(); i++) {
            if (vect.at(i) == BLACK)
                continue;
            else {
                printf("DFS has worked not correctly! (((((\n");
                return;
            }
        }
        //printf("DFS has worked correctly, everything seems to be okay ))))\n");
    }
    
    virtual ~CDfs() {}
    
 private:
    // Возможные цвета покраски вершины.
    enum colour {
        WHITE,
        GREY,
        BLACK
    };
    
    std::stack<CVertex<Tid, Tweight>*> st;
    std::vector<int> vect; // Вектор, в котором хранится, в какой цвет покрашена каждая вершина графа.
    std::list<CEdge<Tid, Tweight>> adjacent_vertices;
    CVertex<Tid, Tweight>* start; // Стартовая вершина.
};


#endif /* Dfs_h */
