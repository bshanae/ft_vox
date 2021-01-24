#pragma once

#include "application/common/templates/singleton/singleton.h"

class				application : public singleton<application>
{
public :
					application();
					~application() override = default;

	static void 	execute();

private :

	static void		initialize_engine();

	static void		initialize_ui();

	static void		initialize_game();
	static void		initialize_texture_atlas();

	static void		initialize_player();
};


