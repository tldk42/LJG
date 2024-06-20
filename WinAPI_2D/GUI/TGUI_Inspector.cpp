#include "TGUI_Inspector.h"

#include <imgui.h>

#include "AActor.h"
#include "InputManager.h"
#include "DirectX/Context.h"
#include "Helper/EngineHelper.h"

LJG::TGUI_Inspector::TGUI_Inspector()
{}

void LJG::TGUI_Inspector::CheckResize()
{
	if (ImGui::IsWindowDocked())
	{
		const ImVec2 currentSize = ImGui::GetContentRegionAvail();
		if (mCachedSize.x != currentSize.x || mCachedSize.y != currentSize.y)
		{
			Context::Get()->SetViewport(GetWindowWidth() - currentSize.x, Context::GetViewportSize().Y);

			mCachedSize = currentSize;
		}
	}
}

void LJG::TGUI_Inspector::RenderCustomGUI()
{
	ImGui::GetIO().NavActive        = false;
	ImGui::GetIO().WantCaptureMouse = true;

	ImGui::Begin("Inspector", &bExit, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{}
			ImGui::Separator();
			if (ImGui::MenuItem("Open"))
			{}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	static bool bEnableDebug = true;
	ImGui::Checkbox("Input debug?", &bEnableDebug);
	InputManager::EnableDebug(bEnableDebug);

	ImGui::NewLine();

	if (mObjectToShow)
	{
		static float loc[2] = {0.f, 0.f};
		{
			loc[0] = mObjectToShow->GetWorldLocation().X;
			loc[1] = mObjectToShow->GetWorldLocation().Y;
		}
		static float rot = mObjectToShow->GetWorldRotation();
		static float scale[2];
		{
			scale[0] = mObjectToShow->GetScale().X;
			scale[1] = mObjectToShow->GetScale().Y;
		}

		ImGui::InputFloat2("Location", loc);
		ImGui::InputFloat("Rotation", &rot);
		ImGui::InputFloat2("Scale", scale);

		static bool bEdit = false;
		ImGui::Checkbox("Edit Actor?", &bEdit);
		if (bEdit)
		{
			mObjectToShow->SetTransform({loc[0], loc[1]}, rot, {scale[0], scale[1]});
		}
	}
	CheckResize();

	ImGui::End();


}
