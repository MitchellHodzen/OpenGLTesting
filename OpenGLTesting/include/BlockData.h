#pragma once
#include <unordered_map>
#include <glm/vec3.hpp>
struct BlockData
{
	enum class BlockVisibility {VISIBLE, INVISIBLE};
	enum class BlockName {DIRT, GRASS, AIR, DEBUG};
	enum class BlockColor {BROWN, GREEN, WHITE, DEBUG};
	static std::unordered_map<BlockName, BlockData*> BlockTypes;
	static std::unordered_map<BlockColor, glm::vec3*> BlockColors;
	static void SetColor(BlockColor color, glm::vec3 value);
	static void CreateBlock(BlockName name, BlockVisibility visibility, BlockColor color);
	BlockData(BlockName name, BlockVisibility visibility, BlockColor color);
	BlockName name;
	BlockVisibility visibility;
	glm::vec3* color;
};


