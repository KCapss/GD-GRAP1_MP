#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Space.h"
#include <string>
#include <iostream>

using namespace std;


/*
Made by: Kevin Carl Capalar
23/05/2022 GDGRAP1

Reference: Plant Pot
https://free3d.com/3d-model/indoor-pot-plant-77983.html 
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
        //Some function


        //Draw Function Call
        space->draw();

    }

    //de-allocate any remaining
    space->deleteBuffer();
   
    return 0;


}