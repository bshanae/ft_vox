#pragma once

#include "common/OpenGL.h"
#include "common/property.h"

class										timestamp
{
	friend class							application;

public :

											timestamp()
	{
		value = glfwGetTime();
	}
											~timestamp() = default;

	float									operator - (const timestamp &that)
	{
		return (*this->value - *that.value);
	}

	property<read_only, float, timestamp>	value;
};