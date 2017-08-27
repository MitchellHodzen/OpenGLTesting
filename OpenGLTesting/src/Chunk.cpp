#include "Chunk.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "World.h"
#include <SDL.h>


Chunk::Chunk(glm::vec3 chunkPosition, World* world, int width, int height, int length, float blockSize, float* heightData)
{
	this->chunkPosition = chunkPosition;
	chunkWidth = width;
	chunkHeight = height;
	chunkLength = length;
	this->blockSize = blockSize;
	//modelMatricies = new std::vector<glm::mat4>;
	//chunkMesh = new Mesh();
	chunkMesh = NULL;
	this->world = world;
	layerHasEmptyBlock = new bool[chunkHeight];
	GenerateChunk(heightData);
}
Chunk::~Chunk()
{
	delete[] chunkData;
	delete chunkMesh;
	delete[] layerHasEmptyBlock;
}
int Chunk::CalculateIndexPosition(int x, int y, int z)
{
	//All Y coordinates grouped together
	//return y + (x * chunkHeight) + (z * chunkHeight * chunkWidth);


	//All y coordinates far appart (layers calculated one Y coordinate at a time)
	return z + (x * chunkLength) + (y * chunkLength * chunkWidth);
}

int Chunk::chunkCount = 0;
void Chunk::GenerateChunk(float* heightData)
{
	/*
	std::cout<<"Generating Chunk "<< chunkCount++<<std::endl;
	double start = (double)SDL_GetTicks();
	*/

	/*
	chunkData = new Block[chunkWidth * chunkHeight * chunkLength];
	for (int i = 0; i < chunkWidth * chunkHeight * chunkLength; ++i)
	{
		chunkData[i] = Block(BlockData::BlockName::GRASS);
	}
	*/
	///*
	chunkData = new Block[chunkWidth * chunkHeight * chunkLength];
	for(int y = 0; y < chunkHeight; ++y)
	{
		for(int x = 0; x < chunkWidth; ++x)
		{
			for(int z = 0; z < chunkLength; ++z)
			{
				float height = (y * blockSize) + chunkPosition.y;
				if (height > heightData[x + (z * chunkWidth)])
				{
					//We generate blocks by column from the bottom to the top. If a block is air, then all blocks above will be air
					layerHasEmptyBlock[y] = true;
					break;
				}
				if (height < heightData[x + (z * chunkWidth)] - .5)
				{
					chunkData[CalculateIndexPosition(x, y, z)] = Block(BlockData::BlockName::DIRT);
				}
				else
				{
					chunkData[CalculateIndexPosition(x, y, z)] = Block(BlockData::BlockName::GRASS);
				}
				layerHasEmptyBlock[y] = false;
				//if (x == 0 || z == 0 || y == 0 || x == chunkWidth -1 || y == chunkHeight -1 || z == chunkLength -1)
				//{
					//chunkData[y + (x * chunkHeight) + (z * chunkHeight * chunkWidth)] = Block(BlockData::BlockName::DEBUG);
				//}
			}
		}
	}
	//*/
	//GenerateChunkMesh();
	/*
	double end = (double) SDL_GetTicks();
	double total = end - start;
	std::cout<<"Start: "<< start<< ". End: "<<end<<". Time to generate: "<<total<<std::endl<<std::endl;
	*/
}

void Chunk::GenerateChunkMesh()
{
	///*
	std::cout<<"Generating Chunk Mesh "<< chunkCount++<<std::endl;
	double start = (double)SDL_GetTicks();
	//*/
	if (chunkMesh == NULL)
	{
		chunkMesh = new Mesh();
	}
	chunkMesh->ClearVertices();
	for(int y = 0; y < chunkHeight; ++y)
	{
		for(int x = 0; x < chunkWidth; ++x)
		{
			for(int z = 0; z < chunkLength; ++z)
			{
				if (GetBlockVisibility(x, y, z) == BlockData::BlockVisibility::VISIBLE)
				{
					CheckVisibleFaces(x, y, z);
				}
			}
		}
	}
	chunkMesh->BuildVBO();
	///*
	double end = (double) SDL_GetTicks();
	double total = end - start;
	std::cout<<"Time to generate: "<<total<<std::endl<<" ms"<<std::endl;
	//*/
}

