#pragma once

#include "common/aliases.h"

template 				<typename type>
class					property_read_functionality
{
	template			<typename, typename, typename>
	friend class 		property;

protected :

	explicit			property_read_functionality(const type *pointer) :
							pointer(pointer)
	{
		getter = [this](){
			assert(is_default_getter_allowed and "Default getter is prohibited");
			return (*this->pointer);
		};
	}

						operator type () const
	{
		assert(getter != nullptr and "Getter is nullptr");
		return (getter());
	}

	const type			&operator * () const
	{
		assert(is_direct_access_allowed and "Direct access is prohibited");
		return (*pointer);
	}

	const type			*operator -> () const
	{
		assert(is_direct_access_allowed and "Direct access is prohibited");
		return (pointer);
	}

protected :

	using 				getter_type = function<type()>;
	getter_type			getter = nullptr;

	bool 				is_default_getter_allowed = true;
	bool 				is_direct_access_allowed = true;

private :

	const type			*pointer;
};

template 				<typename type>
class					property_write_functionality
{
	template			<typename, typename, typename>
	friend class 		property;

protected :

	explicit			property_write_functionality(type *pointer) : pointer(pointer)
	{
		setter = [this](const type &value)
		{
			assert(is_default_setter_allowed and "Default setter is prohibited");
			*this->pointer = value;
		};
	}

	void				operator = (const type &value)
	{
		assert(setter != nullptr and "Setter is nullptr");
		setter(value);
	}

	type				&operator * ()
	{
		assert(is_direct_access_allowed and "Direct access is prohibited");
		return (*pointer);
	}

	type				*operator -> ()
	{
		assert(is_direct_access_allowed and "Direct access is prohibited");
		return (pointer);
	}

protected :

	using 				setter_type = function<void(const type &)>;
	setter_type			setter = nullptr;

	bool 				is_default_setter_allowed = true;
	bool 				is_direct_access_allowed = true;

private :

	type				*pointer;
};

template 				<typename type, typename owner_type>
class 					property_complete_functionality :
							public property_read_functionality<type>,
							public property_write_functionality<type>
{
	template			<typename, typename, typename>
	friend class 		property;

public :
						property_complete_functionality() :
							property_read_functionality<type>(&value),
							property_write_functionality<type>(&value)
						{}

						property_complete_functionality(property_complete_functionality &that) :
							property_read_functionality<type>(&value),
							property_write_functionality<type>(&value)
	{
		this->value = that.value;
	}

						property_complete_functionality	&
						operator = (const property_complete_functionality &that)
	{
		if (*this != that)
			this->value = that.value;
		return (*this);
	}

protected :

	type				value;

	void 				prohibit_default_getter()
	{
		property_read_functionality<type>::is_default_getter_allowed = false;
	}

	void 				prohibit_default_setter()
	{
		property_write_functionality<type>::is_default_setter_allowed = false;
	}

	void 				prohibit_direct_access()
	{
		property_read_functionality<type>::is_direct_access_allowed = false;
		property_write_functionality<type>::is_direct_access_allowed = false;
	}
};

class 					read_only;
class 					write_only;
class 					read_write;

template				<typename access, typename type, typename owner_type>
class					property
{};

template				<typename type, typename owner_type>
class					property<read_only, type, owner_type> : public property_complete_functionality<type, owner_type>
{
	friend				owner_type;

public :

	using				property_read_functionality<type>::operator type;
	using				property_read_functionality<type>::operator ->;
	using				property_read_functionality<type>::operator *;

private :

	using				property_write_functionality<type>::operator =;
};

template				<typename type, typename owner_type>
class					property<write_only, type, owner_type> : public property_complete_functionality<type, owner_type>
{
	friend				owner_type;

public :

	using				property_write_functionality<type>::operator =;
	using				property_write_functionality<type>::operator ->;
	using				property_write_functionality<type>::operator *;

private :

	using				property_read_functionality<type>::operator type;
};

template				<typename type, typename owner_type>
class					property<read_write, type, owner_type> : public property_complete_functionality<type, owner_type>
{
	friend				owner_type;

public :

	using				property_write_functionality<type>::operator =;
	using				property_write_functionality<type>::operator ->;
	using				property_write_functionality<type>::operator *;

	using				property_read_functionality<type>::operator type;
};