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


inline bool			game::is_opaque(block_meta_type meta_type)
{
	return meta_type == block_meta_type::opaque;
}

inline bool			game::is_transparent(block_meta_type meta_type)
{
	return meta_type == block_meta_type::transparent;
}

inline bool			game::is_partially_transparent(block_meta_type meta_type)
{
	return meta_type == block_meta_type::diagonal;
}

inline bool			game::is_transparent_or_partially_transparent(block_meta_type meta_type)
{
	return meta_type == block_meta_type::transparent || meta_type == block_meta_type::diagonal;
}

inline bool			game::is_solid(block_meta_type meta_type)
{
	return meta_type == block_meta_type::opaque;
}

inline bool			game::is_empty(block_meta_type meta_type)
{
	return meta_type == block_meta_type::empty;
}

inline bool			game::is_diagonal(block_meta_type meta_type)
{
	return meta_type == block_meta_type::diagonal;
}

inline bool			game::is_editable(block_meta_type meta_type)
{
	return meta_type == block_meta_type::opaque || meta_type == block_meta_type::diagonal;
}

inline bool			game::does_transmit_light(block_meta_type meta_type)
{
	return meta_type == block_meta_type::empty || meta_type == block_meta_type::transparent;
}