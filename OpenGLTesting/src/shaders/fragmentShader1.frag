#version 450 core
out vec4 FragColor;

//in vec2 texCoord;
in vec3 normal;
in vec3 fragPosition;
in vec3 color;

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
uniform DirectionalLight directionalLight;
uniform PointLight poLight;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDirection);
vec3 CalculateLight(vec3 lightAmbient, vec3 lightDiffuse, vec3 lightSpecular, vec3 lightDirection, vec3 normal, vec3 viewDirection);


void main()
{
	vec3 norm = normalize(normal);
	vec3 viewDirection = normalize(eyePosition - fragPosition);

	vec3 result = CalculateDirectionalLight(directionalLight, norm, viewDirection);
	result += CalculatePointLight(poLight, norm, viewDirection);

	FragColor = vec4(result, 1);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
	vec3 lightDirection = normalize(-light.direction);

	return CalculateLight(light.ambient, light.diffuse, light.specular, lightDirection, normal, viewDirection);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 viewDirection)
{
	vec3 lightDirection = normalize(light.position - fragPosition);

	float distance = length(light.position - fragPosition);
	float attenuation = 1.0/(1 + (light.linear * distance) + (light.quadratic * (distance * distance)));

	return CalculateLight(light.ambient, light.diffuse, light.specular, lightDirection, normal, viewDirection) * attenuation;
}

vec3 CalculateLight(vec3 lightAmbient, vec3 lightDiffuse, vec3 lightSpecular, vec3 lightDirection, vec3 normal, vec3 viewDirection)
{
	float diff = max(dot(normal, lightDirection), 0.0);
	//vec3 diffuse = (diff * vec3(texture(material.diffuse, texCoord))) * lightDiffuse;
	vec3 diffuse = (diff * color) * lightDiffuse;

	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = (material.specular * spec) * lightSpecular;

	//vec3 ambient = vec3(texture(material.diffuse, texCoord)) * lightAmbient;
	vec3 ambient = color * lightAmbient;

	return (ambient + diffuse + specular);

}

