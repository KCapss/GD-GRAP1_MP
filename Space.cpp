#include "Space.h"
#include "ObjectTextureManager.h"


Space::Space(int length, int width)
{
	ObjectTextureManager::getInstance()->loadAll();

    lightSrc = new Light(glm::vec3(-10.0f, 0, 0));
    mainCam = new PerspectiveCamera();
    alterCam = new OrthographicCamera();


	this->lengthDim = length;
	this->widthDim = width;
    
}

bool Space::initializeWindow()
{
    //Init Lib
    if (!glfwInit())
        return true;

    //Init Window
    this->window = glfwCreateWindow(lengthDim, widthDim, "Kevin Capalar", NULL, NULL);
    if (!this->window)
    {
        glfwTerminate();
        return true;
    }

    glfwMakeContextCurrent(this->window);
    gladLoadGL();


    //Initialize ViewPort
    glViewport(0, 0, lengthDim, widthDim);

    return false;
}

void Space::initializeObj()
{
    //Instantiate all obj
    skybox = new Skybox("skybox");
    model = new Model("sword", WithTexture, this->window);
    player = new Player("ship", this->window);
   

    //Retrieve their source
    skybox->retrieveSource(lightSrc, mainCam, alterCam);
    model->retrieveSource(lightSrc, mainCam, alterCam);
    player->retrieveSource(lightSrc, mainCam, alterCam);
   

    //Set their position or Rotation
    model->setInitialPos(glm::vec3(2.0f, 0, 4.0f));
    model->setInitialRotation(glm::vec3(12, 60.0f, 0));
    model->setInitialScale(glm::vec3(0.5));


    player->setInitialPos(glm::vec3(0.5f, 0, 50.0f));
    player->setInitialRotation(glm::vec3(180.0f, 0, 0));
    player->setInitialScale(glm::vec3(30.5f));

    player->recomputeTransform();
    

}

void Space::update()
{

    skybox->update();
    
    player->update();
    model->update();

    //special Case
    model->updateLight();

}

void Space::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    skybox->draw();

    model->draw();
    player->draw();


    /* Swap front and back buffers */
    glfwSwapBuffers(this->window);


    /* Poll for and process events */
    glfwPollEvents();
}

void Space::deleteBuffer()
{
    model->deAllocate();
    glfwTerminate();
}
