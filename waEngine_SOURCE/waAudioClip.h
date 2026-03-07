#pragma once
#include "waFmod.h"
#include "waResource.h"


namespace wa
{
	class AudioClip : public Resource
	{
	public:
		AudioClip();
		~AudioClip();

		HRESULT Load(const std::wstring& path) override;

		void Play();
		void Stop();
		void Set3DAttributes(const Vector2 pos);
		void SetLoop(bool loop) { mbLoop = loop; }

	private:
		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;
		float mMinDistance;
		float mMaxDistance;
		bool mbLoop;
	};

}

