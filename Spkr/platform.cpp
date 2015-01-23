#include "platform.h"

#ifndef WIN32
	#include <unistd.h>
#endif

namespace plat
{
	void pause()
	{
	#ifdef WIN32
		system("pause");
	#else
		::pause();
	#endif
	}
}