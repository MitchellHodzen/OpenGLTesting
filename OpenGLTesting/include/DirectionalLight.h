#pragma once
#include "Light.h"

struct DirectionalLight : public Light
{
	DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : Light(ambient, diffuse, specular)
	{
		this->direction = direction;
	}
	glm::vec3 direction;
};
