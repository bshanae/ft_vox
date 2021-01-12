#pragma once

#include "common/imports/opengl.h"
#include "common/classes/property.h"

namespace			engine
{
	class			timestamp;
}

class				engine::timestamp : public property<read_only, float, timestamp>
{
public :
					timestamp()
	{
		value = glfwGetTime();
	}
					~timestamp() = default;

	float			operator - (const timestamp &that)
	{
		return (this->value - that.value);
	}

	friend ostream	&operator << (ostream &stream, const timestamp &timestamp)
	{
		stream << (float)timestamp << "s.";
		return (stream);
	}
};