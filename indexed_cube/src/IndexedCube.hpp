#ifndef _INDEXED_CUBE_
#define _INDEXED_CUBE_

#include "../../base/IndexedModel.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class IndexedCube : public IndexedModel {
public:
  std::vector<glm::vec4> vertices;
  std::vector<unsigned int> face_indices;
  // Constructor
  IndexedCube();
  ~IndexedCube();

  void Update(const glm::mat4& m) {}
  std::vector<VertexPosColor> getVertices();
  std::vector<unsigned int> getTriVertIndices();
  int numVertices() { return 8; }
  int numTriangles() { return 12; }
};

#endif
