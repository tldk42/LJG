#pragma once
#include "CommonInclude.h"

namespace LJG
{
	enum class EBlendType
	{
		AlphaBlend, // Default: 반투?? ??리, ?? 그림??
		Additive, // Source + Dest: ??펙??
	};

	/**
	 * \brief ??더 ??겟의 ???? ??상 값을 ??떤 ??으??블렌??할지 ??의(??스????합 방식)
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
