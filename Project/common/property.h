#pragma once

#include "common/aliases.h"

template 				<typename type, typename owner_type>
class					property_base
{
	template			<typename, typename, typename>
	friend class 		property;

protected :

	type				value;

						property_base()
	{
		getter = [this](){ return (value); };
		setter = [this](const type &value){ this->value = value; };
	}

	property_base		&operator = (const type &value)
	{
		assert(setter != nullptr and "Setter is nullptr");
		setter(value);
		return (*this);
	}

						operator type () const
	{
		assert(getter != nullptr and "Setter is nullptr");
		return (getter());
	}

	type				operator -> () const
	{
		assert(getter != nullptr and "Setter is nullptr");
		return (getter());
	}

private :

	using 				getter_type = function<type()>;
	using 				setter_type = function<void(const type &)>;

protected :

	getter_type			getter = nullptr;
	setter_type			setter = nullptr;
};

class 					read_only;
class 					write_only;
class 					read_write;

template				<typename access, typename type, typename owner_type>
class					property
{};

template				<typename type, typename owner_type>
class					property<read_only, type, owner_type> : public property_base<type, owner_type>
{
	friend				owner_type;

public :

	using				property_base<type, owner_type>::operator type;
	using				property_base<type, owner_type>::operator ->;

private :

	using				property_base<type, owner_type>::operator =;
};

template				<typename type, typename owner_type>
class					property<write_only, type, owner_type> : public property_base<type, owner_type>
{
	friend				owner_type;

public :

	using				property_base<type, owner_type>::operator =;

private :

	using				property_base<type, owner_type>::operator type;
	using				property_base<type, owner_type>::operator ->;
};

template				<typename type, typename owner_type>
class					property<read_write, type, owner_type> : public property_base<type, owner_type>
{
	friend				owner_type;

public :

	using				property_base<type, owner_type>::operator =;
	using				property_base<type, owner_type>::operator type;
	using				property_base<type, owner_type>::operator ->;
};