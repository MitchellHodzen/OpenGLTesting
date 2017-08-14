#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Material.h"
#include "Chunk.h"
#include <vector>
#include "Mesh.h"
//#include <glm/gtx/quaternion.hpp>
//#include <glm/gtc/quaternion.hpp>

Renderer::Renderer(int screenWidth, int screenHeight, bool debug)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->debug = debug;
}


Renderer::~Renderer()
{
	delete material;
	delete directionalLight;
	delete texture;
	delete shader;
	delete chunk;
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
	glUseProgram(shader->GetShaderID());

	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / screenHeight, 0.1f, 100.0f);
	glm::mat4 VP = projection * view;
	shader->SetMat4("VP", VP);
	

	/*
	//shader->SetVec3("eyePosition", camera->GetPosition());

	//shader->SetMaterial(material);

	shader->SetVec3("poLight.ambient", 0.1, 0.1, 0.1);
	shader->SetVec3("poLight.diffuse", 1, 1, 1);
	shader->SetVec3("poLight.specular", 1.0, 1.0, 1.0);
	shader->SetVec3("poLight.position", 10, 3, 0);
	shader->SetFloat("poLight.linear", 0.045f);
	shader->SetFloat("poLight.quadratic", 0.0075f);

	shader->SetDirectionalLight(directionalLight);
	*/

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

	shader->SetMat4("model", glm::translate(glm::mat4(), chunk->GetChunkPosition()));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	chunk->GetChunkMesh()->Draw();
	SDL_GL_SwapWindow(sdlWindow);

	GLenum err;
	while ((err=glGetError()) != GL_NO_ERROR)
	{
		std::cout<<"Error: "<< err << std::endl;
	}
}

bool Renderer::Initialize()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not be initialized. SDL error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);

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
				glEnable(GL_CULL_FACE);
				glFrontFace(GL_CCW);
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
					directionalLight = new DirectionalLight(glm::vec3(0, -1, 0), glm::vec3(0.1, 0.1, 0.1), glm::vec3(.5, .5, .5), glm::vec3(1.0, 1.0, 1.0));
					material = new Material(texture->GetTextureID(), glm::vec3(0.5, 0.5, 0.5), 32.0);

					chunk = new Chunk(glm::vec3(0, 0, -20), 16, 16, 16, 1.0, 1.0, 1.0);
					shader->SetUniformLocation("VP");
					shader->SetUniformLocation("model");
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
	if (!shader->ReadVertexShader("src/shaders/simpleVertex.vert"))
	{
		std::cout<<"Unable to compile vertex shader"<<std::endl;
		success = false;
	}
	else
	{
		if (!shader->ReadFragmentShader("src/shaders/simpleFragment.frag"))//fragmentShaderCompiled != GL_TRUE)
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
	//	position	texture coords         normals
	float verticies[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,


		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,


		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,


		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,


		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,


		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f
	};
	*/


	/*
	//	position	texture coords         normals
	float verticies[] = {
		//Back Face
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,

		//Front Face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,

		//Left Face
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,

		//Right Face
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

		//Bottom Face
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,

		//Top Face
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	};

	unsigned int indicies[] = {
		//Back Face
		0, 1, 2,
		1, 0, 3,
		//Front Face
		4, 5, 6,
		6, 7, 4,
		//Left Face
		8, 9, 10,
		10, 11, 8,
		//Right Face
		13, 14, 15,
		15, 14, 12,
		//Bottom Face
		16, 17, 18,
		16, 18, 19,
		//Top Face
		22, 23, 21,
		23, 22, 20
	};
	*/

	texture = new Texture();

	//if (!texture->LoadTexture("resources/textures/grass.png", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR))
	if (!texture->LoadTexture("resources/textures/crate1_diffuse.png", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR))
		//if (!texture->LoadTexture("resources/textures/container2.png", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR))
	{
		std::cout<<"Could not load texture"<<std::endl;
		success = false;
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

	target = new glm::vec3(0, 0, 0);
	camera = new Camera();
	camera->SetTarget(target);
	camera->SetPosition(glm::vec3(0, 0, 0));
	camera->SetTarget(NULL);
	return success;

}
