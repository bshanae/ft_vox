#include "block_meta_type.h"

bool			game::is_opaque(block_meta_type meta_type)
{
	return meta_type == block_meta_type::opaque;
}

bool			game::is_transparent(block_meta_type meta_type)
{
	return meta_type == block_meta_type::transparent;
}

bool			game::is_partially_transparent(block_meta_type meta_type)
{
	return meta_type == block_meta_type::diagonal;
}

bool			game::is_transparent_or_partially_transparent(block_meta_type meta_type)
{
	return meta_type == block_meta_type::transparent || meta_type == block_meta_type::diagonal;
}

bool			game::is_solid(block_meta_type meta_type)
{
	return meta_type == block_meta_type::opaque;
}

bool			game::is_empty(block_meta_type meta_type)
{
	return meta_type == block_meta_type::empty;
}

bool			game::is_diagonal(block_meta_type meta_type)
{
	return meta_type == block_meta_type::diagonal;
}

bool			game::is_editable(block_meta_type meta_type)
{
	return meta_type == block_meta_type::opaque || meta_type == block_meta_type::diagonal;
}

bool			game::does_transmit_light(block_meta_type meta_type)
{
	return meta_type == block_meta_type::empty || meta_type == block_meta_type::transparent;
}