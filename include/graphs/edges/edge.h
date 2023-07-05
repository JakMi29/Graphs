//
// Created by jakub on 12.05.2023.
//

#ifndef GRAPH_ALGORITHMS_EDGE_H
#define GRAPH_ALGORITHMS_EDGE_H
#include "graphs/vertices/vertex.h"
#include <list>
class Edge
{
  protected:
    int weight{};
    Vertex* beginVertex{};
    Vertex* endVertex{};
    std::list<Edge*>::iterator edgeList{};

  public:
    Edge(int weight, Vertex* beginVertex, Vertex* endVertex)
        : weight(weight), beginVertex(beginVertex), endVertex(endVertex){
    }
    virtual ~Edge() = default;
    void setWeight(int weight1) { Edge::weight = weight1; }
    void setEdgeList(std::list<Edge*>::iterator edgeList1) { Edge::edgeList = edgeList1; }
    [[nodiscard]] int getWeight() const { return weight; }
    [[nodiscard]] Vertex* getBeginVertex() const { return beginVertex; }
    [[nodiscard]] Vertex* getEndVertex() const { return endVertex; }
    [[nodiscard]] std::list<Edge*>::iterator getEdgeList() const { return edgeList; }
    virtual void marker()=0;
};
#endif // GRAPH_ALGORITHMS_EDGE_H
