#include <cstdlib>
#include <string>
#include <iostream>
#include <cassert>

#include "../base/GLContext.hpp"
#include "../base/Camera.hpp"
#include "../base/InputManager.hpp"
#include "../base/ArgParser.hpp"
#include "../base/SimpleScene.hpp"

#include "src/Cube.hpp"

int main(int argc, char* argv[]) {

  ArgParser args = ArgParser(argc,argv);
  Cube cube = Cube();
  SimpleScene scene = SimpleScene();
  scene.AddModel(&cube);
  GLContext::Initialize(&args,&scene);
  GLContext::Run();
  GLContext::Cleanup();
  return 0;
}
