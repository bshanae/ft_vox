#pragma once

#include "application/common/templates/singleton/singleton.h"

#include "game/world/chunk/chunk/building/chunk_workspace/chunk_workspace.h"

namespace			game
{
	class			chunk_workspace;
	class			chunk_model_builder;
}

class				game::chunk_model_builder : public singleton<game::chunk_model_builder>
{
public :
					chunk_model_builder() = default;
					~chunk_model_builder() override = default;

	static void		launch(const shared_ptr<chunk_workspace> &workspace);

private :

	static void		process_batch
					(
						const shared_ptr<chunk_workspace> &workspace,
						chunk_workspace::batch &batch
					);
};
