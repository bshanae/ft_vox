#pragma once

#include "application/common/imports/std.h"

template			<typename type>
class 				listener
{
public :

	void 			notify(const type &event)
	{
		when_notified(event);
	}

protected :

	virtual void	when_notified(const type &event) = 0;
};