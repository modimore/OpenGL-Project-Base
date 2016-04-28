#include "TriMeshOBJ.hpp"
#include "../base/Utility.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <cmath>

//#include <glm/gtc/type_ptr.hpp>

// Constructor and Destructor ==================================================
void TriMeshOBJ::LoadDefault() {
  // fill vertex array
  vtx_pos_arr = std::vector<glm::vec4>(4);
  vtx_pos_arr[0] = glm::vec4(-1.0,-1.0,-1.0, 1.0);
  vtx_pos_arr[1] = glm::vec4( 3.0, 0.0, 0.0, 1.0);
  vtx_pos_arr[2] = glm::vec4( 0.0, 3.0, 0.0, 1.0);
  vtx_pos_arr[3] = glm::vec4( 0.0, 0.0, 3.0, 1.0);

  // extend bounding box
  for (unsigned int i = 0; i < vtx_pos_arr.size(); i++) {
    bbox.Extend(glm::vec3(vtx_pos_arr[i]));
  }

  // create triangles
  unsigned int f_i[12] = {2,1,0,3,2,0,0,1,3,1,2,3};
  for (unsigned int i = 0; i < 12; i += 3) {
    addTriangle(f_i[i],f_i[i+1],f_i[i+2]);
  }
}
// =============================================================================

// Load from a .obj file =======================================================
// Does not handles full standard, only a limited subset of the specification
// Does skip comments, so feel free to write .obj # comments in your files
// Specifically:
// -- does not bother with vt or vn specification lines
// -- relatedly only deals with faces without those things (and will crash if they are provided)
#define MAX_LINE_LENGTH 200
void TriMeshOBJ::LoadOBJ(std::string input_fname) {
  std::ifstream istr(&(input_fname[0]));
  if (!istr) {
    std::cout << "WARNING: We could not open the file provided."
              << "We will produce our default mesh instead." << std::endl;
    this->LoadDefault();
    return;
  }

  char line[MAX_LINE_LENGTH];
  std::string token;
  double x,y,z,w;
  unsigned int a,b,c;

  while (istr.getline(line,MAX_LINE_LENGTH)) {
    std::stringstream ss;
    ss << line;

    token = "";
    ss >> token;
    if (token == "") continue;

    if (token == std::string("v")) {
      w = 1.0; // default to 1.0 if w is not provided (which is most of the time)
      ss >> x >> y >> z >> w;
      addVertex(glm::vec4(x,y,z,w));
    }
    else if (token == std::string("f")) {
      // assumes faces are defined using a triangle fan-out
      // does not handle vertex textures or normals provided here
      a = b = c = -1;
      ss >> a >> b;
      while (ss >> c) {
        addTriangle(a-1,b-1,c-1);
        b = c;
      }
    }
    else if (token == std::string("vt")) {}
    else if (token == std::string("vn")) {}
    else if (token[0] == '#') {}
    else {
      printf("LINE: '%s'", line);
    }
  }

  std::cout << "Loaded " << numTriangles() << " triangles" << std::endl;
}
