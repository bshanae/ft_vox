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

	explicit		block(type type = type::air) : type(type)
					{}
					~block() = default;

	[[nodiscard]]
	bool			empty() const
	{
		return (type == type::air);
	}

private :

	type			type = type::air;
	int				health = 0;
};