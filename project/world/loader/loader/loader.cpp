#include "loader.h"

#include "world/chunk/chunk.h"
#include "world/loader/loader/loader_settings.h"

using namespace		world;

					loader::loader() : file(loader_settings::path_to_file)
{
	layout = "System";
	should_be_updated = false;
	should_be_rendered = false;

	file.open();
	if (file.is_empty)
		file << loader_settings::header;
	else
	{
		file::string	test(loader_settings::header.size());

		file >> test;
		assert((string)test == loader_settings::header and "Profile has invalid format");
	}
}

						loader::~loader()
{
	file.close();
}

bool					loader::download(const shared_ptr<chunk> &chunk)
{
	auto				&file = instance()->file;

	int					pointer;
	bool 				have_found_chunk = false;

	chunk_state			test_state;
	vec3				test_position;

	file.read_pointer = loader_settings::header.size();
	file.write_pointer = loader_settings::header.size();

	while (file)
	{
		pointer = file.read_pointer;

		file >> (char &)test_state;
		file >> test_position;

		if (test_state == chunk_state::valid and test_position == *chunk->position)
		{
			have_found_chunk = true;
			break ;
		}

		file >> file::ignore(loader_settings::chunk_linear_size);
	}

	if (not have_found_chunk)
	{
		file.clear();
		return (false);
	}

	for (auto iterator = chunk->begin(); iterator != chunk->end(); iterator++)
		file >> (char &)iterator->value().type;

	file.write_pointer = pointer;
	file << (char)(chunk_state::invalid);

	return (true);
}

void					loader::upload(const shared_ptr<chunk> &chunk)
{
	auto				&file = instance()->file;

	bool 				have_found_place_for_writing = false;
	int					pointer;

	chunk_state			state;

	file.read_pointer = loader_settings::header.size();
	file.write_pointer = loader_settings::header.size();

	while (true)
	{
		pointer = file.read_pointer;

		if (not (file >> (char &)state))
			break ;

		file >> file::ignore<float>(3);
		file >> file::ignore(loader_settings::chunk_linear_size);

		if (state == chunk_state::invalid)
		{
			have_found_place_for_writing = true;
			break;
		}
	}

	file.clear();

	if (have_found_place_for_writing)
		file.write_pointer = pointer;
	else
		file.write_pointer = file::end;

	file << (char)chunk_state::valid;
	file << *chunk->position;

	for (auto iterator = chunk->begin(); iterator != chunk->end(); iterator++)
		file << (char)iterator->value().type;
}