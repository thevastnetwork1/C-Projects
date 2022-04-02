#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <src/Sphere.h>


int main(){
    
    
    glfwInit();
    
    GLFWwindow* window= glfwCreateWindow(1200, 700, "Sphere", NULL, NULL);
    
    if(!window){
        std::cout<<"Wondow issue\n";
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    int width,height;
    glfwGetFramebufferSize(window, &width, &height);
    
    glewExperimental=true;
    
    if(GLEW_OK==!glewInit()){
        std::cout<<"GLEW issues\n";
        glfwTerminate();
        return -1;
    }
    
    
    glViewport(0,0, width, height);
    
    
    while(!glfwWindowShouldClose(window)){
        
        glfwPollEvents();
        
        glClearColor(0.1f,0.02f,0.02f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
            Sphere sphere;
        
        
        sphere.set(120, 36, 18);
        sphere.setSmooth(true);
        sphere.draw();

        glfwSwapBuffers(window);
        
    }
    
    glfwTerminate();
    

    
    return 0;
}


