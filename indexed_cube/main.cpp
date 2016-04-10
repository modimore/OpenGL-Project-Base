#include <cstdlib>
#include <string>
#include <iostream>
#include <cassert>

#include "../base/GLContext.hpp"
#include "../base/Camera.hpp"
#include "../base/InputManager.hpp"
#include "../base/IndexedScene.hpp"

#include "src/CubeArgParser.hpp"
#include "src/IndexedCube.hpp"

int main(int argc, char* argv[]) {

  CubeArgParser args = CubeArgParser(argc,argv);
  IndexedCube cube = IndexedCube(&args);
  IndexedScene scene = IndexedScene();
  scene.AddModel(&cube);
  GLContext::Initialize(&args,&scene);
  GLContext::Run();
  GLContext::Cleanup();
  return 0;
}
