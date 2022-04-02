#version 330 core
out vec4 FragColor;
uniform vec3 Color;
in vec3 FragPos;
in vec3 normals;
uniform vec3 cameraPos;
uniform float ambient;
uniform float shininess;
uniform vec3 lightPos;
uniform float alpha;

void main(){
    
    vec3 norm= normalize(normals);
    vec3 lightDir= normalize(lightPos-FragPos);
    vec3 viewDir= normalize(cameraPos-FragPos);
    //ambient lighting
    vec3 ambient= ambient * Color;
    
    //diffuse lighting
    float diff= max(dot(norm,lightDir),0.0);
    vec3 diffuse= diff * Color;
    
    //specular highlights
    float specular_highlight=32.0f;
    vec3 reflectedVec= reflect(-lightDir,norm);
    float spec= pow(max(dot(viewDir,reflectedVec),0.0),shininess);
    vec3 specular= specular_highlight * spec * Color;
    
    FragColor.a= alpha;
    float Alpha = alpha;
    FragColor= vec4((ambient + diffuse + specular),Alpha);
}



