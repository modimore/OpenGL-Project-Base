#include <cstdlib>
#include <string>
#include <iostream>
#include <cassert>

#include "../base/GLContext.hpp"
#include "../base/Camera.hpp"
#include "../base/ArgParser.hpp"
#include "../base/InputManager.hpp"

#include "../scenes/IndexedScene.hpp"
#include "../models/TriMeshOBJ.hpp"


int main(int argc, char* argv[]) {
  ArgParser args = ArgParser(argc, argv);
  TriMeshOBJ tmesh = TriMeshOBJ(args.get_input_path());
  IndexedScene scene = IndexedScene();
  scene.AddModel(&tmesh);
  GLContext::Initialize(&args,&scene);
  GLContext::Run();
  GLContext::Cleanup();
  return 0;
}
