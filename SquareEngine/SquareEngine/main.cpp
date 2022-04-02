#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <Shaders.hpp>
#include <NEX_MATRIX/NEX_MATRIX.hpp>
#include "Game.hpp"
#include "Entity.hpp"
#include "World.hpp"


  

Game game;
int Posx=100,Posy=300;
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);


//Process Key Movements and inputs function


int main(){
    
 
    game.InitGlfw(0.1f, 0.1f, 0.1f, 1200, 700);
    game.InitWindow(1200, 700);
    NEX_MATRIX::Math Operations;

    int W,H,rnChannels;
    unsigned int texture1= game.LoadTextrue(0,"/Users/manishkumarpatel/Desktop/Avatar_Universe/Avatar_data2.jpg",W , H, rnChannels, 640, 400);
    
    World scene(1200);
    Entity square;
    square.Posx=100;
    square.Posy=300;
    
    //Start Position
    Entity Start;
    Start.Posx=100;
    Start.Posy=100;
    
    Entity test;
    test.Posx=500;
    test.Posy=500;

    float testR=0.0f,testG=1.0f,testB=0.0f;
    
    //glfwSetKeyCallback(game.window, ProcessInput);
    int* ptr= &square.Posy;
    std::vector<Entity*>squares;
    bool intitialval=true;
    
    Entity temp;
    temp.Posx=1200;
    temp.Posy=500;
    std::vector<Entity>MultipleObjects;
    MultipleObjects= square.CreateMultiple(30);
    
    std::vector<Entity>Bullets;
    
    Bullets= square.CreateMultiple(30);
    int bull_count=0;
    
    for(int i=0;i<Bullets.size();i++){
        Bullets[i].Posx=-100;
        Bullets[i].Posy=-100;
    }
    
    
    while(!glfwWindowShouldClose(game.window)){
        
        
        glfwPollEvents();
        
        game.gameInit(0.0f, 0.0f, 1.0f, 1200, 700);
    
        test.DrawSqaure(test.Posx, test.Posy, testR, testG, testB, 50.0f);

        square.DrawSqaure(square.Posx, square.Posy, 1.0f, 0.0f, 0.0f, 50.0f);

        Start.DrawSqaure(Start.Posx, Start.Posy, 0.1f, 0.1f, 0.1f, 500.0f);
 
        temp.DrawSqaure(temp.Posx, temp.Posy, 0.0f, 0.0f, 0.0f, 50.0f);
        
        square.ProcessInput(game.window, square);

        
        *ptr= scene.EnableGravity(ptr);
        
        //handle is collision statements
                if( square.Detect_Collision(square, 50.0f, Start, 150.0f, false)){
                    square.Posy=Start.Posy+150.0f;
                }
       
    
     

        //2D "Camera" Implementation
        if(squares.size()>0){
            while(squares.size()!=1){
                squares= Operations.pop_front(squares);
            }
        }
        squares.push_back(&square);
        squares.push_back(&Start);
        squares.push_back(&test);
        squares.push_back(&temp);
      
        if(temp.Posx+50.0f<0){
            temp.Posx=1200;
        }
       
   for(int i=0;i<MultipleObjects.size();i++){
      
       if(MultipleObjects[i].Posx<0){
      
           std::random_device rd;
           std::mt19937 gen(rd());
           std::uniform_int_distribution<> distr(100,700);
           MultipleObjects[i].Posx=1200;
           
           MultipleObjects[i].Posy=distr(gen);//rand()%(700-100+1);
                        
           MultipleObjects[i].Posx=MultipleObjects[i].Posx%(int)MultipleObjects[i].Posy*i+700;
       }
   }
   
            srand(time(NULL));
            //move this for loop to be every frame for a better feel of iteration
        for(int i=0;i<MultipleObjects.size();i++){
                MultipleObjects[i].DrawSqaure(MultipleObjects[i].Posx,MultipleObjects[i].Posy, testR, testG,testB, 50.0f);
                if(square.Detect_Collision(square, 50.0f, MultipleObjects[i], 50.0f, false)){
                    glfwTerminate();
                }
                
            }
     
    
        for(int i=0;i<MultipleObjects.size();i++){
            squares.push_back(&MultipleObjects[i]);
        }
        
        
        
      
        for(int i=0;i<Bullets.size();i++){
       Bullets[i].DrawSqaure(Bullets[i].Posx, Bullets[i].Posy, 1.0f, 0.0f, 0.0f, 20.0f);
               Bullets[i].Posx+=30.0f;
        }
         if(glfwGetKey(game.window, GLFW_KEY_S)==GLFW_PRESS){
            Bullets[bull_count].Posx=square.Posx+50;
            Bullets[bull_count].Posy=square.Posy;
                      bull_count+=1;
               }
        if(bull_count==30){
            bull_count=0;
        }

        
        //set collision detection between Bullets and MultipleObjects
        for(int i=0;i<MultipleObjects.size();i++){
            if(square.Detect_Collision(Bullets[i], 20.0f, MultipleObjects[i], 50.0f,false)){
               MultipleObjects= MultipleObjects[i].Destroy_Entity_From_Group(MultipleObjects, i);
                std::vector<Entity>temp;
                temp= square.CreateMultiple(1);
                MultipleObjects.push_back(temp[0]);
           
            }
        }
        
        game.DrawTexture(texture1);
        
      
      scene.Set_Camera(squares);
        //set this to false so coordinates on randomly genrerated object can change;
        intitialval=false;
  
        
        glfwSwapBuffers(game.window);
  
    }
    glfwTerminate();
    return 0;
    
}
