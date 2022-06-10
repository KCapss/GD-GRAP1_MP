#include "Player.h"
#include "SwitchManager.h"

Player::Player(std::string name, GLFWwindow *window): Model(name, ObjectType::WithTexture, window)
{
	//Majority of the process will be on the base on the base class for now
}

void Player::cameraSwitch()
{
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		this->currCam = SwitchManager::getInstance()->changeCam(currCam);

		//Special Effect for cursor
		if (SwitchManager::getInstance()->isPerspectiveActive(currCam)) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			
		}

		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		SwitchManager::getInstance()->updateCurrCam(currCam);
	}

}

void Player::lightSwitch()
{
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		SwitchManager::getInstance()->changeLightSource();
	}
}

void Player::updateCamera()
{
	cameraSwitch();
	if (currCam == Perspective) {
		//perspCam->
	}
}

void Player::update()
{
	//updatePlayerMovement()
	updateCamera();

}
