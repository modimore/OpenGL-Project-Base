#include "ArgParser.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Utility.hpp"

#include "GLContext.hpp"

ArgParser* GLContext::args = NULL;
Camera* GLContext::camera = NULL;
Model* GLContext::model = NULL;

GLFWwindow* GLContext::window = NULL;

GLuint GLContext::ProgramID;

void GLContext::Initialize(ArgParser* _args, Model* _model) {
  args = _args;
  model = _model;

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

  ProgramID = LoadShaders(args->shader_path + '/' + args->vertex_shader,
                          args->shader_path + '/' + args->fragment_shader);

  model->Create();

  // Camera setup
  glm::vec3 camera_position = glm::vec3(2.0,2.0,2.0);
  glm::vec3 point_of_interest = glm::vec3(0.5,0.5,0.5);
  glm::vec3 up = glm::vec3(0,1,0);

  model->bbox.getCenter(point_of_interest);
  camera_position = point_of_interest + glm::vec3(3.0*model->bbox.maxDim());
  std::cout << point_of_interest.x << " " << point_of_interest.y << " " << point_of_interest.z << std::endl;
  std::cout << camera_position.x << " " << camera_position.y << " " << camera_position.z << std::endl;

  // program uses an orthographic camera (add option to change later??)
  if (args->camera == "orthographic") {
    float size = 1.3;
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
  HandleGLError("GLProgramManager initialization finished");
}

void GLContext::Cleanup() {
  model->Destroy();

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

  GLuint matrix_id = glGetUniformLocation(ProgramID, "MVP");

  while (!glfwWindowShouldClose(window)) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(ProgramID);

    camera->place();
    glm::mat4 projection_matrix = camera->getProjectionMatrix();
    glm::mat4 view_matrix = camera->getViewMatrix();
    glm::mat4 model_matrix = glm::mat4(1.0);
    glm::mat4 MVP = projection_matrix * view_matrix * model_matrix;

    // Call GLProgram Update function
    model->Alter(matrix_id,MVP);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

// Error reporting callback ====================================================
void GLContext::ErrorCallback(int error, const char* message) {
  std::cerr << "ERROR: " << message << std::endl;
}
// =============================================================================
