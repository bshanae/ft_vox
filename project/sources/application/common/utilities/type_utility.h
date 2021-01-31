#pragma once

#include "application/common/imports/std.h"

class 				type_utility
{
public :

	template		<typename test_type, typename actual_type>
	static bool 	check_type(const actual_type &object)
	{
		return dynamic_cast<const test_type *>(&object) != nullptr;
	}
};