#include <cstdlib>
#include <string>
#include <iostream>
#include <cassert>

#include "../base/GLContext.hpp"
#include "../base/Camera.hpp"
#include "../base/InputManager.hpp"
#include "../scenes/IndexedScene.hpp"

#include "../base/ConfigParser.hpp"
#include "src/HalfEdgeMesh.hpp"

int main(int argc, char* argv[]) {
  ConfigParser conf = ConfigParser(argc, argv);
  HalfEdgeMesh hedge = HalfEdgeMesh(conf.get_input_path());
  //HalfEdgeMesh hedge = HalfEdgeMesh();
  IndexedScene scene = IndexedScene();
  scene.AddModel(&hedge);
  GLContext::Initialize(&conf,&scene);
  GLContext::Run();
  GLContext::Cleanup();
  return 0;
}
