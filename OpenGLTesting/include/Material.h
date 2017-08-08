#pragma once
class Texture;
struct Material
{
	Material(Texture* diffuseTexture, glm::vec3 specular, float shininess)
	{
		this->diffuseTexture = diffuseTexture;
		this->specular = specular;
		this->shininess = shininess;
	}
	Material(){}
	Texture* diffuseTexture;
	glm::vec3 specular;
	float shininess;
};
