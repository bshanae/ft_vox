#include "application/application.h"
#include "map/renderer.h"
#include "map/map.h"
#include "map/chunk_generator.h"

int						main()
{
	application::initialize();
	renderer::initialize();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glFrontFace(GL_CCW);

	map::create();

	application::execute();
	return (0);
}
