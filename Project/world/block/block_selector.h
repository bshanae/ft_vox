#pragma once

#include "common/aliases.h"
#include "core/object/unique_object.h"
#include "world/block/block.h"

class 					model;

class					block_selector  : public unique_object<block_selector>
{
	friend class 		block_selector_renderer;
	friend class 		world;

public :
						block_selector();
						~block_selector() override = default;

						property<read_write, vec3, block_selector>
						translation;

						property<read_write, block::face, block_selector>
						selected_face;
private :

	void 				create_implementation() override;

	void				render() override;

	shared_ptr<model>	cube;

	shared_ptr<model>	left;
	shared_ptr<model>	right;
	shared_ptr<model>	front;
	shared_ptr<model>	back;
	shared_ptr<model>	top;
	shared_ptr<model>	bottom;
};


