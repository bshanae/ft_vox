#pragma once

struct					block_settings
{
	static
	inline
	const char 			light_level_limit = 16;
};

class					block
{
	friend class 		chunk;
	friend class 		chunk_editor;

public :

	enum class			type : char
	{
		air,
		dirt,
		dirt_with_grass
	};

	explicit			block(type type = type::air) : type_value(type) {}
						~block() = default;

	[[nodiscard]]
	bool				is_empty() const
	{
		return (type_value == type::air);
	}

private :

	[[deprecated]]
	type				type_value = type::air;

	char				light_level = 0;
};