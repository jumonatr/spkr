#pragma once

#include "event.h"
#include "cwrapper.h"

namespace vlc
{
	class event_manager : public cwrapper<libvlc_event_manager_t>
	{
	public:
		event_manager(libvlc_event_manager_t* manager)
			: cwrapper(manager)
		{}

		event::handle attach(libvlc_event_e ev, event::fun_t&& fun)
		{
			return event::attach(m_instance, ev, std::move(fun));
		}
	};
}