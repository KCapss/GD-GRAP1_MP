#include "Light.h"
#include <iostream>

using namespace std;


Light::Light(glm::vec3 objPos)
{
    //Attributes
    this->lightPos = glm::vec3(10, 0, -10);
    this->lightColor = glm::vec3(0.9f, 0.9f, 0.9f);
    this->greyLight = glm::vec3(0.4f, 0.4f, 0.4f);

    this->ambientStr = 0.3f;
    this->ambientColor = lightColor; // can be customizable

    this->specStr = 1.5f;
    this->specPhong = 60.20f;

    //Parts
    this->speed = 200.0f;
    this->distance = 10.f;
    this->lightRotation = glm::normalize(lightPos);
  

    //debug
    this->d_lightRotation = glm::vec3(-1.0f, 0, 0);

}


//Getter Function
glm::vec3 Light::getLightPos()
{
    return this->lightPos;
}

glm::vec3 Light::getLightColor()
{
    return this->lightColor;
}

float Light::getAmbientStr()
{
    return this->ambientStr;
}

glm::vec3 Light::getAmbientColor()
{
    return this->ambientColor;
}

float Light::getSpecStr()
{
    return this->specStr;
}

float Light::getSpecPhong()
{
    return this->specPhong;
}

void Light::setLightPos(glm::vec3 newLightPos)
{
    this->lightPos = newLightPos;
}



//Rotatate along respect to the current normal position of the object from the center

//Switcher Function
void Light::lightSwitch()
{
    if (lightState == Inactive) {
        lightState = Active;

    }

    else if (lightState == Active) {
        lightState = Inactive;
    }

}

//Active Checker()
glm::vec3 Light::lightCheck()
{
    if (lightState == Inactive) {
        return this->greyLight;

    }

    else if (lightState == Active) {
        return this->lightColor;
    }
}
