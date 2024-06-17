#include "TGUI_Inspector.h"

#include <imgui.h>

#include "AActor.h"

LJG::TGUI_Inspector::TGUI_Inspector(HWND InHwnd)
	: TGUI_Base(InHwnd)
{
}

void LJG::TGUI_Inspector::Initialize()
{
	TGUI_Base::Initialize();
}

void LJG::TGUI_Inspector::Update(float DeltaTime)
{
	TGUI_Base::Update(DeltaTime);

	ShowInspector();
}

void LJG::TGUI_Inspector::Render()
{
	TGUI_Base::Render();
}

void LJG::TGUI_Inspector::Release()
{
	TGUI_Base::Release();
}

void LJG::TGUI_Inspector::ShowInspector()
{
	ImGui::GetIO().NavActive        = false;
	ImGui::GetIO().WantCaptureMouse = true;

	ImGui::Begin("Inspector", &bExit, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Open"))
			{
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (mObjectToShow)
	{
		static float v[2];
		{
			v[0] = mObjectToShow->GetScale().X;
			v[1] = mObjectToShow->GetScale().Y;
		}
		static float s[2] = {0.f, 0.f};
		{
			s[0] = mObjectToShow->GetWorldLocation().X;
			s[1] = mObjectToShow->GetWorldLocation().Y;
		}
		ImGui::InputFloat2("Scale", v);
		ImGui::InputFloat2("Location", s);

		auto worldPos = XMVectorSet(v[0], v[1], 0, 1.f);
		// auto clipPos = XMVector3TransformCoord(worldPos, )

		mObjectToShow->SetWorldLocation({s[0], s[1]});
		mObjectToShow->SetScale({v[0], v[1]});
	}


	ImGui::End();
}
