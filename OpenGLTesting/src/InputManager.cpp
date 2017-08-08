#include "InputManager.h"
#include "CameraController.h"
#include <iostream>


InputManager::InputManager()
{
	currentKeyboardState = SDL_GetKeyboardState(NULL);
	//SDL_GetMouseState(&lastMouseX, &lastMouseY);
}


InputManager::~InputManager()
{
}

void InputManager::SetCam(CameraController* cameraController)
{
	cam = cameraController;
}

bool InputManager::HandleInput()
{
	bool quit = false;
	while (SDL_PollEvent(&e) != 0 && e.key.repeat == 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				break;
			}
		}
		if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				break;
			case SDLK_LEFT:
				break;
			case SDLK_RIGHT:
				break;
			case SDLK_DOWN:
				break;
			}
		}
	}
	if (currentKeyboardState[SDL_SCANCODE_W])
	{
		cam->MoveCamera(CameraController::Direction::UP);
	}
	if (currentKeyboardState[SDL_SCANCODE_A])
	{
		cam->MoveCamera(CameraController::Direction::LEFT);
	}
	if (currentKeyboardState[SDL_SCANCODE_D])
	{
		cam->MoveCamera(CameraController::Direction::RIGHT);
	}
	if (currentKeyboardState[SDL_SCANCODE_S])
	{
		cam->MoveCamera(CameraController::Direction::DOWN);
	}
	int mouseX, mouseY;
	SDL_GetRelativeMouseState(&mouseX, &mouseY);
	//std::cout<<mouseX<<"   "<<mouseY<<std::endl;
	float mouseXOffset = mouseX;//(float) mouseX - lastMouseX; 
	float mouseYOffset = -mouseY;//(float) lastMouseY - mouseY;
	//lastMouseX = mouseX;
	//lastMouseY = mouseY;

	float sensitivity = 0.05;
	//mouseX *= sensitivity;
	//mouseY *= sensitivity;
	mouseXOffset *= sensitivity;
	mouseYOffset *= sensitivity;
	cam->AddCameraAngle(mouseXOffset, mouseYOffset);
	return quit;
}
