//
//  reflections.hpp
//  Solar_System
//
//  Created by manishkumar  patel on 8/23/20.
//  Copyright © 2020 Krish Patel. All rights reserved.
//

#include <iostream>
#include <glew.h>
#include <glfw3.h>


//draw reflection of object given the model matrix and a vec3
void drawReflection(glm::mat4 model, glm::vec3 translation,GLenum config,int size,Shader shader){
    
    translation.y=(translation.y*-1) + (translation.y*-1);
    model= glm::translate(model,translation);
    for(int i=0;i<4;i++){
        model[1][i]=0.0f;
    }
    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLE_FAN, 0, size);
    
}
