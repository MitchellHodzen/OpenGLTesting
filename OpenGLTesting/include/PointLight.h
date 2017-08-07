#pragma once
#include "Light.h"

struct PointLight : public Light
{
	PointLight(glm::vec3 position, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : Light(ambient, diffuse, specular)
	{
		this->position = position;
		this->linear = linear;
		this->quadratic = quadratic;
	}
	glm::vec3 position;
	float linear;
	float quadratic;
};
