#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
class Camera
{
	public:
		Camera();
		~Camera();
		glm::mat4 GetViewMatrix();
		glm::vec3 GetPosition();
		void SetPosition(glm::vec3 newPosition);
		void SetCamera(glm::vec3 newPosition, glm::vec3 newUp, glm::vec3 newRight);
		void SetUp(glm::vec3 newUp);
		void SetForward(glm::vec3 newForward);
		glm::vec3 GetForward();
		glm::vec3 GetUp();
		void SetTarget(glm::vec3* newTarget);
		void SetPitch(float pitch);
		void SetYaw(float yaw);
	private:
		glm::vec3 position;
		glm::vec3* target;
		glm::vec3 up;
		glm::vec3 forward;
		float pitch;
		float yaw;
};
