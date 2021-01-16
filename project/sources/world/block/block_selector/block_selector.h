#pragma once

#include "common/imports/std.h"
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

	vec3						get_translation() const;
	block::face					get_selected_face() const;

	void						set_translation(const vec3 &value);
	void						set_selected_face(block::face face);

private :

	vec3						translation;
	block::face					selected_face;

	shared_ptr<engine::model>	cube;

	shared_ptr<engine::model>	left;
	shared_ptr<engine::model>	right;
	shared_ptr<engine::model>	front;
	shared_ptr<engine::model>	back;
	shared_ptr<engine::model>	top;
	shared_ptr<engine::model>	bottom;

	void 						create_implementation() override;
	void						render() override;
};


