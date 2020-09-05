#include "file.h"

using namespace		world;

					file::file(const class path &path) : path(path)
{
	read_pointer.getter = [this](){ return (stream.tellg()); };
	read_pointer.setter = [this](const int &value){ stream.seekg(value); };
	read_pointer.mark_setter = [this](mark mark){ stream.seekg(0, (ios::seekdir)mark); };
	read_pointer.prohibit_direct_access();

	write_pointer.getter = [this](){ return (stream.tellp()); };
	write_pointer.setter = [this](const int &value){ stream.seekp(value); };
	write_pointer.mark_setter = [this](mark mark){ stream.seekp(0, (ios::seekdir)mark); };
	write_pointer.prohibit_direct_access();

	is_empty.getter = [this]()
	{
		bool			result;

		result = stream.peek() == fstream::traits_type::eof();
		if (result)
			stream.clear();
		return (result);
	};

	is_good.getter = [this](){ return (stream.good()); };
	is_fail.getter = [this](){ return (stream.fail()); };
	is_eof.getter = [this](){ return (stream.eof()); };

}

void				file::open()
{
	stream.open(path, ios::in | ios::out | ios::binary);
	if (not stream.is_open())
		create_new();
}

void				file::close()
{
	stream.close();
}

					file::operator bool () const
{
	return (is_good);
}

void 				file::clear()
{
	stream.clear();
}

file				&world::operator << (file &file, char value)
{
	file.stream.write(&value, sizeof(char));
	return (file);
}

file				&world::operator << (file &file, int value)
{
	file.stream.write(reinterpret_cast<char *>(&value), sizeof(int));
	return (file);
}

file				&world::operator << (file &file, float value)
{
	file.stream.write(reinterpret_cast<char *>(&value), sizeof(float));
	return (file);
}

file				&world::operator << (file &file, const char *value)
{
	file.stream.write(value, strlen(value));
	return (file);
}

file				&world::operator << (file &file, const string &value)
{
	file.stream.write(value.c_str(), value.size());
	return (file);
}

file				&world::operator << (file &file, const vec3 &value)
{
	file << value.x << value.y << value.z;
	return (file);
}

file				&world::operator >> (file &file, char &value)
{
	file.stream.read(&value, sizeof(char));
	return (file);
}

file				&world::operator >> (file &file, int &value)
{
	file.stream.read(reinterpret_cast<char *>(&value), sizeof(int));
	return (file);
}

file				&world::operator >> (file &file, float &value)
{
	file.stream.read(reinterpret_cast<char *>(&value), sizeof(float));
	return (file);
}

file				&world::operator >> (file &file, file::string &value)
{
	char			buffer[value.requested_size + 1];

	file.stream.read(buffer, value.requested_size);
	buffer[value.requested_size] = '\0';

	value.internal = std::string(buffer);
	return (file);
}

file				&world::operator >> (file &file, vec3 &value)
{
	file >> value.x >> value.y >> value.z;
	return (file);
}

void				file::create_new()
{
	stream.close();

	stream.open(path, ios::out);
	assert(stream.is_open() and "Can't open profile");
	stream.close();

	stream.open(path, ios::in | ios::out | ios::binary);
}