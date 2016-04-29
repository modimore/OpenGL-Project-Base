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
  std::vector<glm::vec3> vtx_norm_arr;
  std::vector<glm::vec2> vtx_tex_arr;

public:
  BoundingBox bbox;

  // Constructors and Destructors
  Model() { bbox = BoundingBox(); vtx_pos_arr = std::vector<glm::vec4>(0); }
  ~Model() { }

  // Modifiers
  virtual void addVertexPosition(const glm::vec4& pos) {
    vtx_pos_arr.push_back(pos);
    bbox.Extend(glm::vec3(pos));
  }
  virtual void addVertexNormal(const glm::vec3& norm) {
    vtx_norm_arr.push_back(norm);
  }
  virtual void addVertexTexCoord(const glm::vec2& tex_coord) {
    vtx_tex_arr.push_back(tex_coord);
  }

  virtual void Update(const glm::mat4& m) {}

  // Accessors
  // -- Vertices
  virtual unsigned int numVertices() { return vtx_pos_arr.size(); }
  virtual const bool hasVertexPositions() { return vtx_pos_arr.size() > 0; }
  virtual const std::vector<glm::vec4>& getVertexPositions() const {
    return vtx_pos_arr;
  }
  virtual const bool hasVertexNormals() { return vtx_norm_arr.size() > 0; }
  virtual const std::vector<glm::vec3>& getVertexNormals() const {
    return vtx_norm_arr;
  }
  virtual const bool hasVertexTexCoords() { return vtx_tex_arr.size() > 0; }
  virtual const std::vector<glm::vec2>& getVertexTexCoords() const {
    return vtx_tex_arr;
  }
};

#endif
