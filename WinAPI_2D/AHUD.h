#pragma once
#include "Component/Actor/AActor.h"

namespace LJG
{
	/* TODO: �׽�Ʈ�뵵�� �ۼ� BaseŬ������ �ٽ� �ۼ��ؾ���*/
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
