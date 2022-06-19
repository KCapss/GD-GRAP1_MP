#version 330 core 

uniform vec3 lightColor;

out vec4 FragColor; //Returns a Color

void main()
{
    
    FragColor = vec4(lightColor, 1.0f); //Same color as the lightSource or fade white if disabled;
}