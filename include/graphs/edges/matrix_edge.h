#ifndef GRAPH_ALGORITHMS_MATRIX_EDGE_H
#define GRAPH_ALGORITHMS_MATRIX_EDGE_H
#include "edge.h"
#include <iostream>
class MatrixEdge :public Edge
{
  private:
    std::list<Edge*>::iterator incidentMatrix{};
  public:
    MatrixEdge(int weight, Vertex* beginVertex, Vertex* endVertex) : Edge(weight, beginVertex, endVertex) {
    }
    ~MatrixEdge() override = default;
    void setIncidentMatrix(const std::list<Edge*>::iterator& incidentMatrix)
    {
        MatrixEdge::incidentMatrix = incidentMatrix;
    }
    [[maybe_unused]] [[nodiscard]] std::list<Edge*>::iterator getIncidentMatrix() const { return incidentMatrix; }
    void marker() override { std::cout << ""; }
};

#endif // GRAPH_ALGORITHMS_MATRIX_EDGE_H
