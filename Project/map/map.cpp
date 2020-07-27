#include "map.h"

					map::map()
{
	const auto 		chunk_size = vec3(::chunk_size[0], ::chunk_size[1], ::chunk_size[2]);
	auto 			translation = vec3(0.f);

	for (auto &iterator : *this)
	{
		translation = iterator->get_index().to_glm();
		translation *= chunk_size;

		iterator->get_value() = chunk::create();
		iterator->get_value()->set_translation(translation);

		index_map[iterator->get_value()] = iterator->get_index();
	}

	chunk::neighbor_provider = &map::provide_neighbor_chunk;
}

shared_ptr<chunk>	map::provide_neighbor_chunk(
					const shared_ptr<chunk> &main,
					axis axis,
					sign sign)
{
	auto			index = instance()->index_map[main].neighbor(axis, sign);

	return (index ? instance()->at(index) : nullptr);
}