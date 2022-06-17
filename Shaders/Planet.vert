#version 330 core //Version Number

layout(location = 0) in vec3 aPos; 

uniform mat4 lightTransform;
uniform mat4 lightProjection;
uniform mat4 lightView;

void main()
{
    gl_Position = lightProjection * lightView * lightTransform * vec4(aPos, 1); 
   
}