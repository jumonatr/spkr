#pragma once

#include "vlc/vlc.h"

#include "cwrapper.h"
#include "media_list.h"

#include <string>

namespace vlc
{
	class media_discoverer : public owner_cwrapper<libvlc_media_discoverer_t>
	{
	public:
		media_discoverer(libvlc_instance_t* vlc, const std::string& name)
			: owner_cwrapper(libvlc_media_discoverer_new_from_name(vlc, name.c_str()))
			, m_list(libvlc_media_discoverer_media_list(m_instance))
			, m_events(libvlc_media_discoverer_event_manager(m_instance))
		{}

		bool is_running() const
		{
			return libvlc_media_discoverer_is_running(m_instance) != 0;
		}

		media_list& list()
		{
			return m_list;
		}

		event_manager& events()
		{
			return m_events;
		}

		~media_discoverer()
		{
			libvlc_media_discoverer_release(m_instance);
		}

	private:
		media_list m_list;
		event_manager m_events;
	};
}
