#pragma once
#include "Component/Actor/AAnimatedImage.h"


namespace LJG
{
	/* HUD
	 * �÷��̾� MP ī��
	 */
	class MPCardSlot : public AAnimatedImage
	{
	public:
		explicit MPCardSlot();
		~MPCardSlot() override;

	public:
	#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
	#pragma endregion

		void SetValue(const float_t InValue);

	private:
		static int32_t mCounter;
		float_t        mValue    = 0.f;
		float_t        mMaxValue = 100.f;
	};

}
