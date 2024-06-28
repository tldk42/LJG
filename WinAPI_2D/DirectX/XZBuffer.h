#pragma once
#include "XConstantBuffer.h"

namespace LJG
{
	class XZBuffer : XConstantBuffer
	{
	public:
		XZBuffer(const float_t InZOrder);
		~XZBuffer() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	private:
		float_t mZOrder;
	};
}
