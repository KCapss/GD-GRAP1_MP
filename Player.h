#pragma once
#include "Model.h"
#include <string>

class Player :
    public Model
{
public:
    //Constructor
    Player(std::string);

    enum currCam { Perspective = 1, Orthographic = 2};
    
    

    //Switch Function
    void cameraSwitch();
    void lightSwitch();

    //UpdateFunction
    void playerMovement();
    void updateCamera();

    
    void draw(); //override base class draw()

private:
    float camDistance;
    glm::mat4 transform = glm::mat4(1.0f);

    bool isShipLightActive = true; //default Parameter


    //Note: Create a singleton for inputManager

};

