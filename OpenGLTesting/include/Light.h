#pragma once
#include <glm/vec3.hpp>
struct Light
{
		Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
		{
			this->ambient = ambient;
			this->diffuse = diffuse;
			this->specular = specular;
		}
		glm::vec3 diffuse;
		glm::vec3 specular;
		glm::vec3 ambient;
};
