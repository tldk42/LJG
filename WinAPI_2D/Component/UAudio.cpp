#include "UAudio.h"

#include "Helper/EngineHelper.h"
#include "Manager/SoundManager.h"

namespace LJG
{
	UAudio::UAudio(const WText& InKey)
		: mKey(InKey),
		  mVolume(0.5f)
	{
		UAudio::Initialize();
	}

	UAudio::~UAudio()
	{}

	void UAudio::Initialize()
	{
		assert(
			Manager_Audio.mFmodSystem->createSound(WText2Text(mKey).c_str(), FMOD_DEFAULT, nullptr, &mFmodSound) ==
			FMOD_OK,
			"Sound creation failed");
	}

	void UAudio::Update(float DeltaTime)
	{
#ifdef _DEBUG
		if (mFmodChannel)
		{
			// uint32_t seconds;
			// mFmodChannel->getPosition(&seconds, FMOD_TIMEUNIT_MS);
		}
#endif
	}

	void UAudio::Render()
	{}

	void UAudio::Release()
	{
		if (mFmodSound)
		{
			Stop();
			mFmodSound->release();
		}
	}

	void UAudio::Play(const bool bLoop)
	{
		Manager_Audio.mFmodSystem->playSound(mFmodSound, nullptr, false, &mFmodChannel);

		mFmodChannel->setMode(bLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
	}

	void UAudio::Pause()
	{
		if (mFmodChannel)
		{
			mFmodChannel->isPlaying(&bIsPlaying);
			mFmodChannel->getPaused(&bPaused);
			if (bIsPlaying)
			{
				mFmodChannel->setPaused(!bPaused);
			}
		}
	}

	void UAudio::Stop()
	{
		if (mFmodChannel)
		{
			mFmodChannel->stop();
		}
	}
}
