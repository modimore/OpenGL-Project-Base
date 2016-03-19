#include "ArgParser.hpp"
#include "Camera.hpp"
#include "GLProgramManager.hpp"

ArgParser* GLProgramManager::args = NULL;
Camera* GLProgramManager::camera = NULL;
GLFWwindow* GLProgramManager::window = NULL;
GLProgram* GLProgramManager::program = NULL;

// Inpout state variables defaults =============================================
// Mouse state
int GLProgramManager::mouse_x = 0;
int GLProgramManager::mouse_y = 0;
bool GLProgramManager::left_mouse_pressed = false;
bool GLProgramManager::center_mouse_pressed = false;
bool GLProgramManager::right_mouse_pressed = false;
// Modifier keys
bool GLProgramManager::shift_pressed = false;
bool GLProgramManager::ctrl_pressed = false;
bool GLProgramManager::alt_pressed = false;
bool GLProgramManager::super_pressed = false;
// =============================================================================

// Set up the environment for this program
void GLProgramManager::Initialize(ArgParser* _args) {
  args = _args;
  std::cout << "ProgramManager initialized..." << std::endl;
  std::cout << "Beginning execution with parameters: " << std::endl
            << "\tInput file: " << args->input_file << " in folder " << args->input_path << std::endl;

  // Camera setup
  glm::vec3 camera_position = glm::vec3(0.5,0.5,5);
  glm::vec3 point_of_interest = glm::vec3(0.5,0.5,0.5);
  glm::vec3 up = glm::vec3(0,1,0);

  // program uses an orthographic camera (add option to change later??)
  float size = 1.3;
  camera = new OrthographicCamera(camera_position,point_of_interest,up,size);
  camera->place();
  // End Camera setup

  // GLFW setup
  glfwSetErrorCallback(error_callback);

  if ( !glfwInit() ) {
    std::cerr << "ERROR: " << "Failed to intialize GLFW" << std::endl;
    exit(1);
  }

  // Ask for forward-compatible OpenGL 3.2 Context
  // Possibly add configuration options for this later
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(args->width,args->height, "OpenGL Viewer", NULL, NULL);
  if (!window) {
    std::cerr << "ERROR: " << "Failed to open GLFW window" << std::endl;
    glfwTerminate();
    exit(1);
  }
  glfwMakeContextCurrent(window);
  HandleGLError("After GLFW init");
  // End GLFW setup

  // GLEW setup
  glewExperimental = true;
  if ( glewInit() != GLEW_OK ) {
    std::cerr << "ERROR: " << "Failed to initialize GLEW" << std::endl;
    glfwTerminate();
    exit(1);
  }

  // From Cutler:
  // there seems to be a "GL_INVALID_ENUM" error in glewInit that is a
  // know issue, but can safely be ignored
  HandleGLError("After GLEW init");
  // End GLEW setup

  std::cout << "-------------------------------------------------------" << std::endl;
  std::cout << "OpenGL Version: " << (char*)glGetString(GL_VERSION) << std::endl;
  std::cout << "-------------------------------------------------------" << std::endl;

  // Set user interaction callbacks
  glfwSetCursorPosCallback(window, GLProgramManager::OnMouseMove);
  glfwSetMouseButtonCallback(window, GLProgramManager::OnMouseClick);
  glfwSetKeyCallback(window, GLProgramManager::OnKeypress);

  // Initialization finished
  HandleGLError("GLProgramManager initializatin finished");
}

// Clean up all resources for this program
void GLProgramManager::Cleanup() {
  std::cout << "Exiting Program..." << std::endl;
}

void GLProgramManager::Run() {
  // Setup GL stuff
  glClearColor(1.0f,1.0f,1.0f,0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);

  GLuint program_id = LoadShaders(args->source_path + '/' + args->vertex_shader,
                                  args->source_path + '/' + args->fragment_shader);
  // GLuint matrix_id = glGetUniformLocation(program_id, "MVP");

  while (!glfwWindowShouldClose(window)) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program_id);

    camera->place();
    //glm::mat4 projection_matrix = camera->getProjectionMatrix();
    //glm::mat4 view_matrix = camera->getViewMatrix();
    //glm::mat4 model_matrix = glm::mat4(1.0);
    //glm::mat4 MVP = projection_matrix * view_matrix * model_matrix;

    // Call GLProgram Update

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Call GLProgram Cleanup
  glDeleteProgram(program_id);

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}

// User Input Callbacks ========================================================
void GLProgramManager::OnMouseClick(GLFWwindow* window, int button, int action, int mods) {
  // Action must be PRESS or RELEASE
  assert(action == GLFW_PRESS || action == GLFW_RELEASE);
  bool next_state = ( action == GLFW_PRESS ) ? true : false;

  // Correspond the action to a mouse button
  if (button == GLFW_MOUSE_BUTTON_1) { left_mouse_pressed = next_state; }
  else if (button == GLFW_MOUSE_BUTTON_2) { center_mouse_pressed = next_state; }
  else if (button == GLFW_MOUSE_BUTTON_3 ) { right_mouse_pressed = next_state; }
}

