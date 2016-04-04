#ifndef _CUBE_
#define _CUBE_

#include "CubeArgParser.hpp"
#include "../../base/Model.hpp"
#include "MersenneTwister.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Cube : public Model {
public:
  // Custom Cube ArgParser
  CubeArgParser* args;
  // Constructor
  Cube(CubeArgParser* _args);
  ~Cube();

  // Driver functions
  void Create();
  void Alter(GLuint matrix_id, const glm::mat4 m);
  void Delete();

  // Point mode
  void Setup();
  void Draw();
  void Cleanup();

  GLuint vao_id;
  GLuint vbo_id;
};

#endif
