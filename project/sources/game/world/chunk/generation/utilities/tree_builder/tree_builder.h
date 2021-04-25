#pragma once

#include "game/world/block/block_ptr/block_ptr.h"

namespace					game
{
	class					tree_builder;
}

class						game::tree_builder
{
public :

	static void				build(const block_ptr &block);

private :

	static const inline int	tree_height = 7;

	static void				validate_leave_block(const block_ptr &block);
};
