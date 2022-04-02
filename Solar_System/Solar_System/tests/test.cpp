#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <Shaders.hpp>
#include <NEX_MATRIX/NEX_MATRIX.hpp>
//#include <Model_Loading/Model/Model.hpp>
#include <stb/stb_image.h>
#include "Utilities.hpp"
#include "reflections.hpp"
#define SCR_WIDTH 1200
#define SCR_HEIGHT 700

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window= glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "NEX_ENGINE", NULL, NULL);
    if(!window){
        std::cout<<"ERROR COULD NOT CREATE WINDOW\n";
        glfwTerminate();
        return -1;
    }
    int width,height;
    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window,&width,&height);
    
    glewExperimental=true;
    if(GLEW_OK==!glewInit()){
        std::cout<<"ERROR COULD NOT LOAD GLEW LIBRARY\n";
        glfwTerminate();
        return -1;
    }
    
 NEX_MATRIX::Math Operations;
    
    Shader floor_shader("/Users/manishkumarpatel/Desktop/C++/Solar_System/Solar_System/tests/floor_vertexShader.vs","/Users/manishkumarpatel/Desktop/C++/Solar_System/Solar_System/Shaders/planet_fragmentShader.fs");
    
    unsigned int vao,vbo;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    //pointers
    GLuint position= glGetAttribLocation(floor_shader.ID,"Pos");
    glVertexAttribPointer(position,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(position);
    
    GLuint texcoords= glGetAttribLocation(floor_shader.ID,"TexCoords");
    glVertexAttribPointer(texcoords,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(texcoords);
    
    GLuint normals= glGetAttribLocation(floor_shader.ID,"Normals");
    glVertexAttribPointer(normals,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(5*sizeof(float)));
    glEnableVertexAttribArray(normals);
    //
    
    
    //sphere configurations
    std::vector<std::vector<float> >Sphere_data;
    Sphere_data= Operations.Draw_3D_Sphere(SCR_WIDTH/2, SCR_HEIGHT/2, 50, 60.0f, 36, 18);
    int size= Sphere_data[0].size();
    float sphere_vertices[size];
    for(int i=0;i<size;i++){
        sphere_vertices[i]=Sphere_data[0][i];

    }
    
    
    
    unsigned int vao2,vbo2;
    
    glGenVertexArrays(1,&vao2);
    glBindVertexArray(vao2);
    
    glGenBuffers(1,&vbo2);
    glBindBuffer(GL_ARRAY_BUFFER,vbo2);
    glBufferData(GL_ARRAY_BUFFER,sizeof(sphere_vertices),sphere_vertices,GL_STATIC_DRAW);
   
    glVertexAttribPointer(position,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(position);
    
    //glVertexAttribPointer(normals,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    //glEnableVertexAttribArray(normals);
   
    
    
    
    NEX_MATRIX::matrix<float>projection(4,4);
    NEX_MATRIX::matrix<float>view(4,4);
    NEX_MATRIX::matrix<float>model(4,4);
    
    glfwSetKeyCallback(window, Process_Key_Input);
    glfwSetCursorPosCallback(window, Rotate_Scene_Camera);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    
    glViewport(0,0, width, height);
    
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    
        //set delta time
        float currentFrame= glfwGetTime();
        delta_Time= currentFrame - lastFrame;
        lastFrame= currentFrame;
        
      
        
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //
        for(int i=0;i<4;i++){
            for(int k=0;k<4;k++){
                projection.mat[i][k]=Identity_Matrix[i][k];
                view.mat[i][k]=Identity_Matrix[i][k];
                model.mat[i][k]=Identity_Matrix[i][k];
            }
        }
        
              NEX_MATRIX::vec<float>Rotation(3);
              Rotation.arr[0]=0.5f;
              Rotation.arr[1]=0.5f;
              Rotation.arr[2]=1.0f;
              NEX_MATRIX::vec<float>Translation(3);
              Translation.arr[0]=1.0f;
              Translation.arr[1]=1.0f;
              Translation.arr[2]=-2.0f;
        
        projection= Operations.set_Perspective_Projection(Operations.Radians(45.0f), float(SCR_WIDTH)/float(SCR_HEIGHT), 0.1f, 100.0f);
        float Projection[4][4];
        //view= Operations.Translate(view, Translation);
        //float View[4][4];
        ///model= Operations.Rotation(model, float(glfwGetTime()), Rotation);
        glm::mat4 Model(1.0f);
        Model= glm::scale(Model, glm::vec3(200.0f,1.0f,200.0f));
        //float Model[4][4];
        
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                Projection[i][j]=projection.mat[i][j];
          //      View[i][j]= view.mat[i][j];
          //      Model[i][j]= model.mat[i][j];
            }
        }
        //
        
        glm::mat4 Views= glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
        
        //enable stencil test
        glEnable(GL_STENCIL_TEST);
         glStencilFunc(GL_ALWAYS, 1, 0xffffffff);
        glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    
        
        floor_shader.Use(1);
        floor_shader.setMat4("projection", Projection);
      
        floor_shader.setMat4("view", Views);
        floor_shader.setVec3("cameraPos", cameraPos);
        floor_shader.setVec3("lightPos", lightPos);
        floor_shader.SetFLOAT("ambient",1.0f);
        floor_shader.SetFLOAT("shininess",32.0f);
  
        glDisable(GL_DEPTH_TEST);
        
        
           floor_shader.setVec3("Color", glm::vec3(0.0f,1.0f,0.0f));
             glm::mat4 new_model(1.0f);
        glm::vec3 sphere_translation(0.0f,-100.0f,0.0f);
        new_model= glm::translate(new_model, sphere_translation);
             floor_shader.setMat4("model", new_model);
        floor_shader.SetFLOAT("alpha", 1.0f);
        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLE_FAN, 0, size);
        //draw reflection
    
        
          glStencilFunc(GL_EQUAL, 1, 0xffffffff);  /* draw if stencil ==1 */
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        //blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.7, 0.0, 0.0, 0.40);
            drawReflection(new_model, sphere_translation, GL_TRIANGLE_FAN, size,floor_shader);
             glDisable(GL_STENCIL_TEST);
        
          floor_shader.SetFLOAT("alpha",0.2f);
          floor_shader.setVec3("Color", glm::vec3(1.0f,0.00f,0.00f));
            floor_shader.setMat4("model", Model);
        
              glBindVertexArray(vao);
              glDrawArrays(GL_TRIANGLES, 0, 36);
        
       
        //disable blend after drawing floor
              glDisable(GL_BLEND);
         
            
        
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
