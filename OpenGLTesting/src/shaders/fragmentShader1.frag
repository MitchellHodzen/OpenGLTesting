#version 450 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPosition;

uniform sampler2D currentTexture;
uniform vec3 ambientLight;
uniform vec3 objectColor;
uniform vec3 lightPosition;
uniform vec3 eyePosition;

void main()
{
	float ambientIntensity = 0.1;
	float specularStrength = 0.5;
	float shininess = 32;

	vec3 norm = normalize(normal);
	vec3 lightDirection = normalize(lightPosition - fragPosition);
	vec3 diffuse = max(dot(norm, lightDirection), 0.0) * ambientLight;

	vec3 viewDirection = normalize(eyePosition - fragPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
	vec3 specular = specularStrength * spec * ambientLight;

	vec3 result = ((ambientIntensity * ambientLight) + diffuse + specular) * objectColor;
	FragColor = texture(currentTexture, texCoord) * vec4(result, 1);
}
