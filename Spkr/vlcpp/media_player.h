#pragma once

#include "vlc/vlc.h"

#include "cwrapper.h"
#include "media.h"
#include "event_manager.h"

namespace vlc
{
	class media_player : public owner_cwrapper<libvlc_media_player_t>
	{
	public:
		media_player(libvlc_instance_t* vlc)
			: owner_cwrapper(libvlc_media_player_new(vlc))
			, m_events(libvlc_media_player_event_manager(m_instance))
		{}

		void set_media(media& media)
		{
			libvlc_media_player_set_media(m_instance, media.instance());
		}

		void toggle_mute()
		{
			bool muted = libvlc_audio_get_mute(m_instance) != 0 ? true : false;
			libvlc_audio_set_mute(m_instance, !muted ? 1 : 0);
		}

		libvlc_state_t get_state() const
		{
			return libvlc_media_player_get_state(m_instance);
		}

		void pause()
		{
			libvlc_media_player_pause(m_instance);
		}

		void play()
		{
			libvlc_media_player_play(m_instance);
		}

		void stop()
		{
			libvlc_media_player_stop(m_instance);
		}

		event_manager& events()
		{
			return m_events;
		}

		~media_player()
		{
			libvlc_media_player_release(m_instance);
		}

	private:
		event_manager m_events;
	};
}
