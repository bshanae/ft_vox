#pragma once

#include "application/common/imports/opengl.h"
#include "application/common/imports/std.h"

namespace					engine
{
	class					object;
	class 					object_manipulator;
}

class						engine::object : public enable_shared_from_this<object>
{
	friend class 			engine::object_manipulator;

public :

	enum class				state
	{
		null,
		initialized,
		activated,
		deactivated,
		deinitialized
	};

							object();
	virtual					~object() = default;

	void					activate();
	void					deactivate();

	void					render();
	void					update();

	state					get_state() const;
	const string			&get_layout() const;

protected :

	void 					set_layout(const string &value);

	virtual void			when_initialized() {}
	virtual void			when_deinitialized() {}

	virtual void			when_activated() {}
	virtual void			when_deactivated() {}

	virtual void 			when_updated() {}
	virtual void 			when_rendered() {}

	void 					check_if_initialized();
	void 					check_if_deinitialized();

private :

	enum state				state;
	string 					layout;
};