#pragma once

#include "common/glm.h"
#include "common/aliases.h"
#include "common/property.h"

enum class 						axis : int
{
	x,
	y,
	z
};

enum class 						sign : int
{
	minus = -1,
	plus = +1
};

template 						<typename type, int size_x, int size_y, int size_z>
class							array3
{
private :

	static
	inline
	constexpr bool				validate_indices = true;

	using 						internal_type = array<array<array<type, size_z>, size_y>, size_x>;
	using 						internal_pointer_type = shared_ptr<internal_type>;

public :

								array3()
	{
		data = make_shared<internal_type>();
	}
	virtual						~array3() = default;

	struct						index
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
			return (ivec3(x, y, z));
		}

								operator vec3() const
		{
			return (vec3(x, y, z));
		}

		index					operator + (const index &that) const
		{
			index				result;

			result.x = this->x + that.x;
			result.y = this->y + that.y;
			result.z = this->z + that.z;

			return (result);
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
			return (this->x == that.x and this->y == that.y and this->z == that.z);
		}

		bool					operator != (const index& that) const
		{
			return (this->x != that.x or this->y != that.y or this->z != that.z);
		}

		explicit				operator bool () const
		{
			if (x < 0 or x >= size_x)
				return (false);
			if (y < 0 or y >= size_y)
				return (false);
			if (z < 0 or z >= size_z)
				return (false);
			return (true);
		}

		friend ostream 			&operator << (ostream &stream, const index &index)
		{
			stream << "array3::index(" << index.x << ", " << index.y << ", " << index.z << ")";
			return (stream);
		}

		index					neighbor(axis axis, sign sign) const
		{
			switch (axis)
			{
				case (axis::x) :
					return (*this + index(1, 0, 0) * (int)sign);

				case (axis::y) :
					return (*this + index(0, 1, 0) * (int)sign);

				case (axis::z) :
					return (*this + index(0, 0, 1) * (int)sign);
			}
		}

		index					reflect() const
		{
			index				result = *this;

			auto 				reflect_component = [](int &component, const int &bound)
			{
				if (component < 0)
					component = bound - 1;
				else if (component >= bound)
					component = 0;
			};

			reflect_component(result.x, size_x);
			reflect_component(result.y, size_y);
			reflect_component(result.z, size_z);

			return (result);
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
			assert(operator bool () and "Index for 3D array is not valid");
		}
	};

	auto						&at(const index &index)
	{
		if constexpr (validate_indices)
			index.validate();
		return ((*data)[index.x][index.y][index.z]);
	}

	const auto					&at(const index &index) const
	{
		if constexpr (validate_indices)
			index.validate();
		return ((*data)[index.x][index.y][index.z]);
	}

	auto						&at(int x, int y, int z)
	{
		if constexpr (validate_indices)
			index(x, y, z).validate();
		return ((*data)[x][y][z]);
	}

	const auto					&at(int x, int y, int z) const
	{
		if constexpr (validate_indices)
			index(x, y, z).validate();
		return ((*data)[x][y][z]);
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
			return (*this);
		}

		reference				operator * ()
		{
			return (*this);
		}

		pointer					operator -> ()
		{
			return (this);
		}

		bool					operator == (const iterator& that)
		{
			return (data == that.data and internal_index == that.internal_index);
		}

		bool					operator != (const iterator& that)
		{
			return (data != that.data or internal_index != that.internal_index);
		}

		auto					&value()
		{
			return ((*data)[internal_index.x][internal_index.y][internal_index.z]);
		}

		const auto				&value() const
		{
			return ((*data)[internal_index.x][internal_index.y][internal_index.z]);
		}

		index					&index()
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