#pragma once
#include "TGUI_Base.h"

namespace LJG
{
	class TGUI_Inspector : public TGUI_Base
	{
	public:
		explicit TGUI_Inspector(const WText& InKey);

	public:
		void         CheckResize() override;
		virtual void RenderCustomGUI() override;
	};
}
