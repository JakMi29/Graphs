#ifndef GRAPH_ALGORITHMS_LIST_VERTEX_H
#define GRAPH_ALGORITHMS_LIST_VERTEX_H
#include "graphs/edges/list_edge.h"
#include "list"
#include "vector"
#include "vertex.h"
#include <iostream>

class Edge;
class ListVertex :public Vertex
{
  private:
    std::list<std::list<Edge*>::iterator> outEdgesList;
    std::list<std::list<Edge*>::iterator> inEdgesList;

  public:
    ~ListVertex() override {
        this->outEdgesList.clear();
        this->inEdgesList.clear();
    }
    explicit ListVertex(int value) : Vertex(value) {}
    std::list<std::list<Edge*>::iterator> &getIn(){return this->inEdgesList;};
    std::list<std::list<Edge*>::iterator> &getOut(){return this->outEdgesList;};
    void removeFromInEdgesList(std::list<Edge*>::iterator edge) { this->inEdgesList.remove(edge);}
    void removeFromOutEdgesList(std::list<Edge*>::iterator edge) { this->outEdgesList.remove(edge);}
    void marker() override { std::cout << ""; }
};
#endif // GRAPH_ALGORITHMS_LIST_VERTEX_H
