#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <NEX_MATRIX/NEX_MATRIX.hpp>
#include <Shaders.hpp>
//#include <Model_Loading/Model/Model.hpp>
#include <stb/stb_image.h>
#include "Utilities.hpp"
#define SCR_WIDTH 1200
#define SCR_HEIGHT 700

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window=glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"NEX_SOLAR_SYSTEM_SCENE",NULL,NULL);
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
    
    
    Shader sun_shader("/Users/manishkumarpatel/Desktop/C++/Solar_System/Solar_System/Shaders/sun_vertexShader.vs","/Users/manishkumarpatel/Desktop/C++/Solar_System/Solar_System/Shaders/sun_fragmentShader.fs");
    
    Shader planet_shader("/Users/manishkumarpatel/Desktop/C++/Solar_System/Solar_System/Shaders/planet_vertexShader.vs","/Users/manishkumarpatel/Desktop/C++/Solar_System/Solar_System/Shaders/planet_fragmentShader.fs");
    
    
    int W,H,rnChannels;
    unsigned int texture= LoadTexture(0, W,H ,rnChannels);
    
    NEX_MATRIX::Math Operations;
    std::vector<std::vector<float> >Sphere_data;
    Sphere_data= Create_Sphere(1200/2, 700/2, 50, 120.0f, 36, 18);
    // Sphere_data= Operations.Draw_3D_Sphere(1200/2, 700/2, 50, 120.0f, 36, 18);
    int size= Sphere_data[0].size();
    float data[size];
  
    for(int i=0;i<Sphere_data[0].size();i++){
        data[i]=Sphere_data[0][i];
    }
    
   
        //data structure objects
      unsigned int vao,vbo;
      glGenVertexArrays(1,&vao);

      
      glGenBuffers(1,&vbo);

      
    Bind_Sphere(vao, vbo, Sphere_data[0]);

    
          //pointers
    GLuint position= glGetAttribLocation(sun_shader.ID,"Pos");
    glVertexAttribPointer(position,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(position);
    
    GLuint texcoords= glGetAttribLocation(sun_shader.ID,"TexCoords");
    glVertexAttribPointer(texcoords,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(texcoords);
    //
    
    
    std::vector<std::vector<float> >planet;
    planet= Create_Sphere(1200/2+900, 700/2, 50, 60.0f, 36, 18);
    int size2= planet[0].size();
    
    unsigned int vao2, pvbo1;
    glGenVertexArrays(1,&vao2);
    
    glGenBuffers(1,&pvbo1);
    
    Bind_Sphere(vao2,pvbo1,planet[0]);

    
    position= glGetAttribLocation(planet_shader.ID,"Pos");
    glVertexAttribPointer(position,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(position);
    //3
    GLuint normals= glGetAttribLocation(planet_shader.ID,"Normals");
    glVertexAttribPointer(normals,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(normals);
    
    
    
    NEX_MATRIX::matrix<float>Projection(4,4);
    NEX_MATRIX::matrix<float>View(4,4);
    NEX_MATRIX::matrix<float>Model(4,4);
    
    glfwSetKeyCallback(window, Process_Key_Input);
    glfwSetCursorPosCallback(window, Rotate_Scene_Camera);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    float x;
    float z;
    float dx;
    float dz;
    
    
    glViewport(0, 0, width, height);
    
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        
        float currentFrame= glfwGetTime();
        delta_Time= currentFrame-lastFrame;
        lastFrame=currentFrame;
        
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                Projection.mat[i][j]=Identity_Matrix[i][j];
                View.mat[i][j]=Identity_Matrix[i][j];
                Model.mat[i][j]=Identity_Matrix[i][j];
            }
        }
        
         NEX_MATRIX::vec<float>Rotation(3);
            Rotation.arr[0]=0.5f;
            Rotation.arr[1]=0.5f;
            Rotation.arr[2]=1.0f;
        NEX_MATRIX::vec<float>Translation(3);
            Translation.arr[0]=1.0f;
            Translation.arr[1]=1.0f;
            Translation.arr[2]=-200.0f;
        
        Projection= Operations.set_Perspective_Projection(Operations.Radians(45.0f), float(SCR_WIDTH)/float(SCR_HEIGHT), 0.1f, 100.0f);
        float projection[4][4];
        View= Operations.Translate(View, Translation);
        float view[4][4];
        
        Model= Operations.Rotation(Model, (float)glfwGetTime(), Rotation);
        NEX_MATRIX::Quaternion<float> Q(0.5f,0.5f,1.0f,float(45.0f));
        
        float model[4][4];
        //implememt orientation quaternion around model matrix diagonal and rotate from other quaternions from there;
      

        //Model= Operations.Rotate_With_Quaternion(Model,Q);
        
        
        
       // Model= Operations.Translate(Model, Translation);
        
        NEX_MATRIX::vec<float>svec(3);
        svec.arr[0]=0.2f;
        svec.arr[1]=0.2f;
        svec.arr[2]=0.2f;
        Model= Operations.Scale_Matrix(Model,svec );
        
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
      
                projection[i][j]=Projection.mat[i][j];
                view[i][j]=View.mat[i][j];
                model[i][j]=Model.mat[i][j];
               
            }
        }
        
        glm::mat4 Views(1.0f);
        Views=glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
        
        sun_shader.Use(1);
        sun_shader.setMat4("Projection", projection);
        sun_shader.setMat4("View", Views);
        sun_shader.setMat4("Model", model);
        
      
       
      //  glActiveTexture(GL_TEXTURE0);
      //  glBindTexture(GL_TEXTURE_2D, texture);
      //  sun_shader.SetINT("Tex", 0);
        
       
        
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0, (unsigned int)size);

        planet_shader.Use(1);
        
        planet_shader.setVec3("cameraPos",cameraPos);
        planet_shader.setVec3("lightPos", lightPos);
    //    planet_shader.setVec3("material.ambient", glm::vec3(0.3f,0.4f,0.5f));
    //    planet_shader.setVec3("material.diffuse", glm::vec3(0.2f,0.9f,0.8f));
    //    planet_shader.setVec3("material.specular", glm::vec3(1.0f,1.0f,1.0f));
        planet_shader.SetFLOAT("shininess", 32.0f);
        planet_shader.SetFLOAT("ambient", 0.1f);
      //  planet_shader.setVec3("dirlight.diffuse", glm::vec3(0.3f,0.6f,0.9f));
       // planet_shader.setVec3("dirlight.specular", glm::vec3(1.0f,1.0f,1.0f));
        
        
        planet_shader.setMat4("Projection", projection);
        planet_shader.setMat4("View", Views);
        glm::mat4 models(1.0f);
        dx=170.0f;dz=160.0f;
       x=cos(glfwGetTime()*0.7f)*dx;
       z= sin(glfwGetTime()*0.7f)*dz;
        models= set_planet_orbit(models,x , 1.0f,z);
        models= glm::scale(models,glm::vec3(0.2f));
      
        
        planet_shader.setMat4("Model", models);
        planet_shader.setVec3("Color", glm::vec3(0.9f,0.1f,0.2f));
        
        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLE_FAN, 0,size2);
        
        
        //draw 2 planet
        glm::mat4 model2(1.0f);
 
          model2= glm::scale(model2, glm::vec3(0.1f));
        dx=1500.0f;dz=1200.0f;
        x=cos(glfwGetTime()*0.5f)*dx;
        z=sin(glfwGetTime()*0.5f)*dz;
        model2=set_planet_orbit(model2, x, 0.0f, z);
      
        
        planet_shader.setMat4("Model", model2);
        planet_shader.setVec3("Color", glm::vec3(0.7f,0.4f,0.5f));
        
        glDrawArrays(GL_TRIANGLE_FAN, 0, size2);
        
        //planet 3
        dx=1100.0f;dz=1200.0f;
        x= cos(glfwGetTime()*0.2f)* dx;
        z= sin(glfwGetTime()*0.2f)* dz;
        glm::mat4 model3(1.0f);
        model3= glm::scale(model3, glm::vec3(0.2f));
        model3= set_planet_orbit(model3, x, 0.0f, z);
        planet_shader.setMat4("Model", model3);
        planet_shader.setVec3("Color", glm::vec3(0.3f,0.4f,0.5f));
        glDrawArrays(GL_TRIANGLE_FAN, 0, size2);
        
        //planet 4
        dx=150.0f;dz=180.0f;
        x= cos(glfwGetTime()*0.9f)* dx;
        z= sin(glfwGetTime()*0.9f)* dz;
        model3= glm::scale(model3, glm::vec3(0.7f));
        model3= set_planet_orbit(model3, x, 0.0f, z);
        planet_shader.setMat4("Model", model3);
        planet_shader.setVec3("Color", glm::vec3(0.2f,1.0f,0.4f));
        glDrawArrays(GL_TRIANGLE_FAN, 0, size2);
        
        //planet 5
        dx= 610.0f;dz=630.0f;
        x= cos(glfwGetTime()*0.7f)* dx;
        z= sin(glfwGetTime()*0.7f)* dz;
        model3= glm::scale(model3, glm::vec3(0.4f));
        model3= set_planet_orbit(model3, x, 0.0f, z);
        planet_shader.setMat4("Model", model3);
        planet_shader.setVec3("Color", glm::vec3(0.4f,0.34f,0.9f));
        glDrawArrays(GL_TRIANGLE_FAN, 0, size2);
        
        //planet 6
        dx= 1000.0f;dz= 1200.0f;
        x= cos(glfwGetTime()*0.1f)* dx;
        z= sin(glfwGetTime()*0.1f)* dz;
        model3= glm::scale(model3, glm::vec3(0.7f));
        model3= set_planet_orbit(model3, x, 0.0f, z);
        planet_shader.setMat4("Model", model3);
        planet_shader.setVec3("Color", glm::vec3(0.5f,0.324f,0.754f));
        glDrawArrays(GL_TRIANGLE_FAN, 0, size2);
        
        //planet 7
        dx= 1300.0f;dz=1500.0f;
        x= cos(glfwGetTime()*0.6f)* dx;
        z= sin(glfwGetTime()*0.6f)* dz;
        model3= glm::scale(model3, glm::vec3(0.9f));
        model3= set_planet_orbit(model3, x, 0.0f, z);
        planet_shader.setMat4("Model", model3);
        planet_shader.setVec3("Color", glm::vec3(0.9f,1.0f,1.0f));
        glDrawArrays(GL_TRIANGLE_FAN,0,size2);

        //planet 8
        dx= 1800.0f;dz= 1800.0f;
        x= cos(glfwGetTime()*0.2f)* dx;
        z= sin(glfwGetTime()*0.2f)*dz;
        model3= glm::scale(model3, glm::vec3(2.0f));
        model3= set_planet_orbit(model3, x, 0.0f, z);
        planet_shader.setMat4("Model", model3);
        planet_shader.setVec3("Color", glm::vec3(0.0f,1.0f,1.0f));
        glDrawArrays(GL_TRIANGLE_FAN, 0, size2);
        
        //planet 9
        dx= 2100.0f;dz=2200.0f;
        x= cos(glfwGetTime()*0.1f)* dx;
        z= sin(glfwGetTime()*0.1f)* dz;
        model3= glm::scale(model3, glm::vec3(0.9f));
        model3= set_planet_orbit(model3, x, 0.0f, z);
        planet_shader.setMat4("Model", model3);
        planet_shader.setVec3("Color", glm::vec3(0.5f,0.23f,0.98f));
        glDrawArrays(GL_TRIANGLE_FAN, 0, size2);
        
        //render the Model using Model class
       // Model model("/Users/manishkumarpatel/Downloads/survival-guitar-backpack-low-poly");
        
        
        
        glfwSwapBuffers(window);
        
    }
    Delete_Sphere(vao, vbo);
    Delete_Sphere(vao2, pvbo1);
    glDeleteTextures(1, &texture);
    
    glfwTerminate();
    
    
    return 0;
}
