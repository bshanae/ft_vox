#pragma once

#include "application/common/imports/std.h"

template			<typename type>
class 				listener
{
public :

	void 			notify(const shared_ptr<const type> &pocket)
	{
		when_notified(pocket);
	}

protected :

	virtual void	when_notified(const shared_ptr<const type> &pocket) = 0;
};