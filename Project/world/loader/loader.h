#pragma once

#include "common/aliases.h"
#include "world/chunk/chunk_loader.h"
#include "world/loader/file.h"

struct						loader_settings
{
	friend class			loader;

private :

	static inline int 		chunk_linear_size = chunk_settings::size[0] * chunk_settings::size[1] * chunk_settings::size[2];

	static
	inline
	const string			header = "Vox";
};

/*
 *	Performs IO for .vox files
 *
 * 	Structure :
 * 	"Vox" - header
 * 	[state][x,y,z][blocks] - chunk
 * 	[state][x,y,z][blocks] - chunk
 * 	...
 *
 * 	Size (in bytes) :
 * 	[3] - header
 * 	[1][4,4,4][number of blocks in chunks] - chunk
 *
 * 	vox - identifier of file
 *	state - state of chunk
 *	x, y, z - position of chunk as 3 floats
 *	blocks - types of each block in chunk
 */

class						loader :
								public chunk_loader,
								public global<loader>
{
public :

	explicit				loader(const path &path_to_profile);
							~loader() override;
private :

	enum class 				chunk_state : char
	{
		valid = 'v',
		invalid = 'i'
	};

	file					file;

	void					initializer(shared_ptr<loader> loader) override;

	shared_ptr<chunk>		download_implementation(const vec3 &world_position) override;
	void					upload_implementation(const shared_ptr<chunk> &chunk) override;
};


