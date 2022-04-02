#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/vec3.hpp>
#include <glm/glm/vec4.hpp>
#include <glm/glm/mat4x4.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include "Shaders.hpp"
#include <NEX_MATRIX/NEX_MATRIX.hpp>
#include "Cubes.hpp"
#include <stb_image/stb_image.h>

float deltaTime = 0.0f;
float lastFrame=0.0f;





//function for handling camera rotation
void Camera_Rotation(GLFWwindow* window, double xpos, double ypos){
    float xOffset,yOffset;
    if(firstMouse){
        lastX=xpos;
        lastY=ypos;
        firstMouse=false;
    }
    //calculate offsets
     xOffset= lastX-xpos;
     yOffset= ypos-lastY;
    lastX=xpos;
    lastY=ypos;
    
    
    float sensitivity= 0.1f;
    xOffset*=sensitivity;
    yOffset*=sensitivity;
    
    yaw+=xOffset;
    pitch+=yOffset;
    
    if(pitch>89.0f){
        pitch=89.0f;
    }else if(pitch<-89.0f){
        pitch=-89.0f;
    }
    
    glm::vec3 front;
    front.x= cos(glm::radians(yaw))* cos(glm::radians(pitch));
    front.y= sin(glm::radians(pitch));
    front.z= sin(glm::radians(yaw))* cos(glm::radians(pitch));
    cameraFront=glm::normalize(front);
    
}




