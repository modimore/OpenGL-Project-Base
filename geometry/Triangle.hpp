#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include <vector>

class Triangle {
private:
  std::vector<Vertex*> vertices;

public:
  Triangle() { vertices = std::vector<Vertex*>(3,NULL); }
  Triangle(Vertex* a, Vertex* b, Vertex* c) {
    vertices.resize(3);
    vertices[0] = a;
    vertices[1] = b;
    vertices[2] = c;
  }
  virtual ~Triangle() {
    delete vertices[0];
    delete vertices[1];
    delete vertices[2];
  }

  virtual Vertex* operator[](unsigned int i) const {
    if (i < 3 && i >=0) return vertices[i];
    else return NULL;
  }
};

#endif
