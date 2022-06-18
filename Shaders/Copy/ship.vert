##version 330 core

layout(location = 0) in vec3 aPos;
layout (location =1) in vec3 vertexNormal;
layout(location = 2) in vec2 aTex;
layout(location = 3) in vec3 m_tangent;
layout(location = 3) in vec3 m_bitangent;
// sends out texCoord to be recieved somewhere else
out vec2 texCoord;
out vec3 normCoord;
out vec3 fragPos;
out mat3 TBN;

uniform mat4 transform;

uniform mat4 projection;

uniform mat4 view;
void main()
{
	// calculates for the final possition of the object after projection and transformation
	gl_Position =projection*view*transform*vec4(aPos, 1.0f);

	texCoord = aTex;
	mat3 modelMatrix = mat3(transpose(inverse(transform)));
	normCoord= modelMatrix  * vertexNormal;
	vec3 T = normalize(modelMatrix*m_tangent);
	vec3 B = normalize(modelMatrix*m_bitangent);
	vec3 N = normCoord;
	TBN = mat3(T,B,N);
	fragPos= vec3(transform*vec4(aPos, 1.0f));
}