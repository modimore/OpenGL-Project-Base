#ifndef _SIMPLE_SCENE_HPP_
#define _SIMPLE_SCENE_HPP_

#include <vector>

#include "Scene.hpp"
#include "Model.hpp"

class SimpleScene : public Scene {
public:
  //BoundingBox bbox;
  Model* model;
  //bool updated = true;
  unsigned int num_vertices = 0;

  // Create scene and manage models
  //Scene() { bbox = BoundingBox(); }
  virtual void AddModel(Model* m) {
    model = m;
    bbox.Extend(m->bbox);
    num_vertices += model->numVertices();
  }

  //virtual void Update() {}

  virtual void Initialize();
  virtual void Buffer();
  virtual void Render();
  virtual void Cleanup();

private:
  GLuint vao_id;
  GLuint vertices_vbo_id;
};

#endif
