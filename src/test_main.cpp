#include <cstdlib>
#include <string>
#include <iostream>
#include <cassert>

#include "ArgParser.hpp"
#include "Camera.hpp"
#include "GLProgramManager.hpp"

int main(int argc, char* argv[]) {

  ArgParser args = ArgParser(argc,argv);
  GLProgramManager::Initialize(&args);
  GLProgramManager::Run();
  GLProgramManager::Cleanup();
  return 0;
}
