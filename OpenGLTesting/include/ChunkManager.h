#pragma once
#include "Chunk.h"
#include <vector>
#include <unordered_map>
#include <glm/vec3.hpp>

class World;
class ChunkManager
{
	public:
		ChunkManager(World* world, int chunkWidth, int chunkHeight, int chunkLength);
		~ChunkManager();
		std::vector<Chunk*> QueryChunks(glm::vec3 playerPosition);
	private:
		int chunkWidth, chunkHeight, chunkLength;
		World* world;
};
