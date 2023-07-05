#ifndef ADJACENCY_LIST_GRAPH_HPP_
#define ADJACENCY_LIST_GRAPH_HPP_

#include "graphs/edges/list_edge.h"
#include "graphs/graph.hpp"
#include "graphs/vertices/list_vertex.h"
#include "istream"
#include "shortest_path_algorithms.hpp"
#include <memory>
#include <vector>

class AdjacencyListGraph : public Graph
{
  public:
    std::list<Edge*> incidentEdges(int v) override;
    void addVertex(int v) override;
    explicit AdjacencyListGraph(std::istream& is);
    static std::unique_ptr<Graph> createGraph(std::istream& is);
    void print() override;
    std::list<Edge*> incidentEdges(Vertex* v) override;
    void addEdge(Vertex* v, Vertex* w, int weight) override;
    ~AdjacencyListGraph() override;
    void addVertex(Vertex* v) override;
    void removeVertex(Vertex* v) override;
    void removeEdge(Edge* e) override;
    std::array<Vertex*, 2> endVertices(Edge* e) override;
    Vertex* opposite(Vertex* v, Edge* e) override;
    bool areAdjacent(Vertex* v, Vertex* w) override;
    void replace(Vertex* v, int x) override;
    void replace(Edge* e, int x) override;
};

#endif /* ADJACENCY_LIST_GRAPH_HPP_ */
