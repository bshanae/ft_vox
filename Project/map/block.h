#pragma once

class					block
{
	friend class 		chunk;
	friend class 		chunk_editor;

public :

	enum class			type : char
	{
		air,
		dirt,
		stone
	};

	explicit			block(type type = type::air) : type_value(type)
						{}
						~block() = default;

	[[nodiscard]]
	bool				empty() const
	{
		return (type_value == type::air);
	}

private :

	type				type_value = type::air;
};