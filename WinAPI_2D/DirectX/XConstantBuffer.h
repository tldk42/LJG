#pragma once
#include "CommonInclude.h"

namespace LJG
{

	class XConstantBuffer : public ICoreAPI
	{
	public:
		XConstantBuffer() ;
		~XConstantBuffer() override = default;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	protected:
		virtual HRESULT CreateConstantBuffer();

	protected:
		ComPtr<ID3D11Buffer> mConstantBuffer;
	};
}
