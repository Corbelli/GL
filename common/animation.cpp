//
//  animation.cpp
//  Tutorials
//
//  Created by Rodrigo Corbelli on 10/10/16.
//
//

#include "animation.hpp"


Animation::Animation(int _windowsSize, int _modelSize, int _distanceToCamera, float _FoV){
    
    FoV = _FoV;
    windowsSize = _windowsSize;
    modelSize = _modelSize;
    distanceToCamera = _distanceToCamera;
    timer = std::clock();
    omega = 4 * M_PI_2;
    speed = 100;
    shrinkrate = 100;
    isActive = false;
    
}

mat4 Animation::UpdateAnim(vec3 _position, float _size){
    
    double timeElapsed = (std::clock() - timer) / (double) CLOCKS_PER_SEC;
    
    
    //Calculate Scaling Matrix
    if( _size > 1){
        float sizeToReduce = timeElapsed*shrinkrate;
        _size -= sizeToReduce;
        Scale[0].x = _size;
        Scale[1].y = _size;
        Scale[2].z = 1;
    }
    
    
    //Calculate Translation Matrix;
    if( !isOutOffScreen(_position, _size) ){
        
        float distanceToCover = timeElapsed*speed;
        vec3 acrescimalPosition(0.0f,distanceToCover,0.0f);
        _position += acrescimalPosition;
        Translation[3] = vec4( _position, 1.0f);
    }

    
    //Calculate Rotation Matrix
    if( !isOutOffScreen(_position, _size)){
        
        float radiansToRotate = timeElapsed*omega;
        quat acrescimalOrientation = angleAxis(degrees(radiansToRotate),vec3(1,0,0) );
        currentOrientation *= acrescimalOrientation;
        Rotation = toMat4(currentOrientation);
    }
    else{
        Rotation = toMat4( quat(1,0,0,0));
        isActive = false;
    }

    
 
    
    timer = std::clock();
    return Translation*Rotation*Scale;
}

void Animation::Activate(){
    isActive = true ;
    timer = std::clock();
    
}

bool Animation::isOutOffScreen( vec3 _position, float _size ){
    
    float tg_FoV = tan(FoV*M_PI/180);
    float lowerVerticePosition = (_position.y + (modelSize*_size/2) )/(distanceToCamera*tg_FoV);
    
    if(lowerVerticePosition > 1 )
        return true;
    else
        return false;
}
