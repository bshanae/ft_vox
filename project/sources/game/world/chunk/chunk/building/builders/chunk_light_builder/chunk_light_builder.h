#pragma once

#include "application/common/templates/singleton/singleton.h"

namespace			game
{
	class			chunk_workspace;
	class			chunk_light_builder;
}

class				game::chunk_light_builder : public singleton<game::chunk_light_builder>
{
public :
					chunk_light_builder() = default;
					~chunk_light_builder() override = default;

	static void		launch(const shared_ptr<chunk_workspace> &workspace);

private :

	static void 	do_launch(const shared_ptr<chunk_workspace> &workspace);
};
