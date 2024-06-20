#pragma once
#include "TGUI_Base.h"

namespace LJG
{
	class TGUI_Inspector : public TGUI_Base
	{
	public:
		TGUI_Inspector();

	public:
		void CheckResize() override;
		virtual void RenderCustomGUI() override;
	};
}
