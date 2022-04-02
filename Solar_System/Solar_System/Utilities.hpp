#include <iostream>
#include <glew.h>
#include <glfw3.h>


float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,    0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,    0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,    0.0f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,    0.0f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,    0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f, 1.0f,
    
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
    
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,  0.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,    1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,    1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,    1.0f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,    1.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,    1.0f,  0.0f,  0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,    0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,    0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,    0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,    0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,    0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,    0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f,  0.0f
    
};

float Identity_Matrix[][4]{
    1.0f,0.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,0.0f,
    0.0f,0.0f,1.0f,0.0f,
    0.0f,0.0f,0.0f,1.0f
};



unsigned int LoadTexture(int offset,int W,int H,int rnChannels){
    
    unsigned int texture;
    glGenTextures(1,&texture);
    glActiveTexture(GL_TEXTURE0+offset);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    
    unsigned char* data=
    stbi_load("/Users/manishkumarpatel/Desktop/Avatar_Universe/Avatar_data2.jpg", &W, &H, &rnChannels, 0);
    if(!data){
        std::cout<<"ERROR WHILE LOADING TEXTURE\n";
        glfwTerminate();
        return -1;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 640, 400, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    
    return texture;
}
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);


//yaw and pitch values;
float yaw=-90.0f;
float pitch;
float lastX=600;
float lastY=350;

bool firstMouse=true;

glm::vec3 lightPos(1.2f, -2.0f, 0.5f);
//1.2f,-2.0f,0.5f;


float delta_Time;
float lastFrame;

void Process_Key_Input(GLFWwindow* window, int key,int scancode, int action, int mods){
    float camera_speed=30.0f*delta_Time;
    
    if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS)
        cameraPos+= cameraFront*camera_speed;
    else if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS)
        cameraPos-= cameraFront*camera_speed;
    else if(glfwGetKey(window, GLFW_KEY_LEFT)==GLFW_PRESS)
        cameraPos+= glm::normalize(glm::cross(cameraFront, cameraUp))*camera_speed;
    else if(glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS)
        cameraPos-= glm::normalize(glm::cross(cameraFront, cameraUp))*camera_speed;
    else if(glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_PRESS)
        glfwTerminate();
}

void Rotate_Scene_Camera(GLFWwindow* window,double xpos,double ypos){
    if(firstMouse){
        lastX=xpos;
        lastY=ypos;
        firstMouse=false;
    }
    
    float Xoffset= lastX-xpos;
    float Yoffset= ypos-lastY;
    lastX= xpos;
    lastY= ypos;
    
    
    float sensitivity=0.1f;
    Xoffset*=sensitivity;
    Yoffset*=sensitivity;
    
    yaw+=Xoffset;
    pitch+=Yoffset;
    
    if(pitch>89.0f)
        pitch=89.0f;
    else if(pitch<-89.0f)
        pitch=-89.0f;
    
    glm::vec3 front;
    front.x= cos(glm::radians(yaw))*cos(glm::radians(pitch));
    front.y= sin(glm::radians(pitch));
    front.z= sin(glm::radians(yaw))*cos(glm::radians(pitch));
    cameraFront= glm::normalize(front);

}



std::vector<std::vector<float> >Create_Sphere(GLfloat x,GLfloat y,GLfloat z,GLfloat radius,GLint sectors_num,GLint stack_num){
    NEX_MATRIX::Math Operations;
    return Operations.Draw_3D_Sphere(x, y, z, radius, sectors_num, stack_num);
}


void Bind_Sphere(unsigned int vao,unsigned int vbo,std::vector<float>sphere){
    glBindVertexArray(vao);
    
    int size= sphere.size();
    float data[size];
    for(int i=0;i<size;i++){
        data[i]=sphere[i];
    }
    
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(data),data,GL_STATIC_DRAW);
    
}

void Delete_Sphere(unsigned int vao,unsigned int vbo){
    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vbo);
}


template <typename T>
glm::mat4  set_planet_orbit(glm::mat4 model,T x,T y,T z ){
    model= glm::translate(model, glm::vec3(x,y,z));
    return model;
}
