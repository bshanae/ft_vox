#include "chunk_fauna_generator.h"

#include "game/world/chunk/chunk/chunk.h"

using namespace			game;

						chunk_fauna_generator::chunk_fauna_generator()
{
    biome_collection::construct();

    noise_for_mushroom = perlin_noise(chunk_settings::landscape_seed, 0.07f);
}

void                    chunk_fauna_generator::generation_flora(const shared_ptr<chunk> &chunk)
{
    const int           zero_height = 62;

    const vec3			position = chunk->get_position();
    chunk::index		index;

    for (index.x = 0; index.x < chunk_settings::size[0]; index.x++)
    for (index.y = zero_height; index.y < chunk_settings::size[1]; index.y++)
    for (index.z = 0; index.z < chunk_settings::size[2]; index.z++)
    {
        if (chunk->at(index).get_type() == block_type::dirt)
        {
            if (get_instance()->noise_for_mushroom.generate({position.x + index.x, position.z + index.z}) > 0.95f)
                chunk->at(index).set_type(block_type::mushroom);
        }
        else if (chunk->at(index).get_type() == block_type::dirt_with_grass)
            if ((int)index.x % 4 == 0 && (int)index.z % 4 == 0)
                if (get_instance()->noise_for_mushroom.generate({position.x, position.z}) > 0.80f)
                    generation_tree(chunk, index);
    }
}

void                    chunk_fauna_generator::generation_tree(const shared_ptr<chunk> &chunk, chunk::index index)
{
    int                 height = 7;
    random_noise        random;

    for (int y = 0; y < height; y++)
    {
        chunk->at(index).set_type(block_type::wood);

        int delta = height - y;
        if (delta <= 4)
        {
            if (delta == 4)
                delta = 3;

            for (int x = -delta; x <= delta; x++)
            for (int z = -delta; z <= delta; z++)
            {

                if (x == 0 && z == 0)
                    continue;

                if (random.generate_1d({x, z + y}, 0) > 0.1)
                    chunk->at({index.x + x, index.y, index.z + z}).set_type(block_type::leaves);
            }
        }

        index.y++;
    }
}