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
	bool					is_eof();

	friend file				&operator << (file &file, char value);
	friend file				&operator << (file &file, int value);
	friend file				&operator << (file &file, float value);
	friend file				&operator << (file &file, const vec3 &value);

	friend file				&operator >> (file &file, char &value);
	friend file				&operator >> (file &file, int &value);
	friend file				&operator >> (file &file, float &value);
	friend file				&operator >> (file &file, vec3 &value);

	template				<typename type = char>
	class					ignore
	{
	public :

		explicit			ignore(int value = 1)
		{
			this->value = sizeof(type) * value;
		}

		class				value : public property<int>
		{
			friend class 	file::ignore<type>;

		private :

			void			operator = (const int &value) override
			{
				this->value = value;
			}

		public :

			operator int () const override
			{
				return (value);
			}

		private :

			int				value;
		}					value;
	};

	template				<typename type>
	friend file				&operator >> (file &file, const ignore<type> &ignore)
	{
		file.stream.ignore(ignore.value);
		return (file);
	}

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


