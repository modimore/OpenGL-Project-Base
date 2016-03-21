#ifndef _GL_PROGRAM_HPP_
#define _GL_PROGRAM_HPP_

// GLProgram class
// Specifies the methods which are called by the GLProgramManager
// Have your application's driver class inherit from this for compatability

#include <GL/glew.h>
#include <glm/glm.hpp>

class GLProgram {
public:
  // Constructor
  GLProgram() {}
  virtual void Setup() {}
  virtual void Update(GLuint matrix_id, const glm::mat4 m) {}
  virtual void Cleanup() {}
};

#endif
