#pragma once

#include "common/aliases.h"
#include "world/chunk/chunk_loader.h"
#include "world/loader/file.h"
#include "core/object/unique_object.h"

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

class					loader :
							public chunk_loader,
							public unique_object<loader>
{
public :

	explicit			loader();
						~loader() override;
private :

	enum class 			chunk_state : char
	{
		valid = 'v',
		invalid = 'i'
	};

	file				file;

	void				initialize_implementation() override;

	shared_ptr<chunk>	download_implementation(const vec3 &world_position) override;
	void				upload_implementation(const shared_ptr<chunk> &chunk) override;
};


