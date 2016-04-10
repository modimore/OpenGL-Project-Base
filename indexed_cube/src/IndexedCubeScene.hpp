#ifndef _INDEXED_CUBE_SCENE_HPP_
#define _INDEXED_CUBE_SCENE_HPP_

#include "../../base/Scene.hpp"

class IndexedCubeScene : public Scene {
public:
  unsigned int num_triangles;

  void Initialize();
  void Render();
  void Cleanup();

private:
  GLuint vao_id;
  GLuint vertices_vbo_id;
  GLuint indices_vbo_id;
};

#endif
