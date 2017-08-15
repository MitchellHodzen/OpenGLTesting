#include "ChunkManager.h"
#include "World.h"

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
	std::vector<Chunk*> chunks;
	chunks.push_back(world->GetChunkAtPosition(0, -chunkHeight, 0));
	chunks.push_back(world->GetChunkAtPosition(chunkWidth, -chunkHeight, 0));
	return chunks;
}

