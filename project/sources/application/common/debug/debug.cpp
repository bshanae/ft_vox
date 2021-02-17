#include "debug.h"

#include "application/common/debug/defines.h"

void				debug::log(const string &message)
{
#if FT_VOX_LOG
	cout << message << endl;
#endif
}

void				debug::raise_error(const string &message)
{
	cerr << "(Warning) " << message << endl;
	exit(0);
}


void				debug::check_critical(bool statement, const string &message)
{
	if (!statement)
		raise_error(message);
}


void				debug::raise_warning(const string &message)
{
	cerr << "(Error) " << message << endl;
}


bool				debug::check(bool statement, const string &message)
{
	if (!statement)
		raise_warning(message);

	return statement;
}