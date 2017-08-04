#include "InputManager.h"
#include "CameraController.h"


InputManager::InputManager()
{
	currentKeyboardState = SDL_GetKeyboardState(NULL);
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
	if (currentKeyboardState[SDL_SCANCODE_UP])
	{
		cam->MoveCamera(CameraController::Direction::UP);
	}
	if (currentKeyboardState[SDL_SCANCODE_LEFT])
	{
		cam->MoveCamera(CameraController::Direction::LEFT);
	}
	if (currentKeyboardState[SDL_SCANCODE_RIGHT])
	{
		cam->MoveCamera(CameraController::Direction::RIGHT);
	}
	if (currentKeyboardState[SDL_SCANCODE_DOWN])
	{
		cam->MoveCamera(CameraController::Direction::DOWN);
	}
	return quit;
}
