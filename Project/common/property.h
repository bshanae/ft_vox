#pragma once

#include "common/aliases.h"

template 				<typename type>
class					property
{
public:
						property() = default;
	virtual				~property() = default;

	property(const type &value) : value(value)
	{}

protected :

	virtual type		&operator = (const int &value)
	{
		return (this->value = value);
	}

	virtual				operator type () const
	{
		return (value);
	}

	type				value;
};