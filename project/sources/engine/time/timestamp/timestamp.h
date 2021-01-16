#pragma once

#include "common/imports/std.h"
#include "common/imports/opengl.h"

namespace				engine
{
	class				timestamp;
}

class					engine::timestamp
{
public :
						timestamp();
						~timestamp() = default;

	float 				get_value() const;

						operator float () const;
	float				operator - (const timestamp &that);
	friend ostream		&operator << (ostream &stream, const timestamp &timestamp);

private :

	float				value;
};