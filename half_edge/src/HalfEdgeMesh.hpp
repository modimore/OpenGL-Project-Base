#ifndef _HALF_EDGE_MESH_
#define _HALF_EDGE_MESH_

#include "../../models/TriMeshOBJ.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Edge.hpp"
#include "HalfEdgeTriangle.hpp"

class HalfEdgeMesh : public TriMeshOBJ {
public:
  std::vector<Edge*> edges;

  // Constructor
  HalfEdgeMesh() : TriMeshOBJ() { Reset(); LoadDefault(); }
  HalfEdgeMesh(std::string input_fname) : TriMeshOBJ() {
    Reset();
    LoadOBJ(input_fname);
  }
  ~HalfEdgeMesh() {
    for (unsigned int i = 0; i < edges.size(); i++) {
      if (edges[i] != NULL) delete edges[i];
    }
    for (unsigned int i = 0; i < triangles.size(); i++) {
      if (triangles[i] != NULL) delete triangles[i];
    }
  }

  void LoadDefault();
  void addTriangle(unsigned int a, unsigned int b, unsigned int c);
  void addTriangle(char* tri_spec);

  void Reset() {
    vtx_pos_arr.clear();
    edges.clear(); triangles.clear();
    bbox = BoundingBox();
  }

  std::vector<float> getTriVertexData(unsigned int tri_index, unsigned int v_index) {
    HalfEdgeTriangle* tri = (HalfEdgeTriangle*)triangles[tri_index];
    std::vector<float> result;

    glm::vec4 pos = vtx_pos_arr[ (*tri)[v_index] ];
    result.push_back(pos.x);
    result.push_back(pos.y);
    result.push_back(pos.z);
    result.push_back(pos.w);

    return result;
  }
};

#endif
