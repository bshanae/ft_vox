#include "object.h"

#include "application/application.h"

void	 			object::link_to_application()
{
	application::instance()->objects.push_back(shared_from_this());
}
