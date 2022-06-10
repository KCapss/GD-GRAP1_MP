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
    model = new Model("ship", WithTexture, this->window);
    player = new Player("sword", this->window);
   

    //Retrieve their source
    skybox->retrieveSource(lightSrc, mainCam, alterCam);
    model->retrieveSource(lightSrc, mainCam, alterCam);
    player->retrieveSource(lightSrc, mainCam, alterCam);
   

    //Set their position
    model->setInitialPos(glm::vec3(0.5f, 0, 0));

}

void Space::update()
{
    player->update();
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
