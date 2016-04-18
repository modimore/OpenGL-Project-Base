#ifndef _HALF_EDGE_MESH_
#define _HALF_EDGE_MESH_

#include "../../models/TriMeshOBJ.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Edge.hpp"
#include "HalfEdgeTriangle.hpp"

class HalfEdgeMesh : public TriMeshOBJ {
public:
  std::vector<Edge*> edges;
  std::vector<HalfEdgeTriangle*> triangles;

  // Constructor
  HalfEdgeMesh() : TriMeshOBJ() { LoadDefault(); }
  HalfEdgeMesh(const char input_fname[]) :
  TriMeshOBJ() {
    Reset();
    LoadOBJ(input_fname);
  }
  ~HalfEdgeMesh() {
    for (unsigned int i = 0; i < edges.size(); i++) {
      if (edges[i] != NULL) delete edges[i];
    }
    for (unsigned int i = 0; i < triangles.size(); i++) {
      if (triangles[i] != NULL) delete triangles[i];
    }
  }

  void LoadDefault();
  void addTriangle(Vertex* a, Vertex* b, Vertex* c);

  void Reset() {
    vertices.clear(); edges.clear(); triangles.clear();
    bbox = BoundingBox();
  }

  unsigned int numTriangles() { return triangles.size(); }
  const std::vector<Triangle*> getTriangles() const {
    std::vector<Triangle*> output = std::vector<Triangle*>(triangles.size());
    for (unsigned int i = 0; i < triangles.size(); i++) {
      output[i] = (Triangle*)triangles[i];
    }
    return output;
  }
};

#endif
