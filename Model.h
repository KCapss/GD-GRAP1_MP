#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <vector>


//Class include
#include "Shader.h"
#include "Light.h"
#include "PerspectiveCamera.h" // Replace Later with specific camera type

enum ObjectType {
	NoTexture = 0,
	WithTexture = 1,
	Skybox = 2
};

//Optianal Feature enum for Rotating Debris



//Create A single structure to access all texture, objfile and/or skybox


//This is class for general purpose in using for planet and debris
//but can be used as a Base class for player and skybox
class Model
{

public:
	Model();
	Model(std::string name, ObjectType objType, GLFWwindow *currWindow); //Universal of the Class

	//Setup Function
	void retrieveSource(Light* light, PerspectiveCamera* perspCam); // All external model have same sources
	void setInitialPos(glm::vec3 pos);


	//Initialization Process
	void loadObj();
	void loadTexture();
	void loadBuffer();
	//void loadShaders();

	//EdgeCase Process
	/*void loadSkyboxtexture();*/


	//Process
	void draw();

	//Removing Buffer after program ends
	void deAllocate();


private:
	//Obj information = Default
	std::string name{};
	ObjectType objType = ObjectType::NoTexture; 

	//Obj Vertex data
	std::vector<GLfloat> fullVertexData{};
	unsigned char* tex_bytes;
	GLuint texture = 0;

	//Buffer
	GLuint VAO, VBO;
	
private:
	//Obj Properties
	glm::vec3 position = glm::vec3(0);

	//class container
	Light *light;
	Shader* shader;
	PerspectiveCamera* perspCam;

	GLFWwindow* window;

	

	




};

