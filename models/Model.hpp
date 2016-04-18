#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include <vector>

#define GLM_FORCE_RADIANS
//#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../geometry/ShaderInput.hpp"
#include "../base/BoundingBox.hpp"

#include "../geometry/Vertex.hpp"

class Model {
protected:
  std::vector<Vertex*> vertices;

public:
  BoundingBox bbox;

  // Constructors and Destructors
  Model() { bbox = BoundingBox(); vertices = std::vector<Vertex*>(0); }
  ~Model() {
    for (unsigned int i = 0; i < vertices.size(); i++) { delete vertices[i]; }
  }

  // Modifiers
  virtual void addVertex(glm::vec4 pos,
                         glm::vec4 color=glm::vec4(0.5,0.5,0.5,1.0)) {
    int index = vertices.size();
    vertices.push_back(new Vertex(pos,color));
    vertices[index]->setID(index);
    bbox.Extend(glm::vec3(pos));
  }

  virtual void Update(const glm::mat4& m) {}

  // Accessors
  // -- Vertices
  virtual int numVertices() { return vertices.size(); }
  virtual std::vector<VertexPosColor> getVertices() {
    std::vector<VertexPosColor> output(vertices.size());
    for (unsigned int i = 0; i < output.size(); i++) {
      output[i] = VertexPosColor(vertices[i]->getPosition(),
                                 vertices[i]->getColor());
    }
    return output;
  }
};

#endif
