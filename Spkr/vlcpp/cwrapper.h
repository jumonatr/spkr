#pragma once


namespace vlc
{
	template<typename T>
	class cwrapper
	{
	public:
		cwrapper()
			: m_instance{ nullptr }
		{}

		cwrapper(T* instance)
			: m_instance{ instance }
		{}

		T* instance() const
		{
			return m_instance;
		}

		bool operator ==(const cwrapper& other)
		{
			return m_instance == other.m_instance;
		}

	protected:
		T* m_instance;
	};

	template<typename T>
	class owner_cwrapper : public cwrapper<T>
	{
	public:
		owner_cwrapper() = default;
		owner_cwrapper(T* val)
			: cwrapper(val)
		{}

		owner_cwrapper(const owner_cwrapper& other) = delete;
		owner_cwrapper& operator=(const owner_cwrapper& other) = delete;
	};
}