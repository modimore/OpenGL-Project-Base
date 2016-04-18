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

  virtual int numTriangles() { return triangles.size(); }
  virtual std::vector<unsigned int> getTriVertIndices() {
    std::vector<unsigned int> output(triangles.size()*3);
    for (unsigned int i = 0; i < triangles.size(); i++) {
      unsigned int start = i*3;
      // first triangle
      output[start  ] = (*triangles[i])[0]->getID();
      output[start+1] = (*triangles[i])[1]->getID();
      output[start+2] = (*triangles[i])[2]->getID();
    }
    return output;
  }
};

#endif
