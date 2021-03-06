#include "CameraController.h"
#include <glm/vec3.hpp>
#include <iostream>
CameraController::CameraController(Camera* camera, float speed)
{
	this->camera = camera;
	this->speed = speed;
	yaw = -90;
}
CameraController::~CameraController()
{
}
void CameraController::MoveCamera(Direction direction, float deltaTime)
{
	glm::vec3 camPosition = camera->GetPosition();
	glm::vec3 movementVector;
	switch (direction)
	{
		case Direction::FORWARD:
			//movementVector = glm::normalize(glm::vec3(camera->GetForward().x, 0, camera->GetForward().z)) * speed * deltaTime;
			movementVector = glm::normalize(glm::vec3(camera->GetForward())) * speed * deltaTime;
			camera->SetPosition(camPosition + movementVector);
			break;
		case Direction::BACKWARD:
			//movementVector = -(glm::normalize(glm::vec3(camera->GetForward().x, 0, camera->GetForward().z))) * speed * deltaTime;
			movementVector = -(glm::normalize(glm::vec3(camera->GetForward()))) * speed * deltaTime;
			camera->SetPosition(camPosition + movementVector);
			break;
		case Direction::LEFT:
			{
			glm::vec3 left = glm::cross(camera->GetUp(), camera->GetForward());
			movementVector = glm::normalize(glm::vec3(left.x, 0, left.z)) * speed*deltaTime;
			camera->SetPosition(camPosition + movementVector);
			break;
			}
		case Direction::RIGHT:
			{
			glm::vec3 right = glm::cross(camera->GetForward(), camera->GetUp());
			movementVector = glm::normalize(glm::vec3(right.x, 0, right.z)) * speed* deltaTime;
			camera->SetPosition(camPosition + movementVector);
			break;
			}
		case Direction::UP:
			movementVector = glm::normalize(glm::vec3(camera->GetUp())) * speed * deltaTime;
			camera->SetPosition(camPosition + movementVector);
			break;
		case Direction::DOWN:
			movementVector = glm::normalize(-(glm::vec3(camera->GetUp()))) * speed * deltaTime;
			camera->SetPosition(camPosition + movementVector);
			break;
		default:
			break;
	}
}
void CameraController::AddCameraAngle(float _yaw, float _pitch)
{
	
	yaw += _yaw;
	pitch += _pitch;
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	camera->SetPitch(pitch);
	camera->SetYaw(yaw);
}
