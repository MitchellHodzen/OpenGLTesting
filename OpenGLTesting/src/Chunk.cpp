#include "Chunk.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


Chunk::Chunk(glm::vec3 chunkPosition, int width, int height, int length, float blockWidth, float blockHeight, float blockLength)
{
	this->chunkPosition = chunkPosition;
	chunkWidth = width;
	chunkHeight = height;
	chunkLength = length;
	this->blockWidth = blockWidth;
	this->blockHeight = blockHeight;
	this->blockLength = blockLength;
	//modelMatricies = new std::vector<glm::mat4>;
	chunkMesh = new Mesh();
	GenerateChunk();
}
Chunk::~Chunk()
{
	for (int x = 0; x < chunkWidth; ++x)
	{
		for (int y = 0; y < chunkHeight; ++y)
		{
			delete[] chunkData[x][y];
		}
		delete[] chunkData[x];
	}
	delete[] chunkData;
	delete chunkMesh;
}

void Chunk::GenerateChunk()
{
	chunkData = new BlockVisibility**[chunkWidth];
	for (int x = 0; x < chunkWidth; ++x)
	{
		chunkData[x] = new BlockVisibility*[chunkHeight];
		for (int y = 0; y < chunkHeight; ++y)
		{
			chunkData[x][y] = new BlockVisibility[chunkLength];
			for (int z = 0; z < chunkLength; ++z)
			{
				chunkData[x][y][z] = BlockVisibility::VISIBLE;
			}
		}
	}
	GenerateChunkMesh();
}

void Chunk::GenerateChunkMesh()
{
	chunkMesh->ClearVertices();
	for (int x = 0; x < chunkWidth; ++x)
	{
		for (int y = 0; y < chunkHeight; ++y)
		{
			for (int z = 0; z < chunkLength; ++z)
			{
				if(GetBlockVisibility(x, y, z) == BlockVisibility::VISIBLE)
				{
					CheckVisibleFaces(x, y, z);
				}
				//if (CheckVisibleFaces(x, y, z))
				//{
					//glm::vec3 position = GetBlockPosition(x, y, z);
					//modelMatricies->push_back(glm::translate(glm::mat4(), GetBlockPosition(x, y, z)));
				//}
			}
		}
	}
	chunkMesh->BuildVBO();
}

void Chunk::AddBlockFace(BlockFace face, glm::vec3 blockPosition)
{
	switch(face)
	{
		case BlockFace::FRONT:
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f) + blockPosition, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, 0.5f) + blockPosition, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, 0.5f) + blockPosition, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, 0.5f) + blockPosition, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f) + blockPosition, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f) + blockPosition, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
			break;
		case BlockFace::BACK:
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f) + blockPosition, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, -0.5f) + blockPosition, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, -0.5f) + blockPosition, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, -0.5f) + blockPosition, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f) + blockPosition, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f) + blockPosition, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)));
			break;
		case BlockFace::RIGHT:
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, 0.5f) + blockPosition, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, -0.5f) + blockPosition, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, -0.5f) + blockPosition, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, -0.5f) + blockPosition, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, 0.5f) + blockPosition, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, 0.5f) + blockPosition, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)));
			break;
		case BlockFace::LEFT:
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f) + blockPosition, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f) + blockPosition, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f) + blockPosition, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f) + blockPosition, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f) + blockPosition, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f) + blockPosition, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)));
			break;
		case BlockFace::TOP:
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f) + blockPosition, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, 0.5f) + blockPosition, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, -0.5f) + blockPosition, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f) + blockPosition, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, 0.5f, 0.5f) + blockPosition, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f) + blockPosition, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)));
			break;
		case BlockFace::BOTTOM:
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f) + blockPosition, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, -0.5f) + blockPosition, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, 0.5f) + blockPosition, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(0.5f, -0.5f, 0.5f) + blockPosition, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f) + blockPosition, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)));
			chunkMesh->AddVertex(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f) + blockPosition, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)));
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
bool Chunk::CheckVisibleFaces(int x, int y, int z)
{
	glm::vec3 position(x, y, z);
	bool visible = false;
	if (GetBlockVisibility(x - 1, y, z) == BlockVisibility::INVISIBLE) 
	{
		visible = true;
		AddBlockFace(BlockFace::LEFT, position);
	}
	if (GetBlockVisibility(x, y - 1, z) == BlockVisibility::INVISIBLE) 
	{
		visible = true;
		AddBlockFace(BlockFace::BOTTOM, position);
	}
	if (GetBlockVisibility(x, y, z - 1) == BlockVisibility::INVISIBLE) 
	{
		visible = true;
		AddBlockFace(BlockFace::BACK, position);
	}
	if (GetBlockVisibility(x + 1, y, z) == BlockVisibility::INVISIBLE) 
	{
		visible = true;
		AddBlockFace(BlockFace::RIGHT, position);
	}
	if (GetBlockVisibility(x, y + 1, z) == BlockVisibility::INVISIBLE) 
	{
		visible = true;
		AddBlockFace(BlockFace::TOP, position);
	}
	if (GetBlockVisibility(x, y, z + 1) == BlockVisibility::INVISIBLE) 
	{
		visible = true;
		AddBlockFace(BlockFace::FRONT, position);
	}
	return visible;
}
glm::vec3 Chunk::GetBlockPosition(int x, int y, int z)
{
	return glm::vec3(chunkPosition.x + (x * blockWidth) , chunkPosition.y + (y * blockHeight), chunkPosition.z + (z * blockLength));
}
glm::vec3 Chunk::GetChunkPosition()
{
	return chunkPosition;
}
BlockVisibility Chunk::GetBlockVisibility(int x, int y, int z)
{
	if (x < 0 || y < 0 || z < 0 || x >= chunkWidth || y >= chunkHeight || z >= chunkLength)
	{
		return BlockVisibility::INVISIBLE;
	}
	return chunkData[x][y][z];
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
