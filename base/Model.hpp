#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "BoundingBox.hpp"

class Model {
public:
  BoundingBox bbox;

  Model() { bbox = BoundingBox(); }
  virtual void Create() {}
  virtual void Alter(GLuint matrix_id, const glm::mat4 m) {}
  virtual void Destroy() {}
};

struct VertexPosColor {
public:
  glm::vec4 position;
  glm::vec4 color;

  VertexPosColor(const glm::vec4& pos,const glm::vec4& col)
  { position = pos; color = col; }
};

#endif
