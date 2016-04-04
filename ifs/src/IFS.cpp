#include "IFS.hpp"
#include "../../base/Utility.hpp"

#include <iostream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

IFS::IFS(IFSArgParser* _args)
: Model() {
  args = _args;

  if (args->deterministic) rng = MTRand(87);
  else rng = MTRand();

  // Open the IFS specification for specified in args
  std::ifstream input((args->input_path + "/" + args->input_file).c_str());
  if (!input.good()) {
    std::cout << "ERROR: " << "Must specify valid input file" << std::endl
              << "\tProvided: " << args->input_path + "/" + args->input_file << std::endl;
    exit(1);
  }

  // Read in the number of transforms, allocate memory
  input >> num_transforms;
  transform_probabilities = new float[num_transforms];
  transforms = new glm::mat4[num_transforms];

  // Read in each of the transforms
  float cumulative_probability = 0.0f; // Sum of all probabilities
  for (unsigned int i = 0; i < num_transforms; i++) {
    float probability;
    input >> probability;

    cumulative_probability += probability;
    transform_probabilities[i] = cumulative_probability;

    float t_data[16];
    for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 4; col++ ) {
        input >> t_data[col*4 + row];
      }
    }
    transforms[i] = glm::make_mat4(t_data);
  }
}

IFS::~IFS() {
  delete[] transforms;
  delete[] transform_probabilities;
}

// IFS Program Driver Functions ================================================
void IFS::Create() {
  HandleGLError("Entered IFS::Setup");
  SetupPoints();
  HandleGLError("Finished IFS::Setup");
}

void IFS::Alter(GLuint matrix_id, const glm::mat4 m) {
  HandleGLError("Entered IFS::Update");
  glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &m[0][0]);
  DrawPoints();
  HandleGLError("Finished IFS::Update");
}

void IFS::Delete() {
  HandleGLError("Entered IFS::Cleanup");
  CleanupPoints();
  HandleGLError("Finished IFS::Cleanup");
}
// =============================================================================

// Point Mode Functions ========================================================
void IFS::SetupPoints() {
  HandleGLError("Entered IFS::SetupPoints");

  // Allocate array of points
  struct VertexPosColor* points = new struct VertexPosColor[args->points];

  // Create points and determine locations of each
  for (unsigned int i = 0; i < args->points; i++) {
    // Start at random location
    double x = rng.rand();
    double y = rng.rand();
    double z = rng.rand();
    glm::vec4 pt(x,y,z,1.0f);

    // Apply args->iterations randomly selected transforms
    double probability; int transform_index;
    for (unsigned int j = 0; j < args->iterations; j++) {
      probability = rng.rand();

      transform_index = 0;
      while (transform_probabilities[transform_index] < probability) transform_index++;
      glm::mat4 transform = transforms[transform_index];
      pt = transform * pt;
    }

    // Put location and color into point array
    points[i].position = pt;
    points[i].color = glm::vec4(0.0f,0.0f,0.0f,1.0f);
    bbox.Extend(glm::vec3(pt));
  }

  // Heavy GL stuff
  glGenVertexArrays(1,&vao_id);
  glBindVertexArray(vao_id);
  glGenBuffers(1,&vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER,vbo_id);
  glBufferData(GL_ARRAY_BUFFER,sizeof(struct VertexPosColor) * (args->points),points,GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,sizeof(struct VertexPosColor),0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,sizeof(struct VertexPosColor),(GLvoid*)sizeof(glm::vec4));

  // Increase point rendering size
  glPointSize(2.0f);

  delete[] points;
  HandleGLError("Finished IFS::SetupPoints");
}

void IFS::DrawPoints() {
  HandleGLError("Entered IFS::DrawPoints");
  glDrawArrays(GL_POINTS,0,args->points);
  HandleGLError("Finished IFS::DrawPoints");
}

void IFS::CleanupPoints() {
  HandleGLError("Entered IFS::CleanupPoints");
  glDeleteBuffers(1,&vao_id);
  glDeleteBuffers(1,&vbo_id);
  HandleGLError("Finished IFS::CleanupPoints");
}
// =============================================================================

// Cube Mode Functions =========================================================

// =============================================================================
