#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include <vector>

#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Geometry.hpp"
#include "BoundingBox.hpp"

class Model {
public:
  BoundingBox bbox;

  Model() { bbox = BoundingBox(); }
  virtual void Update(const glm::mat4& m) {}
  virtual int numVertices() { return 0; }
  virtual std::vector<VertexPosColor> getVertices() { return std::vector<VertexPosColor>(0); }
};

#endif
