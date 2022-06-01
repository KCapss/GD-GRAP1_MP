#pragma once
#include "Camera.h"
class PerspectiveCamera :
    public Camera
{
public:
    PerspectiveCamera();
    glm::mat4 getProjection();


private:
    //class Calls
    glm::mat4 projection;

    float distance;

};


