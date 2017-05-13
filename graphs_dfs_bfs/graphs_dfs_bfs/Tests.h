
#ifndef Tests_h
#define Tests_h
#include "CGraph.h"
#include "Dfs.h"
#include "BFS.h"
#include <vector>

template<typename Tid, typename Tweight>
class Tester {
private:
    int n; // Количество графов, которые хотим сгенерировать.
public:
    Tester(int _n) : n(_n) {} // Конструктор, которому передаем количество графов.
    
    void genGraph(CGraph<Tid, Tweight> &graph) // Генерирование связного графа
    {
        int v = rand() % 50 + 2; // Генерируем количество вершин в графе.
        int e = (v - 1) + (rand() % ((v - 1)*(v - 1)) + 1); // Генерируем количество ребер в графе
                                                            // с учетом того, что мин. количество ребер равно (v - 1), т.к. граф должен быть связным
        std::vector<int> connected; // Количество уже связанных вершин
        std::vector<int> unconnected; // Количество еще не связанных вершин
        connected.push_back(0);
        // Генерируем вершины в графе
        for(int i = 0; i < v; ++i) {
            // Добавляем вершину
            //CVertex<Tid, Tweight> *newVertex = new CVertex<Tid, Tweight>(graph.default_value, i);
            graph.AddVertex();
            if(i != 0)
                unconnected.push_back(i);
        }
        
        // Генерируем ребра в графе
        for (int i = 0; i < v - 1; ++i) {
            int from = rand() % connected.size();
            int to = rand() % unconnected.size();
            graph.AddDirectedEdge(connected[from], unconnected[to]);
            graph.AddDirectedEdge(unconnected[to], connected[from]);
            //добавить ребро(connected[from], unconnected[to])
            //добавить ребро(unconnected[to], connected[from])
            connected.push_back(unconnected[to]);
            unconnected.erase(unconnected.begin() + to);
        }
        
        for(int i = v - 1; i < e; ++i) {
            int from = rand() % v;
            int to = rand() % v;
            //добавить ребро(from, to)
            graph.AddDirectedEdge(from, to);
            //добавить ребро(to, from)
            graph.AddDirectedEdge(to, from);
        }
        connected.clear();
        unconnected.clear();
        //printf("A graph has been generated!\n");
    }
    
    // Функция тестирования dfs и bfs
    void test(CGraph<Tid, Tweight> &graph)
    {
        for(int i = 0; i < n; ++i)
        {
            genGraph(graph);
            size_t size = graph.GetSize();
            int num = rand() % size;
            CBfs<Tid, Tweight>* bfs = new CBfs<Tid, Tweight>(size, graph.GetVertex(num));
            bfs->RunCBfs();
            bfs->CheckCBfs();
            CDfs<Tid, Tweight>* dfs = new CDfs<Tid, Tweight>(size, graph.GetVertex(num));
            dfs->RunCDfs();
            dfs->CheckCDfs();
            graph.ClearAll();
        }
    }
    
    ~Tester() {}
};

#endif /* Tests_h */
