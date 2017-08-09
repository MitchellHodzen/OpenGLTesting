#pragma once
#include <SDL.h>
#include <stdio.h>
class CameraController;
class InputManager
{
public:
	InputManager();
	~InputManager();
	bool HandleInput(float deltaTime);
	void SetCam(CameraController* cameraController);
private:
	SDL_Event e;
	const Uint8* currentKeyboardState;
	CameraController* cam;
};

