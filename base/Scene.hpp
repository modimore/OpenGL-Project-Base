#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <vector>

#include "BoundingBox.hpp"

class Model;

class Scene {
public:
  BoundingBox bbox;
  bool updated = true;

  // Create scene and manage models
  Scene() { bbox = BoundingBox(); }

  virtual void Update() {}

  virtual void Initialize() {}
  virtual void Buffer() {}
  virtual void Render() {}
  virtual void Cleanup() {}
};

#endif
