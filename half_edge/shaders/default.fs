#version 330 core

// data flows in from the vertex shader
//in vec4 ex_color;

// data flows out to produce the final rendering
out vec4 out_color;

void main() {

  out_color = vec4(0.5,0.5,0.5,1.0);

}
