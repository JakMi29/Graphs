#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include "graphs/edges/list_edge.h"
#include "graphs/vertices/list_vertex.h"
#include "istream"
#include "shortest_path_algorithms.hpp"
#include <list>
#include <memory>
#include <vector>
class Graph
{
  protected:
    std::list<Vertex*> vertexList;
    std::list<Edge*> edgeList;

  public:
    [[nodiscard]] const std::list<Vertex*>& getVertexList() const { return vertexList; }
    [[nodiscard]] const std::list<Edge*>& getEdgeList() const { return edgeList; }
    virtual void print() = 0;
    virtual ~Graph() {
        for(auto& item : edgeList)
        {
            delete item;
        }
        for(auto& item : vertexList)
        {
            delete item;
        }
        this->vertexList.clear();
        this->edgeList.clear();
    }
    // Metody iterujące
    [[nodiscard]] std::list<Vertex*> vertices() const { return this->getVertexList(); }
    [[nodiscard]] std::list<Edge*> edges() const { return this->getEdgeList(); }
    virtual std::list<Edge*> incidentEdges(Vertex* v) = 0;
    virtual std::list<Edge*> incidentEdges(int v) = 0;
    // Metody uakltualniające
    virtual void addEdge(Vertex* v, Vertex* w, int weight) = 0;
    virtual void addVertex(Vertex* v) = 0;
    virtual void addVertex(int v) = 0;
    virtual void removeVertex(Vertex* v) = 0;
    virtual void removeEdge(Edge* e) = 0;
    // Metody dostępu
    virtual std::array<Vertex*, 2> endVertices(Edge* e) = 0;
    virtual Vertex* opposite(Vertex* v, Edge* e) = 0;
    virtual bool areAdjacent(Vertex* v, Vertex* w) = 0;
    virtual void replace(Vertex* v, int x) = 0;
    virtual void replace(Edge* e, int x) = 0;

