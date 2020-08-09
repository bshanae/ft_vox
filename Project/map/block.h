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