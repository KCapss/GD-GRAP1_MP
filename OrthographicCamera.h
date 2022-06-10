#pragma once
#include "Camera.h"
class OrthographicCamera :
    public Camera
{
public:
    //Constructor && Destructor
    OrthographicCamera();

    //Getter Function
    glm::mat4 getProjection();

    //Update Function


private:

    glm::mat4 projection;
};

