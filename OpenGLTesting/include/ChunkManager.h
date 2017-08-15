#pragma once
#include "Chunk.h"
#include <vector>
#include <unordered_map>
#include <glm/vec3.hpp>

class ChunkManager
{
	public:
		ChunkManager(int chunkWidth, int chunkHeight, int chunkLength, float blockWidth, float blockHeight, float blockLength);
		~ChunkManager();
		std::vector<Chunk*>* QueryChunks(glm::vec3 playerPosition);
	private:
		int chunkWidth, chunkHeight, chunkLength;
		float blockWidth, blockHeight, blockLength;
		void GenerateChunks();
		std::unordered_map< int, std::unordered_map< int, std::unordered_map< int, Chunk* > > > chunkMap;
		void CreateChunkAtPosition(int x, int y, int z);
		std::vector<Chunk*>* currentChunks;
};
