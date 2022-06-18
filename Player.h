#pragma once
#include "Model.h"
#include <string>

class Player :
    public Model
{
public:
    //Constructor
    Player(std::string name, GLFWwindow *window);

    //Presetup
    void recomputeTransform();

    //switch
    void cameraSwitch();
    void lightSwitch();

    //Operation
    void loadObj();
    void loadTexture();
    void loadBuffer();

    
    //UpdateFunction
    void playerMovement();
    void updateCamera();

    void update();
    void draw(); //override base class draw()

private:
    const float SHIP_FORWARD_SPEED = 0.15f;
    float SHIP_ROTATION_SPEED = 0.1f;
    float camDistance;
    glm::mat4 shipTransform = glm::mat4(1.0f);

    

    //Special Parameters
    unsigned char* norm_bytes;
    GLuint normTexture = 0;


    //Note: Create a singleton for inputManager

};

