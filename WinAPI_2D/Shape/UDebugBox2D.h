#pragma once
#include "UDebugShape2D.h"

namespace LJG
{
	class UDebugBox2D : public UDebugShape2D
	{
	public:
		UDebugBox2D();
		~UDebugBox2D() override = default;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	protected:
		void CreateVertexArray() override;
		void CreateIndexArray() override;
	};
}
