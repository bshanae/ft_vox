#pragma once

#include "common/imports/opengl.h"
#include "common/imports/std.h"

namespace					engine
{
	class 					core;
	template				<typename>
	class 					usual_object;
	template				<typename, typename>
	class 					inheritor_object;

	class					object;
}

class						engine::object : public enable_shared_from_this<object>
{
	friend class 			engine::core;

	template				<typename>
	friend class 			engine::usual_object;

	template				<typename, typename>
	friend class 			engine::inheritor_object;

protected :

	enum					state
	{
		undefined,
		active,
		inactive,
		initialized,
		uninitialized
	}						state;

	string 					layout;

	bool 					should_be_rendered = true;
	bool 					should_be_updated = true;

							object()
	{
		state = undefined;
	}

	virtual					~object() = default;

	virtual void			destroy() = 0;

	virtual void			activate() = 0;
	virtual void			deactivate() = 0;

	virtual void 			render() = 0;
	virtual void 			update() = 0;

private :

	bool					should_be_destroyed = false;

	virtual void			initialize() = 0;
	virtual void			deinitialize() = 0;

	void					connect_to_core();
};