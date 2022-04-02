#include <iostream>
#include <math.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <NEX_MATRIX/NEX_MATRIX.hpp>
#include <glm/glm/glm.hpp>
#include <glm/glm/vec3.hpp> // glm::vec3
#include <glm/glm/vec4.hpp> // glm::vec4
#include <glm/glm/mat4x4.hpp> // glm::mat4
#include <glm/glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale,


float vertices_old[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
};




GLfloat vertices[]
{
//   x   y     r  g  b     u, v
    -1.0f, -1.0f,   1, 1, 1,    0, 0,
    1.0f, -1.0f,    1, 1, 1,    1, 0,
    0.0f,  1.0f,    1, 1, 1,    1, 1,
    0.0f,  0.0f,    1, 1, 1,    0, 1,
};


float color_vertices[]
{
    1,1,1,
    1,1,1,
    1,1,1,
    1,1,1
};

float tex_vertices[]
{
    0,0,
    1,0,
    1,1,
    0,1
};


float Identity[][4]
{
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
};

float indicies[]
{
    0,1,2,
    2,1,3
};


//camera vectors
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

//yaw and pitch values;
float yaw=-90.0f;
float pitch;
float lastX=600;
float lastY=350;
bool firstMouse=true;

//global variable for the lightSource coordinates
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


glm::mat4 planet_pos= glm::mat4(1.2,1.2,1.0,1.0,
                                0.5,0.5,0.5,1.0,
                                -0.5,-0.5,0.5,1.0,
                                0.5,-0.5,-0.5,1.0);



std::vector<float> Create_Circles(float Radius,float Theta){
    std::vector<float>Vertexes;

    //initial point will be out center
    float x,y;

    int vertice_count=56;
    for(int j=0;j<vertice_count;j++){
        x= Radius* cos(Theta);
        y= Radius* sin(Theta);
        
   
        
        Vertexes.push_back(x);
        Vertexes.push_back(y);
    }
    
    int size= Vertexes.size();
    float Vertices[size];
    for(int j=0;j<Vertexes.size();j++){
        Vertices[j]=Vertexes[j];
      
    }
    std::cout<<Vertexes.size()<<"\n";
    return Vertexes;
}


void DrawCircle(GLfloat x,GLfloat y,GLfloat z,GLfloat radius,GLint num_of_sides){
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
    glDrawArrays(GL_TRIANGLE_FAN, 0, num_of_vertices);
    
    glDisableClientState(GL_VERTEX_ARRAY);

}


float Single_Stride(32);

std::vector<std::vector<float> > Draw_3D_Sphere(GLfloat x,GLfloat y,GLfloat z,GLfloat radius,GLint sectors_num,GLint stack_num){
    

    
    int num_of_vertices= sectors_num+3;
    
    float const PI= acos(-1);
    
    NEX_MATRIX::Math Operations;
    
    GLfloat sector_step,stack_step;
    sector_step= 2*PI/sectors_num;
    stack_step= PI/stack_num;
    
    std::vector<float>vertices;
    std::vector<float>normalized_points;
    std::vector<float>tex_points;
    float stack_angle,sector_angle,xy,X,Y,Z;
    float normalized_unit= 1.0f/radius;
    

    for(int j=0;j<stack_num;j++){
        //calculate the stack angle per iteration
        stack_angle= PI/2- j*stack_step;
        xy= radius* cosf(stack_angle);
        Z= radius* sinf(stack_angle);
        
        
        for(int k=0;k<sectors_num;k++){
            
            sector_angle= k*sector_step;
            
            X= xy* cosf(sector_angle);
            Y=xy* sinf(sector_angle);
            vertices.push_back(X);
            vertices.push_back(Y);
            vertices.push_back(Z);
            
          //normalized vertices for lighting
            normalized_points.push_back(X*normalized_unit);
            normalized_points.push_back(Y*normalized_unit);
            normalized_points.push_back(Z*normalized_unit);
            
            
            //setting texture coordinates
            tex_points.push_back((float)j*stack_num);
            tex_points.push_back((float)k*sectors_num);
            
            
        }
    }
    

    //accumulate all vectors into one vector
    
    std::vector<float>Single;
   // Single= Operations.Combine_Data_Structures(vertices, normalized_points, tex_points, vertices.size());
    
    for(int j=0,k=0;j<vertices.size();j+=3,k+=2){
        Single.push_back(vertices[j]);
        Single.push_back(vertices[j+1]);
        Single.push_back(vertices[j+2]);
        
        Single.push_back(tex_points[k]);
        Single.push_back(tex_points[k+1]);
    }
    
    
    
    //handling the trinagle indices
    
    std::vector<float>indices;
    int k1,k2;
    
    for(int j=0;j<stack_num;j++){
        //get the beggining position of the current stack and the next stack
        k1= j*(sectors_num+1);
        k2=k1+ sectors_num+1;
        for(int k=0;k<sectors_num;k++){
            
            if(j!=0){
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1+1);
            }
            
            if(j!=stack_num-1){
                indices.push_back(k1+1);
                indices.push_back(k2);
                indices.push_back(k2+1);
            }
            
        }
    }
    
    std::size_t size= indices.size();
    float Indexes[size];
    for(int j=0;j<indices.size();j++){
        Indexes[j]=indices[j];
    }
  
    std::vector<std::vector<float> >Final;
    Final.push_back(Single);
    Final.push_back(indices);
    return Final;
   
}







