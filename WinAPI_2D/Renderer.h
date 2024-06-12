#pragma once
#include "CommonInclude.h"

namespace LJG
{
	CLASS_PTR(Renderer)

	class Renderer : ICoreAPI
	{
	private:
		Renderer(const FWindowData& InWinData, HWND InWindowHandle);

	public:
		~Renderer() override;

	public:
		static void             Create(const FWindowData& WinData, void* DeviceContext);
		inline static Renderer* Get() { return s_Renderer.get(); }

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		static void Clear();

	private:
		static RendererUPtr s_Renderer;

		FWindowData mWindowData;
		HWND        mWindowHandle;
	};
}
