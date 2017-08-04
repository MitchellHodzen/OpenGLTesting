#include "Game.h"
#include "Renderer.h"
#include "InputManager.h"
#include "CameraController.h"
Game::Game()
{
	screenWidth = 800;
	screenHeight = 600;

	renderer = new Renderer(screenWidth, screenHeight, false);
	inputManager = new InputManager();
}


Game::~Game()
{
	delete renderer;
	delete inputManager;
}

void Game::Start()
{
	if (Initialize())
	{
		float averageFramerate = 0;
		int frames = 0;
		bool quit = false;

		Uint32 lastFrameTime = 0;
		Uint32 currentFrameTime = 0;
		float deltaTime = 0.0f;
		currentFrameTime = SDL_GetTicks();

		CameraController cam(renderer->camera, 0.25f);
		inputManager->SetCam(&cam);

		while (quit == false)
		{
			//Calculate frame time
			lastFrameTime = currentFrameTime;
			currentFrameTime = SDL_GetTicks();
			deltaTime = (float)(currentFrameTime - lastFrameTime) / 1000;
			averageFramerate += 1/deltaTime;
			frames++;
			
			//Get user input
			quit = inputManager->HandleInput();
			renderer->Draw();
			
			//SDL_Delay(30);
		}
		averageFramerate = averageFramerate / frames;
		std::cout<<"Average Framerate: " << averageFramerate << std::endl;
	}
}

bool Game::Initialize()
{
	if (renderer->Initialize() == true)
	{
		//mediaManager->CreateTexture("Media/Sprites/megamanx.png", renderer->GetRenderer());
		return true;
	}
	else
	{
		return false;
	}
}


