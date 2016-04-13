#ifndef _HALF_EDGE_MODEL_
#define _HALF_EDGE_MODEL_

#include "../../base/IndexedModel.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Edge.hpp"
#include "Vertex.hpp"
#include "Triangle.hpp"

class HalfEdgeModel : public IndexedModel {
public:
  std::vector<Vertex*> vertices;
  std::vector<Edge*> edges;
  std::vector<Triangle*> triangles;

  // Constructor
  HalfEdgeModel();
  ~HalfEdgeModel();

  void Update(const glm::mat4& m) {}

  std::vector<VertexPosColor> getVertices();
  std::vector<unsigned int> getTriVertIndices();

  int numVertices() { return vertices.size(); }
  int numTriangles() { return triangles.size(); }

  void addTriangle(Vertex* a, Vertex* b, Vertex* c);
};

#endif