#ifndef _CUBE_
#define _CUBE_

#include "../../base/Model.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Cube : public Model {
public:
  // Custom Cube ArgParser
  std::vector<glm::vec4> vertices;
  // Constructor
  Cube();
  ~Cube();

  void Update(const glm::mat4& m) {}
  std::vector<VertexPosColor> getVertices();
  int numVertices() { return 36; }
};

struct ColoredFace {
  int sides[4];
  glm::vec4 color;

  ColoredFace(int _sides[], glm::vec4 _color = glm::vec4(0.5f,0.5f,0.5f,1.0f))
  { for (int i = 0; i < 4; i++) sides[i] = _sides[i]; color = _color; }
};

#endif
