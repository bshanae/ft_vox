#pragma once

#include "common/opengl.h"
#include "common/aliases.h"
#include "common/property.h"

class						object : public enable_shared_from_this<object>
{
	friend class 			core;

	template				<typename>
	friend class 			usual_object;

protected :

	enum class 				state
	{
		undefined,
		active,
		inactive,
		initialized,
		uninitialized
	};

	string 					layout;

	bool 					should_be_rendered = true;
	bool 					should_be_updated = true;

							object()
	{
		state.value = state::undefined;
	}

	virtual					~object() = default;

	virtual void			destroy() = 0;

	virtual void			activate() = 0;
	virtual void			deactivate() = 0;

	class					state_property : public property<read_only, state, object>
	{
		template			<typename>
		friend class 		usual_object;
	}						state;

	virtual void 			render() = 0;
	virtual void 			update() = 0;

private :

	bool					should_be_destroyed = false;

	virtual void			initialize() = 0;
	virtual void			deinitialize() = 0;

	void					connect_to_core();
};