#pragma once
#include "TGUI_Base.h"

namespace LJG
{
	struct FMapData;

	class GUI_Inspector_MapEdit : public TGUI_Base
	{
	public:
		explicit GUI_Inspector_MapEdit(const WText& InKey);

	public:
		void BindImage(FMapData* InImg);

	private:
		void         CheckResize() override;
		void         SetNewData();
		virtual void RenderCustomGUI() override;

	private:
		FMapData* mImgData;

		char    name[32];
		float_t pos[2];
		float_t scale[2];
		float_t rot;
		float_t zOrder;
	};
}
