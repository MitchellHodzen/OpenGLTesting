#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
struct Vertex{
	Vertex(){}
	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 textureCoordinates)
	{
		this->position = position;
		this->normal = normal;
		this->textureCoordinates = textureCoordinates;
	}
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
};
