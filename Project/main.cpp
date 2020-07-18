#include "application/application.h"
#include "chunk/chunk.h"

int						main()
{
	shared_ptr<chunk>	chunk;

	application::initialize();

	chunk = chunk::create();
	application::execute();
	return (0);
}
