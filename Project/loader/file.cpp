#include "file.h"

					file::file(const class path &path) :
						read_pointer(stream),
						write_pointer(stream),
						path(path)
{}

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

bool				file::is_empty()
{
	bool			result;

	result = stream.peek() == fstream::traits_type::eof();
	if (result)
		stream.clear();
	return (result);
}

bool				file::is_good() const
{
	return (stream.good());
}
bool				file::is_fail() const
{
	return (stream.fail());
}
bool				file::is_eof() const
{
	return (stream.eof());
}

					file::operator bool () const
{
	return (is_good());
}

void 				file::clear()
{
	stream.clear();
}

file				&operator << (file &file, char value)
{
	file.stream.write(&value, sizeof(char));
	return (file);
}

file				&operator << (file &file, int value)
{
	file.stream.write(reinterpret_cast<char *>(&value), sizeof(int));
	return (file);
}

file				&operator << (file &file, float value)
{
	file.stream.write(reinterpret_cast<char *>(&value), sizeof(float));
	return (file);
}

file				&operator << (file &file, const char *value)
{
	file.stream.write(value, strlen(value));
	return (file);
}

file				&operator << (file &file, const string &value)
{
	file.stream.write(value.c_str(), value.size());
	return (file);
}

file				&operator << (file &file, const vec3 &value)
{
	file << value.x << value.y << value.z;
	return (file);
}

file				&operator >> (file &file, char &value)
{
	file.stream.read(&value, sizeof(char));
	return (file);
}

file				&operator >> (file &file, int &value)
{
	file.stream.read(reinterpret_cast<char *>(&value), sizeof(int));
	return (file);
}

file				&operator >> (file &file, float &value)
{
	file.stream.read(reinterpret_cast<char *>(&value), sizeof(float));
	return (file);
}

file				&operator >> (file &file, file::string &value)
{
	char			buffer[value.requested_size + 1];

	file.stream.read(buffer, value.requested_size);
	buffer[value.requested_size] = '\0';

	value.internal = std::string(buffer);
	return (file);
}

file				&operator >> (file &file, vec3 &value)
{
	file >> value.x >> value.y >> value.z;
	return (file);
}

void				file::read_pointer::operator = (const int &value)
{
	stream.seekg(value);
}

void				file::read_pointer::operator = (label label)
{
	stream.seekg(0, static_cast<ios::seekdir>(label));
}

					file::read_pointer::operator int () const
{
	return (stream.tellg());
}

void				file::write_pointer::operator = (const int &value)
{
	stream.seekp(value);
}

void 				file::write_pointer::operator = (label label)
{
	stream.seekg(0, static_cast<ios::seekdir>(label));
}
					file::write_pointer::operator int () const
{
	return (stream.tellp());
}

void				file::create_new()
{
	stream.close();

	stream.open(path, ios::out);
	assert(stream.is_open() and "Can't open profile");
	stream.close();

	stream.open(path, ios::in | ios::out | ios::binary);
}