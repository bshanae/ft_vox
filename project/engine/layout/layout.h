#pragma once

#include "common/aliases.h"
#include "engine/object/object/object.h"

namespace						engine
{
	class						core;

	class 						layout;
}

class 							engine::layout
{
	friend class 				engine::core;

public :

	enum class					option
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