#include "ShaderWriter.hpp"

#include <iostream>

// INCOMPLETE
std::string ShaderWriter::GetVertexShader(struct ShaderWriterControl in_ctrl, struct ShaderWriterControl out_ctrl) {
  std::stringstream ss;

  // specify shader version
  ss << "#version 330 core" << std::endl << std::endl;

  // define uniform shader inputs

  ss << "uniform mat4 MVP;" << std::endl;

  ss << std::endl;

  // define per-vertex shader inputs

  unsigned int layout_loc = 0;

  if (in_ctrl.position || true) { // this is necessary for the vertex shader
    ss << "layout(location = " << layout_loc++ << ") in vec4 pr_position;" << std::endl;
  }
  if (in_ctrl.color) {
    ss << "layout(location = " << layout_loc++ << ") in vec4 pr_color;" << std::endl;
  }
  if (in_ctrl.normal) {
    ss << "layout(location = " << layout_loc++ << ") in vec3 pr_normal;" << std::endl;
  }
  if (in_ctrl.texture) {
    ss << "layout(location = " << layout_loc++ << ") in vec2 pr_tex_coord;" << std::endl;
  }

  ss << std::endl;

  // define vertex shader outputs

  if (out_ctrl.position && false)  { ss << "out vec4 vs_position;"   << std::endl; }
  if (out_ctrl.color)     { ss << "out vec4 vs_color;"      << std::endl; }
  if (out_ctrl.normal && false)    { ss << "out vec3 vs_normal;"     << std::endl; }
  if (out_ctrl.texture && false)   { ss << "out vec2 vs_tex_coord;"  << std::endl; }

  ss << std::endl;

  // write vertex shader main function

  ss << "void main() {" << std::endl;
  ss << "gl_Position = MVP * pr_position;" << std::endl;

  if (out_ctrl.color) {
    if (in_ctrl.color) { ss << "\tvs_color = pr_color;" << std::endl; }
    else { ss << "\tvs_color = vec4(0.5,0.5,0.5,0.5)"; }
  }

  ss << "}" << std::endl;

  // PUT THINGS HERE

  // output result as an stl string
  std::cout << ss.str() << std::endl;
  return ss.str();
}

// INCOMPLETE, BUT NOT USED ANYWHERE YET
std::string ShaderWriter::GetFragmentShader(struct ShaderWriterControl in_ctrl, struct ShaderWriterControl out_ctrl) {
  std::stringstream ss;

  // specify shader version
  ss << "#version 330 core" << std::endl << std::endl;

  // REVISIT THESE THINGS

  if (in_ctrl.position)   { ss << "in vec4 vs_position;"   << std::endl; }
  if (in_ctrl.color)      { ss << "in vec4 vs_color;"      << std::endl; }
  if (in_ctrl.normal)     { ss << "in vec3 vs_normal;"     << std::endl; }
  if (in_ctrl.texture)    { ss << "in vec2 vs_tex_coord;"  << std::endl; }

  if (out_ctrl.position && false)  { ss << "out vec4 fs_position;"   << std::endl; }
  if (out_ctrl.color || true)     { ss << "out vec4 fs_color;"      << std::endl; }
  if (out_ctrl.normal && false)    { ss << "out vec3 fs_normal;"     << std::endl; }
  if (out_ctrl.texture)   { ss << "out vec2 fs_tex_coord;"  << std::endl; }

  // write fragment shader main function

  ss << "void main() {" << std::endl;

  if (in_ctrl.color) {
    ss << "\tfs_color = vs_color;" << std::endl;
  }
  else {
    ss << "\tfs_color = vec4(0.5,0.5,0.5,1);" << std::endl;
  }

  ss << "}" << std::endl;

  // PUT THINGS HERE

  // output result as an stl string
  std::cout << ss.str() << std::endl;
  return ss.str();
}
