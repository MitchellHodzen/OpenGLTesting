#pragma once
#include <vector>
#include "Chunk.h"
#include <unordered_map>
class World
{
	public:
		World(int chunkWidth, int chunkHeight, int chunkLength, float blockWidth, float blockHeight, float blockLength);
		~World();
		Chunk* GetChunkAtPosition(int x, int y, int z);
	private:
		std::unordered_map< int, std::unordered_map< int, std::unordered_map< int, Chunk* > > > chunkMap;
		int chunkWidth, chunkHeight, chunkLength;
		float blockWidth, blockHeight, blockLength;
		void GenerateChunks();
		void GenerateBlockData();
		void CreateChunkAtPosition(int x, int y, int z);

};
