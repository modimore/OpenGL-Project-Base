#ifndef _GL_PROGRAM_MANAGER_HPP_
#define _GL_PROGRAM_MANAGER_HPP_

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
class CameraManager;
class GLProgram;

class GLProgramManager {
public:
  static ArgParser* args;
  static Camera* camera;
  static GLFWwindow* window;
  static GLProgram* program;

  // User interaction state
  // Mouse position
  static int mouse_x;
  static int mouse_y;
  // Mouse button
  static bool left_mouse_pressed;
  static bool center_mouse_pressed;
  static bool right_mouse_pressed;
  // Modifier keys
  static bool shift_pressed;
  static bool ctrl_pressed;
  static bool alt_pressed;
  static bool super_pressed;

  // Setup and Cleanup
  static void Initialize(ArgParser* _args, GLProgram* _program);
  static void Cleanup();

  // Main Driver Function
  static void Run();

  // User-input callbacks
  static void OnMouseClick(GLFWwindow* window, int button, int action, int mods);
  static void OnMouseMove(GLFWwindow* window, double x, double y);
  static void OnKeypress(GLFWwindow* window, int key, int scancode, int action, int mods);

  // Error reporting callback
  static void error_callback(int error, const char* message);
};

#endif
