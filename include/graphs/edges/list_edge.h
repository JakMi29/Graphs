#ifndef GRAPH_ALGORITHMS_LIST_EDGE_H
#define GRAPH_ALGORITHMS_LIST_EDGE_H
#include "edge.h"
#include "graphs/vertices/list_vertex.h"
#include <iostream>
class ListEdge :public Edge
{
    std::list<std::list<Edge*>::iterator>::iterator incidentOutList{};
    std::list<std::list<Edge*>::iterator>::iterator incidentInList{};

  public:
    ListEdge(int weight, Vertex* beginVertex, Vertex* endVertex) : Edge(weight, beginVertex, endVertex) {
    }
    ~ListEdge() override = default;

    [[nodiscard]] std::list<std::list<Edge*>::iterator>::iterator getIncidentOutList() const { return incidentOutList; }
    [[nodiscard]] std::list<std::list<Edge*>::iterator>::iterator getIncidentInList() const { return incidentInList; }
    void setIncidentOutList(std::list<std::list<Edge*>::iterator>::iterator incidentOutList1) { incidentOutList = incidentOutList1; }
    void setIncidentInList(std::list<std::list<Edge*>::iterator>::iterator incidentInList2) { incidentInList = incidentInList2; }
    void marker() override { std::cout << ""; }
};

#endif // GRAPH_ALGORITHMS_LIST_EDGE_H
