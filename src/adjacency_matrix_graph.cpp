#include "graphs/adjacency_matrix_graph.hpp"
#include "graphs/edges/matrix_edge.h"
#include "graphs/vertices/matrix_vertex.h"

std::unique_ptr<Graph> AdjacencyMatrixGraph::createGraph(std::istream& is)
{
    return std::make_unique<AdjacencyMatrixGraph>(is);
}
AdjacencyMatrixGraph::AdjacencyMatrixGraph(std::istream& is)
{
    int numberOfVertex;
    int numberOfEdges;
    is >> numberOfVertex;
    is >> numberOfEdges;

    for(int i = 0; i < numberOfVertex; i++)
    {
        this->vertexList.push_back(new MatrixVertex(i,i));
        std::list<Vertex*>::iterator it=this->vertexList.end();
        it--;
        this->vertexList.back()->setElementOfList(it);
    }
    for(int j = 0; j < numberOfVertex; j++)
    {
        std::list<Edge*> list;
        for(int i = 0; i < numberOfVertex; i++)
        {
            list.push_back(nullptr);
        }
        matrix.push_back(list);
    }
    int a, b, c;
    MatrixVertex* begin;
    MatrixVertex* end;
    for(int j = 0; j < numberOfEdges; j++)
    {
        is >> a >> b >> c;
        for(auto& item : vertexList)
        {
            if(item->getValue() == a)
            {
                begin = dynamic_cast<MatrixVertex*>(item);
            }
            if(item->getValue() == b)
            {
                end = dynamic_cast<MatrixVertex*>(item);
            }
        }

        MatrixEdge* edg = new MatrixEdge(c, begin, end);

        auto x = matrix.begin();
        for(int i = 0; i < begin->getIndex(); i++)
            x++;
        auto y = x->begin();
        for(int i = 0; i < end->getIndex(); i++)
            y++;
        edg->setIncidentMatrix(x->insert(y, edg));
        this->edgeList.push_back(edg);
        auto it1=this->edgeList.end();
        it1--;
        edg->setEdgeList(it1);
    }
}
void AdjacencyMatrixGraph::print()
{
    std::cout << this->vertexList.size() << " " << this->edgeList.size() << std::endl;
    for(const auto& item : matrix)
    {
        for(const auto& item1 : item)
        {
            if(item1 != nullptr)
                std::cout << item1->getBeginVertex()->getValue() << " " << item1->getEndVertex()->getValue() << " "
                          << item1->getWeight() << std::endl;
        }
    }
}
std::list<Edge*> AdjacencyMatrixGraph::incidentEdges(Vertex* v)
{
    std::list<Edge*> list;
    int index = dynamic_cast<MatrixVertex*>(v)->getIndex();
    auto x = matrix.begin();
    for(int i = 0; i < index; i++)
        x++;

    for(auto& item : (*x))
        if(item != nullptr)
            list.push_back(item);
    return list;
}
void AdjacencyMatrixGraph::addEdge(Vertex* v, Vertex* w, int weight)
{
    MatrixEdge* edg = new MatrixEdge(weight, v, w);
    auto x = matrix.begin();
    for(int i = 0; i < dynamic_cast<MatrixVertex*>(v)->getIndex(); i++)
        x++;
    auto y = x->begin();
    for(int i = 0; i < dynamic_cast<MatrixVertex*>(w)->getIndex(); i++)
        y++;
    x->insert(y, edg);

    this->edgeList.push_back(edg);
    auto it=this->edgeList.end();
    it--;
    edg->setEdgeList(it);
}
void AdjacencyMatrixGraph::addVertex(int v)
{
    int index=(int)matrix.size();
    auto* vertex = new MatrixVertex(v, index);
    this->addVertex(vertex);
}
void AdjacencyMatrixGraph::addVertex(Vertex* v)
{
    this->vertexList.push_back(v);
    auto it=this->vertexList.end();
    it--;
    v->setElementOfList(it);
    for(auto& item : matrix)
    {
        item.push_back(nullptr);
    }
    std::list<Edge*> list;
    for(int i = 0; i < matrix.size(); i++)
        list.push_back(nullptr);
    this->matrix.push_back(list);
}
void AdjacencyMatrixGraph::removeVertex(Vertex* v)
{
    int index = dynamic_cast<MatrixVertex*>(v)->getIndex();
    auto x = matrix.begin();
    for(int i = 0; i < index; i++)
        x++;

    for(auto& item : (*x))
    {
        this->edgeList.remove(item);
        delete item;
    }
    matrix.erase(x);
    {
        for( auto & item : matrix)
        {
            auto y = item.begin();
            for(int i = 0; i < dynamic_cast<MatrixVertex*>(v)->getIndex(); i++)
                y++;
            item.remove(*y);
        }
    }
    this->vertexList.remove(v);
    delete v;

    for(auto& item : vertexList)
    {
        if(dynamic_cast<MatrixVertex*>(item)->getIndex()>index)
            dynamic_cast<MatrixVertex*>(item)->setIndex(dynamic_cast<MatrixVertex*>(item)->getIndex()-1);
    }
}
void AdjacencyMatrixGraph::removeEdge(Edge* e)
{
    *dynamic_cast<MatrixEdge*>(e)->getIncidentMatrix() = nullptr;
    this->edgeList.remove(e);
    delete e;
}
std::array<Vertex*, 2> AdjacencyMatrixGraph::endVertices(Edge* e)
{
    return std::array<Vertex*, 2>() = {e->getBeginVertex(), e->getEndVertex()};
}
Vertex* AdjacencyMatrixGraph::opposite(Vertex* v, Edge* e)
{
    int index = dynamic_cast<MatrixVertex*>(v)->getIndex();
    auto x = matrix.begin();
    for(int i = 0; i < index; i++)
        x++;

    for(auto& item : (*x))
        if(item == e)

            return e->getEndVertex();
}
bool AdjacencyMatrixGraph::areAdjacent(Vertex* v, Vertex* w)
{
    int index = dynamic_cast<MatrixVertex*>(v)->getIndex();
    auto x = matrix.begin();
    for(int i = 0; i < index; i++)
        x++;

    for(auto& item : (*x))
        if(item != nullptr)
            if(w == item->getEndVertex())
                return true;

    return false;
}
void AdjacencyMatrixGraph::replace(Vertex* v, int x)
{
    v->setValue(x);
}
void AdjacencyMatrixGraph::replace(Edge* e, int x)
{
    e->setWeight(x);
}
AdjacencyMatrixGraph::~AdjacencyMatrixGraph(){
    for(auto & item : matrix)
    {
        item.clear();
    }
    this->matrix.clear();

}
std::list<Edge*> AdjacencyMatrixGraph::incidentEdges(int v)
{
    std::list<Edge*> list;
    for(const auto& item : vertexList)
    {
        if(v == item->getValue())
        {
            int index = dynamic_cast<MatrixVertex*>(item)->getIndex();
            auto x = matrix.begin();
            for(int i = 0; i < index; i++)
                x++;

            for(auto& item1 : (*x))
                if(item1 != nullptr)
                    list.push_back(item1);
            return list;
        }
    }
}
