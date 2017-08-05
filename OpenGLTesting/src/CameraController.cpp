#include "CameraController.h"
#include <glm/vec3.hpp>
#include <iostream>
CameraController::CameraController(Camera* camera, float speed)
{
	this->camera = camera;
	this->speed = speed;
}
CameraController::~CameraController()
{
}
void CameraController::MoveCamera(Direction direction)
{
	glm::vec3 camPosition = camera->GetPosition();
	switch (direction)
	{
		case Direction::UP:
			camera->SetPosition(glm::vec3(camPosition.x, camPosition.y, camPosition.z - speed));
			break;
		case Direction::DOWN:
			camera->SetPosition(glm::vec3(camPosition.x, camPosition.y, camPosition.z + speed));
			break;
		case Direction::LEFT:
			camera->SetPosition(glm::vec3(camPosition.x - speed, camPosition.y, camPosition.z));
			break;
		case Direction::RIGHT:
			camera->SetPosition(glm::vec3(camPosition.x + speed, camPosition.y, camPosition.z));
			break;
		default:
			break;
	}
}

