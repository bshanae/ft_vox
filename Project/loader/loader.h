#pragma once

#include "common/aliases.h"
#include "map/chunk_loader.h"
#include "loader/file.h"

struct						loader_settings
{
	friend class 			loader;

	static
	inline
	const path				path_to_profile = "test.vox";

private :

	static inline int 		chunk_linear_size = chunk_settings::size[0] * chunk_settings::size[1] * chunk_settings::size[2];
};

/*
 *	Performs IO for .vox files
 *
 * 	Structure :
 * 	["vox",a,b,c]
 * 	[state][x,y,z][blocks]
 * 	...
 *
 * 	Size (in bytes) :
 * 	[3 + 3 * 4]
 * 	[  1  ][4,4,4][number of blocks in chunks]
 *
 * 	vox - identifier of file
 * 	a, b, c - size of chunk
 *	state - state of chunk
 *	x, y, z - position of chunk as 3 floats
 *	blocks - types of each block in chunk
 */

class						loader :
								public chunk_loader,
								public global<loader>
{
public :
							loader() : file(loader_settings::path_to_profile) {}
							~loader() override = default;
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


