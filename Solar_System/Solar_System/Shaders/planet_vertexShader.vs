#version 330 core
layout (location=0) in vec3 Pos;
layout (location=1) in vec3 Normals;
out vec3 normals;
out vec3 FragPos;
uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;
void main(){
    FragPos= vec3(Model * vec4(Pos,1.0f));
    gl_Position= Projection * View * vec4(FragPos,1.0f);
    normals= mat3(transpose(inverse(Model)))*Normals;
}
