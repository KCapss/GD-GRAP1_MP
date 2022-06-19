#version 330 core

uniform sampler2D tex0;
uniform sampler2D norm_tex;

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

//for the changing light types
uniform float lightType;	

//gets texCoord, normCoord and fragPos from vert shader
in vec2 texCoord;
in vec3 normCoord;
in vec3 fragPos;
in mat3 TBN;

// output fragment color
out vec4 FragColor;

void main()
{
	//vec3 normal = normalize(normCoord);
	vec3 normal = texture(norm_tex,texCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal =normalize(TBN*normal);

	//conditional for light types 1 = point light, 2 = direction light

	if(lightType == 1){
		vec3 lightDir = normalize(lightPos - fragPos);
	}
	
	else if(lightType == 2){
		vec3 lightDir = normalize(lightPos + fragPos);
	}

	vec4 pixelColor = texture(tex0,texCoord);

	if(pixelColor.a < 0.1) {
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
	if(lightType ==1)
	{
		FragColor = (vec4((specColor + ambientCol + diffuse) * attenuation , 1.0)) * texture(tex0, texCoord)
	}
	else if(lightType ==2)
	{
		FragColor = (vec4((specColor + ambientCol + diffuse), 1.0)) * texture(tex0, texCoord)
	}
}
