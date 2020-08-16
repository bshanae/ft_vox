#pragma once

#include "common/aliases.h"
#include "common/OpenGL.h"
#include "common/property.h"

class						file final
{
public :

	explicit				file(const path &path);
							~file() = default;

	void					open();
	void					close();

	bool					is_empty();
	bool					is_good() const;
	bool					is_fail() const;
	bool					is_eof() const;

	explicit				operator bool () const;

	void 					clear();

	template				<typename type = char>
	class					ignore
	{
		friend class 		::file;

	public :

		explicit			ignore(int value = 1) : value(sizeof(type) * value) {}

	private :

		const int			value;
	};

	class					string
	{
		friend class 		::file;

	public :

		explicit			string(int requested_size) : requested_size(requested_size)
		{
			internal.reserve(requested_size);
		}

							operator std::string ()
		{
			return (internal);
		}

		friend file			&operator >> (file &file, string &value);

	private :

		const int			requested_size;
		std::string 		internal;
	};

	friend file				&operator << (file &file, char value);
	friend file				&operator << (file &file, int value);
	friend file				&operator << (file &file, float value);
	friend file				&operator << (file &file, const char *value);
	friend file				&operator << (file &file, const std::string &value);
	friend file				&operator << (file &file, const vec3 &value);

	friend file				&operator >> (file &file, char &value);
	friend file				&operator >> (file &file, int &value);
	friend file				&operator >> (file &file, float &value);
	friend file				&operator >> (file &file, vec3 &value);

	template				<typename type>
	friend file				&operator >> (file &file, const ignore<type> &ignore)
	{
		file.stream.ignore(ignore.value);
		return (file);
	}

	friend file				&operator >> (file &file, string &value);

	enum class 				mark
	{
		begin = ios::beg,
		end = ios::end
	};

	class					pointer : public property<read_write, int, pointer>
	{
		friend class 		file;

	public :

		using				property<read_write, int, pointer>::operator =;
		using				property<read_write, int, pointer>::operator int;
		using				property<read_write, int, pointer>::operator ->;

		void				operator = (mark mark)
		{
			assert(mark_setter != nullptr and "Mark setter is nullptr");
			mark_setter(mark);
		}

	private :

		using				mark_setter_type = function<void(mark)>;
		mark_setter_type	mark_setter = nullptr;
	};

	pointer					read_pointer;
	pointer					write_pointer;

private :

	const path				path;
	fstream					stream;

	void					create_new();
};


