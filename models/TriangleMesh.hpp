#ifndef _TRI_MESH_HPP_
#define _TRI_MESH_HPP_

#include "Model.hpp"

class TriangleMesh : public Model {
protected:
  std::vector<unsigned int> tri_vert_indices;

public:
  TriangleMesh() { tri_vert_indices = std::vector<unsigned int>(0); }
  ~TriangleMesh() { }
  virtual void addTriangle(unsigned int a, unsigned int b, unsigned int c) {
    tri_vert_indices.push_back(a);
    tri_vert_indices.push_back(b);
    tri_vert_indices.push_back(c);
  }

  virtual unsigned int numTriangles() { return tri_vert_indices.size()/3; }
  virtual const std::vector<unsigned int>& getTriVertIndices() const {
    return tri_vert_indices;
  }
};

#endif
