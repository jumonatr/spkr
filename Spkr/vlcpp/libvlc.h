#pragma once

#include "vlc/vlc.h"

#include "cwrapper.h"
#include "media_player.h"

#include <vector>
#include <string>

namespace vlc
{
	class libvlc : public owner_cwrapper<libvlc_instance_t>
	{
	public:
		libvlc(const std::vector<const char*>& vlc_args)
			: owner_cwrapper(libvlc_new(vlc_args.size(), vlc_args.data()))
			, m_player{ m_instance }
		{}

		media_player& player()
		{
			return m_player;
		}

		~libvlc()
		{
			libvlc_release(m_instance);
		}

	private:
		media_player m_player;
	};
}
