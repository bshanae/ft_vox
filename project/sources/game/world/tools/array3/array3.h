#pragma once

#include "application/common/defines.h"
#include "application/common/debug/debug.h"
#include "application/common/imports/glm.h"
#include "application/common/imports/std.h"

#include "game/world/tools/axis/axis.h"
#include "game/world/tools/sign/sign.h"

namespace						game
{
	template 					<typename, int, int, int>
	class						array3;
}

template 						<typename type, int size_x, int size_y, int size_z>
class							game::array3
{
private :

	using 						internal_type = array<array<array<type, size_z>, size_y>, size_x>;
	using 						internal_pointer_type = shared_ptr<internal_type>;

public :

								array3()
	{
		data = make_shared<internal_type>();
	}

	virtual						~array3() = default;

	struct						index final
	{
		friend class			array3;

	public :

		int 					x = 0;
		int 					y = 0;
		int 					z = 0;

								index() = default;
								~index() = default;

								index(int x, int y, int z) : x(x), y(y), z(z) {}

								operator ivec3() const
		{
			return ivec3(x, y, z);
		}

								operator vec3() const
		{
			return vec3(x, y, z);
		}

		index					operator + (const index &that) const
		{
			index				result;

			result.x = this->x + that.x;
			result.y = this->y + that.y;
			result.z = this->z + that.z;

			return result;
		}

		index					operator - (const index &that) const
		{
			index				result;

			result.x = this->x - that.x;
			result.y = this->y - that.y;
			result.z = this->z - that.z;

			return (result);
		}

		index					operator * (int factor) const
		{
			index				result;

			result.x = this->x * factor;
			result.y = this->y * factor;
			result.z = this->z * factor;

			return (result);
		}

		index					operator / (int factor) const
		{
			index				result;

			result.x = this->x / factor;
			result.y = this->y / factor;
			result.z = this->z / factor;

			return (result);
		}

		index					operator ++ ()
		{
			index				previous = *this;

			increase();
			return (previous);
		}

		index					operator ++ (int)
		{
			increase();
			return (*this);
		}

		index					operator -- ()
		{
			index				previous = *this;

			decrease();
			return (previous);
		}

		index					operator -- (int)
		{
			decrease();
			return (*this);
		}

		bool					operator == (const index& that) const
		{
			return this->x == that.x and this->y == that.y and this->z == that.z;
		}

		bool					operator != (const index& that) const
		{
			return this->x != that.x or this->y != that.y or this->z != that.z;
		}

		friend ostream 			&operator << (ostream &stream, const index &index)
		{
			stream << "array3::index(" << index.x << ", " << index.y << ", " << index.z << ")";
			return (stream);
		}

		bool					is_valid() const
		{
			return
			(
				x >= 0 and x < size_x and
				y >= 0 and y < size_y and
				z >= 0 and z < size_z
			);
		}

		index					get_neighbor(axis axis, sign sign) const
		{
			switch (axis)
			{
				case (axis::x) :
					return *this + index(1, 0, 0) * (int)sign;

				case (axis::y) :
					return *this + index(0, 1, 0) * (int)sign;

				case (axis::z) :
					return *this + index(0, 0, 1) * (int)sign;
			}
		}

	private :

		void					increase()
		{
			bool				can_increase_x = x < size_x - 1;
			bool				can_increase_y = y < size_y - 1;
			bool				can_increase_z = z < size_z - 1;

			if (can_increase_z)
				z++;
			else if (can_increase_y)
			{
				y++;
				z = 0;
			}
			else if (can_increase_x)
			{
				x++;
				y = 0;
				z = 0;
			}
			else
			{
				x = -1;
				y = -1;
				z = -1;
			}
		}

		void					decrease()
		{
			bool				can_decrease_x = x > 0;
			bool				can_decrease_y = y > 0;
			bool				can_decrease_z = z > 0;

			if (can_decrease_z)
				z--;
			else if (can_decrease_y)
			{
				y--;
				z = size_z;
			}
			else if (can_decrease_x)
			{
				x--;
				y = size_z;
			}
			else
			{
				x = -1;
				y = -1;
				z = -1;
			}
		}

		void 					validate() const
		{
			debug::check_critical(is_valid(), "[application::array3] Index for 3D array is not valid");
		}
	};

	auto						&at(const index &index)
	{
#if FT_VOX_ARRAY3_VALIDATION
		index.validate();
#endif

		return (*data)[index.x][index.y][index.z];
	}

	const auto					&at(const index &index) const
	{
#if FT_VOX_ARRAY3_VALIDATION
		index.validate();
#endif

		return (*data)[index.x][index.y][index.z];
	}

	auto						&at(int x, int y, int z)
	{
#if FT_VOX_ARRAY3_VALIDATION
		index(x, y, z).validate();
#endif

		return (*data)[x][y][z];
	}

	const auto					&at(int x, int y, int z) const
	{
#if FT_VOX_ARRAY3_VALIDATION
		index(x, y, z).validate();
#endif

		return (*data)[x][y][z];
	}

	class						iterator
	{
	public:

		using					value_type = iterator;
		using					reference = iterator &;
		using					pointer = iterator *;
		using 					iterator_category = std::input_iterator_tag;
		using 					difference_type = int;

								iterator(const internal_pointer_type &data, const index &index) :
									data(data),
									internal_index(index)
								{}

								iterator(const iterator &that) :
									data(that.data),
									internal_index(that.internal_index)
								{}

		iterator				&operator = (const iterator& that)
		{
			if (this != &that)
			{
				this->data = that.data;
				this->index = that.index;
			}

			return (*this);
		}

		iterator				operator ++ ()
		{
			iterator			previous_state = *this;

			internal_index++;
			return (previous_state);
		}

		iterator				operator ++ (int)
		{
			internal_index++;
			return *this;
		}

		reference				operator * ()
		{
			return *this;
		}

		pointer					operator -> ()
		{
			return this;
		}

		bool					operator == (const iterator& that) const
		{
			return data == that.data and internal_index == that.internal_index;
		}

		auto					&get_value()
		{
			return (*data)[internal_index.x][internal_index.y][internal_index.z];
		}

		const auto				&get_value() const
		{
			return (*data)[internal_index.x][internal_index.y][internal_index.z];
		}

		index					&get_index()
		{
			return (internal_index);
		}

	private:

		internal_pointer_type	data;
		struct index			internal_index;
	};

	iterator					begin()
	{
		return (iterator(data, index(0, 0, 0)));
	}

	iterator					end()
	{
		return (iterator(data, index(-1, -1, -1)));
	}

private :

	internal_pointer_type		data;
};