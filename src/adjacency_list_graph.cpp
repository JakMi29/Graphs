#include "graphs/adjacency_list_graph.hpp"
#include <iostream>
#include <list>
#include <algorithm>

std::unique_ptr<Graph> AdjacencyListGraph::createGraph(std::istream& is)
{
    return std::make_unique<AdjacencyListGraph>(is);
}
AdjacencyListGraph::AdjacencyListGraph(std::istream& is)
{
    int numberOfVertex;
    int numberOfEdges;
    is >> numberOfVertex;
    is >> numberOfEdges;

    for(int i = 0; i < numberOfVertex; i++)
    {
        this->vertexList.push_back(new ListVertex(i));
        std::list<Vertex*>::iterator it=this->vertexList.end();
        it--;
        this->vertexList.back()->setElementOfList(it);
    }

    int a, b, c;
    for(int i = 0; i < numberOfEdges; i++)
    {
        is >> a >> b >> c;
        ListVertex* begin;
        ListVertex* end;
        for(auto& item : vertexList)
        {
            if(item->getValue() == a)
                begin = dynamic_cast<ListVertex*>(item);
            if(item->getValue() == b)
                end = dynamic_cast<ListVertex*>(item);
        }
        ListEdge* edg = new ListEdge(c, begin, end);
        edgeList.push_back(edg);
        std::list<Edge*>::iterator it=this->edgeList.end();
        it--;
        edg->setEdgeList(it);
        end->getIn().push_back(it);
        begin->getOut().push_back(it);
        std::list<std::list<Edge*>::iterator>::iterator it1=end->getIn().end();
        it1--;
        edg->setIncidentInList(it1);
        it1=end->getOut().end();
        it1--;
        edg->setIncidentOutList(it1);
    }
}
void AdjacencyListGraph::print()
{
    std::cout<<this->vertexList.size()<<" "<<this->edgeList.size()<<std::endl;
    for(const auto & item : edgeList)
    {
        std::cout << item->getBeginVertex()->getValue() << " " << item->getEndVertex()->getValue() << " "
                  << item->getWeight() << std::endl;
    }
}

std::list<Edge*> AdjacencyListGraph::incidentEdges(Vertex* v)
{
    std::list<Edge*> list;
    for(const auto & item : dynamic_cast<ListVertex*>(v)->getOut())
    {
        list.push_back(*item);
    }
    return list;
}
void AdjacencyListGraph::addEdge(Vertex* v, Vertex* w, int weight) {
    ListEdge *edge=new ListEdge(weight,v,w);
    this->edgeList.push_back(edge);
    std::list<Edge*>::iterator it=this->edgeList.end();
    it--;
    dynamic_cast<ListVertex*>(v)->getOut().push_back(it);
    dynamic_cast<ListVertex*>(w)->getIn().push_back(it);
    std::list<std::list<Edge*>::iterator>::iterator it1=dynamic_cast<ListVertex*>(w)->getIn().end();
    it1--;
    edge->setIncidentInList(it1);
    it1=dynamic_cast<ListVertex*>(v)->getOut().end();
    it1--;
    edge->setIncidentOutList(it1);
}
void AdjacencyListGraph::addVertex(Vertex* v)
{
    this->vertexList.push_back(v);
}
void AdjacencyListGraph::removeVertex(Vertex* v) {

    int size=(int)dynamic_cast<ListVertex*>(v)->getIn().size();
    for(int i=0;i<size;i++)
    {
        Edge* edg = *dynamic_cast<ListVertex*>(v)->getIn().front();

        this->removeEdge(edg);
    }
    size=(int)dynamic_cast<ListVertex*>(v)->getOut().size();
    for(int i=0;i<size;i++)
    {
        Edge* edg = *dynamic_cast<ListVertex*>(v)->getOut().front();
        this->removeEdge(edg);
    }
    this->vertexList.remove(v);
    delete v;
}
void AdjacencyListGraph::removeEdge(Edge* e) {
    auto it=std::find(edgeList.begin(),edgeList.end(),e);
    dynamic_cast<ListVertex*>(e->getBeginVertex())->removeFromOutEdgesList(it);
    dynamic_cast<ListVertex*>(e->getEndVertex())->removeFromInEdgesList(it);
    this->edgeList.remove(e);
    delete e;
}
std::array<Vertex*, 2> AdjacencyListGraph::endVertices(Edge* e)
{
    return std::array<Vertex*, 2>() = {e->getBeginVertex(), e->getEndVertex()};
}
Vertex* AdjacencyListGraph::opposite(Vertex* v, Edge* e)
{
    if(e->getBeginVertex() == v)
        return e->getEndVertex();
    else
        return nullptr;
}
bool AdjacencyListGraph::areAdjacent(Vertex* v, Vertex* w)
{
    for(const auto& item : edgeList)
    {
        if(item->getBeginVertex() == v && item->getEndVertex() == w)
            return true;
    }
    return false;
}
void AdjacencyListGraph::replace(Vertex* v, int x) {
    v->setValue(x);
}
void AdjacencyListGraph::replace(Edge* e, int x) {
    e->setWeight(x);
}
void AdjacencyListGraph::addVertex(int v) {
    this->addVertex(new ListVertex(v));
}
std::list<Edge*> AdjacencyListGraph::incidentEdges(int v)
{
    return std::list<Edge*>();
}

AdjacencyListGraph::~AdjacencyListGraph() = default;

