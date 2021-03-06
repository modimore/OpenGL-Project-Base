#include <cstdlib>
#include <string>
#include <iostream>
#include <cassert>

#include "../base/GLContext.hpp"
#include "../base/Camera.hpp"
#include "../base/InputManager.hpp"

#include "src/IFSArgParser.hpp"
#include "src/IFS.hpp"

int main(int argc, char* argv[]) {

  IFSArgParser args = IFSArgParser(argc,argv);
  IFS ifs = IFS(&args);
  GLContext::Initialize(&args,&ifs);
  GLContext::Run();
  GLContext::Cleanup();
  return 0;
}
