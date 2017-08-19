#pragma once
#include <vector>
#include "Block.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Vertex.h"
#include "Mesh.h"
class Chunk
{
	public:
		Chunk(glm::vec3 chunkPosition, int width, int height, int length, float blockSize, int* heightData);
		~Chunk();
		enum BlockFace {FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM};
		glm::vec3 GetChunkPosition();
		void GenerateChunkMesh();
		Mesh* GetChunkMesh();
		int GetChunkWidth();
		int GetChunkHeight();
		int GetChunkLength();
		int GetChunkSize();
	private:
		//Block*** chunkData;
		Block* chunkData;
		glm::vec3 GetBlockPosition(int x, int y, int z);
		void AddBlockFace(BlockFace face, glm::vec3 blockPosition, glm::vec3 color);
		void GenerateChunk(int* heightData);
		BlockData::BlockVisibility GetBlockVisibility(int x, int y, int z);
		bool CheckVisibleFaces(int x, int y, int z);
		int chunkLength, chunkWidth, chunkHeight;
		float blockSize;
		glm::vec3 chunkPosition;
		Mesh* chunkMesh;
};
