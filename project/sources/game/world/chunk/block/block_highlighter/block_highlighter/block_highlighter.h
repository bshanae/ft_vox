#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"

#include "game/world/chunk/block/block/block.h"
#include "game/world/chunk/block/block_face/block_face.h"

#include "application/common/imports/glm.h"
#include "application/common/imports/std.h"

namespace						engine
{
	class						model;
}

namespace						game
{
	class						block_pointer;
	class						block_highlighter;
	class						block_highlighter_renderer;
	class						world;
}

class							game::block_highlighter  :
									public engine::object,
									public engine::unique_object_constructor<block_highlighter>

{
	friend class 				block_highlighter_renderer;

public :
								block_highlighter();
								~block_highlighter() override = default;

	static void 				highlight(const block_pointer &block, block_face face);
	static void 				reset();

private :

	vec3						translation;
	block_face					highlighted_face;

	shared_ptr<engine::model>	cube;
	shared_ptr<engine::model>	left;
	shared_ptr<engine::model>	right;
	shared_ptr<engine::model>	front;
	shared_ptr<engine::model>	back;
	shared_ptr<engine::model>	top;
	shared_ptr<engine::model>	bottom;

	bool 						should_render;

	void 						when_initialized() override;
	void						when_rendered() override;
};


