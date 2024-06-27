#pragma once
#include "TGUI_Base.h"

namespace LJG
{
	class GUI_Inspector : public TGUI_Base
	{
	public:
		explicit GUI_Inspector(const WText& InKey);

	public:
		void BindSceneComponent(USceneComponent* InBindObject) { mObjectToShow = InBindObject; }

		void         CheckResize() override;
		virtual void RenderCustomGUI() override;

	protected:
		USceneComponent* mObjectToShow;

	};
}
