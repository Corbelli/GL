//
//  animation.hpp
//  Tutorials
//
//  Created by Rodrigo Corbelli on 10/10/16.
//
//

#ifndef animation_hpp
#define animation_hpp
#include <stdio.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <ctime>
using namespace glm;

class Animation {
    
    
    public :
    
    Animation(int _windowsSize, int _modelSize, int _distanceToCamera, float _FoV);
    mat4 UpdateAnim(vec3 _position,float _size);
    void Activate();
    bool isActive;

    
    
    private :
    
    float             FoV;
    int               windowsSize;
    int               modelSize;
    int               distanceToCamera;
    quat              currentOrientation;
    float             omega;
    float             speed;
    float             shrinkrate;
    std::clock_t      timer;
    
    mat4              Translation;
    mat4              Scale;
    mat4              Rotation;

    bool              isOutOffScreen( vec3 _position , float _size);
    
    
    
    
};






#endif /* animation_hpp */
