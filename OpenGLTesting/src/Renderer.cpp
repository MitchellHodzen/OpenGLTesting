#include "Renderer.h"



Renderer::Renderer(int screenWidth, int screenHeight, bool debug)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->debug = debug;

}


Renderer::~Renderer()
{
	SDL_DestroyRenderer(sdlRenderer);
	SDL_DestroyWindow(sdlWindow);
	sdlRenderer = NULL;
	sdlWindow = NULL;
	IMG_Quit();
	SDL_Quit();
}

//void Renderer::Render(Entity* entity, Camera* camera)
//{
	//entity->GetVisualComponent()->Render((int)entity->GetPosX() - (int)camera->GetPosX(), (int)entity->GetPosY() - (int)camera->GetPosY(), sdlRenderer);
	//if (debug == true)
	//{
	//}
//}
SDL_Window* Renderer::GetWindow()
{
	return sdlWindow;
}
void Renderer::Draw()
{
	//SDL_RenderClear(sdlRenderer);
	//texture->Render(sdlRenderer);	
	//for (unsigned i = 0; i < entityList->size(); ++i)
	//{
		//Render((*entityList)[i], camera);
	//}
	//SDL_RenderPresent(sdlRenderer);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(gProgramID);
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	SDL_GL_SwapWindow(sdlWindow);
}
void Renderer::SetRenderer(SDL_Renderer* renderer)
{
	sdlRenderer = renderer;
}
SDL_Renderer* Renderer::GetRenderer()
{
	return sdlRenderer;
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
		
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		sdlWindow = SDL_CreateWindow("Falling Sand Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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
				InitOpenGL();
			}
		}
	}
	return success;
}
bool Renderer::InitOpenGL()
{

	const GLchar* vertexShaderSource[] = {"#version 450 core\nlayout (location = 0) in vec3 aPos;\nvoid main(){ gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}"};

	const GLchar* fragmentShaderSource[] ={"#version 450 core\nout vec4 FragColor;\nvoid main( ){ FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}"};
	bool success = true;
	gProgramID = glCreateProgram();	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint vertexShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompiled);
	if (vertexShaderCompiled != GL_TRUE)
	{
		std::cout<<"Unable to compile verted shader"<<std::endl;
	}
	
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	GLint fragmentShaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompiled);
	if (fragmentShaderCompiled != GL_TRUE)
	{
		std::cout<<"Unable to compile fragment shader"<<std::endl;
	}
	glAttachShader(gProgramID, vertexShader);
	glAttachShader(gProgramID, fragmentShader);
	glLinkProgram(gProgramID);
	GLint programLinked = GL_FALSE;
	glGetProgramiv(gProgramID, GL_LINK_STATUS, &programLinked);
	if (programLinked != GL_TRUE)
	{
		std::cout<<"Unable to link program"<<std::endl;
	}	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float verticies[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return success;
	
}
