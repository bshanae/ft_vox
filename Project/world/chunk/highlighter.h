#pragma once

#include "common/aliases.h"
#include "core/object/unique_object.h"

class 					model;

class					highlighter  : public unique_object<highlighter>
{
	friend class 		highlighter_renderer;
	friend class 		world;

public :
						highlighter();
						~highlighter() override = default;
private :

	void 				create_implementation() override;

	void				render() override;

	shared_ptr<model>	model;
};


