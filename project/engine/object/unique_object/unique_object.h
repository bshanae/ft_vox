#pragma once

#include "common/opengl.h"
#include "common/aliases.h"
#include "common/global.h"
#include "engine/object/usual_object/usual_object.h"

namespace							engine
{
	template						<typename>
	class							unique_object;
}

template 							<typename final_type>
class								engine::unique_object : public usual_object<final_type>
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