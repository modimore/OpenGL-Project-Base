#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include <vector>

class Triangle {
private:
  std::vector<unsigned int> vtx_indices;

public:
  Triangle() { vtx_indices = std::vector<unsigned int>(3,0); }
  Triangle(unsigned int a, unsigned int b, unsigned int c) {
    vertices.resize(3);
    vertices[0] = a;
    vertices[1] = b;
    vertices[2] = c;
  }
  virtual ~Triangle() { }

  virtual unsigned int operator[](unsigned int i) const {
    return vertices[i];
  }
};

#endif
