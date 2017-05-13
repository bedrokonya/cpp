#pragma once
#ifndef CGraph_h
#define CGraph_h

#include <vector>
#include <list>
#include <cassert>



template <typename Tid, typename Tweight>
class CVertex; // Вершина.

template <typename Tid, typename Tweight>
class CEdge; // Ребро.

template <typename Tid, typename Tweight>
class CEdge { // Ребро.
 public:
    CEdge(CVertex<Tid, Tweight>* _orig, CVertex<Tid, Tweight>* _dest, Tweight w) :
                                                    orig(_orig),  dest(_dest), weight(w) {}
    CEdge(CVertex<Tid, Tweight>* _orig, CVertex<Tid, Tweight>* _dest) :
                                                    orig(_orig),  dest(_dest), weight(1) {}

    
    virtual ~CEdge() {}
    
    CVertex<Tid, Tweight>* GetDest() const {
        return dest;
    }
    
    void SetDest(CVertex<Tid, Tweight>* _dest) {
        dest = _dest;
    }
    
    CVertex<Tid, Tweight> GetOrigin() const {
        return orig;
    }
    
    void SetOrigin(CVertex<Tid, Tweight> _orig) {
        orig = _orig;
    }
    
    Tweight GetWeight() const {
        return weight;
    }
    
    void SetWeight(Tweight w) {
        weight = w;
    }
 protected:
    CVertex<Tid, Tweight>* dest; // Вершина, в которую входит ребро.
    CVertex<Tid, Tweight>* orig; // Вершина, из котороый выходит ребро.
    Tweight weight; // Вес ребра.
};


template <typename Tid, typename Tweight>
class CVertex { // Вершина.
 public:
    CVertex(Tid _value, size_t _number) : value(_value), number(_number) {}
    
    virtual ~CVertex() {}
    
    Tid GetValue() const {
        return value;
    }
    
    void SetValue(Tid _value) {
        value = _value;
    }
    
    size_t GetNumber() const {
        return number;
    }
    
    void SetNumber(size_t _number) {
        number = _number;
    }
    
    const std::list<CEdge<Tid, Tweight>> GetAdjacentVertex() const { // Возвращает список смежности данной вершины.
        return adjacent;
    }
    
    void AddAdjacent(CEdge<Tid, Tweight> edge) { // Добавление вершины в список смежности.
        adjacent.push_back(edge);
    }
 protected:
    Tid value; // Значение, хранящееся в вершине.
    size_t number; // Номер вершины.
    std::list<CEdge<Tid, Tweight>> adjacent; // Список смежности.
};

template <typename Tid, typename Tweight>
class CGraph { // Граф.
 public:
    CGraph() :
            default_value(0), default_weight(1), size(0) {}
    CGraph(Tid _value, Tweight _weight) :
            default_value(_value), default_weight(_weight) {}
    //virtual ~CGraph();
    virtual void AddVertex(Tid _value); // Добавление вершины.
    virtual void AddVertex(CVertex<Tid, Tweight>* v);
    virtual void AddVertex();
    virtual void AddDirectedEdge(int start, int end, Tweight w); // Добавление направленного ребра.
    virtual void AddDirectedEdge(int start, int end);
    virtual Tid GetValue(size_t _number) const; // Получение значения в вершине по номеру.
    virtual CVertex<Tid, Tweight>* GetVertex(size_t _number) const; // Получение вершины по номеру.
    size_t GetSize() const; // Получение количества вершин в графе.
    void ClearAll();
    
 protected:
    std::vector<CVertex<Tid, Tweight>*> vertices; // Вектор вершин.
    size_t size; // Количество вершин в графе.
    const Tweight default_weight; // Значение веса ребра по умолчанию.
    const Tid default_value; // Значение в вершине по умолчанию.
};

template <typename Tid, typename Tweight>
void CGraph<Tid, Tweight>::AddVertex() {
    AddVertex(default_value);
    return;
}

template <typename Tid, typename Tweight>
void CGraph<Tid, Tweight>::AddVertex(Tid _value) {
    CVertex<Tid, Tweight> *newVertex = new CVertex<Tid, Tweight>(_value, 0);
    AddVertex(newVertex);
    return;
}

template <typename Tid, typename Tweight>
void CGraph<Tid, Tweight>::AddVertex(CVertex<Tid, Tweight> *v) {
    v->SetNumber(size);
    vertices.push_back(v);
    size++;
    return;
}

template <typename Tid, typename Tweight>
void CGraph<Tid, Tweight>::AddDirectedEdge(int start, int end, Tweight w) {
    CEdge<Tid, Tweight> *newEdge = new CEdge<Tid, Tweight>(GetVertex(start), GetVertex(end), w);
    CVertex<Tid, Tweight>* tmp = GetVertex(start);
    tmp->AddAdjacent(*newEdge);
 
}

template <typename Tid, typename Tweight>
void CGraph<Tid, Tweight>::AddDirectedEdge(int start, int end) {
    CEdge<Tid, Tweight> *newEdge = new CEdge<Tid, Tweight>(GetVertex(start), GetVertex(end), default_weight);
    CVertex<Tid, Tweight>* tmp = GetVertex(start);
    tmp->AddAdjacent(*newEdge);
}

template <typename Tid, typename Tweight>
Tid CGraph<Tid, Tweight>::GetValue(size_t _number) const {
    return vertices.at(_number)->GetValue();
}

template <typename Tid, typename Tweight>
CVertex<Tid, Tweight>* CGraph<Tid, Tweight>::GetVertex(size_t _number) const {
    return vertices.at(_number);
}

template <typename Tid, typename Tweight>
size_t CGraph<Tid, Tweight>::GetSize() const {
    return size;
}

template <typename Tid, typename Tweight>
void CGraph<Tid, Tweight>::ClearAll() {
    vertices.clear();
    size = 0;
}


#endif /* CGraph_h */
