#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera()
{
    this->projection = glm::perspective(glm::radians(60.0f),
        800.f / 800.f,
        0.01f,
        100.0f);

    this->distance = 30.0f;
    this->cameraPos = glm::vec3(0, 0, -distance);
   
    updateCamera();

   
   
}

glm::mat4 PerspectiveCamera::getProjection()
{
    return this->projection;
}
