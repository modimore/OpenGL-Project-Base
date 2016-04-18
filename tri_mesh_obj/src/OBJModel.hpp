#ifndef _OBJ_MODEL_
#define _OBJ_MODEL_

#include "../../models/TriangleMesh.hpp"

class OBJModel : public TriangleMesh {
public:
  OBJModel();
  OBJModel(const char input_fname[]);
  void LoadOBJ(const char input_fname[]);
};

#endif
