#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <stb/stb_image.h>

#pragma once
class Game{
public:
    //init new game
    Game(){
        
    }

public:
    
    //base functionality goes here
//texture count to keep track of the texture numbers
    int texture_count;//shows current texture number
 
    
    GLFWwindow* window;
    
    //Init glfw
    void InitGlfw(float red,float green,float blue,int SrW,int SrH){
        glfwInit();
        
    }
    
    void InitWindow(int W,int H){
        window= glfwCreateWindow(W, H, "SquareEngine", NULL, NULL);
        
        if(!window){
            std::cout<<"ERROR COULD NOT INTIIALIZE WINDOW\n";
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(window);
        int width,height;
        glfwGetFramebufferSize(window, &width, &height);
        
        glewExperimental=true;
        if(GLEW_OK==!glewInit()){
            std::cout<<"ERROR COULD NOT LOAD GLEW LIBRARY\n";
            glfwTerminate();
            return;
        }
        
        glViewport(0, 0, width, height);
        
    }
    
    
    
    
    
    void gameInit(float red,float green, float blue,int SrW,int SrH){
         glClearColor(red, green,blue, 0.0);
         glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
         gluOrtho2D(0.0, SrW, 0.0,SrH );
         glClear(GL_COLOR_BUFFER_BIT);
     
        
         glFlush();
    }
    
    
   
    
    
    
    //LoadTexture
   unsigned int LoadTextrue(int tex_num,std::string filename,int W,int H,int rnChannels,int iW,int iH){
        unsigned int texture;
        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0+tex_num);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        
        unsigned char* data= stbi_load("/Users/manishkumarpatel/Desktop/Avatar_Universe/Avatar_data2.jpg",&W , &H, &rnChannels, 0);
        if(!data){
            std::cout<<"ERROR COULD NOT LOAD TEXTURE\n";
            return -1;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iW, iH, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return texture;
    }
   
    //function for drawing texture to screen
    void DrawTexture(unsigned int texture){
        
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(1.0f, 0.0f);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        
    }
    
    
    
    void sleep(float seconds){
        clock_t startTime= clock();
        float Seconds_Left= seconds*CLOCKS_PER_SEC;

        
        while(clock()<(startTime+Seconds_Left)){
        }
            
            return;
    }

    
    
    };

  
    
