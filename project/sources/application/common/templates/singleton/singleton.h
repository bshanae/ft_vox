#pragma once

#include "application/common/imports/std.h"

template						<typename type>
class							singleton
{
public :
								singleton() = default;
	virtual						~singleton() = default;

	static void					construct()
	{
		shared_ptr<singleton>	instance_as_singleton;

		assert(instance == nullptr and "Singleton instance is already constructed");
		instance = make_shared<type>();

		instance_as_singleton = dynamic_pointer_cast<singleton>(instance);
		if (instance_as_singleton == nullptr)
		{

		}
		assert(instance_as_singleton != nullptr);
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