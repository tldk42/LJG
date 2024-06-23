#include "TGUI_MapEditor.h"

#include "DirectX/XTexture.h"

namespace LJG
{

	TGUI_MapEditor::TGUI_MapEditor(const WText& InKey)
		: TGUI_Base(InKey) {}

	void TGUI_MapEditor::CheckResize()
	{}

	void TGUI_MapEditor::SavePointsToFile(const std::string& filename, const ImVector<ImVec2>& points)
	{
		std::ofstream file(filename);
		if (!file.is_open())
		{
			std::cerr << "Error: Could not open file for writing!" << std::endl;
			return;
		}

		for (int i = 0; i < points.Size; ++i)
		{
			file << points[i].x << " " << points[i].y << std::endl;
		}

		file.close();
	}

	void TGUI_MapEditor::RenderCustomGUI()
	{
		ImGui::GetIO().NavActive        = false;
		ImGui::GetIO().WantCaptureMouse = true;

		ImGui::Begin(u8"맵 에디터", &bExit, ImGuiWindowFlags_MenuBar);

		static ImVector<ImVec2>                          points;
		static std::vector<std::pair<ImVec2, XTexture*>> images;
		static ImVec2                                    scrolling(0.0f, 0.0f);
		static bool                                      opt_enable_grid         = true;
		static bool                                      opt_enable_context_menu = true;
		static bool                                      adding_line             = false;
		static float                                     gridSize                = 64;
		ImGui::Checkbox("Enable grid", &opt_enable_grid);
		ImGui::SameLine();
		ImGui::InputFloat("grid Scale", &gridSize);

		if (ImGui::Button(u8"저장"))
		{
			SavePointsToFile("points.txt", points);
		}


		// Using InvisibleButton() as a convenience 1) it will advance the layout cursor and 2) allows us to use IsItemHovered()/IsItemActive()
		ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
		ImVec2 canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
		if (canvas_sz.x < 50.0f)
			canvas_sz.x = 50.0f;
		if (canvas_sz.y < 50.0f)
			canvas_sz.y = 50.0f;
		ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);

		// Draw border and background color
		ImGuiIO&    io        = ImGui::GetIO();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(50, 50, 50, 255));
		draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));

		for (auto& image : images)
		{
			ImGui::InvisibleButton("image", {
									   static_cast<float>(image.second->GetTextureDesc().Width),
									   static_cast<float>(image.second->GetTextureDesc().Height)
								   });


			if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
			{
				ImGui::GetIO().WantCaptureMouse = true;

				// 이동 처리

				image.first.x += io.MouseDelta.x;
				image.first.y += io.MouseDelta.y;


				// 이미지 테두리 그리기 (선택된 이미지 강조 표시)
				draw_list->AddRect(image.first, ImVec2(image.first.x + image.second->GetTextureDesc().Width,
													   image.first.y + image.second->GetTextureDesc().Height),
								   IM_COL32(255, 255, 0, 255));
			}
		}


		// This will catch our interactions
		ImGui::InvisibleButton("canvas", canvas_sz,
							   ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
		const bool   is_hovered    = ImGui::IsItemHovered(); // Hovered
		const bool   is_active     = ImGui::IsItemActive();   // Held
		const ImVec2 canvas_center = ImVec2(canvas_p0.x + canvas_sz.x * 0.5f, canvas_p0.y + canvas_sz.y * 0.5f);
		const ImVec2 origin(canvas_p0.x + scrolling.x, canvas_p0.y + scrolling.y); // Lock scrolled origin
		const ImVec2 mouse_pos_in_canvas(io.MousePos.x - origin.x, io.MousePos.y - origin.y);


		// Pan (we use a zero mouse threshold when there's no context menu)
		// You may decide to make that threshold dynamic based on whether the mouse is hovering something etc.
		const float mouse_threshold_for_pan = opt_enable_context_menu ? -1.0f : 0.0f;
		if (is_active && ImGui::IsMouseDragging(ImGuiMouseButton_Right, mouse_threshold_for_pan))
		{
			scrolling.x += io.MouseDelta.x;
			scrolling.y += io.MouseDelta.y;
		}

		// Context menu (under default mouse threshold)
		ImVec2 drag_delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);
		if (opt_enable_context_menu && drag_delta.x == 0.0f && drag_delta.y == 0.0f)
			ImGui::OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);
		if (ImGui::BeginPopup("context"))


		{
			if (adding_line)
				points.resize(points.size() - 2);
			adding_line = false;
			if (ImGui::MenuItem("Remove one", NULL, false, points.Size > 0)) { points.resize(points.size() - 2); }
			if (ImGui::MenuItem("Remove all", NULL, false, points.Size > 0)) { points.clear(); }
			ImGui::EndPopup();
		}

		// Draw grid + all lines in the canvas
		draw_list->PushClipRect(canvas_p0, canvas_p1, true);
		if (opt_enable_grid)
		{
			for (float x = fmodf(scrolling.x, gridSize); x < canvas_sz.x; x += gridSize)
				draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y),
								   IM_COL32(200, 200, 200, 40));
			for (float y = fmodf(scrolling.y, gridSize); y < canvas_sz.y; y += gridSize)
				draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y),
								   IM_COL32(200, 200, 200, 40));
		}

		// Draw origin (0,0) marker
		draw_list->AddCircleFilled(origin, 5.0f, IM_COL32(230, 126, 34, 255));

		for (int n = 0; n < points.Size; n += 2)
		{
			draw_list->AddLine(ImVec2(origin.x + points[n].x, origin.y + points[n].y),
							   ImVec2(origin.x + points[n + 1].x, origin.y + points[n + 1].y),
							   IM_COL32(255, 255, 0, 255), 2.0f);
		}


		draw_list->PopClipRect();

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MAP_Editor_DD"))
			{
				XTexture* dropped_tex = *(XTexture**)payload->Data;
				images.emplace_back(mouse_pos_in_canvas, dropped_tex);
			}
		}

		for (auto& image : images)
		{


			const ImVec2 topLeft = {origin.x + image.first.x, origin.y + image.first.y};
			draw_list->AddImage((ImTextureID)image.second->GetShaderResourceView(),
								topLeft,
								{
									topLeft.x + image.second->GetTextureDesc().Width,
									topLeft.y + image.second->GetTextureDesc().Height
								});
		}

		ImGui::End();

	}
}
