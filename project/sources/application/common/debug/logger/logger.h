#pragma once

#include "application/common/imports/std.h"

namespace			debug
{
	class 			logger;
}

class				debug::logger
{
public:

	enum			log_group
	{
		engine,
		player
	};

	static void 	log(log_group group, const string &message);

private:

	static void 	log_engine(const string &message);
	static void 	log_player(const string &message);
};