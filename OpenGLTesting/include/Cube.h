#pragma once
#include "glm/vec3.hpp"

class Cube
{
	public:
		Cube();
		Cube(glm::vec3 position);
		//Cube(float x, float y, float z);
		~Cube();
		glm::vec3 GetPosition();
		void SetPosition(glm::vec3 position);
		//void SetPosition(float x, float y, float z);
	private:
		glm::vec3 position;
};

