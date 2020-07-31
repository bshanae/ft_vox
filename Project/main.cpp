#include "application/application.h"
#include "map/map.h"
#include "map/texture_atlas.h"
#include "camera/camera.h"
#include "renderer/renderer.h"
#include "generator/generator_controller.h"
#include "loader/loader.h"

int						main()
{
	application::initialize();

	texture_atlas::initialize("Project/resources/atlases/default.png");
	texture_atlas::associate_texture_with_block(block::type::dirt, ivec2(2, 15));

	renderer::initialize();
	generator_controller::initialize();
	loader::initialize();

	camera::create();
	map::create();

	{
		auto left = chunk::create(vec3(-5, 10, -20));
		auto right = chunk::create(vec3(5, 10, -20));
		auto upper = chunk::create(vec3(5, 20, -20));

		loader::upload(left);
		loader::upload(right);
		loader::upload(upper);

		loader::download(vec3(-5, 10, -20));
		loader::download(vec3(5, 20, -20));

		left->destroy();
		right->destroy();

	}

	application::execute();
	return (0);
}
