#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"

class							object : public enable_shared_from_this<object>
{
	friend class 				application;

public :

	enum class 					state
	{
		undefined,
		just_created,
		normal,
		should_be_destroyed
	};

								object() = default;
	virtual						~object() = default;

	static shared_ptr<object>	create();
	void 						destroy();

protected :

	bool 						manual_start = false;

	virtual void 				start()
	{
		start_internal();
	}

	virtual void 				finish() {}
	virtual void 				render() {}
	virtual void 				update() {}

	void						create_internal();
	void						start_internal();

	[[deprecated]]
	state						get_state() const
	{
		return (state);
	}

private :

	state						state = state::undefined;

	void						connect_to_application();
};