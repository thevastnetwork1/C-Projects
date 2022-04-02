#version 330 core
layout (location=0) in vec3 Pos;
layout (location=2) in vec3 Normals;
out vec3 normals;
out vec3 FragPos;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
void main(){
    FragPos= vec3(model * vec4(Pos,1.0f));
    gl_Position= projection * view * vec4(FragPos,1.0f);
    normals= mat3(transpose(inverse(model)))*Normals;
}
