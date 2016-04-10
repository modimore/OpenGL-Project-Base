#ifndef _INDEXED_CUBE_
#define _INDEXED_CUBE_

#include "CubeArgParser.hpp"
#include "../../base/IndexedModel.hpp"
#include "MersenneTwister.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class IndexedCube : public IndexedModel {
public:
  // Custom Cube ArgParser
  CubeArgParser* args;
  std::vector<glm::vec4> vertices;
  std::vector<unsigned int> face_indices;
  // Constructor
  IndexedCube(CubeArgParser* _args);
  ~IndexedCube();

  void Update(const glm::mat4& m) {}
  std::vector<VertexPosColor> getVertices();
  std::vector<unsigned int> getTriVertIndices();
  int numVertices() { return 8; }
  int numTriangles() { return 12; }
};

#endif
