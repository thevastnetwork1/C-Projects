#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "Game.hpp"

class World:Game{
public:
    int Posx,Posy;
 
    int threshold;
    //public other objects store for camera manipulation
    std::vector<Entity>OtherObjects;
    
    
    
    float Gravity=0.5f;
    
    World(int SCRW){
        threshold= SCRW-100;
    }
    
    int EnableGravity(int* Posy){
        return *Posy=float(*Posy)-Gravity;
    }
    
    
    //implement orthogonal camera and functionality in this class
    void Set_Camera(std::vector<Entity*>OtherObjects){
        
      
       // for(int i=1;i<OtherObjects.size();i++){
           // if(OtherObjects[0]->Posx>threshold){
              //  OtherObjects[0]->Posx=threshold;
                //for(int j=1;j<OtherObjects.size();j++){
               // OtherObjects[j]->Posx-=3.0f;
               // }
           
         //   }else if(OtherObjects[0]->Posx<(threshold-threshold+100)){
            //    OtherObjects[0]->Posx=threshold-threshold+100;
                 for(int j=1;j<OtherObjects.size();j++){
                OtherObjects[j]->Posx-=3.0f;
                }
     
        
            //}
        }

     
        
    
    
    void Set_View_Matrix(glm::mat4 Views){
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
     
        
    }
    
    
};
