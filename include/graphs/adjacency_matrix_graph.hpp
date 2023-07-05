#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <memory>

#include "graphs/graph.hpp"


class AdjacencyMatrixGraph : public Graph
{
  public:
    void addVertex(int v) override;
  private:
    std::list<std::list<Edge*>> matrix;
  public:
    ~AdjacencyMatrixGraph() override;
    static std::unique_ptr<Graph> createGraph(std::istream& is);

  public:
    std::list<Edge*> incidentEdges(int v) override;
    explicit AdjacencyMatrixGraph(std::istream& is);
    void print() override;
    std::list<Edge*> incidentEdges(Vertex* v) override;
    void addEdge(Vertex* v, Vertex* w, int weight) override;
    void addVertex(Vertex* v) override;
    void removeVertex(Vertex* v) override;
    void removeEdge(Edge* e) override;
    std::array<Vertex*, 2> endVertices(Edge* e) override;
    Vertex* opposite(Vertex* v, Edge* e) override;
    bool areAdjacent(Vertex* v, Vertex* w) override;
    void replace(Vertex* v, int x) override;
    void replace(Edge* e, int x) override;
};

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
