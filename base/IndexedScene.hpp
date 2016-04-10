#ifndef _INDEXED_SCENE_HPP_
#define _INDEXED_SCENE_HPP_

#include "Scene.hpp"
#include "IndexedModel.hpp"

class IndexedScene : public Scene {
public:
  IndexedModel* model;
  unsigned int num_vertices = 0;
  unsigned int num_triangles = 0;

  virtual void AddModel(IndexedModel* m) {
    model = m;
    bbox.Extend(m->bbox);
    num_vertices += model->numVertices();
    num_triangles += model->numTriangles();
  }

  //virtual void Update() {}

  virtual void Initialize();
  virtual void Buffer();
  virtual void Render();
  virtual void Cleanup();

private:
  unsigned int vao_id;
  unsigned int vertices_vbo_id;
  unsigned int indices_vbo_id;
};

#endif
