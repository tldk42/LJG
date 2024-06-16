#pragma once
#include "CommonInclude.h"

namespace LJG
{
	class Renderer
	{
	private:
		Renderer();

	public:
		~Renderer();

	public:
		[[nodiscard]] inline static Renderer& Get()
		{
			static Renderer instance;
			return instance;
		}

	public:
		static void Initialize();
		static void Update(float DeltaTime);
		static void Render();
		static void Release();

		static void Clear(const FLinearColor& InClearColor = FLinearColor::Gray);
	};
}
