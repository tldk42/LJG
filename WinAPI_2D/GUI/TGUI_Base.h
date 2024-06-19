#pragma once
#include "../CommonInclude.h"

namespace LJG
{
	class USceneComponent;

	class TGUI_Base : public IManagedAPI
	{
	public:
		TGUI_Base();

	public:
		void SetID(WTextView InKey) override;

		virtual void RenderCustomGUI() = 0;

		void BindSceneComponent(USceneComponent* InBindObject) { mObjectToShow = InBindObject; }

	protected:
		WText            mKey;
		USceneComponent* mObjectToShow;
	};
}
