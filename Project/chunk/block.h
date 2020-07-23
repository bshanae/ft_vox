#pragma once

class				block
{
public :

	enum class		type
	{
		air,
		dirt
	};
					block(type type = type::air) : type(type)
					{}
					~block() = default;

	bool			is_empty()
	{
		return (false);
	}

	type			type;

	int				health;
};