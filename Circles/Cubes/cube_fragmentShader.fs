#version 330 core
out vec4 FragColor;
in vec3 outNormal;
in vec3 FragPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 Position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
void main(){
    float ambientStrength = 0.1f;
    vec3 ambient = material.ambient * light.ambient;
    // diffuse
    vec3 norm = normalize(outNormal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff*material.diffuse) * light.diffuse;
    //view reflection
    float specular_intensity=0.5;
    vec3 camera_direction= normalize(cameraPos-FragPos);
    vec3 reflection= reflect(-lightDir,norm);
    
    float spec= pow(max(dot(reflection,camera_direction),0.0),material.shininess);
    vec3 specular_light= (material.specular*spec)*light.specular;
  
    vec3 result = (ambient + diffuse + specular_light) * objectColor;
    FragColor = vec4(result, 1.0);
}
