#pragma once
#include "Vector3.h"

class Cube
{
	public:
		Cube();
		Cube(Vector3 position);
		Cube(float x, float y, float z);
		~Cube();
		Vector3 GetPosition();
		void SetPosition(Vector3 position);
		void SetPosition(float x, float y, float z);
	private:
		Vector3 position;
};

