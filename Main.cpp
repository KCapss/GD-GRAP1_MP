#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Space.h"
#include <string>
#include <iostream>

using namespace std;


/*
Made by: Kevin Carl Capalar && Carlos Arquillos
20/06/2022 GDGRAP1

Reference for the obj and Texture:
1) Skybox = auto generated space skybox - 
https://tools.wwwtyro.net/space-3d/index.html#animationSpeed=2.049970070436972&fov=81&nebulae=
true&pointStars=true&resolution=512&seed=5va8ki692no0&stars=true&sun=true

2) Player(ship) = E-45 Ship from https://free3d.com/3d-model/e-45-aircraft-71823.html

//Debri List
3)Statue - https://free3d.com/3d-model/statue-v1--445854.html

4)Statue2 - https://free3d.com/3d-model/statue-v1--372946.html

5)SpaceRock - https://open3dmodel.com/download.php

6)Tower(Eifel) - https://free3d.com/3d-model/-eiffel-tower-v1--470573.html

7)Generator - https://free3d.com/3d-model/sci-fi-emergency-backup-generator-480843.html

8 -

Note from Tester please do go too deep or the orthocam will not be able to scan
*/

int main(void)
{
   Space* space = new Space(800, 800);
    
    if (space->initializeWindow()) {
        return 0;
    }

    space->initializeObj();

    while (!glfwWindowShouldClose(space->window))
    {
       
        //Update Data Function Call
        space->update();

        //Draw Function Call
        space->draw();

    }

    //de-allocate any remaining
    space->deleteBuffer();
   
    return 0;


}