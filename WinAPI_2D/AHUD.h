#pragma once
#include "Component/Actor/AActor.h"

namespace LJG
{
	/* TODO: 테스트용도로 작성 Base클래스로 다시 작성해야함*/
	class AHUD : public AActor, TSingleton<AHUD>
	{
	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	private:
		UTextBlock* mFpsText;

	private:
		friend class TSingleton<AHUD>;

		AHUD();
		~AHUD() override = default;

	public:
		AHUD(const AHUD&)            = delete;
		AHUD& operator=(const AHUD&) = delete;
	};

}
