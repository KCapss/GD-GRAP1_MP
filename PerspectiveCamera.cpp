#include "PerspectiveCamera.h"
#include <cmath>

PerspectiveCamera::PerspectiveCamera()
{
    this->projection = glm::perspective(glm::radians(60.0f),
        800.f / 800.f,
        0.01f,
        10000.0f);

    this->distance = 10.0f;
    this->cameraPos = glm::vec3(0, 0, -distance);
   
    updateCamera();

   
   
}

glm::mat4 PerspectiveCamera::getProjection()
{
    return this->projection;
}

void PerspectiveCamera::RotateCam(GLFWwindow* window, glm::mat4 shipPosTransformMat)
{

    ////Rotation can occur if left mouse button is pressed
    //glfwGetCursorPos(window, &xCamCurrPos, &yCamCurrPos);

    ////Calibrate the first mouse Cursor location when press
    //if (!this->rotateActive)
    //{
    //    lastX = xCamCurrPos;
    //    lastY = yCamCurrPos;
    //    this->rotateActive = true;
    //}

    ////Determine the offset starting and current position
    //float xoffset = xCamCurrPos - lastX;
    //float yoffset = lastY - yCamCurrPos;

    //lastX = xCamCurrPos;
    //lastY = yCamCurrPos;

    ////For Smoother rotation
    //xoffset *= camSensitivity;
    //yoffset *= camSensitivity;



    ///*typecast from float to int then int to float */
    //float currZRotate = (float)abs((int)d_camRotate.y % 360); // current angle in Degree

    ////boundaries for the xz-plane
    //if (((currZRotate > 45.0f && currZRotate < 135.0f))
    //    || (currZRotate > 235.0f && currZRotate < 315.0f)) {

    //    if (onXplane)
    //        d_camRotate.z = d_camRotate.x; //Retrieve the other axis-angle 

    //    onXplane = false;
    //}

    //else {
    //    if (!onXplane)
    //        d_camRotate.x = d_camRotate.z; //Retrieve the other axis-angle 

    //    onXplane = true;
    //}


    //d_camRotate.y += xoffset; // offset
    ////Boundaries of going up too-much in xy-plane
    //if ((d_camRotate.z + yoffset < 80.0f && d_camRotate.z + yoffset > -80.0f)
    //    && !onXplane) {
    //    if (currZRotate > 45.0f && currZRotate < 135.0f)
    //        d_camRotate.z -= yoffset;
    //    else
    //        d_camRotate.z += yoffset;


    //    newCamPosition(shishipPosTransformMat, glm::vec3(0, d_camRotate.y, d_camRotate.z), this->distance);
    //}

    //else if ((d_camRotate.x + yoffset < 80.0f &&
    //    d_camRotate.x + yoffset > -80.0f) && onXplane) {

    //    if (currZRotate > 135.0f && currZRotate < 225.0f)
    //        d_camRotate.x += yoffset;
    //    else
    //        d_camRotate.x -= yoffset;
    //    newCamPosition(shishipPosTransformMat, glm::vec3(0, d_camRotate.y, d_camRotate.z), this->distance);
    //}



    ////Edge Case
    //else if (d_camRotate.x > 80.0f || d_camRotate.z > 80.0f) {
    //    d_camRotate.x = 79.0f;
    //    d_camRotate.z = 79.0f;

    //}

    //else if (d_camRotate.x < -80.0f || d_camRotate.z < -80.0f) {
    //    d_camRotate.x = -79.0f;
    //    d_camRotate.z = -79.0f;
    //}


    //glm::vec4 objPos;
    //glm::vec4 startPos = glm::vec4(0, 0, 0, 1.0f);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

        //CurrentCam Pos
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        if (!this->rotateActive)
        {
            lastX = xPos;
            lastY = yPos;
            this->rotateActive = true;
        }

        //Compared to Last Check
        float xoffset = xPos - lastX;
        float yoffset = lastY - yPos;
        lastX = xPos;
        lastY = yPos;

        float sensitivity = this->camSensitivity;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        //Any Offset will increment
        x += xoffset;
        y += yoffset;

        //Preventing Rotating in Vertical Manner
        if (y > 89.0f)
            y = 89.0f;
        if (y < -89.0f)
            y = -89.0f;

        //Simplified Rotation
        
        direction.x = cos(glm::radians(x + -90.f)) * cos(glm::radians(y));
        direction.y = sin(glm::radians(y));
        direction.z = sin(glm::radians(x + -90.f)) * cos(glm::radians(y));

        //New Focus Point
        glm::mat4 camTransform = glm::translate(shipPosTransformMat, -direction * distance);
        this->cameraPos = glm::vec3(camTransform * glm::vec4(0, 0, 0, 1));
        
        glm::mat4 centerTransform = glm::translate(shipPosTransformMat, direction * distance / 2.f);
        this->Center = glm::vec3(centerTransform * glm::vec4(0, 0, 0, 1));
        //this->Center = glm::vec3(shipPosTransformMat * glm::vec4(0, 0, 0, 1));
        
    }

    else {
        this->rotateActive = false;
    }
}

void PerspectiveCamera::newCamPos(glm::mat4 shipPosTransformMat)
{
    glm::mat4 camTransform = glm::translate(shipPosTransformMat, -direction * distance);
    this->cameraPos = glm::vec3(camTransform * glm::vec4(0, 0, 0, 1));

    glm::mat4 centerTransform = glm::translate(shipPosTransformMat, direction * distance / 2.f);
    this->Center = glm::vec3(centerTransform * glm::vec4(0, 0, 0, 1));

    /*glm::mat4 camTransform = glm::translate(shipPosTransformMat, -direction * distance);
    this->cameraPos = glm::vec3(camTransform * glm::vec4(0, 0, 0, 1));
    this->Center = glm::vec3(shipPosTransformMat * glm::vec4(0, 0, 0, 1));*/

    updateCamera();
}
