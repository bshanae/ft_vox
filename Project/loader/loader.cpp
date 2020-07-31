#include "loader.h"

void					loader::initializer(shared_ptr<loader> loader)
{
	static_assert(sizeof(block::type) == 1u and "Block type should be size of byte");
	chunk_loader::pointer = static_pointer_cast<chunk_loader>(loader);
}

#warning "Need header"

shared_ptr<chunk>		loader::download_implementation(const vec3 &world_position)
{
	int					pointer;
	bool 				have_found_chunk = false;

	chunk_state			test_state;
	vec3				test_position;

	file.open();

	while (not file.is_eof())
	{
		pointer = file.read_pointer;

		file >> (char &)test_state;
		file >> test_position;

		cerr << "test state = " << (char)test_state << endl;
		cerr << "test position = " << to_string(test_position) << endl << endl;

		if (test_position == world_position)
		{
			have_found_chunk = true;
			break ;
		}

		file >> file::ignore(loader_settings::chunk_linear_size);
	}

	if (not have_found_chunk)
	{
		cerr << "Chunk not found" << endl;
		return (nullptr);
	}

	shared_ptr<chunk>	chunk;

	chunk = chunk::create(world_position);
	chunk_editor::use(chunk);
	for (auto iterator = chunk_editor::begin(); iterator != chunk_editor::end(); iterator++)
		file >> (char &)chunk_editor::at(iterator);

	file.write_pointer = pointer;
	file << (char)(chunk_state::invalid);

	file.close();

	return (chunk);
}

void					loader::upload_implementation(const shared_ptr<chunk> &chunk)
{
	bool 				have_found_place_for_writing = false;
	int					pointer = 0;

	chunk_state			state;

	file.open();

	if (not file.is_empty())
	{
		while (not file.is_eof())
		{
			pointer = file.read_pointer;

			file >> (char &)state;
			file >> file::ignore<float>(3);
			file >> file::ignore(loader_settings::chunk_linear_size);

			if (state != chunk_state::valid)
			{
				have_found_place_for_writing = true;
				break;
			}
		}

		if (have_found_place_for_writing)
			file.write_pointer = pointer;
		else
			file.write_pointer = file::label::end;
	}

	file << (char)chunk_state::valid;
	file << chunk->get_position();

	chunk_editor::use(chunk);
	for (auto iterator = chunk_editor::begin(); iterator != chunk_editor::end(); iterator++)
		file << (char)chunk_editor::at(iterator);

	file.close();
}