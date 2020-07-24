#pragma once

#include "common/aliases.h"

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
								~array3() = default;

	struct						index
	{
		friend class			array3;

	public :

		int 					x = 0;
		int 					y = 0;
		int 					z = 0;

								index() = default;
								~index() = default;

								index(int x, int y, int z) : x(x), y(y), z(z)
								{}

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

								operator bool () const
		{
			if (x < 0 or x >= size_x)
				return (false);
			if (y < 0 or y >= size_y)
				return (false);
			if (z < 0 or z >= size_z)
				return (false);
			return (true);
		}

		index					neighbor(axis axis, sign sign) const
		{
			int					sign_value;

			switch (sign)
			{
				case (sign::plus) :
					sign_value = +1;
					break ;

				case (sign::minus) :
					sign_value = -1;
					break ;
			}

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
		return (data[index.x][index.y][index.z]);
	}

	auto						&at(int x, int y, int z)
	{
		if constexpr (validate_indices)
			index(x, y, z).validate();
		return (data[x][y][z]);
	}

	const auto					&at(int x, int y, int z) const
	{
		if constexpr (validate_indices)
			index(x, y, z).validate();
		return (data[x][y][z]);
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
									index(index)
								{}

								iterator(const iterator &that) :
									data(that.data),
									index(that.index)
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

			index++;
			return (previous_state);
		}

		iterator				operator ++ (int)
		{
			index++;
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
			return (data == that.data and index == that.index);
		}

		bool					operator != (const iterator& that)
		{
			return (data != that.data or index != that.index);
		}

		auto					&get_value() const
		{
			return ((*data)[index.x][index.y][index.z]);
		}

		const index				&get_index() const
		{
			return (index);
		}

	private:

		internal_pointer_type	data;
		index					index;
	};

	class						const_iterator
	{
	public:

		using					value_type = iterator;
		using					reference = iterator &;
		using					pointer = iterator *;
		using 					iterator_category = std::input_iterator_tag;
		using 					difference_type = int;

								const_iterator(const internal_pointer_type &data, const index &index) :
										data(data),
										index(index)
								{}

								const_iterator(const const_iterator &that) :
										data(that.data),
										index(that.index)
								{}

		const_iterator			&operator = (const const_iterator& that)
		{
			if (this != &that)
			{
				this->data = that.data;
				this->index = that.index;
			}

			return (*this);
		}

		const_iterator			operator ++ ()
		{
			const_iterator		previous_state = *this;

			index++;
			return (previous_state);
		}

		const_iterator			operator ++ (int)
		{
			index++;
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

		bool					operator == (const const_iterator& that)
		{
			return (data == that.data and index == that.index);
		}

		bool					operator != (const const_iterator& that)
		{
			return (data != that.data or index != that.index);
		}

		const auto				&get_value() const
		{
			return ((*data)[index.x][index.y][index.z]);
		}

		const index				&get_index() const
		{
			return (index);
		}

	private:

		internal_pointer_type	data;
		index					index;
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