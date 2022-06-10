#pragma once
#include "Camera.h"
class PerspectiveCamera :
    public Camera
{
public:
    PerspectiveCamera();
    glm::mat4 getProjection();

    //UpdateFunctio
    void perpectiveCamUpdate(GLFWwindow *window, glm::mat4 shishipPosTransformMat);
    void RotateCam(GLFWwindow *window, glm::mat4 shishipPosTransformMat); //only applies on perspective


private:
    bool rotateActive = false;
    glm::mat4 projection;
    float distance;


    glm::vec3 d_camRotate = glm::vec3(0);

   

    float camSensitivity;

    double xCamCurrPos = 0, yCamCurrPos = 0;
    float lastX = 800 / 2.0f;  // starting last position of the mouse
    float lastY = 800 / 2.0f; // starting last position of the mouse


    
    bool onXplane = false;

};


