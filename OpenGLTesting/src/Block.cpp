#include "Block.h"

Block::Block(BlockData::BlockName name)
{
	type = BlockData::BlockTypes[name];
}
