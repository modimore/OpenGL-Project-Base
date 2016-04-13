#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include <cassert>
#include <iostream>

#include "Edge.hpp"

class Triangle {
private:
  Edge* e;

public:
  Triangle() { e = NULL; }
  Triangle(Edge* _e) {
    e = _e;
    e->setTriangle(this);
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
