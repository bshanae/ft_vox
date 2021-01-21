#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"

#include "game/world/chunk/block/block/block.h"

#include "application/common/imports/glm.h"
#include "application/common/imports/std.h"

namespace						engine
{
	class						model;
}

namespace						game
{
	class						block_highlighter_renderer;
	class						world;

	class						block_highlighter;
}

class							game::block_highlighter  :
									public engine::object,
									public engine::unique_object_constructor<block_highlighter>

{
	friend class 				block_highlighter_renderer;

public :
								block_highlighter();
								~block_highlighter() override = default;

	static vec3					get_translation();
	static block::face			get_selected_face();

	static void					set_translation(const vec3 &value);
	static void					set_selected_face(block::face face);

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


