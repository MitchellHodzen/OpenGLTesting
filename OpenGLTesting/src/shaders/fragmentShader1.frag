#version 450 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPosition;

struct Material
{
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 eyePosition;

uniform Material material;
uniform Light light;

void main()
{
	vec3 norm = normalize(normal);
	vec3 lightDirection = normalize(light.position - fragPosition);
	vec3 viewDirection = normalize(eyePosition - fragPosition);
	vec3 reflectDirection = reflect(-lightDirection, norm);

	vec3 diffuse = (max(dot(norm, lightDirection), 0.0) * vec3(texture(material.diffuse, texCoord))) * light.diffuse;

	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = (material.specular * spec) * light.specular;

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));

	vec3 result = ambient + diffuse + specular;
	//FragColor = texture(material.diffuse, texCoord) * vec4(result, 1);
	FragColor = vec4(result, 1);
}
