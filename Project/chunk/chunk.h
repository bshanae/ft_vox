#pragma once

#include "common/OpenGL.h"
#include "model.h"
#include "object/object.h"
#include "program/program.h"
#include "program/uniform.h"
#include "chunk/block.h"

#warning "Move to .cpp"
#include "camera/camera.h"

class							chunk :
									public object,
									public model
{
public :

								chunk();
								~chunk() override = default;

	static
	shared_ptr<chunk>			create()
	{
		auto					chunk = make_shared<class chunk>();

		link_to_application(chunk);
		return (chunk);
	}

	void						render() override;

private :

	static constexpr int		size[3] = {16, 16, 256};

	using						blocks_type = array<array<array<block, size[2]>, size[1]>, size[0]>;

	blocks_type					blocks;
	shared_ptr<model>			model;

	vector<float>				vertices;
	vector<GLuint>				indices;

	class						renderer
	{
	public :
								renderer()
		{
			program = make_unique<class program>(path_to_vertex_shader, path_to_fragment_shader);
			uniform_projection = program->create_uniform<mat4>("uniform_projection");
			uniform_view = program->create_uniform<mat4>("uniform_view");
		}
								~renderer() = default;

		void					render(const chunk &chunk)
		{
			const auto			&model = chunk.model;

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			program->bind(true);
			model->bind(true);

			uniform_projection.upload(camera::get_projection_matrix());
			uniform_view.upload(camera::get_view_matrix());

			glDrawElements(GL_TRIANGLES, model->get_number_of_indices(), GL_UNSIGNED_INT, nullptr);

			model->bind(false);
			program->bind(false);
		}

	private :

		inline static const
		path					path_to_vertex_shader = "Project/resources/shaders/vertex.glsl";
		inline static const
		path					path_to_fragment_shader = "Project/resources/shaders/fragment.glsl";

		unique_ptr<program>		program;

		uniform<mat4>			uniform_projection;
		uniform<mat4>			uniform_view;
	};

	static inline
	unique_ptr<renderer>		renderer;

	enum class					direction
	{
		begin,
		left,
		right,
		bottom,
		top,
		back,
		front,
		end
	};

	void						build_block(block block_type, ivec3 index);
	void						build_quad(direction type, ivec3 index);

	ivec3						get_neighbor(ivec3 index, direction direction)
	{
		switch (direction)
		{
			case (direction::left) :
				return (index + ivec3(-1, 0, 0));

			case (direction::right) :
				return (index + ivec3(1, 0, 0));

			case (direction::bottom) :
				return (index + ivec3(0, -1, 0));

			case (direction::top) :
				return (index + ivec3(0, 1, 0));

			case (direction::back) :
				return (index + ivec3(0, 0, -1));

			case (direction::front) :
				return (index + ivec3(0, 0, 1));

			default :
				return (index);
		}
	}

	bool						does_index_exist(ivec3 value)
	{
		if (value.x < 0 or value.x >= size[0])
			return (false);
		if (value.y < 0 or value.y >= size[1])
			return (false);
		if (value.z < 0 or value.z >= size[2])
			return (false);
		return (true);
	}

	bool						is_block_empty(ivec3 index)
	{
		return (blocks[index.x][index.y][index.z].is_empty());
	}
};