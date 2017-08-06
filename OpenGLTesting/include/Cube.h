#pragma once
#include "glm/vec3.hpp"

class Cube
{
	public:
		Cube();
		Cube(glm::vec3 position, float width, float height, float length);
		~Cube();
		glm::vec3 GetPosition();
		void SetPosition(glm::vec3 position);
		float GetWidth();
		float GetHeight();
		float GetLength();	
		void SetWidth(float width);
		void SetHeight(float height);
		void SetLength(float length);
	private:
		enum Side {LENGTH, WIDTH, HEIGHT};
		glm::vec3 position;
		float sides[3];
};

