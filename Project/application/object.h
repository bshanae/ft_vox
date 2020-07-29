#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"

class							object : public enable_shared_from_this<object>
{
	friend class 				application;

public :

								object() = default;
	virtual						~object() = default;

	static shared_ptr<object>	create();
	void 						destroy();

protected :

	static void					create_internal(const shared_ptr<object> &object);

	virtual void 				start() {}
	virtual void 				finish() {}
	virtual void 				render() {}
	virtual void 				update() {}

private :

	enum class 					state
	{
		undefined,
		just_created,
		normal,
		should_be_destroyed
	}							state = state::undefined;

	void						connect_to_application();
};