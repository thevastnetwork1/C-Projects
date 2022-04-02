#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Work.hpp"
#include "Shaders.hpp"
#include <stb_image/stb_image.h>
#include <NEX_MATRIX/NEX_MATRIX.hpp>


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
     yOffset= lastY-ypos;
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



void Process_Input(GLFWwindow* window, int key, int scancode, int action, int mods){
    float cameraSpeed=10.0f;
    //handle input
    if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS){
        cameraPos+= cameraFront*cameraSpeed;
    }else if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
        cameraPos-= cameraFront*cameraSpeed;
    }else if(glfwGetKey(window, GLFW_KEY_LEFT)==GLFW_PRESS){
        cameraPos+= glm::normalize(glm::cross(cameraFront, cameraUp))*cameraSpeed;
    }else if(glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS){
        cameraPos-= glm::normalize(glm::cross(cameraFront,cameraUp))*cameraSpeed;
    }else if(glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_PRESS){
        glfwTerminate();
    }

}


int main(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    GLFWwindow* window= glfwCreateWindow(1200, 700, "NEX_ENGINE", NULL, NULL);
    
    if(!window){
        std::cout<<"ERROR COULD NOT CREATE WINDOW\n";
        glfwTerminate();
        return -1;
    }
    
    int width,height;
    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &width, &height);
 
    
    glewExperimental=true;
    
    if(GLEW_OK==!glewInit()){
        std::cout<<"ERROR COULD NOT LOAD GLEW LIBRARY\n";
        glfwTerminate();
        return -1;
    }
    
    //instantiate shader
    Shader shader("/Users/manishkumarpatel/Desktop/C++/Circles/Circles/vertexShader.vs","/Users/manishkumarpatel/Desktop/C++/Circles/Circles/fragmentShader.fs");
    
    Shader light_shader("/Users/manishkumarpatel/Desktop/C++/Circles/Circles/Light_Shader/light_vertexShader.vs","/Users/manishkumarpatel/Desktop/C++/Circles/Circles/Light_Shader/light_fragment_shader.fs");
    
    
    std::vector<std::vector<float> >Result;
    Result=Draw_3D_Sphere(1200/2, 700/2, 50, 120.0f, 36, 18);
  std::size_t size1= Result[0].size();
  std::size_t size2= Result[1].size();
  float vertices_new[size1];
  float indicies_new[size2];
  
  for(int j=0;j<size1;j++){
      vertices_new[j]=Result[0][j];
  }
  for(int k=0;k<size2;k++){
      indicies_new[k]=Result[1][k];
  }
    
    
    //defining data objects
    unsigned int vao,vbo,ebo;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices_new),vertices_new,GL_STATIC_DRAW);
    
    //setting up the pointers
    GLuint position= glGetAttribLocation(shader.ID,"Pos");
    glVertexAttribPointer(position,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(position);
    

    
    //create a new vertex array for the light source
    std::vector<std::vector<float> >Result2;
    Result2= Draw_3D_Sphere(1200/2, 700/2, 50, 50, 36, 18);
    std::size_t size11= Result2[0].size();
    std::size_t size22= Result[1].size();
    float newer_vertices[size11];
    for(int j=0;j<size11;j++){
        newer_vertices[j]=Result[0][j];
    }
    
    
    
    unsigned int vao2,vbo2;
    glGenVertexArrays(1,&vao2);
    
    glBindVertexArray(vao2);
    //vbo buffer already contains the necessary data
    glGenBuffers(1,&vbo2);
    glBindBuffer(GL_ARRAY_BUFFER,vbo2);
    glBufferData(GL_ARRAY_BUFFER,sizeof(newer_vertices),newer_vertices,GL_STATIC_DRAW);
    
    GLuint position2= glGetUniformLocation(light_shader.ID,"Pos");
    glVertexAttribPointer(position2,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(position2);
    
    
    unsigned int texture;
    glGenTextures(2, &texture);
    glActiveTexture(GL_TEXTURE0+1);
    glBindTexture(GL_TEXTURE_2D, texture);
    
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
     
    
    //load in image
    int W,H,rnChannels;
    unsigned char* data= stbi_load("/Users/manishkumarpatel/Desktop/rgb.jpg", &W, &H, &rnChannels, 0);
    
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 960, 540, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout<<"ERROR COULD NOT LOAD IN TEXTURE\n";
        glfwTerminate();
        return -1;
    }
    stbi_image_free(data);
    
    
    NEX_MATRIX::Math Operations;
    
    NEX_MATRIX::matrix<float>Projection(4,4);
    
    NEX_MATRIX::matrix<float>Model_Matrix(4,4);
    
    NEX_MATRIX::matrix<float>View_Matrix(4,4);
    
    
    glViewport(0,0, width, height);
    
    /* glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
       glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
       glOrtho( 0, 1200, 0, 700, 0, 1 ); // essentially set coordinate system
       glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
       glLoadIdentity( ); // same as above comment*/
    
    
    glfwSetKeyCallback(window, Process_Input);
    glfwSetCursorPosCallback(window, Camera_Rotation);
    
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0f,0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
         
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
                Projection.mat[j][k]=Identity[j][k];
                Model_Matrix.mat[j][k]=Identity[j][k];
                View_Matrix.mat[j][k]=Identity[j][k];
            }
        }
        
        NEX_MATRIX::vec<float>Translation(3);
        NEX_MATRIX::vec<float>Rotation(3);
        
        Translation.arr[0]=-40.0f;
        Translation.arr[1]=0.0f;
        Translation.arr[2]=-200.0f;
        
        Rotation.arr[0]=1.0f;
        Rotation.arr[1]=0.5f;
        Rotation.arr[2]=0.5f;
        
        
        Projection= Operations.set_Perspective_Projection(Operations.Radians(45.0f), (float)1200/(float)700, 0.1f, 100.0f);
        float projection[4][4];
        
        Model_Matrix= Operations.Rotation(Model_Matrix, (float)45, Rotation);
        float rotation[4][4];
        
        View_Matrix= Operations.Translate(View_Matrix, Translation);
        float translate[4][4];
        
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
                projection[j][k]=Projection.mat[j][k];
                rotation[j][k]= Model_Matrix.mat[j][k];
                translate[j][k]=View_Matrix.mat[j][k];
            }
        }
        
        //camera movement
        glm::mat4 Views;
        Views= glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
        
            shader.Use(1);
        unsigned int mod_loc= glGetUniformLocation(shader.ID,"model");
        unsigned int view_loc= glGetUniformLocation(shader.ID,"view");
        unsigned int proj_loc= glGetUniformLocation(shader.ID,"Projection");
        //unsigned int tex_loc= glGetUniformLocation(shader.ID,"textures");
        
        glm::mat4 model2= glm::mat4(planet_pos);
        
        glUniformMatrix4fv(mod_loc,1,GL_FALSE,&rotation[0][0]);
        glUniformMatrix4fv(view_loc,1,GL_FALSE,&Views[0][0]);
        glUniformMatrix4fv(proj_loc,1,GL_FALSE,&projection[0][0]);
        shader.setVec3("objectColor", 1.0f,0.5f,0.31f);
        shader.setVec3("lightColor", 1.0f,1.0f,1.0f);
        
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0,(unsigned int)size1);
        
        light_shader.Use(1);
        glm::mat4 moodel= glm::mat4(1.0f);
        moodel= glm::scale(moodel, glm::vec3(5.0f));
        

        
        light_shader.setMat4("model", moodel);
        light_shader.setMat4("view",Views);
        light_shader.setMat4("Projection", projection);
        
       // glBindVertexArray(vao2);
          glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0, (unsigned int)size1);
    
        glfwSwapBuffers(window);
    }
    glDeleteBuffers(1,&vbo);
    glDeleteBuffers(1,&ebo);
    glDeleteVertexArrays(1,&vao);
    glDeleteVertexArrays(1,&vao2);

    glfwTerminate();
    
    return 0;
    
}
