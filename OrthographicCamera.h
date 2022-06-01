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

private:

    glm::mat4 projection;


};

