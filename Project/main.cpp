#include "application/application.h"
#include "map/renderer.h"
#include "map/chunk.h"

int						main()
{
	application::initialize();
#warning "Improve architecture"
	renderer::initialize();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	chunk::create();
	application::execute();
	return (0);
}
