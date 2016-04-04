#include "GLContext.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"

int InputManager::mouse_x = 0;
int InputManager::mouse_y = 0;
bool InputManager::left_mouse_pressed = false;
bool InputManager::center_mouse_pressed = false;
bool InputManager::right_mouse_pressed = false;
bool InputManager::shift_pressed = false;
bool InputManager::ctrl_pressed = false;
bool InputManager::alt_pressed = false;
bool InputManager::super_pressed = false;

// User Input Callbacks ========================================================
void InputManager::OnMouseClick(GLFWwindow* window, int button, int action, int mods) {
  // Action must be PRESS or RELEASE
  assert(action == GLFW_PRESS || action == GLFW_RELEASE);
  bool next_state = ( action == GLFW_PRESS ) ? true : false;

  // Correspond the action to a mouse button
  if (button == GLFW_MOUSE_BUTTON_1) { left_mouse_pressed = next_state; }
  else if (button == GLFW_MOUSE_BUTTON_2) { center_mouse_pressed = next_state; }
  else if (button == GLFW_MOUSE_BUTTON_3 ) { right_mouse_pressed = next_state; }
}

void InputManager::OnMouseMove(GLFWwindow* window, double x, double y) {
    // Select Camera
    Camera* camera = GLContext::camera;

  // Options only for a 3-button mouse, no mod keys pressed
  if ( !(shift_pressed || ctrl_pressed || alt_pressed) ) {
    if (left_mouse_pressed) { camera->rotate(mouse_x-x, mouse_y - y); }
    else if (center_mouse_pressed) { camera->truck(mouse_x-x, mouse_y-y); }
    else if (right_mouse_pressed) { camera->dolly(mouse_y - y); }
  }

  // Options that do not rely on having 3 buttons
  if (left_mouse_pressed || center_mouse_pressed || right_mouse_pressed) {
    if (shift_pressed) { camera->zoom(mouse_y-y); }
    else if (ctrl_pressed) { camera->truck(mouse_x-x, mouse_y-y); }
    else if (alt_pressed) { camera->dolly(y-mouse_y); }
  }

  mouse_x = x;
  mouse_y = y;
}

void InputManager::OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
  // check modifier keys
  if (key == GLFW_KEY_LEFT_SHIFT || key == GLFW_KEY_RIGHT_SHIFT)
    shift_pressed = (action == GLFW_PRESS || action == GLFW_REPEAT);
  else if (key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)
    ctrl_pressed = (action == GLFW_PRESS || action == GLFW_REPEAT);
  else if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT)
    alt_pressed = (action == GLFW_PRESS || action == GLFW_REPEAT);
  else if (key == GLFW_KEY_LEFT_SUPER || key == GLFW_KEY_RIGHT_SUPER)
    super_pressed = (action == GLFW_PRESS || action == GLFW_REPEAT);
  // action-linked keys
  else if (action == GLFW_PRESS && key < 255) {
    if (key == GLFW_KEY_ESCAPE || key == 'q' || key == 'Q')
      { glfwSetWindowShouldClose(window, GL_TRUE); }
    else
      { std::cout << "UNKNOWN KEYBOARD INPUT: '" << (char)key << "'" << std::endl; }
  }
}
// End User Input Callbacks ====================================================
