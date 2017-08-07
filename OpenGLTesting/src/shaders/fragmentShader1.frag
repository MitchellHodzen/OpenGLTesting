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

struct DirectionalLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	float linear;
	float quadratic;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 eyePosition;

uniform Material material;
uniform DirectionalLight dirLight;
uniform PointLight poLight;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDirection);

void main()
{
	vec3 norm = normalize(normal);
	vec3 viewDirection = normalize(eyePosition - fragPosition);

	vec3 result = CalculateDirectionalLight(dirLight, norm, viewDirection);
	result += CalculatePointLight(poLight, norm, viewDirection);

	FragColor = vec4(result, 1);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
	vec3 lightDirection = normalize(-light.direction);

	vec3 diffuse = (max(dot(normal, lightDirection), 0.0) * vec3(texture(material.diffuse, texCoord))) * light.diffuse;

	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess); 
	vec3 specular = (material.specular * spec) * light.specular;

	vec3 ambient = vec3(texture(material.diffuse, texCoord)) * light.ambient;

	return ambient + diffuse + specular;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDirection)
{
	vec3 lightDirection = normalize(light.position - fragPosition);

	vec3 diffuse = (max(dot(normal, lightDirection), 0.0) * vec3(texture(material.diffuse, texCoord))) * light.diffuse;

	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess); 
	vec3 specular = (material.specular * spec) * light.specular;

	vec3 ambient = vec3(texture(material.diffuse, texCoord)) * light.ambient;
	float distance = length(light.position - fragPosition);
	float attenuation = 1.0/(1 + (light.linear * distance) + (light.quadratic * (distance * distance)));

	return (ambient + diffuse + specular) * attenuation;
}
