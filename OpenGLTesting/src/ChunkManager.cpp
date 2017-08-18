#include "ChunkManager.h"
#include "World.h"
#include <iostream>

ChunkManager::ChunkManager(World* world, int chunkWidth, int chunkHeight, int chunkLength)
{
	this->chunkWidth = chunkWidth;
	this->chunkHeight = chunkHeight;
	this->chunkLength = chunkLength;
	this->world = world;
}
ChunkManager::~ChunkManager()
{
}

std::vector<Chunk*> ChunkManager::QueryChunks(glm::vec3 playerPosition)
{
	//We add an offset of one half the block size because a block's origin is its center. May be easier to change blocks origin to corner
	int chunkX = floor((playerPosition.x + world->GetBlockSize()/2) / chunkWidth);
	int chunkY = floor((playerPosition.y + world->GetBlockSize()/2) / chunkHeight);
	int chunkZ = floor((playerPosition.z + world->GetBlockSize()/2) / chunkLength);
	std::cout<<chunkX << ", " << chunkY << ", " << chunkZ << std::endl;
	std::vector<Chunk*> chunks;
	chunks.push_back(world->GetChunkAtPosition(chunkX, chunkY - 1, chunkZ));
	chunks.push_back(world->GetChunkAtPosition(chunkX + 1, chunkY - 1, chunkZ));
	chunks.push_back(world->GetChunkAtPosition(chunkX - 1, chunkY - 1, chunkZ));
	chunks.push_back(world->GetChunkAtPosition(chunkX, chunkY - 1, chunkZ + 1));
	chunks.push_back(world->GetChunkAtPosition(chunkX, chunkY - 1, chunkZ - 1));
	/*
	chunks.push_back(world->GetChunkAtPosition(0, -1, 0));
	chunks.push_back(world->GetChunkAtPosition(1, -1, 0));
	chunks.push_back(world->GetChunkAtPosition(-1, -1, 0));
	chunks.push_back(world->GetChunkAtPosition(0, -1, -1));
	chunks.push_back(world->GetChunkAtPosition(0, -1, 1));
	*/
	return chunks;
}

