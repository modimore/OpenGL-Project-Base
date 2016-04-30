#include <cstdlib>
#include <string>
#include <iostream>
#include <cassert>

#include "../base/GLContext.hpp"
#include "../base/Camera.hpp"
#include "../base/ConfigParser.hpp"
#include "../base/InputManager.hpp"

#include "../scenes/IndexedScene.hpp"
#include "../models/TriMeshOBJ.hpp"


int main(int argc, char* argv[]) {
  ConfigParser conf = ConfigParser(argc, argv);
  TriMeshOBJ tmesh = TriMeshOBJ(conf.get_input_path());
  IndexedScene scene = IndexedScene();
  scene.AddModel(&tmesh);
  GLContext::Initialize(&conf,&scene);
  GLContext::Run();
  GLContext::Cleanup();
  return 0;
}
