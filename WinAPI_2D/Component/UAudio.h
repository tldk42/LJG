#pragma once

#include "CommonInclude.h"
#include "fmod.hpp"
#include "fmod_errors.h"

namespace LJG
{
	class UAudio : public ICoreAPI, public IManagedAPI
	{
	public:
		UAudio(const WText& InKey);
		~UAudio() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

#pragma region Manager Interface
		void SetID(WTextView InKey) override { mKey = InKey; }
#pragma endregion

		void Play(const bool bLoop = false);
		void Pause();
		void Stop();

	protected:
		friend class SoundManager;
		WText mKey;

		float mVolume;
		bool  bIsPlaying;
		bool  bPaused;

#pragma region Fmod Interface
		FMOD::Sound*   mFmodSound;
		FMOD::Channel* mFmodChannel;
#pragma endregion
	};
}
