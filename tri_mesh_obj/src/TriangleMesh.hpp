#ifndef _HALF_EDGE_MODEL_
#define _HALF_EDGE_MODEL_

#include "../../base/IndexedModel.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Vertex.hpp"
#include "Triangle.hpp"

class TriangleMesh : public IndexedModel {
public:
  std::vector<Vertex*> vertices;
  std::vector<Triangle*> triangles;

  // Constructor
  TriangleMesh();
  TriangleMesh(const char input_fname[]);
  ~TriangleMesh();

  void LoadOBJ(const char input_fname[]);

  void Update(const glm::mat4& m) {}

  std::vector<VertexPosColor> getVertices();
  std::vector<unsigned int> getTriVertIndices();

  int numVertices() { return vertices.size(); }
  int numTriangles() { return triangles.size(); }

  void addVertex(glm::vec4 pos, glm::vec4 color=glm::vec4(0.5,0.5,0.5,1.0));
  void addTriangle(Vertex* a, Vertex* b, Vertex* c);
};

#endif