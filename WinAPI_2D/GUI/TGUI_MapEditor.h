#pragma once
#include "TGUI_Base.h"

namespace LJG
{
	class TGUI_MapEditor : public TGUI_Base
	{
	public:
		explicit TGUI_MapEditor(const WText& InKey);

	public:
		void         CheckResize() override;
		void         SavePointsToFile(const std::string& filename, const ImVector<ImVec2>& points);
		virtual void RenderCustomGUI() override;
	};
}
