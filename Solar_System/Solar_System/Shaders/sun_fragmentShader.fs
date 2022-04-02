#version 330 core
out vec4 FragColor;
in vec2 texcoords;

uniform sampler2D Tex;

    


void main(){
    FragColor= vec4(0.8f,0.5f,0.0f,1.0f);

    
    
    
    FragColor= texture(Tex,texcoords);
}

