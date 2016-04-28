#include "HalfEdgeMesh.hpp"
#include "../../base/Utility.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

// Constructor and Destructor ==================================================
void HalfEdgeMesh::LoadDefault() {
  // fill vertex array
  vtx_pos_arr = std::vector<glm::vec4>(8);
  vtx_pos_arr[0] = glm::vec4(-0.5,-0.5,-0.5, 1.0);
  vtx_pos_arr[1] = glm::vec4(-0.5,-0.5, 0.5, 1.0);
  vtx_pos_arr[2] = glm::vec4( 0.5,-0.5,-0.5, 1.0);
  vtx_pos_arr[3] = glm::vec4( 0.5,-0.5, 0.5, 1.0);
  vtx_pos_arr[4] = glm::vec4(-0.5, 0.5,-0.5, 1.0);
  vtx_pos_arr[5] = glm::vec4(-0.5, 0.5, 0.5, 1.0);
  vtx_pos_arr[6] = glm::vec4( 0.5, 0.5,-0.5, 1.0);
  vtx_pos_arr[7] = glm::vec4( 0.5, 0.5, 0.5, 1.0);

  // extend bounding box
  for (unsigned int i = 0; i < vtx_pos_arr.size(); i++) {
    bbox.Extend(glm::vec3(vtx_pos_arr[i]));
  }

  // create triangles
  unsigned int f_i[24] = {0,4,2,6,1,3,5,7,0,2,1,3,4,5,6,7,0,1,4,5,2,6,3,7};
  for (unsigned int i = 0; i < 24; i += 4) {
    addTriangle(f_i[i],f_i[i+1],f_i[i+3]);
    addTriangle(f_i[i],f_i[i+3],f_i[i+2]);
  }
}
// =============================================================================

// Add a Triangle ==============================================================
void HalfEdgeMesh::addTriangle(unsigned int a, unsigned int b, unsigned int c) {
  TriangleMesh::addTriangle(a,b,c);
  unsigned int index = edges.size();

  edges.push_back(new Edge(a,b));
  edges.push_back(new Edge(b,c));
  edges.push_back(new Edge(c,a));

  edges[index  ]->setNext(edges[index+1]);
  edges[index+1]->setNext(edges[index+2]);
  edges[index+2]->setNext(edges[index  ]);

  triangles.push_back(new HalfEdgeTriangle(edges[index]));
}
// =============================================================================
