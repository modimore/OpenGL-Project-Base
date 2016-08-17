#include "ConfigParser.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "../scenes/Scene.hpp"
#include "Utility.hpp"
#include "ShaderWriter.hpp"

#include "GLContext.hpp"

#include <cmath>

// Declare all static GLContext member variables
ConfigParser* GLContext::conf = NULL;
Camera* GLContext::camera = NULL;
Scene* GLContext::scene = NULL;

GLFWwindow* GLContext::window = NULL;

GLuint GLContext::ProgramID;

void GLContext::Initialize(ConfigParser* _conf, Scene* _scene) {
  conf = _conf;
  scene = _scene;

  // GLFW setup
  glfwSetErrorCallback(ErrorCallback);

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

  // This line stops execution (not compilation or linking) on Windows
  // at least when using Visual Studio 14 (2015) compiler
#ifndef _WINDOWS
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  // Create OpenGL Display Window
  window = glfwCreateWindow(conf->width,conf->height, "OpenGL Viewer", NULL, NULL);
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
  std::cout << "*** Don't worry about the GL_ENUM error, okay :) ***" << std::endl;
  HandleGLError("After GLEW init");
  // End GLEW setup

  std::cout << "-------------------------------------------------------" << std::endl;
  std::cout << "OpenGL Version: " << (char*)glGetString(GL_VERSION) << std::endl;
  std::cout << "-------------------------------------------------------" << std::endl;

  // Set user interaction callbacks
  glfwSetCursorPosCallback(window, InputManager::OnMouseMove);
  glfwSetMouseButtonCallback(window, InputManager::OnMouseClick);
  glfwSetKeyCallback(window, InputManager::OnKeyEvent);

  // Create OpenGL program from shaders
  if (conf->generate_shaders) {
    // Generate shaders based on the needs of the scene.
    struct ShaderWriterControl pr_out = scene->getVertexAttribs();
    struct ShaderWriterControl vs_out(false,pr_out.color,false,false);
    //struct ShaderWriterControl fs_out(false,true,false,false);
    ProgramID = LoadShaders( ShaderWriter::GetVertexShader(pr_out,vs_out),
                             ShaderWriter::GetFragmentShader(vs_out) );
  }
  else {
    // Load persistent shader files
    ProgramID = LoadShaders( ReadShaderCode(conf->get_vs_path()),
                             ReadShaderCode(conf->get_fs_path()) );
  }

  // Initialize the scene in preparation for camera setup
  scene->Initialize();

  // Camera setup
  glm::vec3 up = glm::vec3(0,1,0);

  double offset = scene->bbox.majorDiagLength();
  glm::vec3 point_of_interest = scene->bbox.getCenter();
  glm::vec3 camera_position = point_of_interest + glm::vec3(offset);
  // program can use either an orthographic camera or a perspective camera
  if (conf->camera == "orthographic") {
    float size = scene->bbox.majorDiagLength();
    camera = new OrthographicCamera(camera_position,point_of_interest,up,size);
  }
  else
  {
    float angle = 20.0;
    camera = new PerspectiveCamera(camera_position,point_of_interest,up,angle);
  }

  camera->place();
  // End Camera setup
  // Initialization finished
  HandleGLError("GLContext initialization finished");
}

void GLContext::Cleanup() {
  scene->Cleanup();

  glDeleteProgram(ProgramID);
  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}

void GLContext::Run() {
  // Setup GL stuff
  glClearColor(1.0f,1.0f,1.0f,0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);

  GLuint gl_MVP = glGetUniformLocation(ProgramID, "MVP");

  while (!glfwWindowShouldClose(window)) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(ProgramID);

    glm::mat4 projection_matrix = camera->getProjectionMatrix();
    glm::mat4 view_matrix = camera->getViewMatrix();
    glm::mat4 model_matrix = glm::mat4(1.0);
    glm::mat4 MVP = projection_matrix * view_matrix * model_matrix;

    glUniformMatrix4fv(gl_MVP, 1, GL_FALSE, &MVP[0][0]);

    // Update and render the scene
    scene->Update();
    scene->Render();
    glfwSwapBuffers(window);

    // Check for user interaction
    glfwPollEvents();
  }
}

// Error reporting callback ====================================================
void GLContext::ErrorCallback(int error, const char* message) {
  std::cerr << "ERROR: " << message << std::endl;
}
// =============================================================================
