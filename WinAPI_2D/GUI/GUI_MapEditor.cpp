#include "GUI_MapEditor.h"

#include <imgui.h>
#include <imgui_internal.h>
#include "GUI_Inspector_MapEdit.h"
#include "Component/Manager/GUIManager.h"
#include "Component/Manager/SceneManager.h"
#include "Component/Manager/TextureManager.h"
#include "DirectX/XTexture.h"
#include "Helper/EngineHelper.h"

namespace LJG
{

	void ImageRotated(ImTextureID tex_id, ImVec2 center, ImVec2 size, float angle)
	{

		angle *= (M_PI / 180);
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		float       cos_a     = cosf(angle);
		float       sin_a     = sinf(angle);
		ImVec2      pos[4]    =
		{
			center + ImRotate(ImVec2(-size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
			center + ImRotate(ImVec2(+size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
			center + ImRotate(ImVec2(+size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a),
			center + ImRotate(ImVec2(-size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a)
		};
		ImVec2 uvs[4] =
		{
			ImVec2(0.0f, 0.0f),
			ImVec2(1.0f, 0.0f),
			ImVec2(1.0f, 1.0f),
			ImVec2(0.0f, 1.0f)
		};

		draw_list->AddImageQuad(tex_id, pos[0], pos[1], pos[2], pos[3], uvs[0], uvs[1], uvs[2], uvs[3], IM_COL32_WHITE);
	}


	GUI_MapEditor::GUI_MapEditor(const WText& InKey)
		: TGUI_Base(InKey) {}

	void GUI_MapEditor::CheckResize()
	{}

	void GUI_MapEditor::SavePointsToFile(const Text& filename)
	{
		SaveJsonFile();
	}

	void GUI_MapEditor::RenderCustomGUI()
	{
		ImGui::GetIO().NavActive        = false;
		ImGui::GetIO().WantCaptureMouse = true;

		ImGui::Begin(u8"맵 에디터", &bExit, ImGuiWindowFlags_MenuBar);

		ShowOptions();

		ShowGridPanel();

		HandleImage();

		ImGui::End();
	}

	void GUI_MapEditor::ShowOptions()
	{
		ImGui::Checkbox("Enable grid", &bEnableGrid);
		ImGui::SameLine();
		ImGui::SetNextItemWidth(80);
		ImGui::InputFloat("grid Scale", &mGridSize);
		ImGui::SameLine();

		if (ImGui::Button(u8"저장"))
		{
			SavePointsToFile(mCurrentSceneName + ".json");
		}

		ImGui::SameLine();
		static int item_current_idx = 0;
		ImGui::SetNextItemWidth(150);
		static std::vector<bool> bSceneInitialized(IM_ARRAYSIZE(SceneList), false);
		if (ImGui::BeginCombo("Scene", item_current_idx == -1 ? "Select" : SceneList[item_current_idx]))
		{
			for (int i = 0; i < IM_ARRAYSIZE(SceneList); ++i)
			{
				const bool is_selected = item_current_idx == i;
				if (ImGui::Selectable(SceneList[i], is_selected))
				{
					item_current_idx  = i;
					mCurrentSceneName = SceneList[item_current_idx];
				}

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
					if (!bSceneInitialized[i])
					{
						if (LoadScene(mCurrentSceneName))
						{
							bSceneInitialized[i] = true;
						}
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::SameLine();
		if (ImGui::Button(u8"새로고침"))
		{
			mSelectedData = nullptr;
			Manager_GUI.GetResource<GUI_Inspector_MapEdit>(L"MapInspector")->BindImage(mSelectedData);
			std::ranges::sort(mMapDatas, [](const FMapData& a, const FMapData& b){
				return a.ZOrder >= b.ZOrder;
			});
		}
	}

	void GUI_MapEditor::ShowGridPanel()
	{
		// Using InvisibleButton() as a convenience 1) it will advance the layout cursor and 2) allows us to use IsItemHovered()/IsItemActive()
		ImVec2   canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
		ImVec2   canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
		ImGuiIO& io        = ImGui::GetIO();
		mOrigin            = ImVec2(canvas_p0.x + mScrolling.x, canvas_p0.y + mScrolling.y); // Lock scrolled origin
		mMouseCanvasPos    = ImVec2((io.MousePos.x - mOrigin.x) / mZoom, (io.MousePos.y - mOrigin.y) / mZoom);
		mDrawList          = ImGui::GetWindowDrawList();

		if (canvas_sz.x < 50.0f)
			canvas_sz.x = 50.0f;
		if (canvas_sz.y < 50.0f)
			canvas_sz.y = 50.0f;
		ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

		// Draw border and background color
		mDrawList->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
		mDrawList->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));

		ImGui::SetNextItemAllowOverlap(); // InvisibleButton 다음에 오는 Item은 Overlap 가능
		// This will catch our interactions
		ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);

		const bool   is_hovered    = ImGui::IsItemHovered(); // Hovered
		const ImVec2 canvas_center = ImVec2(canvas_p0.x + canvas_sz.x * 0.5f, canvas_p0.y + canvas_sz.y * 0.5f);

		// Pan (we use a zero mouse threshold when there's no context menu)
		// You may decide to make that threshold dynamic based on whether the mouse is hovering something etc.
		const float mouse_threshold_for_pan = bEnableContextMenu ? -1.0f : 0.0f;
		if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Right, mouse_threshold_for_pan))
		{
			mScrolling.x += io.MouseDelta.x;
			mScrolling.y += io.MouseDelta.y;
		}

		// Context menu (under default mouse threshold)
		ImVec2 drag_delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);
		// if (drag_delta.x == 0.0f && drag_delta.y == 0.0f)
		// {}

		// if (ImGui::IsItemHovered())
		// {
		if (io.MouseWheel != 0.0f)
		{
			float zoom_factor = 1.1f;
			if (io.MouseWheel < 0.0f)
				zoom_factor = 1.0f / zoom_factor;

			// Adjust zoom level
			mZoom *= zoom_factor;

			// Adjust scrolling to zoom to the mouse position
			ImVec2 mouse_pos_rel_to_origin = ImVec2(io.MousePos.x - mOrigin.x, io.MousePos.y - mOrigin.y);
			mScrolling.x = (mScrolling.x - mouse_pos_rel_to_origin.x) * zoom_factor + mouse_pos_rel_to_origin.x;
			mScrolling.y = (mScrolling.y - mouse_pos_rel_to_origin.y) * zoom_factor + mouse_pos_rel_to_origin.y;
		}
		// }

		// Draw grid + all lines in the canvas
		mDrawList->PushClipRect(canvas_p0, canvas_p1, true);
		if (bEnableGrid)
		{
			for (float x = fmodf(mScrolling.x, mGridSize * mZoom); x < canvas_sz.x; x += mGridSize * mZoom)
				mDrawList->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y),
								   IM_COL32(200, 200, 200, 40));
			for (float y = fmodf(mScrolling.y, mGridSize * mZoom); y < canvas_sz.y; y += mGridSize * mZoom)
				mDrawList->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y),
								   IM_COL32(200, 200, 200, 40));
		}

