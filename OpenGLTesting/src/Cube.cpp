#include "Cube.h"

Cube::Cube()
{
	position = Vector3();
}
Cube::Cube(Vector3 position)
{
	this->position = position;
}
Cube::Cube(float x, float y, float z)
{
	position = Vector3(x, y, z);
}
Cube::~Cube()
{
}

Vector3 Cube::GetPosition()
{
	return position;
}

void Cube::SetPosition(Vector3 position)
{
	this->position = position;
}
void Cube::SetPosition(float x, float y, float z)
{
	position = Vector3(x, y, z);
}

