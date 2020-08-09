#pragma once

class						chunk;

struct						block_settings
{
	static
	inline
	const char 				light_level_min = 4;

	static
	inline
	const char 				light_level_max = 16;

	static
	inline
	const char 				default_light_level = 10;

	static
	inline
	const char 				sun_light_level = 15;
};

class						block
{
	friend class 			chunk;
	friend class 			chunk_editor;
	friend class 			map;

public :

	enum class				type : char
	{
		air,
		dirt,
		dirt_with_grass,
		torch
	};

	explicit				block(enum type type = type::air)
	{
		this->type = type;
	}

	[[nodiscard]]
	bool					is_empty() const
	{
		return (type == type::air);
	}

	type					type;
	char					light_level = 0;
};