#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Cube.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Vertex.h"
#include "Material.h"
#include "Chunk.h"

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
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	delete material;
	delete directionalLight;
	delete texture;
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
	glm::mat4 VP = projection * view;

	shader->SetMat4("VP", VP);
	shader->SetVec3("eyePosition", camera->GetPosition());

	shader->SetMaterial(material);

	shader->SetVec3("poLight.ambient", 0.1, 0.1, 0.1);
	shader->SetVec3("poLight.diffuse", 1, 1, 1);
	shader->SetVec3("poLight.specular", 1.0, 1.0, 1.0);
	shader->SetVec3("poLight.position", 10, 3, 10);
	shader->SetFloat("poLight.linear", 0.045f);
	shader->SetFloat("poLight.quadratic", 0.0075f);

	shader->SetDirectionalLight(directionalLight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader->GetShaderID());
	glBindVertexArray(VAO);
	/*
	for (int i = 0; i < cubeAmount; ++i)
	{
		glm::mat4 model;
		model = glm::translate(model, cubeArray[i].GetPosition());
		//model = glm::rotate(model, ((float)SDL_GetTicks()/1000)*glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		//glm::quat myQuat = glm::normalize(glm::angleAxis(((float)SDL_GetTicks()/1000)*glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)));
		//model = model * glm::mat4_cast(myQuat);
		shader->SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	*/
	for (int x = 0; x < chunk->GetChunkWidth(); ++x)
	{
		for (int y = 0; y < chunk->GetChunkHeight(); ++y)
		{
			for (int z = 0; z < chunk->GetChunkLength(); ++z)
			{
				glm::mat4 model;
				model = glm::translate(model, chunk->GetBlockPosition(x, y, z));
				shader->SetMat4("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}
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
					int width = glm::sqrt(cubeAmount);
					int length = glm::sqrt(cubeAmount);
					int counter = 0;
					for (int x = 0; x < width; ++x)
					{
						for (int z = 0; z < length; ++z)
						{
							cubeArray[counter++] = Cube(glm::vec3(x, -1, z), 1.0f, 1.0f, 1.0f);
						}
					}
					directionalLight = new DirectionalLight(glm::vec3(0, -1, 0), glm::vec3(0.1, 0.1, 0.1), glm::vec3(.5, .5, .5), glm::vec3(1.0, 1.0, 1.0));
					material = new Material(texture->GetTextureID(), glm::vec3(0.5, 0.5, 0.5), 32.0);

					chunk = new Chunk(glm::vec3(), 16, 16, 16, 4.0, 4.0, 4.0);


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
	//	position	texture coords         normals
	float verticies[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

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
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GL_FLOAT), (void*)(5*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

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
	camera->SetPosition(glm::vec3(0, 0, 3));
	camera->SetTarget(NULL);
	return success;

}
