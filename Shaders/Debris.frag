#version 330 core

uniform sampler2D tex0;
// for diffuse
uniform vec3 lightPos;
uniform vec3 lightColor;
// for ambience
uniform float ambientStr;
uniform vec3 ambientClr;
//for specular
uniform vec3 cameraPos;
uniform float specStr;
uniform float specPhong;
	

//gets texCoord, normCoord and fragPos from vert shader
in vec2 texCoord;
in vec3 normCoord;
in vec3 fragPos;
// output fragment color
out vec4 FragColor;

void main()
{
vec3 normal = normalize(normCoord);
vec3 lightDir = normalize(lightPos - fragPos);
vec4 pixelColor = texture(tex0,texCoord);
if(pixelColor.a<0.1)
{
discard;
}
float diff =max(dot(normal,lightDir),0.0);
//diffuse lighting
vec3 diffuse = diff * lightColor;
// ambient lighting
vec3 ambientCol = ambientClr * ambientStr;
// specular Lighting
vec3 viewDir = normalize(cameraPos - fragPos);
vec3 reflectDir = reflect(-lightDir, normal);
float spec = pow(max(dot(reflectDir, viewDir), 0.1), specPhong);
vec3 specColor = spec * specStr * lightColor;	
//point light
float distance = length(lightPos-fragPos);
float attenuation = 1.f/(pow(distance, 2));

// applies textures to object
FragColor = (vec4((specColor + ambientCol + diffuse), 1.0)*attenuation) * texture(tex0, texCoord);
} 

}