#pragma once
#include "Camera.h"
class CameraController
{
	public:
		CameraController(Camera* camera, float speed);
		~CameraController();
		enum class Direction {UP, DOWN, LEFT, RIGHT};
		void MoveCamera(Direction direction);
		void AddCameraAngle(float yaw, float pitch);
	private:
		float speed;
		Camera* camera;
		float yaw;
		float pitch;
};
