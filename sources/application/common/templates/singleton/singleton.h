#pragma once

#include "application/common/imports/std.h"
#include "application/common/debug/debug.h"

template						<typename type>
class							singleton
{
public :
								singleton() = default;
	virtual						~singleton() = default;

	static void					construct()
	{
		shared_ptr<singleton>	instance_as_singleton;

		debug::check_critical(instance == nullptr, "[application::singleton] Instance is already constructed");
		instance = make_shared<type>();

		instance_as_singleton = dynamic_pointer_cast<singleton>(instance);
		debug::check_critical(instance_as_singleton != nullptr, "[application::singleton] Can't construct instance");

		instance_as_singleton->when_constructed();
	}

	static auto					get_instance()
	{
		if (instance == nullptr)
			construct();

		return instance;
	}

protected :

	virtual void				when_constructed() {}

private :

	static inline
	shared_ptr<type>			instance;
};