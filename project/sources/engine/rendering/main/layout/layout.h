#pragma once

#include "engine/core/object/object/object.h"

#include "application/common/imports/std.h"

namespace						engine
{
	class						core;

	class 						layout;
}

class 							engine::layout
{
	friend class 				engine::processor;

public :

	enum						option
	{
		use_depth_test = 1 << 0
	};

								layout(const string &name, int options) :
									name(name),
									options(options)
								{}
								~layout() = default;
private :

	const string	name;
	const int		options;

	vector<shared_ptr<object>>	objects;
};