#include "Edge.hpp"
#include "../../geometry/Vertex.hpp"
#include "HalfEdgeTriangle.hpp"

#include <cassert>

// Constructor and Desctructor ===========================
Edge::Edge(Vertex* _start, Vertex* _end) {
  start = _start;
  end = _end;
  tri = NULL;
  next = NULL;
  opposite = NULL;
}

Edge::~Edge() {
  if (next != NULL && next->next != NULL)
    next->next->next = NULL;
  if (opposite != NULL)
    opposite->opposite = NULL;
}
// =======================================================

// Set opposite and next =================================
void Edge::setNext(Edge* e) {
  assert(next == NULL && e != NULL);
  assert(e->start == this->end);
  next = e;
}

void Edge::setOpposite(Edge* e) {
  assert(e->start == this->end && e->end == this->start);
  opposite = e;
  e->opposite = this;
}
// =======================================================

// Set triangle ==========================================
void Edge::setTriangle(HalfEdgeTriangle* _tri) {
  tri = _tri;
  if (next->tri != _tri) next->setTriangle(_tri);
}
// =======================================================

// Length of edge ========================================
float Edge::getLength() const {
  return glm::length(end->getPosition()-start->getPosition());
}
// =======================================================
