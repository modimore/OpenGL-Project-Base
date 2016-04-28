#include "SimpleScene.hpp"
#include <iostream>

// GL-related functions ========================================================
void SimpleScene::Initialize() {
  // Bindings
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);
  glGenBuffers(1, &vertices_vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo_id);
}

void SimpleScene::Buffer() {
  std::vector<glm::vec4> vtx_positions = model->getVertexPositions();

  glBufferData(GL_ARRAY_BUFFER, vtx_positions.size()*sizeof(glm::vec4), &all_vertices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);
}

void SimpleScene::Render() {
  if (updated) {
    Buffer();
    updated = false;
  }

  glDrawArrays(GL_TRIANGLES,0,num_vertices);
}

void SimpleScene::Cleanup() {
  glDeleteBuffers(1,&vao_id);
  glDeleteBuffers(1,&vertices_vbo_id);
}
// =============================================================================
