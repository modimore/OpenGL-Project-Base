#include "Cube.hpp"
#include "../../base/Utility.hpp"

#include <iostream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

Cube::Cube(CubeArgParser* _args)
: Model() {
  args = _args;
}

Cube::~Cube() { }

// Cube Program Driver Functions ================================================
void Cube::Create() {
  HandleGLError("Entered Cube::Setup");
  Setup();
  HandleGLError("Finished Cube::Setup");
}

void Cube::Alter(GLuint matrix_id, const glm::mat4 m) {
  HandleGLError("Entered Cube::Update");
  glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &m[0][0]);
  Draw();
  HandleGLError("Finished Cube::Update");
}

void Cube::Delete() {
  HandleGLError("Entered Cube::Cleanup");
  Cleanup();
  HandleGLError("Finished Cube::Cleanup");
}
// =============================================================================

// Point Mode Functions ========================================================
void Cube::Setup() {
  HandleGLError("Entered Cube::SetupPoints");

  // Bindings
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);
  glGenBuffers(1, &vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

  glm::vec4 v8[8];
  v8[0] = glm::vec4(-0.5,-0.5,-0.5, 1.0);
  v8[2] = glm::vec4(-0.5, 0.5,-0.5, 1.0);
  v8[6] = glm::vec4( 0.5, 0.5,-0.5, 1.0);
  v8[4] = glm::vec4( 0.5,-0.5,-0.5, 1.0);
  v8[1] = glm::vec4(-0.5,-0.5, 0.5, 1.0);
  v8[3] = glm::vec4(-0.5, 0.5, 0.5, 1.0);
  v8[7] = glm::vec4( 0.5, 0.5, 0.5, 1.0);
  v8[5] = glm::vec4( 0.5,-0.5, 0.5, 1.0);

  for (unsigned int i = 0; i < 8; i++) bbox.Extend(glm::vec3(v8[i]));

  VertexPosColor all_vertices[36] =
  {
    // back face, cyan 0 2 6 0 6 4
    VertexPosColor(v8[0],glm::vec4(0,1,1, 1.0f)),
    VertexPosColor(v8[2],glm::vec4(0,1,1, 1.0f)),
    VertexPosColor(v8[6],glm::vec4(0,1,1, 1.0f)),

    VertexPosColor(v8[0],glm::vec4(0,1,1, 1.0f)),
    VertexPosColor(v8[6],glm::vec4(0,1,1, 1.0f)),
    VertexPosColor(v8[4],glm::vec4(0,1,1, 1.0f)),

    // front face, red 1 7 3 1 5 7
    VertexPosColor(v8[1],glm::vec4(1,0,0, 1.0f)),
    VertexPosColor(v8[7],glm::vec4(1,0,0, 1.0f)),
    VertexPosColor(v8[3],glm::vec4(1,0,0, 1.0f)),

    VertexPosColor(v8[1],glm::vec4(1,0,0, 1.0f)),
    VertexPosColor(v8[5],glm::vec4(1,0,0, 1.0f)),
    VertexPosColor(v8[7],glm::vec4(1,0,0, 1.0f)),

    // bottom face, purple 0 5 1 0 4 5
    VertexPosColor(v8[0],glm::vec4(1,0,1, 1.0f)),
    VertexPosColor(v8[5],glm::vec4(1,0,1, 1.0f)),
    VertexPosColor(v8[1],glm::vec4(1,0,1, 1.0f)),

    VertexPosColor(v8[0],glm::vec4(1,0,1, 1.0f)),
    VertexPosColor(v8[4],glm::vec4(1,0,1, 1.0f)),
    VertexPosColor(v8[5],glm::vec4(1,0,1, 1.0f)),

    // top face, green 2 3 7 2 7 6
    VertexPosColor(v8[2],glm::vec4(0,1,0, 1.0f)),
    VertexPosColor(v8[3],glm::vec4(0,1,0, 1.0f)),
    VertexPosColor(v8[7],glm::vec4(0,1,0, 1.0f)),

    VertexPosColor(v8[2],glm::vec4(0,1,0, 1.0f)),
    VertexPosColor(v8[7],glm::vec4(0,1,0, 1.0f)),
    VertexPosColor(v8[6],glm::vec4(0,1,0, 1.0f)),

    // left face, yellow 0 1 3 0 3 2
    VertexPosColor(v8[0],glm::vec4(1,1,0, 1.0f)),
    VertexPosColor(v8[1],glm::vec4(1,1,0, 1.0f)),
    VertexPosColor(v8[3],glm::vec4(1,1,0, 1.0f)),

    VertexPosColor(v8[0],glm::vec4(1,1,0, 1.0f)),
    VertexPosColor(v8[3],glm::vec4(1,1,0, 1.0f)),
    VertexPosColor(v8[2],glm::vec4(1,1,0, 1.0f)),

    // right face, blue 4 7 5 4 6 7
    VertexPosColor(v8[4],glm::vec4(0,0,1, 1.0f)),
    VertexPosColor(v8[7],glm::vec4(0,0,1, 1.0f)),
    VertexPosColor(v8[5],glm::vec4(0,0,1, 1.0f)),

    VertexPosColor(v8[4],glm::vec4(0,0,1, 1.0f)),
    VertexPosColor(v8[6],glm::vec4(0,0,1, 1.0f)),
    VertexPosColor(v8[7],glm::vec4(0,0,1, 1.0f))
  };

  glBufferData(GL_ARRAY_BUFFER, sizeof(all_vertices), all_vertices, GL_STATIC_DRAW);
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor), (GLvoid*)sizeof(glm::vec4));
  HandleGLError("Finished Cube::SetupPoints");
}

void Cube::Draw() {
  HandleGLError("Entered Cube::DrawPoints");
  glDrawArrays(GL_TRIANGLES,0,36);
  HandleGLError("Finished Cube::DrawPoints");
}

void Cube::Cleanup() {
  HandleGLError("Entered Cube::CleanupPoints");
  glDeleteBuffers(1,&vao_id);
  glDeleteBuffers(1,&vbo_id);
  HandleGLError("Finished Cube::CleanupPoints");
}
// =============================================================================
