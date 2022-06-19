#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//#define TINYOBJLOADER_IMPLEMENTATION
//#include "tiny_obj_loader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <vector>


class Light
{
public:
	//Constructor and Destructor
	Light(glm::vec3 objPos);

	//Getter Function
	glm::vec3 getLightPos();
	glm::vec3 getLightColor();

	float getAmbientStr();
	glm::vec3 getAmbientColor();

	float getSpecStr();
	float getSpecPhong();

	//Setter
	void setLightPos(glm::vec3 newLightPos);

	//LightSwitch
	enum LightState {
		Inactive = 0,
		Active = 1
	};
	void lightSwitch();
	glm::vec3 lightCheck();


private:
	//Attributes
		//Light
	glm::vec3 lightPos;
	glm::vec3 lightColor;
	glm::vec3 greyLight;

	//Ambient
	float ambientStr;
	glm::vec3 ambientColor;

	//Specular
	float specStr;
	float specPhong;

	//World Position
	float distance;
	float speed;
	glm::vec3 lightRotation;

	//Class Handle
	

	//State
	LightState lightState = Active;

	//Debug
	glm::vec3 d_lightRotation;
};

