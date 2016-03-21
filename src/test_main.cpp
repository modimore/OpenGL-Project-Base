#include <cstdlib>
#include <string>
#include <iostream>
#include <cassert>

#include "core/Camera.hpp"
#include "core/GLProgramManager.hpp"

#include "ifs/IFSArgParser.hpp"
#include "ifs/IFS.hpp"

int main(int argc, char* argv[]) {

  IFSArgParser args = IFSArgParser(argc,argv);
  IFS ifs = IFS(&args);
  GLProgramManager::Initialize(&args,&ifs);
  GLProgramManager::Run();
  GLProgramManager::Cleanup();
  return 0;
}
