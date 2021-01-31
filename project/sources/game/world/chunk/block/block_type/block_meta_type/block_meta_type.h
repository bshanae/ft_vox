#pragma once

namespace			game
{
	enum class		block_meta_type
	{
		empty,
		transparent,
		diagonal,
		opaque
	};

	bool			is_opaque(block_meta_type meta_type);
	bool			is_transparent(block_meta_type meta_type);
	bool			is_partially_transparent(block_meta_type meta_type);
	bool			is_transparent_or_partially_transparent(block_meta_type meta_type);

	bool			is_solid(block_meta_type meta_type);
	bool			is_empty(block_meta_type meta_type);

	bool			is_diagonal(block_meta_type meta_type);

	bool			is_editable(block_meta_type meta_type);

	bool			does_transmit_light(block_meta_type meta_type);
}


