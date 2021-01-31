#include "block.h"

#include "game/world/tools/array3/array3.h"

#include "application/common/debug/debug.h"

using namespace		game;

					block::block(block_type type) : type(type) {}

ostream				&operator << (ostream &stream, block_type type)
{
	switch (type)
	{
		case block_type::air :
			stream << "air";
			break ;

		case block_type::dirt :
			stream << "dirt";
			break ;

		case block_type::dirt_with_grass :
			stream << "dirt_with_grass";
			break ;

		case block_type::water :
			stream << "water";
			break ;

		case block_type::blue_flower :
			stream << "blue_flower";
			break ;

		default :
			break ;
	}
	return (stream);
}