void Chunk::AddBlockFace(BlockFace face, glm::vec3 blockPosition, glm::vec3 color)
{
	switch(face)
	{
		case BlockFace::FRONT:
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 0.0f, 1.0f), color));//glm::vec2(0.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 0.0f, 1.0f), color));//glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 0.0f, 1.0f), color));//glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 0.0f, 1.0f), color));//glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 0.0f, 1.0f), color));//glm::vec2(0.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 0.0f, 1.0f), color));//glm::vec2(0.0f, 0.0f)));
			break;
		case BlockFace::BACK:
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 0.0f, -1.0f), color));//glm::vec2(0.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 0.0f, -1.0f), color));//glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 0.0f, -1.0f), color));//glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 0.0f, -1.0f), color));//glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 0.0f, -1.0f), color));//glm::vec2(0.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 0.0f, -1.0f), color));//glm::vec2(0.0f, 1.0f)));
			break;
		case BlockFace::RIGHT:
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(1.0f, 0.0f, 0.0f), color));//glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(1.0f, 0.0f, 0.0f), color));//glm::vec2(0.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(1.0f, 0.0f, 0.0f), color));//glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(1.0f, 0.0f, 0.0f), color));//glm::vec2(0.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(1.0f, 0.0f, 0.0f), color));//glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(1.0f, 0.0f, 0.0f), color));//glm::vec2(0.0f, 0.0f)));
			break;
		case BlockFace::LEFT:
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(-1.0f, 0.0f, 0.0f), color));//glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(-1.0f, 0.0f, 0.0f), color));//glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(-1.0f, 0.0f, 0.0f), color));//glm::vec2(0.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(-1.0f, 0.0f, 0.0f), color));//glm::vec2(0.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(-1.0f, 0.0f, 0.0f), color));//glm::vec2(0.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(-1.0f, 0.0f, 0.0f), color));//glm::vec2(1.0f, 0.0f)));
			break;
		case BlockFace::TOP:
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 1.0f, 0.0f), color));//glm::vec2(0.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 1.0f, 0.0f), color));//glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 1.0f, 0.0f), color));//glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 1.0f, 0.0f), color));//glm::vec2(0.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 1.0f, 0.0f), color));//glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(0.0f, 1.0f, 0.0f), color));//glm::vec2(0.0f, 1.0f)));
			break;
		case BlockFace::BOTTOM:
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(0.0f, -1.0f, 0.0f), color));//glm::vec2(0.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(0.0f, -1.0f, 0.0f), color));//glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(0.0f, -1.0f, 0.0f), color));//glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(0.0f, -1.0f, 0.0f), color));//glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f) * blockSize + blockPosition, glm::vec3(0.0f, -1.0f, 0.0f), color));//glm::vec2(0.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f) * blockSize + blockPosition, glm::vec3(0.0f, -1.0f, 0.0f), color));//glm::vec2(0.0f, 1.0f)));
			break;
	}

}

Mesh* Chunk::GetChunkMesh()
{
	return chunkMesh;
}
//std::vector<glm::mat4>* Chunk::GetModelMatricies()
//{
	//return modelMatricies;
//}
void Chunk::CheckVisibleFaces(int x, int y, int z)
{
	glm::vec3 position = glm::vec3(x, y, z) * blockSize;
	glm::vec3 color = *chunkData[CalculateIndexPosition(x, y, z)].type->color;//glm::vec3(0.0f, 0.6f, 0.1f);
	if (GetBlockVisibility(x - 1, y, z) == BlockData::BlockVisibility::INVISIBLE)
	{
		AddBlockFace(BlockFace::LEFT, position, color);
	}
	if (GetBlockVisibility(x, y - 1, z) == BlockData::BlockVisibility::INVISIBLE)
	{
		AddBlockFace(BlockFace::BOTTOM, position, color);
	}
	if (GetBlockVisibility(x, y, z - 1) == BlockData::BlockVisibility::INVISIBLE)
	{
		AddBlockFace(BlockFace::BACK, position, color);
	}
	if (GetBlockVisibility(x + 1, y, z) == BlockData::BlockVisibility::INVISIBLE)
	{
		AddBlockFace(BlockFace::RIGHT, position, color);
	}
	if (GetBlockVisibility(x, y + 1, z) == BlockData::BlockVisibility::INVISIBLE)
	{
		AddBlockFace(BlockFace::TOP, position, color);
	}
	if (GetBlockVisibility(x, y, z + 1) == BlockData::BlockVisibility::INVISIBLE)
	{
		AddBlockFace(BlockFace::FRONT, position, color);
	}
}
glm::vec3 Chunk::GetBlockPosition(int x, int y, int z)
{
	return glm::vec3(chunkPosition.x + (x * blockSize) , chunkPosition.y + (y * blockSize), chunkPosition.z + (z * blockSize));
}
glm::vec3 Chunk::GetChunkPosition()
{
	return chunkPosition;
}
bool Chunk::LayerContainsEmptyBlocks(int layerNumber)
{
	if (layerNumber < 0 || layerNumber >= chunkHeight)
	{
		return false;
	}
	return layerHasEmptyBlock[layerNumber];
}
BlockData::BlockVisibility Chunk::GetBlockVisibility(int x, int y, int z)
{
	if (x < 0 || y < 0 || z < 0 || x >= chunkWidth || y >= chunkHeight || z >= chunkLength)
	{
		return world->GetBlockAtPosition(GetBlockPosition(x, y, z))->type->visibility;
		//return BlockData::BlockVisibility::INVISIBLE;
	}
	return chunkData[CalculateIndexPosition(x, y, z)].type->visibility;
}
Block* Chunk::GetBlockAtPosition(int x, int y, int z)
{
	return &chunkData[CalculateIndexPosition(x, y, z)];
}
int Chunk::GetChunkWidth()
{
	return chunkWidth;
}
int Chunk::GetChunkHeight()
{
	return chunkHeight;
}
int Chunk::GetChunkLength()
{
	return chunkLength;
}
int Chunk::GetChunkSize()
{
	return chunkWidth * chunkHeight * chunkLength;
}
