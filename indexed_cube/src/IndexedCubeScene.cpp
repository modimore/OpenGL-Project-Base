#include "IndexedCubeScene.hpp"

// GL-related functions ========================================================
void IndexedCubeScene::Initialize() {
  // Bindings
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);
  glGenBuffers(1, &vertices_vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo_id);
  glGenBuffers(1, &indices_vbo_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id);
}

void IndexedCubeScene::Render() {
  if (updated) {
    std::vector<VertexPosColor> all_vertices = model->getVertices();
    num_vertices = all_vertices.size();
    std::vector<unsigned int> all_indices = model->getTriVertIndices();
    num_triangles = all_indices.size()/3;

    glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(VertexPosColor), &all_vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*num_triangles*sizeof(unsigned int), &all_indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor), (GLvoid*)sizeof(glm::vec4));

    updated = false;
  }

  //glDrawArrays(GL_TRIANGLES,0,8);
  glDrawElements(GL_TRIANGLES,num_triangles*3,GL_UNSIGNED_INT,(GLvoid*)0);
}

void IndexedCubeScene::Cleanup() {
  glDeleteBuffers(1,&vao_id);
  glDeleteBuffers(1,&vertices_vbo_id);
}
// =============================================================================
