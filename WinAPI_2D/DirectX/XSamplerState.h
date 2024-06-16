#pragma once
#include "CommonInclude.h"

namespace LJG
{
	enum class ESamplerType
	{
		PointWrap,
		LinearWrap,
		PointBorder,
		LinearBorder
	};

	class XSamplerState : public ICoreAPI
	{
	public:
		XSamplerState(const UINT          InSlot  = 0, const ESamplerType InSamplerType = ESamplerType::LinearWrap,
					  const FLinearColor& InColor = FLinearColor());
		~XSamplerState() override;

#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	private:
		UINT                       mSlot;
		ESamplerType               mSamplerType;
		FLinearColor               mColor;
		ComPtr<ID3D11SamplerState> mSampler;
	};
}
