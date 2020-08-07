#pragma once

#include "common/aliases.h"

template						<typename final_type>
class							global
{
public :
								global() = default;
	virtual						~global() = default;

	template					<typename ...args_type>
	static void					initialize(args_type ...args)
	{
		if constexpr (not is_base_of<global<final_type>, final_type>::value)
			assert(false and "Bad usage of global class");

		assert(pointer == nullptr and "Global instance is already initialized");
		pointer = make_shared<final_type>(args...);
		static_pointer_cast<global>(pointer)->initializer(pointer);
	}

protected :

	static auto					instance()
	{
		assert(pointer != nullptr and "Global instance is not initialized");
		return (pointer);
	}

	virtual void				initializer(shared_ptr<final_type>)
	{}

private :

	static
	inline
	shared_ptr<final_type>		pointer;
};