#ifndef _GL_CONTEXT_HPP_
#define _GL_CONTEXT_HPP_

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>

#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ArgParser;
class Camera;
class Model;

class GLContext {
public:
  static ArgParser* args;
  static Camera* camera;
  static Model* model;
  static GLFWwindow* window;

  // GL Context Variables
  static GLuint ProgramID;

  static void Initialize(ArgParser* _args, Model* _model);
  static void Cleanup();
  static void Run();
  static void ErrorCallback(int error, const char* message);
};

#endif
