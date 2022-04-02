#include <iostream>
#include <random>
#include "Game.hpp"

class Entity:Game{
  
public:
   int Posx,Posy;
    std::vector<float>oldvec1;
    std::vector<float>oldvec2;
    NEX_MATRIX::Math Operations;

    Entity(){}
    
    
     //draw square
      void DrawSqaure(int Posx,int Posy,float red,float green,float blue,float size){

          glPointSize(size);
          glColor3f(red,green,blue);
          glBegin(GL_POINTS);
          glVertex2f(Posx,Posy);
          glEnd();
          
      }
       
       void DrawPolygon(int texture){
                 
           float SqaureVertices[]
            {
                300,300,0,    0.0f,0.0f,
                300,100,0,    1.0f,0.0f,
                500,300,0,    1.0f,1.0f,
                300,500,0,    0.0f,1.0f,
                100,300,0,    0.0f,0.0f
            };

           
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
            glEnableClientState(GL_VERTEX_ARRAY);
           glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, SqaureVertices);
           glVertexPointer(2, GL_FLOAT, 3*sizeof(float), SqaureVertices);
           
           glActiveTexture(GL_TEXTURE0+texture);
           glBindTexture(GL_TEXTURE_2D, texture);
        
           
           glDrawArrays(GL_POLYGON, 0, 5);
            glDisableClientState(GL_VERTEX_ARRAY);
           glDisableClientState(GL_TEXTURE_COORD_ARRAY);
           
       }

    
    
    
       //Universal Collision detection function
   
        bool Detect_Collision(Entity object1,GLfloat radius1,Entity object2,GLfloat radius2,bool DebugMode){
        NEX_MATRIX::Math Operations;
        float* circleVertex1;
        float* circleVertex2;
        std::vector<float>velocity1;
        std::vector<float>velocity2;
        
            
        //draw imaginary circle around both shapes
        if(DebugMode){
        DrawCircle(object1.Posx, object1.Posy, 0, radius1, 100, DebugMode);
        
        DrawCircle(object2.Posx,object2.Posy,0,radius2,100,DebugMode);
            }
                
        std::vector<float>vec1;
        std::vector<float>vec2;
        vec1.push_back(object1.Posx);
        vec1.push_back(object1.Posy);
        vec2.push_back(object2.Posx);
        vec2.push_back(object2.Posy);
        
       /// vec1= Operations.Normalize_Vector(vec1);
        ///vec2= Operations.Normalize_Vector(vec2);
        
        float Distance= /*sqrt((vec2[0]-vec1[0])+(vec2[1]-vec1[1]));*/Operations.Find_Euclidean_Distance(vec1, vec2);
     
 
        std::vector<float>radials;
        radials.push_back(radius1);
        radials.push_back(radius2);
        radials= Operations.Normalize_Vector(radials);
        
        float rLength= Operations.Vec_Length(vec1)+Operations.Vec_Length(vec2);
     
        if(oldvec1.size()==0&&oldvec2.size()==0){
            for(int i=0;i<vec1.size();i++){
                oldvec1.push_back(vec1[i]);
                oldvec2.push_back(vec2[i]);
            }
        }
        
        //calclate the velocity vectors
        velocity1= Operations.Vector_Subtract(oldvec1, vec1);
        velocity2= Operations.Vector_Subtract(oldvec2,vec2);
  
       
        
        std::vector<float>A;
        std::vector<float>B;

        A= Operations.Vector_Subtract(vec1, vec2);
        B= Operations.Vector_Subtract(velocity1, velocity2);
        //calcalte results with d^2 formula
        
        float dSquared=0;
        for(int i=0;i<A.size();i++){
            dSquared=pow(A[i],2)-(pow(A[i]*B[i],2)/pow(B[i],2));
            
        }
            
        if((radius1*radius1+radius2*radius2)>((pow(object1.Posx-object2.Posx,2))+(pow(object1.Posy-object2.Posy,2)))){
            
            return true;
        }
        
        //store the current vectors in the old vec storage for velocity
        for(int i=0;i<2;i++){
            oldvec1.pop_back();
            oldvec2.pop_back();
        }
        
        for(int i=0;i<vec1.size();i++){
            oldvec1.push_back(vec1[i]);
            oldvec2.push_back(vec2[i]);
        }
        //if(((object1.Posx+50)>=object2.Posx)&&(object1.Posx<=(object2.Posx+50))&&((object1.Posy+50)>=object2.Posy)&&(object1.Posy<=(object2.Posy+50))){
//            glfwTerminate();
        return false;
        }
  
       

       
    
    void ProcessInput(GLFWwindow* window,Entity &object){
        
        if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS)
            object.Posy+=10.0f;
        else if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS)
            object.Posy-=10.0f;
        else if(glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_PRESS)
            object.Posx+=10.0f;
        else if(glfwGetKey(window,GLFW_KEY_LEFT)==GLFW_PRESS)
            object.Posx-=10.0f;
        else if(glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_PRESS)
            glfwTerminate();
    }

    
      //generate random funciton
      Entity Generate_Random_Objects(bool intitialval){
          Entity new_object;
          if(intitialval){
          new_object.Posx=900;
          new_object.Posy=500;
          }
        new_object.DrawSqaure(new_object.Posx, new_object.Posy, 0.0f, 0.0f, 0.0f, 50);

          
          return new_object;
      }
    
    //create multiple function will create multiple shapes store them in array and pass them on
    std::vector<Entity> CreateMultiple(int num){
        
        std::vector<Entity>vec;
        Entity temp;
        
        for(int i=0;i<num;i++){
            vec.push_back(temp);
        }
        
        std::random_device rd; //initial for random number generator
        std::mt19937 gen(rd()); //seed random generator
        std::uniform_int_distribution<> distr(100,700); //define the range
        
        
     
        /*for(int i=0;i<num;i++){
            vec[i].Posx=1200;
            vec[i].Posy=400;
        }*/
        
        
        return vec;
    }
    
    
    //draw bullet function
    //:= call the draw square manipulate paramters to give a bullet like look
    void DrawBullet(Entity object){
        object.DrawSqaure(object.Posx, object.Posy, 1.0f, 0.0f, 0.0f, 20.0f);
    }
    
    
    //destroy form data function to get rid of an entity from a game group
    std::vector<Entity> Destroy_Entity_From_Group(std::vector<Entity>vec,int index){
        vec.erase(vec.begin()+index);
        return vec;
    }
    
    
    
    
