#ifndef _IFS_
#define _IFS_

#include "IFSArgParser.hpp"
#include "../../base/Model.hpp"
#include "MersenneTwister.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class IFS : public Model {
public:
  // Custom IFS ArgParser
  IFSArgParser* args;
  // Constructor
  IFS(IFSArgParser* _args);
  ~IFS();

  // Driver functions
  void Create();
  void Alter(GLuint matrix_id, const glm::mat4 m);
  void Delete();

  // Point mode
  void SetupPoints();
  void DrawPoints();
  void CleanupPoints();

  // Member Variables
  unsigned int num_transforms;
  glm::mat4* transforms;
  float* transform_probabilities;
  MTRand rng;
  GLuint vao_id;
  GLuint vbo_id;
};

struct VertexPosColor {
  glm::vec4 position;
  glm::vec4 color;
};

#endif
