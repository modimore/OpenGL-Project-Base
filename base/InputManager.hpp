#ifndef _INPUT_MANAGER_HPP_
#define _INPUT_MANAGER_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLContext;

class InputManager {
public:
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

  // User input callbacks
  static void OnMouseClick(GLFWwindow* window, int button, int action, int mods);
  static void OnMouseMove(GLFWwindow* window, double x, double y);
  static void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
