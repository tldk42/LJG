#include "InGame_HUD.h"

#include "Camera.h"
#include "MPCardSlot.h"
#include "Component/UImage.h"
#include "Component/Manager/TextureManager.h"

namespace LJG
{
	InGame_HUD::InGame_HUD()
		: AHUD(L"HUD_InGame")
	{
		mHP = CreateDefaultSubObject<UImage>(L"HUD_HP", L"rsc/Sprite/hud_hp_1.png", 0.01f);
		mHP->SetWorldLocation({-580.f, -420.f});

		int32_t index = 0;
		for (auto& mMPCard : mMPCards)
		{
			mMPCard = CreateDefaultSubObject<MPCardSlot>();
			mMPCard->SetActive(false);
		}
	}

	void InGame_HUD::Initialize()
	{
		AHUD::Initialize();
	}

	void InGame_HUD::Update(float DeltaTime)
	{
		AHUD::Update(DeltaTime);

		mHP->SetWorldLocation(MainCam.GetWorldLocation() + mHPOffset);
		int32_t index = 0;
		for (auto& mMPCard : mMPCards)
		{
			mMPCard->SetWorldLocation(MainCam.GetWorldLocation() + FVector2f{-500.f + 30 * index++, mHPOffset.Y});
		}
	}

	void InGame_HUD::Render()
	{
		AHUD::Render();
	}

	void InGame_HUD::Release()
	{
		AHUD::Release();
	}

	void InGame_HUD::OnHPChanged(const int32_t InHP) const
	{
		mHP->SetTexture(Manager_Texture.CreateOrLoad(std::format(L"rsc/Sprite/hud_hp_{}.png", InHP)));
	}

	void InGame_HUD::OnMPChanged(const int32_t InMP)
	{
		int32_t cardNum  = InMP / 100;
		int32_t remained = InMP % 100;

		if (mCurrentMPCardNum != cardNum)
		{
			for (auto& mMPCard : mMPCards)
			{
				mMPCard->SetActive(false);
			}

			for (int32_t i = 0; i < cardNum; ++i)
			{
				mMPCards[i]->SetActive(true);
				mMPCards[i]->Play(false, true);
			}

			mCurrentMPCardNum = cardNum;
		}
		else
		{
			if (remained > 0)
			{
				mMPCards[cardNum]->SetValue(remained);
			}
		}
	}

}
