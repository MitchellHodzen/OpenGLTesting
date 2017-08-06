#include "Cube.h"

Cube::Cube()
{
	position = glm::vec3();
}
Cube::Cube(glm::vec3 position)
{
	this->position = position;
}
Cube::~Cube()
{
}

glm::vec3 Cube::GetPosition()
{
	return position;
}

void Cube::SetPosition(glm::vec3 position)
{
	this->position = position;
}

