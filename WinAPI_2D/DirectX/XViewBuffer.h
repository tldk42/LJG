#pragma once
#include "XConstantBuffer.h"

namespace LJG
{

	class XViewBuffer : public XConstantBuffer
	{
	public:
		XViewBuffer();
		~XViewBuffer() override = default;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
		inline void SetViewMatrix(const Matrix& InMatrix) { mViewMatrix = XMMatrixTranspose(InMatrix); }

	private:
		HRESULT CreateConstantBuffer() override;

	private:
		Matrix mViewMatrix = XMMatrixIdentity();
	};
}
