#include "TriangleMesh.hpp"
#include "../../base/Utility.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <cmath>

#include <glm/gtc/type_ptr.hpp>

// Constructor and Destructor ==================================================
TriangleMesh::TriangleMesh()
: IndexedModel() {
  // fill vertex array
  vertices = std::vector<Vertex*>(4);
  float one_third = 1.0 / 3.0;
  vertices[0] = new Vertex(glm::vec4(-one_third,-one_third,-one_third,1.0),glm::vec4( 0.0, 0.0, 0.0, 1.0));
  vertices[1] = new Vertex(glm::vec4( 1.0, 0.0, 0.0, 1.0),glm::vec4( 1.0, 0.0, 0.0, 1.0));
  vertices[2] = new Vertex(glm::vec4( 0.0, 1.0, 0.0, 1.0),glm::vec4( 0.0, 1.0, 0.0, 1.0));
  vertices[3] = new Vertex(glm::vec4( 0.0, 0.0, 1.0, 1.0),glm::vec4( 0.0, 0.0, 1.0, 1.0));

  // extend bounding box
  for (unsigned int i = 0; i < vertices.size(); i++) {
    vertices[i]->setID(i);
    bbox.Extend(glm::vec3(vertices[i]->getPosition()));
  }

  // create triangles
  unsigned int f_i[12] = {2,1,0,3,2,0,0,1,3,1,2,3};
  for (unsigned int i = 0; i < 12; i += 3) {
    addTriangle(vertices[f_i[i]],vertices[f_i[i+1]],vertices[f_i[i+2]]);
  }
}

TriangleMesh::TriangleMesh(const char input_fname[]) {
  LoadOBJ(input_fname);
}

TriangleMesh::~TriangleMesh() { }
// =============================================================================

// Load from a .obj file =======================================================
// Does not handles full standard, only a limited subset of the specification
// Does skip comments, so feel free to write .obj # comments in your files
// Specifically:
// -- does not bother with vt or vn specification lines
// -- relatedly only deals with faces without those things (and will crash if they are provided)
#define MAX_LINE_LENGTH 200
void TriangleMesh::LoadOBJ(const char input_fname[]) {
  std::ifstream istr(input_fname);
  if (!istr) {
    std::cout << "WARNING: We could not open the file provided."
              << "We will produce our default mesh instead." << std::endl;
    *this = TriangleMesh();
    return;
  }

  char line[MAX_LINE_LENGTH];
  std::string token;
  double x,y,z,w;
  int a,b,c;

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
        addTriangle(vertices[a-1],vertices[b-1],vertices[c-1]);
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
// =============================================================================

// Add a Triangle ==============================================================
void TriangleMesh::addVertex(glm::vec4 pos, glm::vec4 color) {
  int index = vertices.size();
  vertices.push_back(new Vertex(pos,color));
  vertices[index]->setID(index);
  bbox.Extend(glm::vec3(pos));
}

void TriangleMesh::addTriangle(Vertex* a, Vertex* b, Vertex* c) {
  triangles.push_back(new Triangle(a,b,c));
}
// =============================================================================

// Vertex and Index export =====================================================
std::vector<VertexPosColor> TriangleMesh::getVertices() {
  std::vector<VertexPosColor> output(vertices.size());

  for (unsigned int i = 0; i < output.size(); i++) {
    output[i] = VertexPosColor(vertices[i]->getPosition(),vertices[i]->getColor());
  }

  return output;
}

std::vector<unsigned int> TriangleMesh::getTriVertIndices() {
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
