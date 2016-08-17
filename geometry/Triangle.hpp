#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include <vector>

class BaseTriangle {
public:
  BaseTriangle() { }
};

class Triangle : public BaseTriangle {
public:
  std::vector<unsigned int> pos_indices;
  std::vector<unsigned int> norm_indices;
  std::vector<unsigned int> tex_coord_indices;

  Triangle() : BaseTriangle() {}
  Triangle(unsigned int a, unsigned int b, unsigned int c) : BaseTriangle() {
    pos_indices.resize(3);
    pos_indices[0] = a;
    pos_indices[1] = b;
    pos_indices[2] = c;
  }
  ~Triangle() { }

  void addPosIndices(unsigned int a, unsigned int b, unsigned int c) {
    pos_indices.resize(3);
    pos_indices[0] = a;
    pos_indices[1] = b;
    pos_indices[2] = c;
  }
  void addNormIndices(unsigned int a, unsigned int b, unsigned int c) {
    norm_indices.resize(3);
    norm_indices[0] = a;
    norm_indices[1] = b;
    norm_indices[2] = c;
  }
  void addTexCoordIndices(unsigned int a, unsigned int b, unsigned int c) {
    tex_coord_indices.resize(3);
    tex_coord_indices[0] = a;
    tex_coord_indices[1] = b;
    tex_coord_indices[2] = c;
  }
};

#endif
