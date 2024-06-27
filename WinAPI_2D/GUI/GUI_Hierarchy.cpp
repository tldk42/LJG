#include "GUI_Hierarchy.h"

#include "GUI_Inspector_MapEdit.h"
#include "GUI_MapEditor.h"
#include "Component/Manager/GUIManager.h"

namespace LJG
{
	GUI_Hierarchy::GUI_Hierarchy(const WText& InKey)
		: TGUI_Base(InKey)
	{
		g_mapEditor    = Manager_GUI.CreateOrLoad<GUI_MapEditor>(L"MapEditor");
		g_mapInspector = Manager_GUI.CreateOrLoad<GUI_Inspector_MapEdit>(L"MapInspector");
	}

	void GUI_Hierarchy::CheckResize() {}

	void GUI_Hierarchy::RenderCustomGUI()
	{
		ImGui::GetIO().NavActive        = false;
		ImGui::GetIO().WantCaptureMouse = true;

		ImGui::Begin("Hierarchy", &bExit);


		for (int i = 0; i < g_mapEditor->mMapDatas.size(); i++)
		{
			if (i == 0)
				ImGui::SetNextItemOpen(true, ImGuiCond_Once);

			if (ImGui::TreeNode((void*)(intptr_t)i, "%s", g_mapEditor->mMapDatas[i].Key.c_str()))
			{
				g_mapInspector->BindImage(&g_mapEditor->mMapDatas[i]);
				ImGui::TreePop();
				if (ImGui::BeginDragDropTarget())
				{
					if (const auto* payload = ImGui::AcceptDragDropPayload("MAP_Editor_HH"))
					{
						Text* key = static_cast<Text*>(payload->Data);
						if (ImGui::TreeNode(key->c_str()))
							ImGui::TreePop();

					}
				}
			}

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
			{
				ImGui::SetDragDropPayload("MAP_Editor_HH", g_mapEditor->mMapDatas[i].Key.c_str(),
										  sizeof(wchar_t) * (g_mapEditor->mMapDatas[i].Key.size() + 1));
				ImGui::EndDragDropSource();
			}


		}
		// ImGui::TreePop();


		ImGui::End();
	}
}