//handling arrow key movement
void ProcessInput(GLFWwindow* window, int key, int scancode, int action, int mods){
   
    float  Camera_Speed=15.0f*deltaTime;
    //check to see which key is pressed and move accordingly
    if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS){
         cameraPos+= cameraFront*Camera_Speed;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
        cameraPos-= cameraFront*Camera_Speed;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS){
        cameraPos-= glm::normalize(glm::cross(cameraFront, cameraUp))*Camera_Speed;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT)==GLFW_PRESS){
        cameraPos+= glm::normalize(glm::cross(cameraFront, cameraUp))*Camera_Speed;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_PRESS){
        glfwTerminate();
    }
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
 
    GLFWwindow* window= glfwCreateWindow(1200, 700, "NEX_ENGINE_SCENE", glfwGetPrimaryMonitor(), NULL);
    if(!window){
        std::cout<<"ERROR COULD NOT CREATE WINDOW\n";
        return -1;
    }
    
     glfwMakeContextCurrent(window);
    int width,height;
    glfwGetFramebufferSize(window,&width , &height);
   
    
    glewExperimental=true;
    if(GLEW_OK==!glewInit()){
        std::cout<<"ERROR COULD NOT INITILIZE GLEW LIBRARY\n";
        return -1;
    }
    
 glEnable(GL_DEPTH_TEST);
    
    Shader regular_shader("/Users/manishkumarpatel/Desktop/C++/Circles/Cubes/cube_vertexShader.vs","/Users/manishkumarpatel/Desktop/C++/Circles/Cubes/cube_fragmentShader.fs");
    
    
    Shader light_shader("/Users/manishkumarpatel/Desktop/C++/Circles/Cubes/light_vertexShader.vs","/Users/manishkumarpatel/Desktop/C++/Circles/Cubes/light_fragmentShader.fs");
    
    
    //data objects
   unsigned int vao,vbo;
       glGenVertexArrays(1,&vao);
       glBindVertexArray(vao);

       glGenBuffers(1,&vbo);
       glBindBuffer(GL_ARRAY_BUFFER,vbo);
       glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    //attrib pointer
  
    GLuint position= glGetAttribLocation(regular_shader.ID,"Pos");
    glVertexAttribPointer(position,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(position);
    
    GLuint normals= glGetUniformLocation(regular_shader.ID,"normal");
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    

    
    
     //second cube
        unsigned int vao2,vbo2;
        glGenVertexArrays(1,&vao2);
        glBindVertexArray(vao2);
        
        glGenBuffers(1,&vbo2);
        glBindBuffer(GL_ARRAY_BUFFER,vbo2);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    
      GLuint position2= glGetAttribLocation(light_shader.ID,"Position");
        glVertexAttribPointer(position2,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
        glEnableVertexAttribArray(position2);
        
        
    
    
     unsigned int texture;
      glGenTextures(2, &texture);
      glActiveTexture(GL_TEXTURE0+1);
      glBindTexture(GL_TEXTURE_2D, texture);
      
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      
      int W,H,rnChannels;
     unsigned char* data= stbi_load("/Users/manishkumarpatel/Desktop/Avatar_Universe/AZULA.jpg", &W, &H, &rnChannels, 0);
      
      if(data){
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 500, 333, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
          glGenerateMipmap(GL_TEXTURE_2D);
      }else{
          std::cout<<"ERROR COULD NOT LOAD IN IMAGE\n";
          glfwTerminate();
          return -1;
      }
      stbi_image_free(data);
    
    
    
    
    
    NEX_MATRIX::Math Operations;
    NEX_MATRIX::matrix<float>Projection_Matrix(4,4);
    
    NEX_MATRIX::matrix<float>View_Matrix(4,4);
    
    NEX_MATRIX::matrix<float>Model_Matrix(4,4);
    
    
    glViewport(0, 0, width, height);
    
    
    glfwSetKeyCallback(window, ProcessInput);
    glfwSetCursorPosCallback(window, Camera_Rotation);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    
    //declare the light position vector for later use in the fragment shader
  regular_shader.Use(1);
    regular_shader.setVec3("lightPos", lightPos);
    regular_shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    regular_shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    regular_shader.setVec3("cameraPos", cameraPos);
    //render loop
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        
        
                float currentFrame = glfwGetTime();
               deltaTime = currentFrame - lastFrame;
               lastFrame = currentFrame;
        
          
        glClearColor(0.1f,0.02f,0.02f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

       
   
            for(int j=0;j<4;j++){
                for(int k=0;k<4;k++){
                    Projection_Matrix.mat[j][k]=Identity_matrix[j][k];
                    View_Matrix.mat[j][k]=Identity_matrix[j][k];
                    Model_Matrix.mat[j][k]=Identity_matrix[j][k];
                }
            }
            
            NEX_MATRIX::vec<float>Translation(3);
            Translation.arr[0]=0.0f;
            Translation.arr[1]=1.0f;
            Translation.arr[2]=0.0f;
            
            NEX_MATRIX::vec<float>Rotation(3);
            Rotation.arr[0]=0.0f;
            Rotation.arr[1]=1.5f;
            Rotation.arr[2]=0.0f;
            

            
            Projection_Matrix=Operations.set_Perspective_Projection(Operations.Radians(45.0f),(float)1200/(float)700 , 0.1f, 100.0f);
            float projection[4][4];
        
        
            View_Matrix= Operations.Translate(View_Matrix, Translation);
            float view[4][4];
            
            Model_Matrix= Operations.Rotation(Model_Matrix, (float)glfwGetTime(), Rotation);
            float modell[4][4];
            
            
            for(int j=0;j<4;j++){
                for(int k=0;k<4;k++){
                    projection[j][k]=Projection_Matrix.mat[j][k];
                    view[j][k]=View_Matrix.mat[j][k];
                    modell[j][k]=Model_Matrix.mat[j][k];
                }
            }

        glm::mat4 Views;
        Views= glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
        
                 

            
        
        
        regular_shader.setMat4("view", Views);
        regular_shader.setMat4("Projection", projection);
             glm::mat4 Model = glm::mat4(1.0f);
          regular_shader.setMat4("model", Model);
        regular_shader.setVec3("material.ambient",1.0f, 0.5f, 0.31f);
     regular_shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
     regular_shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
     regular_shader.setFloat("material.shininess", 32.0f);
        
             glm::vec3 varying_color;
             varying_color.x= sin(glfwGetTime()*2.0f);
             varying_color.y= sin(glfwGetTime()* 0.7f);
             varying_color.z= sin(glfwGetTime()* 1.3f);
             glm::vec3 diffuse_color= varying_color* glm::vec3(0.5f);
             glm::vec3 ambient_color= varying_color* glm::vec3(0.2f);
    regular_shader.setVec3("light.ambient", ambient_color);
    regular_shader.setVec3("light.diffuse",diffuse_color);
    regular_shader.setVec3("light.specular",1.0f, 1.0f, 1.0f);
    
        
       
        
        
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        

        
            light_shader.Use(1);

    light_shader.setMat4("Projection", projection);
  
        //calculate the radius and the circumfrence of the camera viewer respect tot the fragment of the object
        
        
        light_shader.setMat4("View", Views);
  
        //calculate orbital translation
        float Xpos= sin((float)glfwGetTime());
        float Ypos=-0.3f;
        float Zpos= -1.5*cos((float)glfwGetTime());
        //update light_fragmentShader with vec3 lightPOs
        glm::vec3 orbital_trsnslation(Xpos,Ypos,Zpos);
    
        Model = glm::translate(Model,lightPos );
        Model = glm::scale(Model, glm::vec3(0.2f)); // a smaller cube
        glm::vec3 rotate(0.5f,1.5f,1.0f);
        Model= glm::rotate(Model, (float)glfwGetTime(),rotate );
        
      
        light_shader.setMat4("Model",Model);
  
        
        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        regular_shader.Use(1);
        //regular_shader.setVec3("lightPos",lightPos );
        //regular_shader.setMat4("model", Model);
        
        
        glfwSwapBuffers(window);
 
    }
    glDeleteVertexArrays(1,&vao);
    glDeleteVertexArrays(1,&vao2);
    glDeleteBuffers(1,&vbo2);
    glDeleteBuffers(1,&vbo);

    
    glfwTerminate();
    
    return 0;
}
