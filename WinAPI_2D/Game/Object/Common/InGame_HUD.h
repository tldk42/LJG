#pragma once
#include "AHUD.h"

namespace LJG
{
	#define GAME_HUD InGame_HUD::Get()

	class UImage;
	class AAnimatedImage;
	class MPCardSlot;


	class InGame_HUD : public AHUD, public TSingleton<InGame_HUD>
	{
	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
		void OnHPChanged(const int32_t InHP) const;
		void OnMPChanged(const int32_t InMP) const;

	private:
		UImage*     mHP;
		MPCardSlot* mMPCards[5];

	private:
		friend class TSingleton<InGame_HUD>;

		InGame_HUD();
		~InGame_HUD() override = default;

	public:
		InGame_HUD(const InGame_HUD&)            = delete;
		InGame_HUD& operator=(const InGame_HUD&) = delete;
	};
}
