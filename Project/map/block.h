#pragma once

class				block
{
	friend class 	chunk;

public :

	enum class		type
	{
		air,
		dirt
	};

	explicit		block(type type = type::air) : type_value(type)
					{}
					~block() = default;

	[[nodiscard]]
	bool			empty() const
	{
		return (type_value == type::air);
	}

private :

	type			type_value = type::air;

	int				health = 0;
};