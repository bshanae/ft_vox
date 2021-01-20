#pragma once

#include "engine/core/object/object/object.h"
#include "engine/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"

#include "game/world/chunk/block/block/block.h"

#include "application/common/imports/glm.h"
#include "application/common/imports/std.h"

namespace						engine
{
	class						model;
}

namespace						game
{
	class						block_selector_renderer;
	class						world;

	class						block_selector;
}

class							game::block_selector  :
									public engine::object,
									public engine::unique_object_constructor<block_selector>

{
	friend class 				::game::block_selector_renderer;
	friend class 				::game::world;

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

	void 						when_initialized() override;
	void						when_rendered() override;
};


