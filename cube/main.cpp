#include <cstdlib>
#include <string>
#include <iostream>
#include <cassert>

#include "../base/GLContext.hpp"
#include "../base/Camera.hpp"
#include "../base/InputManager.hpp"
#include "../base/Scene.hpp"

#include "src/CubeArgParser.hpp"
#include "src/Cube.hpp"

int main(int argc, char* argv[]) {

  CubeArgParser args = CubeArgParser(argc,argv);
  Cube cube = Cube(&args);
  Scene scene = Scene();
  scene.AddModel(&cube);
  GLContext::Initialize(&args,&scene);
  GLContext::Run();
  GLContext::Cleanup();
  return 0;
}
