#pragma once

namespace						engine
{
	class						model;
}

namespace						game
{
	class						chunk_build;
}

struct							game::chunk_build
{
	shared_ptr<engine::model>	model_for_opaque;
	shared_ptr<engine::model>	model_for_transparent;
	shared_ptr<engine::model>	model_for_partially_transparent;
};