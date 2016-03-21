#ifndef _GLPM_UTILITY_HPP_
#define _GLPM_UTILITY_HPP_

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Simple vertex representation struct
struct VertexPosColor {
  glm::vec4 position;
  glm::vec4 color;
};

// Helper functions (mostly for GLProgramManager)
std::string ReadShaderCode(const std::string& code_path);
void CompileShader(const GLuint shader_id, const std::string& shader_code);
GLuint LoadShaders(const std::string& vs_path, const std::string& fs_path);

// Helper functions (more general)
std::string WhichGLError(GLenum& error);
int HandleGLError(const std::string& message = "", bool ignore=false);

#endif
