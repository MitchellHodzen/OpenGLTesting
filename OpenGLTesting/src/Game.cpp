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
		double averageFramerate = 0;
		int frames = 0;
		bool quit = false;
		bool firstFrame = true;

		Uint32 lastFrameTime = 0;
		Uint32 currentFrameTime = 0;
		double deltaTime = 0.0f;
		currentFrameTime = SDL_GetTicks();

		CameraController cam(renderer->camera, 4.0f);
		inputManager->SetCam(&cam);

		Uint32 startTicks = SDL_GetTicks();
		while (quit == false)
		{
			//Get user input
			quit = inputManager->HandleInput(deltaTime);
			renderer->Draw();

			//Calculate frame time
			lastFrameTime = currentFrameTime;
			currentFrameTime = SDL_GetTicks();
			deltaTime = (double)(currentFrameTime - lastFrameTime) / 1000;

			frames++;
			//SDL_Delay(30);
		}
		std::cout<<"Average Framerate: " << std::fixed<<(double)frames/(((double)SDL_GetTicks() - startTicks)/1000) << std::endl;
		std::cout<<"Average milliseconds per Frame: " <<std::fixed<<((double)SDL_GetTicks() - startTicks)/(double)frames<<std::endl;
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


