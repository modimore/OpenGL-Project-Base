#include "HalfEdgeModel.hpp"
#include "../../base/Utility.hpp"

#include <iostream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

// Constructor and Destructor ==================================================
HalfEdgeModel::HalfEdgeModel()
: IndexedModel() {
  // fill vertex array
  vertices = std::vector<Vertex*>(8);
  vertices[0] = new Vertex(glm::vec4(-0.5,-0.5,-0.5, 1.0));
  vertices[1] = new Vertex(glm::vec4(-0.5,-0.5, 0.5, 1.0));
  vertices[2] = new Vertex(glm::vec4( 0.5,-0.5,-0.5, 1.0));
  vertices[3] = new Vertex(glm::vec4( 0.5,-0.5, 0.5, 1.0));
  vertices[4] = new Vertex(glm::vec4(-0.5, 0.5,-0.5, 1.0));
  vertices[5] = new Vertex(glm::vec4(-0.5, 0.5, 0.5, 1.0));
  vertices[6] = new Vertex(glm::vec4( 0.5, 0.5,-0.5, 1.0));
  vertices[7] = new Vertex(glm::vec4( 0.5, 0.5, 0.5, 1.0));

  // extend bounding box
  for (unsigned int i = 0; i < vertices.size(); i++) {
    vertices[i]->setID(i);
    bbox.Extend(glm::vec3(vertices[i]->getPosition()));
  }

  // create triangles
  unsigned int f_i[24] = {0,4,2,6,1,3,5,7,0,2,1,3,4,5,6,7,0,1,4,5,2,6,3,7};
  for (unsigned int i = 0; i < 24; i += 4) {
    addTriangle(vertices[f_i[i]],vertices[f_i[i+1]],vertices[f_i[i+3]]);
    addTriangle(vertices[f_i[i]],vertices[f_i[i+3]],vertices[f_i[i+2]]);
  }
}

HalfEdgeModel::~HalfEdgeModel() { }
// =============================================================================

// Add a Triangle ==============================================================
void HalfEdgeModel::addTriangle(Vertex* a, Vertex* b, Vertex* c) {
  unsigned int index = edges.size();

  edges.push_back(new Edge(a,b));
  edges.push_back(new Edge(b,c));
  edges.push_back(new Edge(c,a));

  edges[index  ]->setNext(edges[index+1]);
  edges[index+1]->setNext(edges[index+2]);
  edges[index+2]->setNext(edges[index  ]);

  triangles.push_back(new Triangle(edges[index]));
}
// =============================================================================

// Vertex and Index export =====================================================
std::vector<VertexPosColor> HalfEdgeModel::getVertices() {
  std::vector<VertexPosColor> output(8);

  for (unsigned int i = 0; i < output.size(); i++) {
    // first triangle
    output[i] = VertexPosColor(vertices[i]->getPosition(),vertices[i]->getColor());
  }

  return output;
}

std::vector<unsigned int> HalfEdgeModel::getTriVertIndices() {
  std::vector<unsigned int> output(triangles.size()*3);
  
  for (unsigned int i = 0; i < triangles.size(); i++) {
    unsigned int start = i*3;
    // first triangle
    output[start  ] = (*triangles[i])[0]->getID();
    output[start+1] = (*triangles[i])[1]->getID();
    output[start+2] = (*triangles[i])[2]->getID();
  }

  return output;
}
// =============================================================================
