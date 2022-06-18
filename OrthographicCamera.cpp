#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera()
{
	//Pre-Defined Settings
	this->projection = glm::ortho(-15.0f,  //LeftMost
		15.0f,  //RightMost
		-15.0f,  //bottomMost
		15.0f,  //topMost 
		0.0f,  //Z-Near
		400.0f   //Z-Far = can be adjusted 
	);

	this->cameraPos = glm::vec3(15.0f, 15.0f, 3.0f);

	updateCamera();
}

glm::mat4 OrthographicCamera::getProjection()
{
	return this->projection;
}