void GLProgramManager::OnMouseMove(GLFWwindow* window, double x, double y) {
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

void GLProgramManager::OnKeypress(GLFWwindow* window, int key, int scancode, int action, int mods) {
  // check modifier keys
  shift_pressed = (GLFW_MOD_SHIFT & mods);
  ctrl_pressed = (GLFW_MOD_CONTROL & mods);
  alt_pressed = (GLFW_MOD_ALT & mods);
  super_pressed = (GLFW_MOD_SUPER & mods);
  // action-linked keys
  if (action == GLFW_PRESS && key < 255) {
    if (key == GLFW_KEY_ESCAPE || key == 'q' || key == 'Q')
      { glfwSetWindowShouldClose(GLProgramManager::window, GL_TRUE); }
    else
      { std::cout << "UNKNOWN KEYBOARD INPUT: '" << (char)key << "'" << std::endl; }
  }
}
// End User Input Callbacks ====================================================

// Error reporting callback ====================================================
void GLProgramManager::error_callback(int error, const char* message) {
  std::cerr << "ERROR: " << message << std::endl;
}

// Read Shader code from specified file
std::string ReadShaderCode(const std::string& code_path) {
  std::string code;

  std::ifstream shaderfile_stream(code_path.c_str(), std::ios::in);
  if (!shaderfile_stream.is_open()) {
    std::cerr << "ERROR: " << "cannot open " << code_path << std::endl;
    exit(0);
  }

  std::string line = "";
  while (getline(shaderfile_stream,line))
    code += "\n" + line;
  shaderfile_stream.close();

  return code;
}

// =============================================================================
// Compile shader code
void CompileShader(const GLuint shader_id, const std::string& shader_code) {
  GLint result = GL_FALSE;
  int InfoLogLength;

  char const * source_ptr = shader_code.c_str();
  glShaderSource(shader_id, 1, &source_ptr, NULL);
  glCompileShader(shader_id);
  // Check compilation result
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
  glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> error_message(InfoLogLength+1);
    glGetShaderInfoLog(shader_id,InfoLogLength,NULL,&error_message[0]);
    if (error_message.size() > 0) {
      std::string error_text;
      for (unsigned int i = 0; i < error_message.size(); i++)
        { error_text.push_back(error_message[i]); }
      std::cerr << "ERROR: " << error_text << std::endl;
    }
  }
}

// Function to create shader program from a vertex shader file and a fragment shader file
GLuint LoadShaders(const std::string& vs_path, const std::string& fs_path) {
  // Create shaders
  GLuint vs_id = glCreateShader(GL_VERTEX_SHADER);
  GLuint fs_id = glCreateShader(GL_FRAGMENT_SHADER);

  // Read in the vertex shader from the file
  std::string vs_code = ReadShaderCode(vs_path);
  std::string fs_code = ReadShaderCode(fs_path);

  std::cout << "Compiling shader: " << vs_path << std::endl;
  CompileShader(vs_id, vs_code);
  std::cout << "Compiling shader: " << fs_path << std::endl;
  CompileShader(fs_id, fs_code);

  // Link the shaders into one program
  GLint result = GL_FALSE;
  int InfoLogLength;

  GLuint program_id = glCreateProgram();
  glAttachShader(program_id, vs_id);
  glAttachShader(program_id, fs_id);
  glLinkProgram(program_id);
  // Check linking result
  glGetProgramiv(program_id, GL_LINK_STATUS, &result);
  glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> program_error_message(InfoLogLength+1);
    glGetProgramInfoLog(program_id, InfoLogLength, NULL, &program_error_message[0]);
    if (program_error_message.size() > 0) {
      std::string error_text;
      for (unsigned int i = 0; i < program_error_message.size(); i++ )
        { error_text.push_back(program_error_message[i]); }
      std::cout << "ERROR: " << error_text << std::endl;
    }
  }

  glDeleteShader(vs_id);
  glDeleteShader(fs_id);

  return program_id;
}
// =============================================================================

// Stuff that has to do with errors ============================================
std::string WhichGLError(GLenum &error) {
  switch (error) {
  case GL_NO_ERROR:
    return "NO_ERROR";
  case GL_INVALID_ENUM:
    return "GL_INVALID_ENUM";
  case GL_INVALID_VALUE:
    return "GL_INVALID_VALUE";
  case GL_INVALID_OPERATION:
    return "GL_INVALID_OPERATION";
  case GL_INVALID_FRAMEBUFFER_OPERATION:
    return "GL_INVALID_FRAMEBUFFER_OPERATION";
  case GL_OUT_OF_MEMORY:
    return "GL_OUT_OF_MEMORY";
  case GL_STACK_UNDERFLOW:
    return "GL_STACK_UNDERFLOW";
  case GL_STACK_OVERFLOW:
    return "GL_STACK_OVERFLOW";
  default:
    return "OTHER GL ERROR";
  }
}

int HandleGLError(const std::string &message, bool ignore) {
  GLenum error;
  int i = 0;
  while ( (error = glGetError()) != GL_NO_ERROR ) {
    if (!ignore) {
      if (message != "")
        std::cout << "[" << message << "] ";
      std::cout << "GL ERROR(" << i << ") " << WhichGLError(error) << std::endl;
    }
    i++;
  }
  if (i == 0) return 1;
  return 0;
}
// =============================================================================
