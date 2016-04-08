#include "Scene.hpp"
#include <iostream>

void Scene::AddModel(Model* m) {
  model = m;
  bbox.Extend(m->bbox);
  num_vertices += model->numVertices();
}

// GL-related functions ========================================================
void Scene::Initialize() {
  // Bindings
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);
  glGenBuffers(1, &vertices_vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo_id);

  std::vector<VertexPosColor> all_vertices = model->getVertices();
  std::cout << all_vertices.size();

  glBufferData(GL_ARRAY_BUFFER, all_vertices.size()*sizeof(VertexPosColor), &all_vertices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor), (GLvoid*)sizeof(glm::vec4));

  model_updated = false;
}

void Scene::Render() {
  glDrawArrays(GL_TRIANGLES,0,num_vertices);
}

void Scene::Cleanup() {
  glDeleteBuffers(1,&vao_id);
  glDeleteBuffers(1,&vertices_vbo_id);
}
// =============================================================================
