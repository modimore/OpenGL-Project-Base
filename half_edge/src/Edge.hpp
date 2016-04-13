#ifndef _EDGE_HPP_
#define _EDGE_HPP_

class Vertex;
class Triangle;

class Edge {
private:
  Vertex* start;
  Vertex* end;
  Triangle* tri;

  Edge* next;
  Edge* opposite;

protected:
  Vertex* getStartVertex() const { return start; }
  Vertex* getEndVetex() const { return end; }

public:
  Edge(Vertex* _start, Vertex* _end);
  ~Edge();

  Vertex* getVertex() const { return end; }

  void setNext(Edge* e);
  Edge* getNext() const { return next; }

  void setOpposite(Edge* e);
  Edge* getOpposite() const { return opposite; }

  void setTriangle(Triangle* _tri);
  Triangle* getTriangle() const { return tri; }

  float getLength() const;
};

#endif
