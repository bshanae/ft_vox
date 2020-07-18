#pragma once

#include "common/aliases.h"
#include "common/global.h"

class						object;

class 						object_linker
{
public :
							object_linker() = default;
	virtual					~object_linker() = default;

protected :

	static void				link_to_application(const shared_ptr<object> &object);
};
