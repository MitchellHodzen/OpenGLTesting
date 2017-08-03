#include "Renderer.h"



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
	glUseProgram(shader->GetShaderID());
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
				if (!InitOpenGL())
				{
					std::cout<<"Failed to initialize OpenGL"<<std::endl;
					success = false;
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
	//std::string vertexShaderSourceString = ReadShader("src/shaders/vertexShader1.vert");
	//std::string fragmentShaderSourceString = ReadShader("src/shaders/fragmentShader1.frag");
	//const char* vertexShaderSource = vertexShaderSourceString.c_str();
	//const char* fragmentShaderSource = fragmentShaderSourceString.c_str();

	//gProgramID = glCreateProgram();	
	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1,&vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	//GLint vertexShaderCompiled = GL_FALSE;
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompiled);
	if (!shader->ReadVertexShader("src/shaders/vertexShader1.vert"))
	{
		std::cout<<"Unable to compile vertex shader"<<std::endl;
		success = false;
	}
	else
	{
		//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		//glCompileShader(fragmentShader);
		//GLint fragmentShaderCompiled = GL_FALSE;
		//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompiled);
		if (!shader->ReadFragmentShader("src/shaders/fragmentShader1.frag"))//fragmentShaderCompiled != GL_TRUE)
		{
			std::cout<<"Unable to compile fragment shader"<<std::endl;
			success = false;
		}
		else
		{
			//glAttachShader(gProgramID, vertexShader);
			//glAttachShader(gProgramID, fragmentShader);
			//glLinkProgram(gProgramID);
			//GLint programLinked = GL_FALSE;
			//glGetProgramiv(gProgramID, GL_LINK_STATUS, &programLinked);
			if (!shader->LinkShaders())//programLinked != GL_TRUE)
			{
				std::cout<<"Unable to link program"<<std::endl;
				success = false;
			}	
			//else
			//{

				//glDeleteShader(vertexShader);
				//glDeleteShader(fragmentShader);
			//}
		}
	}
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

std::string Renderer::ReadShader(std::string location)
{
	std::ifstream shaderStream(location, std::ios::in);
	std::string shaderString{ std::istreambuf_iterator<char>(shaderStream), std::istreambuf_iterator<char>()};
	return shaderString;
}
