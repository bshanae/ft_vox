#pragma once

#include "common/aliases.h"

template 				<typename type>
class					property
{
public:
						property() = default;
	virtual				~property() = default;

protected :

	virtual void		operator = (const type &value) = 0;

	virtual				operator type () const = 0;
};