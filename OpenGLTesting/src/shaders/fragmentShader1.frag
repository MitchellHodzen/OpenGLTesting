#version 450 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPosition;

uniform sampler2D currentTexture;
uniform vec3 ambientLight;
uniform vec3 objectColor;
uniform vec3 lightPosition;

void main()
{
	vec3 norm = normalize(normal);
	vec3 lightDirection = normalize(lightPosition - fragPosition);
	float diff = max(dot(norm, lightDirection), 0.0);
	vec3 diffuse = diff * ambientLight;
	float ambientIntensity = 0.1;
	vec3 amb = ambientIntensity * ambientLight;
	vec3 result = (amb + diffuse) * objectColor;
	FragColor = texture(currentTexture, texCoord) * vec4(result, 1);
}
