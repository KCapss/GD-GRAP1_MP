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
1) Skybox =

2) Player =


//Debri List
3)

4)

5)

6)

7)


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