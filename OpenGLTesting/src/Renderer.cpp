#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Cube.h"


Renderer::Renderer(int screenWidth, int screenHeight, bool debug)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->debug = debug;
}


Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	delete shader;
	SDL_DestroyWindow(sdlWindow);
	sdlWindow = NULL;
	SDL_Quit();
}

SDL_Window* Renderer::GetWindow()
{
	return sdlWindow;
}
void Renderer::Draw()
{
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / screenHeight, 0.1f, 100.0f);

	int viewLoc = glGetUniformLocation(shader->GetShaderID(), "view");
	int projLoc = glGetUniformLocation(shader->GetShaderID(), "projection");
	
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader->GetShaderID());
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
	glBindVertexArray(VAO);
	for (int i = 0; i < cubeAmount; ++i)
	{
		glm::mat4 model;
		model = glm::translate(model, cubeArray[i].GetPosition());
		model = glm::rotate(model, ((float)SDL_GetTicks()/1000)*glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		int modelLoc = glGetUniformLocation(shader->GetShaderID(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	SDL_GL_SwapWindow(sdlWindow);
}

bool Renderer::Initialize()
{
	bool success = true;
	cubeAmount = 1000;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not be initialized. SDL error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		sdlWindow = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (sdlWindow == NULL)
		{
			std::cout << "SDL Window could not be created. SDL error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			gContext = SDL_GL_CreateContext(sdlWindow);
			if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
			{
				std::cout<<"Failed to initialize GLAD" << std::endl;
				success = false;
			}
			else 
			{
				glViewport(0, 0, screenWidth, screenHeight);
				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glEnable(GL_DEPTH_TEST);
				if (SDL_GL_SetSwapInterval(0) < 0)
				{
					std::cout<<"Unable to disable vsync"<<std::endl;
				}
				if (!InitOpenGL())
				{
					std::cout<<"Failed to initialize OpenGL"<<std::endl;
					success = false;
				}
				else
				{
					cubeArray = new Cube[cubeAmount];
					for (int i = 0; i < cubeAmount; ++i)
					{
						cubeArray[i] = Cube(glm::vec3(i, 0, 0));
					}
				}
			}
		}
	}
	return success;
}
bool Renderer::InitOpenGL()
{
	bool success = true;
	shader = new Shader();
	if (!shader->ReadVertexShader("src/shaders/vertexShader1.vert"))
	{
		std::cout<<"Unable to compile vertex shader"<<std::endl;
		success = false;
	}
	else
	{
		if (!shader->ReadFragmentShader("src/shaders/fragmentShader1.frag"))//fragmentShaderCompiled != GL_TRUE)
		{
			std::cout<<"Unable to compile fragment shader"<<std::endl;
			success = false;
		}
		else
		{
			if (!shader->LinkShaders())//programLinked != GL_TRUE)
			{
				std::cout<<"Unable to link program"<<std::endl;
				success = false;
			}	
		}
	}
	/*	
	float verticies[] = {
		//Position          Texture coords
		0.5f, 0.5f, 0.0f,   1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,  0.0f, 1.0f
	};
	*/
	//	position	texture coords
	float verticies[] = {
   		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	unsigned int indicies[] = {
		0, 1, 3,
		1, 2, 3
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	texture = new Texture();

	//if (!texture->LoadTexture("resources/textures/grass.png", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR))
	if (!texture->LoadTexture("resources/textures/crate1_diffuse.png", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR))
	{
		std::cout<<"Could not load texture"<<std::endl;
		success = false;
	}	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

	target = new glm::vec3(0, 0, 0);
	camera = new Camera();
	camera->SetTarget(target);
	camera->SetPosition(glm::vec3(0, 0, 3));
	camera->SetTarget(NULL);
	return success;
	
}
