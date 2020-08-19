#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/global.h"
#include "core/object/object_template.h"

template 							<typename final_type>
class								unique_object : public object_template<final_type>
{
public :
									unique_object() = default;
									~unique_object() override = default;
protected :

	static shared_ptr<final_type>	instance()
	{
		return (pointer);
	}

	void 							create_implementation() override
	{
		if constexpr (not is_base_of<unique_object<final_type>, final_type>::value)
			assert(false and "Bad usage of unique object");

		assert(pointer == nullptr and "Unique object instance is already initialized");
		pointer = dynamic_pointer_cast<final_type>(object::shared_from_this());
	}

private :

	static
	inline
	shared_ptr<final_type>			pointer;
};