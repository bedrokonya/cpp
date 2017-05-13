#ifndef GraphTraverse_h
#define GraphTraverse_h
#include "CGraph.h"

// Абстрактный класс метода обхода графа.
template <typename Tid, typename Tweight>
class CGraphTraverse {
public:
    virtual void MarkVisited(CVertex<Tid, Tweight>* v) = 0; // Виртуальная функция покраски вершины.
    virtual ~CGraphTraverse() {};
};

#endif /* GraphTraverse_h */
