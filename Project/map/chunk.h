#pragma once

#include "common/OpenGL.h"
#include "common/array3.h"
#include "application/object.h"
#include "map/model.h"

#include "map/block.h"

#warning "Create settings module"
static constexpr int	chunk_size[3] = {4, 4, 4};


class					chunk :
							public object,
							public model,
							private array3<block, chunk_size[0], chunk_size[1], chunk_size[2]>
{
	friend class		chunk_generator;
	friend class 		map;
	friend class 		renderer;

public :

	using				index = array3<block, chunk_size[0], chunk_size[1], chunk_size[2]>::index;

						chunk();
						~chunk() override = default;

	static
	shared_ptr<chunk>	create()
	{
		auto			chunk = make_shared<class chunk>();

		chunk->link_to_application();
		return (chunk);
	}

private :

	shared_ptr<model>	model;

	vector<GLfloat>		vertices;
	vector<GLfloat>		texture_coordinates;
	vector<GLuint>		indices;

	void				render() override;

	void				build_model();
	void				build_block(const index &index);
	void				build_quad(axis axis, sign sign, const index &index);

	template			<typename type>
	void				append_to_vector(vector<type> &target, const vector<type> &source)
	{
		target.insert(target.end(), source.begin(), source.end());
	}
};