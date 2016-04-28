#ifndef _EDGE_HPP_
#define _EDGE_HPP_

class Vertex;
class HalfEdgeTriangle;

class Edge {
private:
  unsigned int start;
  unsigned int end;
  HalfEdgeTriangle* tri;

  Edge* next;
  Edge* opposite;

protected:
  unsigned int getStartVertex() const { return start; }
  unsigned int getEndVetex() const { return end; }

public:
  Edge(unsigned int _start, unsigned int _end);
  ~Edge();

  unsigned int getVertex() const { return end; }

  void setNext(Edge* e);
  Edge* getNext() const { return next; }

  void setOpposite(Edge* e);
  Edge* getOpposite() const { return opposite; }

  void setTriangle(HalfEdgeTriangle* _tri);
  HalfEdgeTriangle* getTriangle() const { return tri; }
};

#endif
