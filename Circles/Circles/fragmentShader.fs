#version 330 core
in vec2 texcoords;
out vec4 FragColor;
uniform sampler2D textures;
uniform vec3 objectColor;
uniform vec3 lightColor;
void main(){
    FragColor= vec4(lightColor* objectColor,1.0f);
}
