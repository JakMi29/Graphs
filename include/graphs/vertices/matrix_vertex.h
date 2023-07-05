#ifndef GRAPH_ALGORITHMS_MATRIX_VERTEX_H
#define GRAPH_ALGORITHMS_MATRIX_VERTEX_H

#include "vertex.h"
class MatrixVertex :public Vertex
{
  private:
    int index;
  public:
    explicit MatrixVertex(int value,int index) : Vertex(value){
        this->index=index;
    }
    ~MatrixVertex() override;
    [[nodiscard]] int getIndex() const { return index; }
    void setIndex(int index1) { MatrixVertex::index = index1; }
    void marker() override {
        std::cout<<"";
    }
};
MatrixVertex::~MatrixVertex() {}
#endif // GRAPH_ALGORITHMS_MATRIX_VERTEX_H
