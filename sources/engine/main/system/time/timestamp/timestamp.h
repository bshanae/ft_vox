#pragma once

#include "application/common/imports/std.h"
#include "application/common/imports/opengl.h"

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
	float				operator - (const timestamp &that) const;

	friend ostream		&operator << (ostream &stream, const timestamp &timestamp);
	friend string 		to_string(const timestamp &timestamp);

private :

	float				value;
};