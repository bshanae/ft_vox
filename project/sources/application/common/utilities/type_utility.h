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

	template		<typename test_type, typename actual_type>
	static bool 	check_type(const shared_ptr<actual_type> &object)
	{
		return dynamic_pointer_cast<test_type>(object) != nullptr;
	}
};