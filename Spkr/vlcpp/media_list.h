#pragma once

#include "vlc/vlc.h"

#include "cwrapper.h"
#include "media.h"
#include "event_manager.h"

#include <exception>

namespace vlc
{
	class media_list : public cwrapper<libvlc_media_list_t>
	{
	public:
		media_list(libvlc_media_list_t* list)
			: cwrapper(list), m_events{ libvlc_media_list_event_manager(m_instance) }
		{}

		size_t size() const
		{
			return libvlc_media_list_count(m_instance);
		}

		media get(size_t idx) const
		{
			if (idx < 0 || idx >= size())
				throw std::runtime_error("idx out of bounds");

			auto ptr = libvlc_media_list_item_at_index(m_instance, idx);
			if (ptr == nullptr)
				throw std::runtime_error("media element at index is null");

			return{ ptr };
		}

		event_manager& events()
		{
			return m_events;
		}

	private:
		event_manager m_events;
	};
}
