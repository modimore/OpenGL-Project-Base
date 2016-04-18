#ifndef _GEOMETRY_HPP_
#define _GEOMETRY_HPP_

#include <glm/glm.hpp>

struct VertexPosColor {
public:
  glm::vec4 position;
  glm::vec4 color;

  VertexPosColor(const glm::vec4& pos = glm::vec4(0.0,0.0,0.0,1.0),
                 const glm::vec4& col = glm::vec4(0.5,0.5,0.5,1.0))
  { position = pos; color = col; }
};

#endif // _GEOMETRY_HPP_