    // interfejs użytkownika
    void userRequiredVertices()
    {
        if(this->vertexList.empty())
            std::cout << "This graph does not have any vertices" << std::endl;
        else
        {
            std::cout << "Graph has below vertices: " << std::endl;
            for(const auto& item : this->vertices())
            {
                std::cout << item->getValue() << " ";
            }
            std::cout << std::endl;
        }
    }
    void userRequiredEdges()
    {
        if(this->edgeList.empty())
            std::cout << "This graph does not have any vertices" << std::endl;
        else
        {
            std::cout << "Graph has below edges: " << std::endl;
            for(const auto& item : this->edges())
            {
                std::cout << item->getBeginVertex()->getValue() << " " << item->getEndVertex()->getValue() << " "
                          << item->getWeight() << std::endl;
            }
            std::cout << std::endl;
        }
    }
    void userRequiredVertexIncidentList(int v)
    {
        for(const auto& item : vertexList)
        {
            if(item->getValue() == v)
            {
                std::cout << "edges coming out from the vertex: " << v << std::endl;
                for(const auto& getInEdgesList : incidentEdges(item))
                {
                    std::cout << getInEdgesList->getBeginVertex()->getValue() << " "
                              << getInEdgesList->getEndVertex()->getValue() << " " << getInEdgesList->getWeight()
                              << std::endl;
                }

                return;
            }
        }
        std::cout << "This graph does not have vertex with value v: " << v << std::endl;
    }
    void userRequiredToAddEdge(int begin, int end, int weight)
    {
        if(begin == end)
        {
            std::cout << "Incorrect input data(can not connect the same vertices)" << std::endl;
            return;
        }
        Vertex* beginVertex = nullptr;
        Vertex* endVertex = nullptr;
        for(const auto& item : vertexList)
        {
            if(item->getValue() == begin)
                beginVertex = item;
            if(item->getValue() == end)
                endVertex = item;
        }
        if(beginVertex == nullptr || endVertex == nullptr)
        {
            std::cout << "Incorrect input data(one or both of the specified vertices do not exist in this graph)"
                      << std::endl;
            return;
        }

        for(const auto& item : this->edgeList)
        {
            if(item->getBeginVertex() == beginVertex && item->getEndVertex() == endVertex)
            {
                std::cout << "Cannot create an edge because the graph already contains one edge pointing between these "
                             "vertices"
                          << std::endl;
                return;
            }
        }
        std::cout << "the edge was created correctly: " << beginVertex->getValue() << " " << endVertex->getValue()
                  << " " << weight << std::endl;
        this->addEdge(beginVertex, endVertex, weight);
    }
    void userRequiredToAddVertex(int v)
    {
        for(const auto& item : vertexList)
        {
            if(item->getValue() == v)
            {
                std::cout << "Vertex: " << v << " already exist in this graph" << std::endl;
                return;
            }
        }
        this->addVertex(v);
        std::cout << "vertex: " << v << " was created successful" << std::endl;
    }
    void userRequiredToRemoveVertex(int v)
    {
        for(auto& item : vertexList)
        {
            if(item->getValue() == v)
            {
                this->removeVertex(item);
                std::cout << "Vertex: " << v << "deleted successful" << std::endl;
                return;
            }
        }
        std::cout << "Graph does not have vertex: " << v << std::endl;
    }
    void userRequiredToRemoveEdge(int begin, int end, int weight)
    {
        for(auto& item : edgeList)
        {
            if(item->getBeginVertex()->getValue() == begin && item->getEndVertex()->getValue() == end &&
               item->getWeight() == weight)
            {
                this->removeEdge(item);
                std::cout << "successfully remove edge: " << begin << " " << end << " " << weight << std::endl;
                return;
            }
        }
        std::cout << "Graph does not have edge: " << begin << " "
                  << " " << weight << std::endl;
    }
    void userRequiredToEditVertex(int v, int newValue)
    {
        for(const auto& item : vertexList)
        {
            if(item->getValue() == newValue)
            {
                std::cout << "Vertex change unsuccessful, this graph already has vertex: " << newValue << std::endl;
                return;
            }
            if(item->getValue() == v)
            {
                this->replace(item, newValue);
                std::cout << "Vertex: " << v << " was change to: " << newValue << std::endl;
                return;
            }
        }
        std::cout << "Graph does not have vertex: " << v << std::endl;
    }
    void userRequiredToEditEdge(int begin, int end, int weight, int newWeight)
    {
        for(const auto& item : edgeList)
        {
            if(item->getBeginVertex()->getValue() == begin && item->getEndVertex()->getValue() == end &&
               item->getWeight() == weight)
            {
                this->replace(item, newWeight);
                std::cout << "successfully edit edge: " << begin << " " << end << " " << weight << " to " << begin
                          << " " << end << " " << newWeight << std::endl;
                return;
            }
        }
        std::cout << "Graph does not have edge: " << begin << " "
                  << " " << weight << std::endl;
    }
    void userRequiredToEndVertices(int begin, int end, int weight)
    {
        for(const auto& item : edgeList)
        {
            if(item->getBeginVertex()->getValue() == begin && item->getEndVertex()->getValue() == end &&
               item->getWeight() == weight)
            {
                std::array<Vertex*, 2> array = this->endVertices(item);
                std::cout << "Begin vertex: " << array[0]->getValue() << ", end Vertex: " << array[1]->getValue()
                          << std::endl;
                return;
            }
        }
        std::cout << "Graph does not have edge: " << begin << " "
                  << " " << weight << std::endl;
    }
    void userRequiredToAreAdjacent(int v, int w)
    {
        Vertex* beginVertex = nullptr;
        Vertex* endVertex = nullptr;
        for(const auto& item : vertexList)
        {
            if(item->getValue() == v)
                beginVertex = item;
            if(item->getValue() == w)
                endVertex = item;
        }
        if(beginVertex == nullptr || endVertex == nullptr)
        {
            std::cout << "Incorrect input data, graph does not have one or both vertices" << std::endl;
            return;
        }
        if(this->areAdjacent(beginVertex, endVertex))
        {
            std::cout << "Vertices: " << v << ", " << w << " are adjacent" << std::endl;
            return;
        }
        std::cout << "Vertices: " << v << ", " << w << " are not adjacent" << std::endl;
    }
    void userRequiredToOpposite(int v, int begin, int end, int weight)
    {
        if(v == begin)
        {
            Vertex* beginVertex = nullptr;
            Vertex* endVertex = nullptr;
            for(const auto& item : vertexList)
            {
                if(item->getValue() == begin)
                    beginVertex = item;
                if(item->getValue() == end)
                    endVertex = item;
            }
            for(const auto& item : edgeList)
            {
                if(item->getBeginVertex()->getValue() == begin && item->getEndVertex()->getValue()==end &&
                   item->getWeight() == weight)
                {
                    std::cout<<"Opposite to vertex: "<<begin<<" relative to edge: "<<begin<<" "<<end<<" "<<weight<<" is vertex: " <<this->opposite(beginVertex,item)->getValue()<<std::endl;
                    return;
                }
            }
        }
        std::cout << "Incorrect input data there is no vertex or edge or edge is not coming out from vertex"
                  << std::endl;
    }

};

#endif /* GRAPH_HPP_ */
