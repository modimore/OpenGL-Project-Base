#include "IndexedCube.hpp"
#include "../../base/Utility.hpp"

#include <iostream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

// Constructor and Destructor ==================================================
IndexedCube::IndexedCube(CubeArgParser* _args)
: IndexedModel() {
  args = _args;

  // fill vertex array
  vertices = std::vector<glm::vec4>(8);
  vertices[0] = glm::vec4(-0.5,-0.5,-0.5, 1.0);
  vertices[1] = glm::vec4(-0.5,-0.5, 0.5, 1.0);
  vertices[2] = glm::vec4( 0.5,-0.5,-0.5, 1.0);
  vertices[3] = glm::vec4( 0.5,-0.5, 0.5, 1.0);
  vertices[4] = glm::vec4(-0.5, 0.5,-0.5, 1.0);
  vertices[5] = glm::vec4(-0.5, 0.5, 0.5, 1.0);
  vertices[6] = glm::vec4( 0.5, 0.5,-0.5, 1.0);
  vertices[7] = glm::vec4( 0.5, 0.5, 0.5, 1.0);

  // extend bounding box
  for (unsigned int i = 0; i < vertices.size(); i++)
  { bbox.Extend(glm::vec3(vertices[i])); }

  // fill index array
  unsigned int f_i[24] = {0,4,2,6,1,3,5,7,0,2,1,3,4,5,6,7,0,1,4,5,2,6,3,7};
  face_indices = std::vector<unsigned int>(f_i, f_i + sizeof(f_i)/sizeof(unsigned int));
}

IndexedCube::~IndexedCube() { }
// =============================================================================

// Vertex and Index export ===============================================================
std::vector<VertexPosColor> IndexedCube::getVertices() {
  std::vector<VertexPosColor> output(8);

  for (unsigned int i = 0; i < output.size(); i++) {
    // first triangle
    output[i] = VertexPosColor(vertices[i], vertices[i] + glm::vec4(0.5f,0.5f,0.5f,0));
  }

  return output;
}

std::vector<unsigned int> IndexedCube::getTriVertIndices() {
  std::vector<unsigned int> output(36);

  for (unsigned int i = 0; i < 6; i++) {
    unsigned int in_start = 4*i;
    unsigned int out_start = 6*i;
    // first triangle
    output[out_start  ] = face_indices[in_start  ];
    output[out_start+1] = face_indices[in_start+1];
    output[out_start+2] = face_indices[in_start+3];
    // second triangle
    output[out_start+3] = face_indices[in_start  ];
    output[out_start+4] = face_indices[in_start+3];
    output[out_start+5] = face_indices[in_start+2];
  }

  return output;
}
// =============================================================================
