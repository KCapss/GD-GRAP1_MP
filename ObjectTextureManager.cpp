#include "ObjectTextureManager.h"
#include <iostream>

ObjectTextureManager* ObjectTextureManager::sharedInstance = NULL;

ObjectTextureManager* ObjectTextureManager::getInstance() {
	//initial only when we need it
	if (sharedInstance == NULL) {
		sharedInstance = new ObjectTextureManager();
	}

	return sharedInstance;

}
void ObjectTextureManager::loadAll()
{
	//Loading for Obj
	loadObj("sword", "3D/sword.obj");
	loadObj("refrigerator", "3D/refrigerator.obj");
	//loadObj("ship", "3D/ship.obj");
	loadObj("ship", "3D/statue.obj");

	//Loading for Texture;
	loadTexture("sword", "3D/swordTexture.jpg");
	loadTexture("refrigerator", "3D/refrigeratorTexture.jpg");
	//loadTexture("ship", "3D/shipTexture.obj");
	loadTexture("ship", "3D/statueTexture.jpg");

	//Additional Feat. Load for Skybox Array List;
}

std::string ObjectTextureManager::getObjPath(std::string key)
{
	if (objPathMap.find(key) != objPathMap.end()) {
		return objPathMap[key];
	}

	else {
		std::cout << "No objPath found for " << key << std::endl;
		return NULL;
	}
	
}

std::string ObjectTextureManager::getTexturePath(std::string key)
{
	key = key + "Texture";
	if (texturePathMap.find(key) != texturePathMap.end()) {
		return texturePathMap[key];
	}

	else {
		std::cout << "No texturePath found for " << key << std::endl;
		return NULL;
	}

}



void ObjectTextureManager::loadObj(std::string key, std::string path)
{
	objPathMap[key] = path;
}

void ObjectTextureManager::loadTexture(std::string key, std::string path)
{
	texturePathMap[key + "Texture"] = path;
}

