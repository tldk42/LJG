#pragma once
#include "CommonInclude.h"

namespace LJG
{
	class Renderer : ICoreAPI
	{
	private:
		Renderer(const FWindowData& InWinData, HWND InWindowHandle);

	public:
		static void      Create(const FWindowData& WinData, void* DeviceContext);
		static Renderer* GetRenderer();

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Release() override;
#pragma endregion

		void Clear();

	private:
		static Renderer* s_Renderer;

		FWindowData mWindowData;
		HWND        mWindowHandle;
	};
}
