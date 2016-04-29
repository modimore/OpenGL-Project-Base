#ifndef __GLSL_SHADER_WRITER_HPP__
#define __GLSL_SHADER_WRITER_HPP__

#include <string>
#include <sstream>

struct ShaderWriterControl {
  bool position; bool normal; bool texture; bool color;
  ShaderWriterControl(pos=true,color=true,norm=false,tex=false)
  { position = pos; color = color; normal = norm; texture = tex; }
}

class ShaderWriter {
public:
  static std::string WriteVertexShader(struct ShaderWriterControl in_ctrl, struct ShaderWriterControl out_ctrl);
  static std::string WriteFragmentShader(struct ShaderWriterControl in_ctrl, struct ShaderWriterControl out_ctrl);
};
