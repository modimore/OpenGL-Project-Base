#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../base/BoundingBox.hpp"

class Model {
protected:
  std::vector<glm::vec4> vtx_pos_arr;

public:
  BoundingBox bbox;

  // Constructors and Destructors
  Model() { bbox = BoundingBox(); vtx_pos_arr = std::vector<glm::vec4>(0); }
  ~Model() { }

  // Modifiers
  virtual void addVertex(glm::vec4 pos) {
    vtx_pos_arr.push_back(pos);
    bbox.Extend(glm::vec3(pos));
  }

  virtual void Update(const glm::mat4& m) {}

  // Accessors
  // -- Vertices
  virtual unsigned int numVertices() { return vtx_pos_arr.size(); }
  virtual const std::vector<glm::vec4>& getVertexPositions() const {
    return vtx_pos_arr;
  }
};

#endif
