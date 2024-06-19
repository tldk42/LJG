#pragma once
#include "TGUI_Base.h"

namespace LJG
{
	class TGUI_Inspector : public TGUI_Base
	{
	public:
		TGUI_Inspector();

	public:
		virtual void RenderCustomGUI() override;

	private:
		bool bExit;
	};
}
