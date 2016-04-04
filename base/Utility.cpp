#include "Utility.hpp"

#include <iostream>
#include <fstream>
#include <vector>

// Shaders =====================================================================
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

// Compile shader code
void CompileShader(const GLuint shader_id, const std::string& shader_code) {
  GLint result = GL_FALSE;
  GLint InfoLogLength = 0;

  char const * source_ptr = shader_code.c_str();
  glShaderSource(shader_id, 1, &source_ptr, NULL);
  glCompileShader(shader_id);
  // Check compilation result
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
  glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 1) {
    std::string error_message(" ", InfoLogLength);
    glGetShaderInfoLog(shader_id,InfoLogLength,NULL,&error_message[0]);
    std::cerr << "ERROR: " << error_message << std::endl;
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
  if (InfoLogLength > 1) {
    std::string error_message(" ", InfoLogLength);
    glGetProgramInfoLog(program_id, InfoLogLength, NULL, &error_message[0]);
    std::cerr << "ERROR: " << error_message << std::endl;
  }

  glDeleteShader(vs_id);
  glDeleteShader(fs_id);

  return program_id;
}
// =============================================================================

// Error Reporting =============================================================
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

void vec3print(const glm::vec3& p) {
  std::cout << "vec3(" << p.x << "," << p.y << "," << p.z << ")" << std::endl;
}
