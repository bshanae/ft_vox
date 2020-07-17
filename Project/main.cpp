#include "application/application.h"

int					main()
{
	std::shared_ptr<object> o = std::make_shared<object>();
	application::initialize();
	return 0;
}
