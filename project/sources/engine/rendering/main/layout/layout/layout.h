#pragma once

#include "engine/core/object/object/object.h"

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
	int 				get_options() const;

	[[nodiscard]]
	const data_type		&get_objects() const;

private :

	const string		name;
	const int			options;

	data_type			objects;
};