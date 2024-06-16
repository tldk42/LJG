#pragma once
#include "TGUI_Base.h"

namespace LJG
{
	class TGUI_Inspector : public TGUI_Base
	{
	public:
		TGUI_Inspector(HWND InHwnd);

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion


	private:
		void ShowInspector();

	private:
		bool     bExit;
	};
}
