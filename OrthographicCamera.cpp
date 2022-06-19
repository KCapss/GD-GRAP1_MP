#include "OrthographicCamera.h"
#include <iostream>

using namespace std;

OrthographicCamera::OrthographicCamera()
{
	//Pre-Defined Settings == Defined by the xand y axis of the map
	//The Outline would prefer to be squarish
	this->projection = glm::ortho(
		-1500.0f,  //LeftMost
		1500.0f,  //RightMost
		-1500.0f,  //bottomMost
		1500.0f,  //topMost 
		0.01f,  //Z-Near
		1400.0f   //Z-Far = can be adjusted 
	);

	this->cameraPos = glm::vec3(15.0f, 15.0f, 3.0f);
	this->distance = 400.0f;
	updateCamera();
}

glm::mat4 OrthographicCamera::getProjection()
{
	return this->projection;
}

void OrthographicCamera::updatePosition(glm::vec3 shipPos)
{

	//Set this as Center
	this->Center = shipPos;
	this->cameraPos = glm::vec3(shipPos.x, shipPos.y - distance, shipPos.z);

	
	updateCamera();
}

void OrthographicCamera::camPanning(GLFWwindow* window, glm::vec3 shipPos)
{
	//Insert Solution Here



	//Any after change for the cam and center should these, for updatiing view matrix;
	updateCamera();
}

void OrthographicCamera::camPanningReset()
{
	this->xOffset = 0;
	this->zOffset = 0;
}
