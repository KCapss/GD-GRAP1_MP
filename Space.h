#pragma once
#include "Space.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"
#include "Light.h"
#include "PerspectiveCamera.h"

#include <string>
#include <iostream>

class Space
{
public: 
	//Constructor
	GLFWwindow* window;
	Space(int length, int width);
	bool initializeWindow();

	void initializeObj();

	void draw();
	void deleteBuffer();
	
	
	


	
private:
	//Interface:
	//Model for the Skybox;
	//Model for the player;
	Model* model; //change into vector later Note. An array of Debris

	//External Src
	Light* lightSrc;
	PerspectiveCamera* mainCam;

	int lengthDim = 0, widthDim = 0; //set default

};

