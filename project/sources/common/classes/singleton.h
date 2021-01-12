#pragma once

#include "common/aliases.h"

template						<typename final_type>
class							singleton
{
public :
								singleton() = default;
	virtual						~singleton() = default;

	template					<typename ...args_type>
	static void					initialize(args_type ...args)
	{
		if constexpr (not is_base_of<singleton<final_type>, final_type>::value)
			assert(false and "Bad usage of global class");

		assert(instance == nullptr and "Global instance is already initialized");

		instance = make_shared<final_type>(args...);
		static_pointer_cast<singleton>(instance)->initializer(instance);
	}

protected :

	static auto					get_instance()
	{
		assert(instance != nullptr and "Global instance is not initialized");
		return (instance);
	}

	virtual void				initializer(shared_ptr<final_type>)
	{}

private :

	static inline
	shared_ptr<final_type>		instance;
};