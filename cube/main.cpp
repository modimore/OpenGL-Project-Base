#include <cstdlib>
#include <string>
#include <iostream>
#include <cassert>

#include "../base/GLContext.hpp"
#include "../base/Camera.hpp"
#include "../base/InputManager.hpp"

#include "src/CubeArgParser.hpp"
#include "src/Cube.hpp"

int main(int argc, char* argv[]) {

  CubeArgParser args = CubeArgParser(argc,argv);
  Cube cube = Cube(&args);
  GLContext::Initialize(&args,&cube);
  GLContext::Run();
  GLContext::Cleanup();
  return 0;
}
