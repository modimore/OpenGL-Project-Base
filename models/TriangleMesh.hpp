#ifndef _TRI_MESH_HPP_
#define _TRI_MESH_HPP_

#include "Model.hpp"
#include "../geometry/Triangle.hpp"

#include <cstdio>

class TriangleMesh : public Model {
protected:
  std::vector<BaseTriangle*> triangles;

public:
  TriangleMesh() { triangles = std::vector<BaseTriangle*>(0); }
  ~TriangleMesh() { }

  virtual void addTriangle(unsigned int a, unsigned int b, unsigned int c) {
    triangles.push_back(new Triangle(a,b,c));
  }

  virtual void addTriangle(char* tri_spec) {
    unsigned int a_pos,  b_pos,  c_pos;
    unsigned int a_norm, b_norm, c_norm;
    unsigned int a_tex,  b_tex,  c_tex;

    Triangle* new_tri = new Triangle();

    if (sscanf(tri_spec,
               "%u/%u/%u %u/%u/%u %u/%u/%u",
               &a_pos, &a_norm, &a_tex,
               &b_pos, &b_norm, &b_tex,
               &c_pos, &c_norm, &c_tex) == 9) {
      new_tri->addPosIndices(a_pos-1,b_pos-1,c_pos-1);
      new_tri->addNormIndices(a_norm-1,b_norm-1,c_norm-1);
      new_tri->addTexCoordIndices(a_tex-1,b_tex-1,c_tex-1);
    } else if (sscanf(tri_spec,
                      "%u//%u %u//%u %u//%u",
                      &a_pos, &a_tex,
                      &b_pos, &b_tex,
                      &c_pos, &c_tex) == 6) {
      new_tri->addPosIndices(a_pos-1,b_pos-1,c_pos-1);
      new_tri->addTexCoordIndices(a_tex-1,b_tex-1,c_tex-1);
    } else if (sscanf(tri_spec,
                      "%u/%u %u/%u %u/%u",
                      &a_pos, &a_norm,
                      &b_pos, &b_norm,
                      &c_pos, &c_norm) == 6) {
      new_tri->addPosIndices(a_pos-1,b_pos-1,c_pos-1);
      new_tri->addNormIndices(a_norm-1,b_norm-1,c_norm-1);
    } else if (sscanf(tri_spec,
                      "%u %u %u",
                      &a_pos, &b_pos, &c_pos) == 3) {
      new_tri->addPosIndices(a_pos-1,b_pos-1,c_pos-1);
    } else {
      fprintf(stderr, "Invalid triangle: %s\n", tri_spec);
      return;
    }

    triangles.push_back(new_tri);
  }

  virtual std::vector<float> getTriVertexData(unsigned int i, unsigned int j) {
    Triangle* tri = (Triangle*)triangles[i];
    std::vector<float> result;

    if (tri->pos_indices.size() > 0) {
      glm::vec4 pos = vtx_pos_arr[tri->pos_indices[j]];
      result.push_back(pos.x);
      result.push_back(pos.y);
      result.push_back(pos.z);
      result.push_back(pos.w);
    }

    if (tri->norm_indices.size() > 0) {
      glm::vec3 norm = vtx_norm_arr[tri->norm_indices[j]];
      result.push_back(norm.x);
      result.push_back(norm.y);
      result.push_back(norm.z);
    }

    if (tri->tex_coord_indices.size() > 0) {
      glm::vec2 tex_coord = vtx_tex_arr[tri->tex_coord_indices[j]];
      result.push_back(tex_coord.x);
      result.push_back(tex_coord.y);
    }

    return result;
  }

  virtual unsigned int numTriangles() { return triangles.size(); }
  virtual unsigned int numVertices() { return triangles.size() * 3; }
};

#endif
