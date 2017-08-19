#include "BlockData.h"
#include <iostream>

std::unordered_map<BlockData::BlockName, BlockData*> BlockData::BlockTypes;
std::unordered_map<BlockData::BlockColor, glm::vec3*> BlockData::BlockColors;

BlockData::BlockData(BlockName name, BlockVisibility visibility, BlockColor color)
{
	this->name = name;
	this->visibility = visibility;
	this->color = BlockColors[color];
}
void BlockData::CreateBlock(BlockName name, BlockVisibility visibility, BlockColor color)
{
	if (BlockTypes.count(name))
	{
		std::cout<<"Block already exists in BlockTypes map"<<std::endl;
	}
	else
	{
		BlockTypes[name] = new BlockData(name, visibility, color);
	}
}
void BlockData::SetColor(BlockColor color, glm::vec3 value)
{
	if(BlockColors.count(color))
	{
		std::cout<<"Color already exists in BlockColors map"<<std::endl;
	}
	else
	{
		BlockColors[color] = new glm::vec3(value);
	}
}
