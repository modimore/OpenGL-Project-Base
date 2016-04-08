#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <vector>

#include "Model.hpp"
#include "BoundingBox.hpp"

class Scene {
public:
  BoundingBox bbox;
  Model* model;
  bool model_updated = true;
  unsigned int num_vertices = 0;

  // Create scene and manage models
  Scene() { bbox = BoundingBox(); }
  virtual void AddModel(Model* m);

  virtual void Update() {}

  virtual void Initialize();
  virtual void Render();
  virtual void Cleanup();

private:
  GLuint vao_id;
  GLuint vertices_vbo_id;
};

#endif
