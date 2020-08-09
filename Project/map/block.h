#pragma once

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
		water
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

	[[nodiscard]]
	bool					is_transparent() const
	{
		return (type == type::air or type == type::water);
	}

	type					type;
	char					light_level = 0;
};