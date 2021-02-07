#include "block_type.h"

#include "application/common/debug/debug.h"

using namespace		game;

block_meta_type		game::get_meta_type(block_type type)
{
	switch (type)
	{
		case block_type::air:
			return block_meta_type::empty;

		case block_type::stone:
		case block_type::dirt:
		case block_type::dirt_with_grass:
			return block_meta_type::opaque;

		case block_type::water:
			return block_meta_type::transparent;

		case block_type::blue_flower:
			return block_meta_type::diagonal;
	}

	debug::raise_error("[block_type] Unexpected code branch");
}