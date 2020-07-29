#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/global.h"
#include "application/object.h"

template 							<typename final_type>
class								unique_object :
										public object,
										public global<final_type>
{
public :
									unique_object() = default;
									~unique_object() override = default;

	static
	shared_ptr<unique_object>		create()
	{
		if constexpr (not is_base_of<unique_object<final_type>, final_type>::value)
			assert(false and "Bad usage of unique object");

		shared_ptr<unique_object>	object;

		global<final_type>::initialize();
		object = global<final_type>::instance();
		create_internal(object);
		pointer = dynamic_pointer_cast<final_type>(object);
		return (object);
	}

protected :

	static shared_ptr<final_type>	instance()
	{
		return (pointer);
	}

private :

	static
	inline
	shared_ptr<final_type>			pointer;
};