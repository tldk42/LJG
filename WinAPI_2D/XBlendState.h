#pragma once
#include "CommonInclude.h"

namespace LJG
{
	enum class EBlendType
	{
		AlphaBlend, // Default: 반투명, 유리, 물, 그림자
		Additive, // Source + Dest: 이펙트
	};

	/**
	 * \brief 렌더 타겟의 픽셀 색상 값을 어떤 식으로 블렌딩할지 정의(텍스처 혼합 방식)
	 */
	class XBlendState : public ICoreAPI
	{
	public:
		XBlendState(const EBlendType Type = EBlendType::AlphaBlend);
		~XBlendState() override;

#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	private:
		EBlendType               mBlendType;
		ComPtr<ID3D11BlendState> mBlendState;
	};
}