private:
     GLfloat* DrawCircle(GLfloat x,GLfloat y,GLfloat z,GLfloat radius,GLint num_of_sides,bool Mode){
           GLint num_of_vertices=num_of_sides+2;
           GLdouble doublePI= 2.0* M_PI;
           
           GLfloat circleVerticesX[num_of_vertices];
           GLfloat circleVerticesY[num_of_vertices];

               //setting the center point for our circle
           circleVerticesX[0]=x;
           circleVerticesY[0]=y;
           
           //setting all other vertices
           for(int i=1;i<num_of_vertices;i++){
               circleVerticesX[i]= x+ (radius* cos(i*doublePI/num_of_sides));
               circleVerticesY[i]= y+ (radius* sin(i*doublePI/num_of_sides));
               
           }

            //array to hold all vertices
           GLfloat allCircleVertices[num_of_vertices*2];
           
           for(int i=0;i<num_of_vertices;i++){
               allCircleVertices[i*2]= circleVerticesX[i];
               allCircleVertices[(i*2)+1]= circleVerticesY[i];
           }
               
           glEnableClientState(GL_VERTEX_ARRAY);
    
           glVertexPointer(2, GL_FLOAT, 0, allCircleVertices);
         if(!Mode){
           glDrawArrays(GL_TRIANGLE_FAN, 0, num_of_vertices);
         }else{
             glDrawArrays(GL_LINES, 0, num_of_vertices);
         }
         
         
           glDisableClientState(GL_VERTEX_ARRAY);

         return allCircleVertices;
       }
    
  
    
    
    
    
};
