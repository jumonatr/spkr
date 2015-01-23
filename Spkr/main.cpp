#include "vlc/vlc.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <thread>
#include <memory>
#include <type_traits>

#include "platform.h"

#include "vlcpp/media_discoverer.h"
#include "vlcpp/libvlc.h"

using namespace std;
using namespace vlc;

const vector<const char*> vlc_args = { "--network-caching=1000 --sap-timeout=10 --sap-strict --aout alsa" };

char const* const RTP_GUID = "BCA12FD8-85C0-4D37-9959-047FE0D708C6";

class sap_listener
{
public:
	sap_listener()
		: m_vlc(vlc_args)
	{
		register_discoverer();
	}

private:
	void register_discoverer()
	{
		m_events.clear();

		m_discoverer = make_shared<media_discoverer>(m_vlc.instance(), "SAP");

		attach(m_discoverer->events(),
			libvlc_event_e::libvlc_MediaDiscovererEnded,
			&sap_listener::discovery_ended);

		attach(m_discoverer->list().events(),
			libvlc_event_e::libvlc_MediaListItemAdded,
			&sap_listener::item_added);

		attach(m_discoverer->list().events(),
			libvlc_event_e::libvlc_MediaListItemDeleted,
			&sap_listener::item_removed);
	}

	void discovery_ended(const libvlc_event_t* evt)
	{
		cout << "discovery stopped" << endl;

		register_discoverer();
	}

	void item_added(const libvlc_event_t* evt)
	{
		cout << "item added at idx: " << evt->u.media_list_item_added.index << endl;
		
		media media{ evt->u.media_list_item_added.item };
		cout << "item has name: " << media.name() << endl;

		if (media.name() == RTP_GUID)
		{
			m_vlc.player().set_media(media);
			m_vlc.player().play();
			m_playing = media;
		}
	}

	void item_removed(const libvlc_event_t* evt)
	{
		cout << "item removed at idx: " << evt->u.media_list_item_deleted.index << endl;

		media media{ evt->u.media_list_item_deleted.item };
		cout << "item has name: " << media.name() << endl;

		if (m_playing == media)
		{
			m_vlc.player().stop();
			m_playing = {};
		}
	}

	void attach(event_manager& manager, libvlc_event_e evtt, void (sap_listener::*fun)(const libvlc_event_t*))
	{
		m_events.push_back(manager.attach(evtt, bind(mem_fn(fun), this, placeholders::_1)));
	}

	media m_playing;
	shared_ptr<media_discoverer> m_discoverer;

	vector<event::handle> m_events;
	libvlc m_vlc;
};

int main(int argc, char** argv)
{
	sap_listener listener;

	plat::pause();

	return 0;
}
