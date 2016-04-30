#ifndef __GLSL_SHADER_WRITER_HPP__
#define __GLSL_SHADER_WRITER_HPP__

#include <string>
#include <sstream>

struct ShaderWriterControl {
  bool position; bool normal; bool texture; bool color;
  ShaderWriterControl(bool pos=true, bool col=true, bool norm=false, bool tex=false)
  { position = pos; color = col; normal = norm; texture = tex; }
};

class ShaderWriter {
public:
  static std::string GetVertexShader(struct ShaderWriterControl in_ctrl, struct ShaderWriterControl out_ctrl);
  static std::string GetFragmentShader(struct ShaderWriterControl in_ctrl, struct ShaderWriterControl out_ctrl);
};

#endif
