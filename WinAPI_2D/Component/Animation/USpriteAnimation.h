#pragma once
#include "Component/USceneComponent.h"
#include "Component/Manager/TextureManager.h"
#include "DirectX/XSprite2D.h"

namespace LJG
{
	struct FAnimData
	{
		std::vector<XTexture*> Textures;
		float_t                FrameTime;

		FAnimData() = default;
		FAnimData(const WText& InKey) {};
	};

	namespace AnimUtil
	{
		inline FAnimData LoadAnimations(WTextView      InPath, const uint32_t InMaxSprite,
										const uint32_t InCustomFrame,
										const bool     bForceCustomFrame)
		{
			// C++11 이후에 local var를 반환하면 r-value로 간주되어서 이동생성자로 최적화 된다고하는데 과연...(NRVO, release모드에서 최적화)
			FAnimData animData;

			animData.FrameTime = bForceCustomFrame ? 1.f / InCustomFrame : 1.f / 60.f;

			for (uint32_t i = 1; i <= InMaxSprite; ++i)
			{
				std::wstringstream stringstream;

				stringstream << InPath << std::setw(4) << std::setfill(L'0') << i << L".png";

				WText filePath = stringstream.str();

				animData.Textures.emplace_back(Manager_Texture.CreateOrLoad<XTexture>(filePath));
			}

			return animData;
		}
	}


	// 프레임에 해도 되고 시간에 해도 됨
	DECLARE_DYNAMIC_DELEGATE(FOnAnimNotifyBegin)

	DECLARE_DYNAMIC_DELEGATE(FOnAnimFinished)

	class USpriteAnimation : public USceneComponent
	{
	public:
		explicit USpriteAnimation(const WText& InKey);
		~USpriteAnimation() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
		void Play(const bool InLoop);
		void PlayReverse(const bool InLoop);
		void Pause();
		void Stop();

		XTexture* GetCurrentTexture() const { return mAnimationData.Textures[mCurrentFrame]; }

	public:
		void SetAnimData(const FAnimData& InAnimData)
		{
			mAnimationData = InAnimData;
			OnAnimNotifyBegin.resize(InAnimData.Textures.size());
		}

		void SetSpeed(const float_t InSpeed) { mSpeed = InSpeed; }
		void SetLoop(const bool InLoop) { bLoop = InLoop; }
		void SetFlip(const bool bEnable) { bFlipX = bEnable; }

		uint8_t GetNextAnim() const { return mNextAnimState; }

		void AddTransition(const uint8_t InState, const std::function<bool()>& InCond);

	public:
		std::vector<FOnAnimNotifyBegin> OnAnimNotifyBegin;
		FOnAnimFinished                 OnAnimFinished;

	private:
		uint32_t                 mCurrentFrame;
		time_point<steady_clock> mElapsedTime;
		float_t                  mSpeed;
		bool                     bLoop;
		bool                     bReverse;
		bool                     bFlipX;
		bool                     bIsPlaying;
		bool                     bIsPaused;

		FAnimData mAnimationData;
		uint8_t   mNextAnimState;

		std::unordered_map<uint8_t, std::vector<std::function<bool()>>> mTransitions;

	};

}
