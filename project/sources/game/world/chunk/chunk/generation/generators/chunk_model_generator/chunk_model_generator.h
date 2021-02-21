#pragma once

#include "application/common/templates/singleton/singleton.h"

#include "game/world/chunk/chunk/generation/chunk_workspace/chunk_workspace.h"

namespace			game
{
	class			chunk_workspace;
	class			chunk_model_generator;
}

class				game::chunk_model_generator : public singleton<game::chunk_model_generator>
{
public :
					chunk_model_generator() = default;
					~chunk_model_generator() override = default;

	static void		process(const shared_ptr<chunk_workspace> &workspace);

private :

	static void		process_batch
					(
						const shared_ptr<chunk_workspace> &workspace,
						chunk_workspace::batch &batch
					);
};
