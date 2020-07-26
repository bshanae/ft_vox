#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"

class						object : public enable_shared_from_this<object>
{
	friend class 			application;

public :

							object() = default;
	virtual					~object() = default;

	static
	shared_ptr<object>		create()
	{
		shared_ptr<object>	object;

		object = make_shared<class object>();
		object->link_to_application();
		return (object);
	}

protected :

	virtual void 			render()
	{}

	virtual void 			update()
	{}

	void	 				link_to_application();
};