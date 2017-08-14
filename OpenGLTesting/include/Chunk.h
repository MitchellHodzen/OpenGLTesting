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
		Chunk(glm::vec3 chunkPosition, int width, int height, int length, float blockWidth, float blockHeight, float blockLength);
		~Chunk();
		BlockVisibility*** chunkData;
		enum BlockFace {FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM};
		void AddBlockFace(BlockFace face, glm::vec3 blockPosition);
		glm::vec3 GetBlockPosition(int x, int y, int z);
		glm::vec3 GetChunkPosition();
		void GenerateModelMatricies();
		std::vector<glm::mat4>* GetModelMatricies();
		//std::vector<Vertex>* GetChunkMesh();
		Mesh* GetChunkMesh();
		int GetChunkWidth();
		int GetChunkHeight();
		int GetChunkLength();
		int GetChunkSize();
	private:
		void GenerateChunk();
		BlockVisibility GetBlockVisibility(int x, int y, int z);
		bool CheckBlockVisible(int x, int y, int z);
		int chunkLength, chunkWidth, chunkHeight;
		float blockWidth, blockHeight, blockLength;
		glm::vec3 chunkPosition;
		std::vector<glm::mat4>* modelMatricies;
		//std::vector<Vertex>* chunkMesh;
		Mesh* chunkMesh;
};