		// Draw origin (0,0) marker
		mDrawList->AddCircleFilled(ImVec2(mOrigin.x, mOrigin.y), 5.0f * mZoom, IM_COL32(230, 126, 34, 255));

		mDrawList->PopClipRect();
	}

	void GUI_MapEditor::HandleImage()
	{
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MAP_Editor_DD"))
			{
				static int32_t num     = 0;
				const wchar_t* texPath = static_cast<wchar_t*>(payload->Data);
				FMapData       mapData{};
				{
					mapData.Key      = std::format("Object_{}", num++);
					mapData.TexPath  = texPath;
					mapData.Position = FVector2f(mMouseCanvasPos.x, mMouseCanvasPos.y);
				}
				mMapDatas.emplace_back(mapData);
			}
		}

		for (auto image = mMapDatas.begin(); image != mMapDatas.end();)
		{
			const XTexture* texRef = Manager_Texture.CreateOrLoad(image->TexPath);
			assert(texRef);
			const ImVec2 canvasImagePos = {
				mOrigin.x + image->Position.X * mZoom,
				mOrigin.y + image->Position.Y * mZoom
			};
			const FVector2f clampedScale = {
				texRef->GetTextureDesc().Width * image->Scale.X * mZoom,
				texRef->GetTextureDesc().Height * image->Scale.Y * mZoom
			};

			ImVec2 min = {canvasImagePos.x - clampedScale.X / 2, canvasImagePos.y - clampedScale.Y / 2};
			ImVec2 max = {canvasImagePos.x + clampedScale.X / 2, canvasImagePos.y + clampedScale.Y / 2};

			ImageRotated(texRef->GetShaderResourceView(), canvasImagePos, {clampedScale.X, clampedScale.Y},
						 image->Rotation);

			ImGui::SetNextItemAllowOverlap(); // InvisibleButton 다음에 오는 Item은 Overlap 가능
			ImGui::SetCursorScreenPos(min);
			ImGui::InvisibleButton("ImageEdit", {clampedScale.X, clampedScale.Y});
			// if (ImGui::IsItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
			// {
			// 	image.Position.X += ImGui::GetIO().MouseDelta.x;
			// 	image.Position.X += ImGui::GetIO().MouseDelta.y;
			// }
			if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
			{
				mSelectedData = image._Ptr;
				Manager_GUI.GetResource<GUI_Inspector_MapEdit>(L"MapInspector")->BindImage(mSelectedData);
			}

			if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
			{
				// ImGui::OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);
				ImGui::BeginPopupModal("context");
				if (ImGui::BeginPopup("context"))
				{
					if (ImGui::MenuItem("Remove one", NULL, false))
					{
						image = mMapDatas.erase(image);
						ImGui::EndPopup();
						continue;;
					}
					if (ImGui::MenuItem("Remove all", NULL, false, mMapDatas.size() > 0))
					{
						mMapDatas.clear();
						ImGui::EndPopup();
						break;
					}
					ImGui::EndPopup();
				}
			}


			if (mSelectedData && image->Key == mSelectedData->Key)
			{
				mDrawList->AddRect(min, max,IM_COL32(255, 255, 0, 255));
			}

			++image;
		}
	}


	void GUI_MapEditor::SaveJsonFile()
	{
		std::ofstream file("data/scene/" + mCurrentSceneName + ".json");

		auto jsonObjects = json::array();
		for (const FMapData& mapData : mMapDatas)
		{
			json saveData = mapData;
			jsonObjects.push_back(saveData);
		}
		file << jsonObjects;

		file.close();
	}


	bool GUI_MapEditor::LoadScene(const Text& FileName)
	{
		nlohmann::json jsonData = EngineHelper::LoadFile(L"data/scenes/" + Text2WText(FileName));

		if (jsonData == nullptr)
			return false;

		for (const auto& element : jsonData)
		{
			FMapData savedData;
			savedData = element.get<FMapData>();
			mMapDatas.push_back(savedData);
		}
		return true;
	}

}
