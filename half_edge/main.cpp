#include <cstdlib>
#include <string>
#include <iostream>
#include <cassert>

#include "../base/GLContext.hpp"
#include "../base/Camera.hpp"
#include "../base/InputManager.hpp"
#include "../scenes/IndexedScene.hpp"

#include "../base/ArgParser.hpp"
#include "src/HalfEdgeMesh.hpp"

int main(int argc, char* argv[]) {
  ArgParser args = ArgParser(argc, argv);
  HalfEdgeMesh hedge = HalfEdgeMesh(&(args.get_input_path()[0]));
  IndexedScene scene = IndexedScene();
  scene.AddModel(&hedge);
  GLContext::Initialize(&args,&scene);
  GLContext::Run();
  GLContext::Cleanup();
  return 0;
}
