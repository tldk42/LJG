#include "GUI_Inspector.h"

#include <imgui.h>

#include "Component/Actor/AActor.h"
#include "InputManager.h"
#include "Component/Manager/SoundManager.h"
#include "DirectX/Context.h"
#include "Helper/EngineHelper.h"
#include "World/World.h"

namespace LJG
{
	GUI_Inspector::GUI_Inspector(const WText& InKey)
		: TGUI_Base(InKey)
	{}

	void GUI_Inspector::CheckResize()
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
		else
		{
			Context::Get()->SetViewport(GetWindowWidth(), Context::GetViewportSize().Y);
		}
	}

	void GUI_Inspector::RenderCustomGUI()
	{
		ImGui::GetIO().NavActive        = false;
		ImGui::GetIO().WantCaptureMouse = true;

		ImGui::Begin("Inspector", &bExit, ImGuiWindowFlags_MenuBar);

		CheckResize();

		// if (ImGui::BeginMenuBar())
		// {
		// 	if (ImGui::BeginMenu("File"))
		// 	{
		// 		if (ImGui::MenuItem("Save"))
		// 		{}
		// 		ImGui::Separator();
		// 		if (ImGui::MenuItem("Open"))
		// 		{}
		// 		ImGui::EndMenu();
		// 	}
		// 	ImGui::EndMenuBar();
		// }

		static bool bEnableDebug = false;
		ImGui::Checkbox("Input debug?", &bEnableDebug);
		InputManager::EnableDebug(bEnableDebug);

		ImGui::SameLine();

		static bool bMusic = true;
		if (ImGui::Checkbox("BGM?", &bMusic))
		{
			Manager_Audio.PauseAll();
		}

		if (mObjectToShow)
		{
			ImGui::NewLine();

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

		ImGui::NewLine();

		static int  item_current_idx = 0; // Here we store our selection data as an index.
		static bool bInitialized     = false;
		if (ImGui::BeginListBox(u8"¾À ¸ñ·Ï"))
		{
			for (int n = 0; n < IM_ARRAYSIZE(SceneList); n++)
			{
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(SceneList[n], is_selected))
				{
					item_current_idx = n;
				}

				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();

					if (!bInitialized)
					{
						GWorld.MoveScene(SceneList[item_current_idx]);
						bInitialized = true;
					}

				}
			}
			ImGui::EndListBox();
		}

		ImGui::End();


	}

}
