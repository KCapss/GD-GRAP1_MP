#include "Camera.h"

Camera::Camera()
{
    this->cameraPos = glm::vec3(0, 0, -30.0f);
    this->WorldUp = glm::vec3(0, 1.0f, 0);
    this->Center = glm::vec3(0, 0, 0);

    this->viewMatrix = glm::mat4(1.0f);
    updateCamera();
}

void Camera::updateCamera()
{
    //this->cameraPos = glm::vec3(0, 0, -10.0f);
    glm::mat4 cameraPositionMatrix = glm::translate(glm::mat4(1.0f),
        cameraPos * -1.0f);

    //Option 1 = Non Standard
    glm::vec3 F = glm::normalize(glm::vec3(Center - cameraPos));
    glm::vec3 R = glm::normalize(glm::cross(F, WorldUp));
    glm::vec3 U = (glm::cross(R, F));

    glm::mat4 cameraOrientation = glm::mat4(
        glm::vec4(R, 0),
        glm::vec4(U, 0),
        glm::vec4(F * -1.0f, 0),
        glm::vec4(glm::vec3(0, 0, 0), 1.0f));
    cameraOrientation = glm::transpose(cameraOrientation);
    this->viewMatrix = cameraOrientation * cameraPositionMatrix;
    //this->viewMatrix = glm::lookAt(cameraPos, Center, WorldUp);
}

glm::vec3 Camera::getCameraPos()
{
    return this->cameraPos;
}

glm::mat4 Camera::getViewMatrix()
{
    return this->viewMatrix;
}

void Camera::newCamPosition(glm::mat4 shipPosTransformMat, glm::vec3 rotateVector, float distance)
{
    //Get the current orientation of the camera
    glm::mat4 camRotMat = glm::mat4(1);
    camRotMat = glm::rotate(camRotMat, glm::radians(rotateVector.y), glm::vec3(0, 1.0f, 0));
    camRotMat = glm::rotate(camRotMat, glm::radians(rotateVector.x), glm::vec3(1.0f, 0, 0));
    camRotMat = glm::rotate(camRotMat, glm::radians(rotateVector.z), glm::vec3(0, 0, 1.0f));

    glm::vec3 camDirection = glm::vec3(glm::normalize(glm::vec4(0, 0, 0, 1.0f) * camRotMat));
    camDirection = camDirection * distance;

//Translate it in opposite direction to get the center and the position
    //Translation reffered on the current ship orientation
    glm::mat4 cameraPosMat = glm::translate(shipPosTransformMat, camDirection * -1.0f); //Back position Matrix of the Cam
    glm::vec4 cameraVec4Pos = cameraPosMat[3]; //Retrieve Col 4 (index = 3)
    this->cameraPos = cameraVec4Pos; //Typecast to vec3

    glm::mat4 centerPosMat = glm::translate(shipPosTransformMat, -camDirection / 2.0f ); //Forward position Matrix of the Center
    glm::vec4 centerVec4Pos = centerPosMat[3];  //Retrieve Col 4 (index = 3)
    this->Center = centerVec4Pos; //Typecast to vec3

    updateCamera();

}
