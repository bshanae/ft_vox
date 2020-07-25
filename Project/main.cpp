#include "application/application.h"
#include "map/renderer.h"
#include "map/chunk.h"

int						main()
{
	application::initialize();
	renderer::initialize();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	auto 				chunk = chunk::create();

	application::execute();
	return (0);
}
