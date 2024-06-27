#pragma once
#include "TGUI_Base.h"


namespace LJG
{
	class GUI_MapEditor;
	class GUI_Inspector_MapEdit;

	DECLARE_DYNAMIC_DELEGATE(FOnObjectAttached, Text)

	class GUI_Hierarchy : public TGUI_Base
	{
	public:
		explicit GUI_Hierarchy(const WText& InKey);

	public:
		virtual void CheckResize();
		virtual void RenderCustomGUI();

	public:
		FOnObjectAttached OnObjectAttached;

	private:
		GUI_MapEditor*         g_mapEditor;
		GUI_Inspector_MapEdit* g_mapInspector;
		friend class GUI_MapEditor;
	};
}
