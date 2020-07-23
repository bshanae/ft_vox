#include "application/application.h"
#include "chunk/chunk.h"

int						main()
{
	application::initialize();
	chunk::create();
	application::execute();
	return (0);
}
