#pragma once
#include <imgui.h>

#include "../CommonInclude.h"

namespace LJG
{
	class USceneComponent;

	class TGUI_Base
	{
	public:
		explicit TGUI_Base(const WText& InKey);

	public:
		virtual void CheckResize() = 0;
		virtual void RenderCustomGUI() = 0;

		void BindSceneComponent(USceneComponent* InBindObject) { mObjectToShow = InBindObject; }

	protected:
		WText            mKey;
		USceneComponent* mObjectToShow;
		bool             bExit;
		ImVec2           mCachedSize;
	};
}
