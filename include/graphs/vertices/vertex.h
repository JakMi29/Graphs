#ifndef GRAPH_ALGORITHMS_VERTEX_H
#define GRAPH_ALGORITHMS_VERTEX_H
#include <list>
class Vertex
{
  protected:
    int value;
    std::list<Vertex*>::iterator elementOfList;

  public:
    explicit Vertex(int value1) : value(value1) {
    }
    virtual ~Vertex() = default;
    [[nodiscard]] int getValue() const { return value; }
    [[nodiscard]] std::list<Vertex*>::iterator getElementOfList() const { return elementOfList; }
    void setValue(int value1) { Vertex::value = value1; }
    void setElementOfList(std::list<Vertex*>::iterator elementOfList1) { Vertex::elementOfList = elementOfList1; }
    virtual void marker()=0;
};
#endif // GRAPH_ALGORITHMS_VERTEX_H
