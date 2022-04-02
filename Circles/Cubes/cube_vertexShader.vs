#version 330 core
layout (location=0) in vec3 Pos;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 texcoords;
out vec2 tex;
out vec3 outNormal;
out vec3 FragPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 Projection;
void main(){
     FragPos= vec3(model*vec4(Pos,1.0f));
    
    gl_Position=Projection*view*vec4(FragPos,1.0f);
    tex=texcoords;
    outNormal=mat3(transpose(inverse(model)))*normal;
}
