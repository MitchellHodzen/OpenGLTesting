#include "Cube.h"

Cube::Cube()
{
	position = glm::vec3();
	sides[WIDTH] = 0.0f;
	sides[HEIGHT] = 0.0f;
	sides[LENGTH] = 0.0f;
}
Cube::Cube(glm::vec3 position, float width, float height, float length)
{
	this->position = position;
	sides[WIDTH] = width;
	sides[HEIGHT] = height;
	sides[LENGTH] = length;
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
float Cube::GetWidth()
{
	return sides[WIDTH];
}
float Cube::GetHeight()
{
	return sides[HEIGHT];
}
float Cube::GetLength()
{
	return sides[LENGTH];
}
void Cube::SetWidth(float width)
{
	sides[WIDTH] = width;
}
void Cube::SetHeight(float height)
{
	sides[HEIGHT] = height;
}
void Cube::SetLength(float length)
{
	sides[LENGTH] = length;
}
