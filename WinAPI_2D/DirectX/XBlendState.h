#pragma once
#include "CommonInclude.h"

namespace LJG
{
	enum class EBlendType
	{
		AlphaBlend, // Default: ����?? ??��, ?? �׸�??
		Additive, // Source + Dest: ??��??
	};

	/**
	 * \brief ??�� ??���� ???? ??�� ���� ??�� ??��??��??���� ??��(??��????�� ���)
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
