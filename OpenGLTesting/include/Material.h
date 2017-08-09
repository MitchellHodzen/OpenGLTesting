#pragma once
#include <SDL_opengl.h>
struct Material
{
	Material(GLuint diffuseTextureID, glm::vec3 specular, float shininess)
	{
		this->diffuseTextureID = diffuseTextureID;
		this->specular = specular;
		this->shininess = shininess;
	}
	Material(){}
	GLuint diffuseTextureID;
	glm::vec3 specular;
	float shininess;
};
