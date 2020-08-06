#pragma once

struct						block_settings
{
	static
	inline
	const char 				light_level_limit = 16;
};

class						block
{
	friend class 			chunk;
	friend class 			chunk_editor;

public :

	enum class				type : char
	{
		air,
		dirt,
		dirt_with_grass
	};

	type					type;
	char					light_level = 0;

	explicit				block(enum type type = type::air)
	{
		this->type = type;
	}

	[[nodiscard]]
	bool					is_empty() const
	{
		return (type == type::air);
	}
};