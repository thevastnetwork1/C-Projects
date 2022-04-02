#version 330 core
layout (location=0) in vec3 Pos;
layout (location=2) in vec2 TexCoords;
out vec2 texcoords;
uniform mat4 model;
uniform mat4 view;
uniform mat4 Projection;
void main(){
    gl_Position=Projection*view*model*vec4(Pos,1.0f);
    texcoords=TexCoords;
}
