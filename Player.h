#pragma once
#include "Model.h"
#include <string>

class Player :
    public Model
{
public:
    //Constructor
    Player(std::string name, GLFWwindow *window);

    //switch
    void cameraSwitch();
    void lightSwitch();

    
    //UpdateFunction
    //void playerMovement();
    void updateCamera();

    void update();
    //void draw(); //override base class draw()

private:
    float camDistance;
    glm::mat4 shipTransform = glm::mat4(1.0f);
    

    //Note: Create a singleton for inputManager

};

