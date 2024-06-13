#pragma once
#include "AActor.h"

namespace LJG
{
	/* TODO: �׽�Ʈ�뵵�� �ۼ� BaseŬ������ �ٽ� �ۼ��ؾ���*/
	class AHUD : public AActor
	{
	public:
		AHUD();
		~AHUD() override = default;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void UpdateFpsText(WTextView InText) const;

	private:
		UTextBlock* mFpsText;
	};

}
