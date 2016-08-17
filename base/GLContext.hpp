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

class ConfigParser;
class Camera;
class Scene;

/* OpenGL Context Manager
 * Manages the interface between C++ components and the OpenGL program.
 * */
class GLContext {
public:
  // References to C++ objects
  static ConfigParser* conf;
  static Camera* camera;
  static Scene* scene;
  static GLFWwindow* window;

  // GL Context Variables
  static GLuint ProgramID;
  
  static void Initialize(ConfigParser* _conf, Scene* _scene);
  static void Cleanup();
  static void Run();
  static void ErrorCallback(int error, const char* message);
};

#endif
