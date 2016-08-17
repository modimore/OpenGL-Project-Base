 #ifndef _HALF_EDGE_TRIANGLE_HPP_
#define _HALF_EDGE_TRIANGLE_HPP_

#include <cassert>
#include <iostream>

#include "Edge.hpp"
#include "../../geometry/Triangle.hpp"

class HalfEdgeTriangle : public BaseTriangle {
private:
  Edge* e;

  Edge* edgeAt(unsigned int i) const {
    Edge* answer = e;
    while(i > 0) {
      answer = answer->getNext();
      i--;
    }
    return answer;
  }

public:
  HalfEdgeTriangle() : BaseTriangle() { e = NULL; }
  HalfEdgeTriangle(Edge* _e) : BaseTriangle() {
    e = _e;
    e->setTriangle(this);
  }
  ~HalfEdgeTriangle() {
    if (e != NULL) delete e;
  }

  void setEdge(Edge* _e) { e = _e; }
  Edge* getEdge() const { return e; }

  unsigned int operator[](unsigned int i) const {
    assert(e != NULL);
    assert(i < 3);
    return this->edgeAt(i)->getVertex();
  }
};

#endif
