#pragma once

#include "engine/main/core/object/object/object.h"

#include "application/common/imports/std.h"

namespace				engine
{
	class 				layout;
	class 				layout_manager;
}

class 					engine::layout
{
	friend class 		layout_manager;

	using 				data_type = vector<shared_ptr<object>>;

public :

	enum				option
	{
		use_depth_test = 1 << 0
	};

						layout(const string &name, int options);
						~layout() = default;

	[[nodiscard]]
	const data_type		&get_objects() const;

	void 				apply_options() const;

private :

	const string		name;
	const int			options;

	data_type			objects;
};