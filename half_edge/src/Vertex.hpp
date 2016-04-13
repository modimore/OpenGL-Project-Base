#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define _default_vertex_color glm::vec4(0.5,0.5,0.5,1.0)

class Vertex {
private:
  unsigned int vid;
  glm::vec4 position;
  glm::vec4 color;

public:
  Vertex(const glm::vec4 pos=glm::vec4(0.0,0.0,0.0,1.0), const glm::vec4 col=_default_vertex_color) :
  position(pos), color(col) { }

  glm::vec4 getPosition() const { return position; }
  glm::vec4 getColor() const { return color; }

  void setID(unsigned int _vid) { vid = _vid; }
  unsigned int getID() const { return vid; }
};

#endif
