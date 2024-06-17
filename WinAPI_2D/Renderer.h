#pragma once
#include "CommonInclude.h"

namespace LJG
{
	class Renderer
	{
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

	private:
		Renderer()  = default;
		~Renderer() = default;

	public:
		Renderer(const Renderer& Other)           = delete;
		Renderer operator=(const Renderer& Other) = delete;
	};
}
