#ifndef _INDEXED_MODEL_HPP_
#define _INDEXED_MODEL_HPP_

#include "Model.hpp"

class IndexedModel : public Model {
public:
  virtual int numTriangles() { return 0; }
  virtual std::vector<unsigned int> getTriVertIndices() { return std::vector<unsigned int>(0); }
};

#endif
