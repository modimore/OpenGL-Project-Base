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
class Scene;

class GLContext {
public:
  static ArgParser* args;
  static Camera* camera;
  static Scene* scene;
  static GLFWwindow* window;

  // GL Context Variables
  static GLuint ProgramID;

  static void Initialize(ArgParser* _args, Scene* _scene);
  static void Cleanup();
  static void Run();
  static void ErrorCallback(int error, const char* message);
};

#endif
