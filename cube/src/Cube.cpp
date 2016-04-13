#include "Cube.hpp"
#include "../../base/Utility.hpp"

#include <iostream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

// Constructor and Destructor ==================================================
Cube::Cube()
: Model() {
  vertices = std::vector<glm::vec4>(8);
  vertices[0] = glm::vec4(-0.5,-0.5,-0.5, 1.0);
  vertices[1] = glm::vec4(-0.5,-0.5, 0.5, 1.0);
  vertices[2] = glm::vec4( 0.5,-0.5,-0.5, 1.0);
  vertices[3] = glm::vec4( 0.5,-0.5, 0.5, 1.0);
  vertices[4] = glm::vec4(-0.5, 0.5,-0.5, 1.0);
  vertices[5] = glm::vec4(-0.5, 0.5, 0.5, 1.0);
  vertices[6] = glm::vec4( 0.5, 0.5,-0.5, 1.0);
  vertices[7] = glm::vec4( 0.5, 0.5, 0.5, 1.0);

  for (unsigned int i = 0; i < vertices.size(); i++)
  { bbox.Extend(glm::vec3(vertices[i])); }
}

Cube::~Cube() { }
// =============================================================================

// Vertex export ===============================================================
std::vector<VertexPosColor> Cube::getVertices() {
  std::vector<VertexPosColor> output(36);

  //             ^       ^       ^       ^       ^       ^      //
  int f_i[24] = {0,4,2,6,1,3,5,7,0,2,1,3,4,5,6,7,0,1,4,5,2,6,3,7};
  //             ^       ^       ^       ^       ^       ^      //
  std::vector<ColoredFace> faces;
  faces.push_back(ColoredFace(f_i   , glm::vec4(0,1,1, 1.0f)));
  faces.push_back(ColoredFace(f_i+ 4, glm::vec4(1,0,0, 1.0f)));
  faces.push_back(ColoredFace(f_i+ 8, glm::vec4(1,0,1, 1.0f)));
  faces.push_back(ColoredFace(f_i+12, glm::vec4(0,1,0, 1.0f)));
  faces.push_back(ColoredFace(f_i+16, glm::vec4(1,1,0, 1.0f)));
  faces.push_back(ColoredFace(f_i+20, glm::vec4(0,0,1, 1.0f)));

  // back   cyan   0 2 6 0 6 4
  // front  red    1 7 3 1 5 7
  // bottom purple 0 5 1 0 4 5
  // top    green  2 3 7 2 7 6
  // left   yellow 0 1 3 0 3 2
  // right  blue   4 7 5 4 6 7

  for (int i = 0; i < 6; i++) {
    int start = 6*i;
    // first triangle
    output[start  ] = VertexPosColor(vertices[faces[i].sides[0]],faces[i].color);
    output[start+1] = VertexPosColor(vertices[faces[i].sides[1]],faces[i].color);
    output[start+2] = VertexPosColor(vertices[faces[i].sides[3]],faces[i].color);
    // second triangle
    output[start+3] = VertexPosColor(vertices[faces[i].sides[0]],faces[i].color);
    output[start+4] = VertexPosColor(vertices[faces[i].sides[3]],faces[i].color);
    output[start+5] = VertexPosColor(vertices[faces[i].sides[2]],faces[i].color);
  }

  return output;
}
// =============================================================================
