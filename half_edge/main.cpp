#include <cstdlib>
#include <string>
#include <iostream>
#include <cassert>

#include "../base/GLContext.hpp"
#include "../base/Camera.hpp"
#include "../base/InputManager.hpp"
#include "../base/IndexedScene.hpp"

#include "../base/ArgParser.hpp"
#include "src/HalfEdgeModel.hpp"

int main(int argc, char* argv[]) {
  ArgParser args = ArgParser(argc, argv);
  HalfEdgeModel hedge = HalfEdgeModel("../inputs/cube.obj");
  IndexedScene scene = IndexedScene();
  scene.AddModel(&hedge);
  GLContext::Initialize(&args,&scene);
  GLContext::Run();
  GLContext::Cleanup();
  return 0;
}
