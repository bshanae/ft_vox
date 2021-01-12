#pragma once

#include "common/aliases.h"
#include "engine/object/unique_object/unique_object.h"
#include "world/block/block/block.h"

namespace						engine
{
	class						model;
}

namespace						world
{
	class						block_selector_renderer;
	class						world;

	class						block_selector;
}

class							world::block_selector  : public engine::unique_object<block_selector>
{
	friend class 				::world::block_selector_renderer;
	friend class 				::world::world;

public :
								block_selector();
								~block_selector() override = default;

								property<read_write, vec3, block_selector>
								translation;

								property<read_write, block::face, block_selector>
								selected_face;
private :

	void 						create_implementation() override;

	void						render() override;

	shared_ptr<engine::model>	cube;

	shared_ptr<engine::model>	left;
	shared_ptr<engine::model>	right;
	shared_ptr<engine::model>	front;
	shared_ptr<engine::model>	back;
	shared_ptr<engine::model>	top;
	shared_ptr<engine::model>	bottom;
};


