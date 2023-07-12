#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texture;
layout(location = 3) in vec3 normal;

out vec3 vertexColor;
out vec2 textureCoordinates;
out vec3 vertexNormal;
out vec3 vertexFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	vertexColor = color;

	textureCoordinates = texture;

	vertexNormal = mat3(transpose(inverse(model))) * normal;
	vertexFragPos = vec3(model * vec4(position, 1.0f));
}

#shader fragment
#version 440 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 textureCoordinates;
in vec3 vertexNormal;
in vec3 vertexFragPos;

uniform sampler2D tex0;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 lightColorSec;
uniform vec3 lightPosSec;
uniform vec3 viewPos;

void main()
{
	// Ambient Light
	float ambientStrength = 0.65f;
	vec3 ambient = ambientStrength * vec3(1.0f);

	// Diffuse Light
	vec3 norm = normalize(vertexNormal);
	vec3 lightDir = normalize(lightPos - vertexFragPos);
	float impact = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = impact * lightColor;

	// Secondary Diffuse Light
	vec3 lightDirSec = normalize(lightPosSec - vertexFragPos);
	float impactSec = max(dot(norm, lightDirSec), 0.0);
	vec3 diffuseSec = impactSec * lightColorSec;

	// Specular Light
	float specularIntensity = 0.5f;
	float highlightSize = 16.0f;
	vec3 viewDir = normalize(viewPos - vertexFragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	//Calculate specular component
	float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
	vec3 specular = specularIntensity * specularComponent * lightColor;

	// Texture holds the color to be used for all three components
	vec4 textureColor = texture(tex0, textureCoordinates);

	vec3 result = (ambient + diffuse + +diffuseSec + specular) * textureColor.xyz;
	FragColor = vec4(result, 1.0);
}
