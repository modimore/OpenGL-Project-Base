#ifndef _TRI_MESH_OBJ_HPP_
#define _TRI_MESH_OBJ_HPP_

#include "TriangleMesh.hpp"

class TriMeshOBJ : public TriangleMesh {
public:
  TriMeshOBJ() { LoadDefault(); }
  TriMeshOBJ(std::string input_fname) { LoadOBJ(input_fname); }
  virtual void LoadDefault();
  void LoadOBJ(std::string input_fname);
};

#endif
