#ifndef _TRI_MESH_HPP_
#define _TRI_MESH_HPP_

#include "Model.hpp"
#include "../geometry/Triangle.hpp"

class TriangleMesh : public Model {
protected:
  std::vector<Triangle*> triangles;

public:
  TriangleMesh() { triangles = std::vector<Triangle*>(0); }
  ~TriangleMesh() {
    for (unsigned int i = 0; i < triangles.size(); i++) { delete triangles[i]; }
  }
  virtual void addTriangle(Vertex* a, Vertex* b, Vertex* c) {
    triangles.push_back(new Triangle(a,b,c));
  }

  virtual unsigned int numTriangles() { return triangles.size(); }
  virtual const std::vector<Triangle*> getTriangles() const {
    return triangles;
  }
};

#endif
