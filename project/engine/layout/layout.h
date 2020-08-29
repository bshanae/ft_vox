#pragma once

#include "common/aliases.h"
#include "engine/object/object.h"

class 							layout
{
	friend class 				core;

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