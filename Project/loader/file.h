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

							operator bool () const;

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

	enum class				label
	{
		begin = ios::beg,
		end = ios::end
	};

	class					read_pointer : public property<int>
	{
	public:
							read_pointer(fstream &stream) : stream(stream) {}

		void				operator = (const int &value) override;
		void				operator = (label label);

							operator int () const override;
	private :

		fstream				&stream;
	}						read_pointer;

	class					write_pointer : public property<int>
	{
	public:
							write_pointer(fstream &stream) : stream(stream) {}

		void				operator = (const int &value) override;
		void				operator = (label label);

							operator int () const override;
	private :

		fstream				&stream;
	}						write_pointer;

private :

	const path				path;
	fstream					stream;

	void					create_new();
};


