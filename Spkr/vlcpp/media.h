#pragma once

#include "vlc\vlc.h"

#include "cwrapper.h"
#include <string>

namespace vlc
{
	class media : public cwrapper<libvlc_media_t>
	{
	public:
		media() = default;

		media(libvlc_media_t* media)
			: cwrapper(media)
		{
			libvlc_media_parse(media);
		}

		//avoid calling parse again on the same media element
		media(const media& other)
			: cwrapper(other.m_instance)
		{}

		media& operator=(const media& other)
		{
			m_instance = other.m_instance;
			return *this;
		}

		std::string name() const
		{
			return libvlc_media_get_meta(m_instance, libvlc_meta_t::libvlc_meta_Title);
		}
	};
}