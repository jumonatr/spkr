#pragma once

#include "vlc/vlc.h"

#include <functional>
#include <memory>

namespace vlc
{
	void event_callback(const libvlc_event_t* ev, void* hptr);

	class event
	{
	public:
		typedef std::function<void(const libvlc_event_t* ev)> fun_t;
		typedef std::shared_ptr<event> handle;

		static handle attach(libvlc_event_manager_t* manager, libvlc_event_e evt_e, fun_t&& fun)
		{
			return handle{ new event{ manager, evt_e, move(fun) } };
		}

		~event()
		{
			libvlc_event_detach(m_manager, m_evt, event_callback, this);
		}

	private:
		event(libvlc_event_manager_t* manager, libvlc_event_e evt, fun_t&& fun)
			: m_fun(fun), m_manager(manager), m_evt(evt)
		{
			libvlc_event_attach(m_manager, m_evt, event_callback, this);
		}

		fun_t m_fun;
		libvlc_event_manager_t* m_manager;
		libvlc_event_e m_evt;
		
		friend void event_callback(const libvlc_event_t* ev, void* hptr)
		{
			auto ptr = (event*)hptr;
			ptr->m_fun(ev);
		}
	};
}
