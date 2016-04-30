#include "IndexedScene.hpp"

// GL-related functions ========================================================
void IndexedScene::Initialize() {
  // Bindings
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);
  glGenBuffers(1, &vertices_vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo_id);
  glGenBuffers(1, &indices_vbo_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id);
}

void IndexedScene::Buffer() {
  // get vertex attributes
  const std::vector<glm::vec4> vtx_positions = model->getVertexPositions();

  glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(glm::vec4), &vtx_positions[0], GL_STATIC_DRAW);


  // get vertex indices for all triangles
  const std::vector<unsigned int> tri_vert_indices = model->getTriVertIndices();

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*num_triangles*sizeof(unsigned int), &tri_vert_indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), 0);
}

void IndexedScene::Render() {
  if (updated) {
    Buffer();
    updated = false;
  }

  glDrawElements(GL_TRIANGLES,num_triangles*3,GL_UNSIGNED_INT,(GLvoid*)0);
}

void IndexedScene::Cleanup() {
  glDeleteBuffers(1,&vao_id);
  glDeleteBuffers(1,&vertices_vbo_id);
  glDeleteBuffers(1,&indices_vbo_id);
}
// =============================================================================
