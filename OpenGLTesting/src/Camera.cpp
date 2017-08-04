#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
	//Default camera at the origin, pointing upright away form the screen
	position = glm::vec3();
	up = glm::vec3(0, 1, 0);
	forward = glm::vec3(0, 0, -1);
	target = NULL;
}
Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	//If there is no target, point in the foward direction
	if (target == NULL)
	{
		return glm::lookAt(position, position + forward, up);
	}
	//Otherwise point at the target
	return glm::lookAt(position, *target, up); 
}

glm::vec3 Camera::GetPosition()
{
	return position;
}

void Camera::SetPosition(glm::vec3 newPosition)
{
	position = newPosition;
}
void Camera::SetUp(glm::vec3 newUp)
{
	up = newUp;
}
void Camera::SetForward(glm::vec3 newForward)
{
	forward = newForward;
}
void Camera::SetCamera(glm::vec3 newPosition, glm::vec3 newUp, glm::vec3 newForward)
{
	position = newPosition;
	up = newUp;
	forward = newForward;
}
void Camera::SetTarget(glm::vec3* newTarget)
{
	//If there was a target and it has been removed, set the forward direction to point towards the previous target
	if (newTarget == NULL && target != NULL)
	{
		forward = glm::normalize(*target - position);
	}
	target = newTarget;
}
