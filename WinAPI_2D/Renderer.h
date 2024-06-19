#pragma once
#include "CommonInclude.h"
#include "Component/Manager/Manager.h"

namespace LJG
{
	class Renderer : public TSingleton<Renderer>
	{

	public:
		static void Initialize();
		static void Update(float DeltaTime);
		static void Render();
		static void Release();

		static void Clear(const FLinearColor& InClearColor = FLinearColor::Gray);

	private:
		friend class TSingleton<Renderer>;
		Renderer()  = default;
		~Renderer() = default;

	public:
		Renderer(const Renderer& Other)           = delete;
		Renderer operator=(const Renderer& Other) = delete;
	};
}
