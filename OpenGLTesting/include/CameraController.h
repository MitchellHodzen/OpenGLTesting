#pragma once
#include "Camera.h"
class CameraController
{
	public:
		CameraController(Camera* camera, float speed);
		~CameraController();
		enum class Direction {UP, DOWN, LEFT, RIGHT};
		void MoveCamera(Direction direction);
	private:
		float speed;
		Camera* camera;
};
