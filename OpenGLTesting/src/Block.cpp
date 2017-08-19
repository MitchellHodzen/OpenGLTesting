#include "Block.h"

Block::Block(BlockData::BlockName name)
{
	type = BlockData::BlockTypes[name];
}
Block::Block()
{
	type = BlockData::BlockTypes[BlockData::BlockName::AIR];
}
