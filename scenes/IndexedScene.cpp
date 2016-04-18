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
  const std::vector<Vertex*> model_vertices = model->getVertices();
  const std::vector<Triangle*> model_tris = model->getTriangles();

  std::vector<VertexPosColor> gl_vertices(model_vertices.size());
  std::vector<unsigned int> tri_vert_indices(model_tris.size()*3);

  for (unsigned int i = 0; i < model_vertices.size(); i++) {
    gl_vertices[i] = VertexPosColor(model_vertices[i]->getPosition(),
                                    model_vertices[i]->getColor());
  }

  for (unsigned int i = 0; i < model_tris.size(); i++) {
    unsigned int start = i * 3;
    tri_vert_indices[start  ] = (*model_tris[i])[0]->getID();
    tri_vert_indices[start+1] = (*model_tris[i])[1]->getID();
    tri_vert_indices[start+2] = (*model_tris[i])[2]->getID();
  }

  glBufferData(GL_ARRAY_BUFFER, num_vertices*sizeof(VertexPosColor), &gl_vertices[0], GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*num_triangles*sizeof(unsigned int), &tri_vert_indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPosColor), (GLvoid*)sizeof(glm::vec4));
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
