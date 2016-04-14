#include "HalfEdgeModel.hpp"
#include "../../base/Utility.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

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

HalfEdgeModel::HalfEdgeModel(const char input_fname[]) {
  LoadOBJ(input_fname);
}

HalfEdgeModel::~HalfEdgeModel() { }
// =============================================================================

// Load from a .obj file =======================================================
// Does not handles full standard, only a limited subset of the specification
// Does skip comments, so feel free to write .obj # comments in your files
// Specifically:
// -- does not bother with vt or vn specification lines
// -- relatedly only deals with faces without those things (and will crash if they are provided)
#define MAX_LINE_LENGTH 200
void HalfEdgeModel::LoadOBJ(const char input_fname[]) {
  std::ifstream istr(input_fname);
  if (!istr) {
    std::cout << "WARNING: We could not open the file provided."
              << "We will produce a cube instead." << std::endl;
    *this = HalfEdgeModel();
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
void HalfEdgeModel::addVertex(glm::vec4 pos, glm::vec4 color) {
  int index = vertices.size();
  vertices.push_back(new Vertex(pos,color));
  vertices[index]->setID(index);
  bbox.Extend(glm::vec3(pos));
}

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
