#pragma once

#include "CommonInclude.h"
#include "fmod.hpp"
#include "fmod_errors.h"

namespace LJG
{
	class UAudio : public ICoreAPI, public IManagedAPI
	{
	private:
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

	protected:
		virtual void Load();

	protected:
		friend class SoundManager;
		WText mKey;

#pragma region Fmod Interface
		FMOD::System*  mFmodSystem;
		FMOD::Sound*   mFmodSound;
		FMOD::Channel* mFmodChannel;
#pragma endregion
	};
}
