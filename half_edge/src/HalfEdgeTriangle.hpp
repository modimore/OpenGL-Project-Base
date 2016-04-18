#ifndef _HALF_EDGE_TRIANGLE_HPP_
#define _HALF_EDGE_TRIANGLE_HPP_

#include <cassert>
#include <iostream>

#include "Edge.hpp"
#include "../../geometry/Triangle.hpp"

class HalfEdgeTriangle : public Triangle {
private:
  Edge* e;

public:
  HalfEdgeTriangle() : Triangle() { e = NULL; }
  HalfEdgeTriangle(Edge* _e) : Triangle() {
    e = _e;
    e->setTriangle(this);
  }
  ~HalfEdgeTriangle() {
    if (e != NULL) delete e;
  }

  void setEdge(Edge* _e) { e = _e; }
  Edge* getEdge() const { return e; }

  Vertex* operator[](unsigned int i) const {
    assert(e != NULL);
    assert(i < 3);
    if (i == 0) return e->getVertex();
    else if (i == 1) return e->getNext()->getVertex();
    else if (i == 2) return e->getNext()->getNext()->getVertex();
    else return NULL;
  }
};

#endif
