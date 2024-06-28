#include "GUI_Inspector_MapEdit.h"

#include "GUI_MapEditor.h"

namespace LJG
{

	GUI_Inspector_MapEdit::GUI_Inspector_MapEdit(const WText& InKey)
		: TGUI_Base(InKey) {}

	void GUI_Inspector_MapEdit::BindImage(FMapData* InImg)
	{
		mImgData = InImg;
		SetNewData();
	}

	void GUI_Inspector_MapEdit::CheckResize()
	{}

	void GUI_Inspector_MapEdit::SetNewData()
	{
		if (mImgData)
		{
			strncpy_s(name, sizeof(name), mImgData->Key.c_str(), sizeof(name) - 1);

			pos[0]   = mImgData->Position.X;
			pos[1]   = mImgData->Position.Y;
			scale[0] = mImgData->Scale.X;
			scale[1] = mImgData->Scale.Y;
			rot      = mImgData->Rotation;
			zOrder   = mImgData->ZOrder;
		}
	}

	void GUI_Inspector_MapEdit::RenderCustomGUI()
	{
		ImGui::Begin(u8"Map Inspector", &bExit);
		ImGui::NewLine();
		if (mImgData)
		{
			ImGui::InputText("Key", name, sizeof(name), ImGuiInputTextFlags_CharsNoBlank);
			ImGui::DragFloat2("Location", pos);
			ImGui::DragFloat2("Scale", scale);
			ImGui::DragFloat("Rotation", &rot);
			ImGui::DragFloat("Z-Order", &zOrder);

			mImgData->Key      = name;
			mImgData->Position = {pos[0], pos[1]};
			mImgData->Rotation = rot;
			mImgData->Scale    = {scale[0], scale[1]};
			mImgData->ZOrder   = zOrder;

		}
		ImGui::End();

	}
}
