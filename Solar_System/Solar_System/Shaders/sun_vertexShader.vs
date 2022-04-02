#version 330 core
layout (location=0) in vec3 Pos;
layout (location=1) in vec2 TexCoords;
out vec2 texcoords;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
void main(){
    gl_Position= Projection * View * Model * vec4(Pos,1.0);
    texcoords=TexCoords;
}
