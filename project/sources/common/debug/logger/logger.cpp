#include "logger.h"

#include "common/debug/debug.h"

using namespace		debug;

void 				logger::log(log_group group, const string &message)
{
	switch (group)
	{
		case engine:
			log_engine(message);
			break;

		case player:
			log_player(message);
			break;
	}
}

void				logger::log_engine(const string &message)
{
#if FT_DEBUG && FT_LOG_ENGINE
	cout << message << endl;
#endif
}

void				logger::log_player(const string &message)
{
#if FT_DEBUG && FT_LOG_PLAYER
	cout << message << endl;
#endif
}