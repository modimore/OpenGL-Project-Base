#include "IndexedScene.hpp"

// GL-related functions ========================================================
void IndexedScene::Initialize() {
  // Bindings
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);
  glGenBuffers(1, &vertices_vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo_id);
}

void IndexedScene::Buffer() {
  std::cout << "start buffer" << std::endl;
  // get vertex attributes
  size_t vertex_data_memsize = 0;
  unsigned int vertex_data_size = 0;
  std::vector<size_t> offset_arr(0);
  std::vector<unsigned int> attr_size_arr(0);

  if (model->usesVertexPositions()) {
    offset_arr.push_back(vertex_data_size);
    attr_size_arr.push_back(4);
    vertex_data_memsize += sizeof(glm::vec4);
    vertex_data_size += 4;
    std::cout << " use pos" << std::endl;
  }
  if (model->usesVertexNormals()) {
    offset_arr.push_back(vertex_data_size);
    attr_size_arr.push_back(3);
    vertex_data_memsize += sizeof(glm::vec3);
    vertex_data_size += 3;
    std::cout << " use norm" << std::endl;
  }
  if (model->usesVertexTexCoords()) {
    offset_arr.push_back(vertex_data_size);
    attr_size_arr.push_back(2);
    vertex_data_memsize += sizeof(glm::vec2);
    vertex_data_size += 2;
    std::cout << " use tex" << std::endl;
  }

  std::cout << "attrs set" << std::endl;

  std::vector<float> vertex_data_arr(vertex_data_size*num_vertices);
  std::vector<float> tri_data_single;

  std::cout << "mem allocated" << std::endl;

  unsigned int flt_i = 0;
  for (unsigned int i = 0; i < model->numTriangles(); i++) {

    for (unsigned int j = 0; j < 3; j++) {
      tri_data_single = model->getTriVertexData(i,j);
      std::cout << tri_data_single.size() << std::endl;

      for (unsigned int k = 0; k < vertex_data_size; k++) {
        vertex_data_arr[flt_i + k] = tri_data_single[k];
      }

      flt_i += vertex_data_size;
    }

  }

  std::cout << "mem assigned" << std::endl;

  glBufferData(GL_ARRAY_BUFFER, num_vertices*vertex_data_memsize, &vertex_data_arr[0], GL_STATIC_DRAW);

  std::cout << "data buffered" << std::endl;
  std::cout << num_vertices << std::endl;
  std::cout << vertex_data_size << " " << vertex_data_memsize << std::endl;
  std::cout << vertex_data_arr.size() << std::endl;

  for (unsigned int i = 0; i < attr_size_arr.size(); i++) {
    glEnableVertexAttribArray((GLuint)i);
    glVertexAttribPointer((GLuint)i, attr_size_arr[i], GL_FLOAT, GL_FALSE, vertex_data_memsize, (GLvoid*)offset_arr[i]);
  }

  std::cout << "attrs enabled" << std::endl;
}

void IndexedScene::Render() {
  if (updated) {
    Buffer();
    updated = false;
  }

  glDrawArrays(GL_TRIANGLES,0,num_triangles*3);
}

void IndexedScene::Cleanup() {
  glDeleteBuffers(1,&vao_id);
  glDeleteBuffers(1,&vertices_vbo_id);
}
// =============================================================================
