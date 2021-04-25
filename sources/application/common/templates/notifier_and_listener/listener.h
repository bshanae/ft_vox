#pragma once

#include "application/common/imports/std.h"

template			<typename type>
class 				listener
{
public :

	void 			notify(const type &notification)
	{
		when_notified(notification);
	}

protected :

	virtual void	when_notified(const type &notification) = 0;
};