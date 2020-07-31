#pragma once

#include "common/OpenGL.h"
#include "common/global.h"

#include "map/chunk.h"
#include "map/chunk_editor.h"

class							chunk_loader : public chunk_editor
{
public :
								chunk_loader() = default;
								~chunk_loader() override = default;

	static shared_ptr<chunk>	download(const vec3 &position)
	{
		assert(pointer != nullptr and "Can't download chunk");
		return (pointer->download_implementation(position));
	}

	static void					upload(const shared_ptr<chunk> &chunk)
	{
		assert(pointer != nullptr and "Can't upload chunk");
		return (pointer->upload_implementation(chunk));
	}

protected :

	static
	inline
	shared_ptr<chunk_loader>	pointer;

	virtual shared_ptr<chunk>	download_implementation(const vec3 &position) = 0;
	virtual void				upload_implementation(const shared_ptr<chunk> &chunk) = 0;
};