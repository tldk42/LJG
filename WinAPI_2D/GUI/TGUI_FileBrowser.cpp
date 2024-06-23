#include "TGUI_FileBrowser.h"

#include <filesystem>
#include <imgui.h>
#include <imgui_stdlib.h>
#include "imgui_filebrowser.h"
#include "Component/Manager/TextureManager.h"
#include "DirectX/Context.h"
#include "DirectX/XTexture.h"
#include "Helper/EngineHelper.h"


namespace LJG
{
	namespace fs = std::filesystem;

	TGUI_FileBrowser::TGUI_FileBrowser(const WText& InKey)
		: TGUI_Base(InKey),
		  mPath(L"./") {}

	void TGUI_FileBrowser::CheckResize()
	{
		// ImGui::GetWindowDockID()
		if (ImGui::IsWindowDocked())
		{
			const ImVec2 currentSize = ImGui::GetContentRegionAvail();

			if (mCachedSize.x != currentSize.x || mCachedSize.y != currentSize.y)
			{
				Context::Get()->SetViewport(Context::GetViewportSize().X, GetWindowHeight() - currentSize.y);

				mCachedSize = currentSize;
			}
		}
		else
		{
			Context::Get()->SetViewport(Context::GetViewportSize().X, GetWindowHeight());
		}
	}

	void TGUI_FileBrowser::RenderCustomGUI()
	{
		ImGui::GetIO().NavActive        = false;
		ImGui::GetIO().WantCaptureMouse = true;

		ImGui::Begin(u8"파일 탐색기", &bExit, ImGuiWindowFlags_MenuBar);

		// CheckResize();

		if (TryOpen(mPath))
		{
			WText result;

			ShowDirectories(mPath, result);
		}

		// if (ImGui::FetchFileBrowserResult("rsc/", result))
		// {}

		ImGui::End();
	}

	bool TGUI_FileBrowser::TryOpen(const WText& InPath, EFileBrowserOption InOption, const std::set<WText>& InExtent)
	{
		auto directory = InPath;

		// 파일 디렉토리 경로가 아닐 경우 부모 디렉토리가 있는지 확인
		if (!fs::is_directory(directory))
		{
			const auto dirPath = fs::path(directory);
			if (dirPath.has_parent_path())
			{
				directory = dirPath.parent_path().wstring();
			}
		}

		mOriginalPath      = InPath;
		mFileBrowserOption = InOption;
		mExtent            = InExtent;

		if (!TryApplyPath(directory))
			return false;

		return true;
	}

	bool TGUI_FileBrowser::ShowDirectories(const WText& InPath, WText& OutSelectedPath)
	{

		EditContent();

		return true;
	}

	bool TGUI_FileBrowser::TryApplyPath(const WText& InText)
	{
		const fs::path path(InText);
		if (!fs::exists(path))
		{
			return false;
		}

		mPath       = path.wstring();
		mEditedPath = L"";

		Refresh();

		return true;
	}

	bool TGUI_FileBrowser::TryPopPath()
	{
		fs::path path(mPath);

		while (!fs::exists(path) && path.has_parent_path())
		{
			path = path.parent_path();
		}

		return TryApplyPath(path.parent_path().wstring());
	}

	void TGUI_FileBrowser::Refresh()
	{
		const fs::path path(mPath);

		if (!fs::exists(path))
		{
			TryPopPath();
			return;
		}

		mDirectories.clear();
		mFiles.clear();
		for (auto& entry : std::filesystem::directory_iterator(path))
		{
			if (entry.is_directory())
			{
				mDirectories.emplace_back(entry.path().filename().wstring());
			}
			else if (mFileBrowserOption != EFileBrowserOption::Directory || mDirectories.empty())
			{
				if (!mExtent.empty())
				{
					if (!entry.path().has_extension())
					{
						continue;
					}
					const std::wstring extent = entry.path().extension().wstring();
					if (!mExtent.contains(extent))
					{
						continue;
					}
				}
				mFiles.emplace_back(entry.path().filename().wstring());
			}
		}

		// mSelected.clear();
		// mRenameResult.clear();
		// mNavigationGuess.clear();
		// bNewEntry = false;

		// RefreshGuess();
	}

	void TGUI_FileBrowser::EditContent()
	{
		constexpr ImVec2 buttonSize(100.f, 0.f);


		if (ImGui::Button(u8"새폴더", buttonSize))
		{
			Refresh();

			WText newFileName = L"새폴더";
			mSelected         = newFileName;
			mRenameResult     = newFileName;
		}

		bool bDisabled = mSelected.empty();
		if (bDisabled)
		{
			ImGui::BeginDisabled();
		}

		ImGui::SameLine();

		if (ImGui::Button(u8"복제", buttonSize))
		{}

		ImGui::SameLine();

		if (ImGui::Button(u8"삭제", buttonSize))
		{}

		if (bDisabled)
		{
			ImGui::EndDisabled();
		}

		const ImGuiStyle style = ImGui::GetStyle();

		if (ImGui::BeginListBox("##FileBrowserContent"))
		{
			ImGui::Spacing();
			ImGui::Spacing();

			if (!mPath.empty())
				if (ImGui::Selectable("  ..##FileListBack"))
					TryPopPath();

			bool renaming = !mRenameResult.empty();

			WText newDir;
			for (auto& dir : mDirectories)
			{
				if (ContentEntry(dir, true))
				{
					if (dir == mSelected)
					{
						newDir = dir;
					}
					else
					{
						mSelected     = dir;
						mRenameResult = L"";
					}
				}
			}


			for (auto& file : mFiles)
			{
				if (ContentEntry(file, false))
				{
					mSelected     = file;
					mRenameResult = L"";
				}
			}

			if (!newDir.empty())
				TryApplyPath(mPath + L"\\" + newDir);

			if (renaming && mRenameResult.empty())
				Refresh();

			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::EndListBox();
		}
	}

	bool TGUI_FileBrowser::ContentEntry(const std::wstring& InDir, bool InCond)
	{
		const bool selected = mSelected == InDir;
		if (selected && !mRenameResult.empty())
		{
			constexpr ImGuiInputTextFlags flags =
			ImGuiInputTextFlags_EnterReturnsTrue |
			ImGuiInputTextFlags_EscapeClearsAll |
			ImGuiInputTextFlags_CharsNoBlank;
			// if (ImGui::InputText("##ListEntryRename", &mRenameResult, flags))
			// {
			// 	// TryApplyRename(Selected, RenameResult);
			// 	// RenameResult = "";
			// }
			return false;
		}

		if (fs::path(InDir).extension() == ".png")
		{
			ImGui::SetItemAllowOverlap();

			XTexture* tex = Manager_Texture.Load(mPath + L"\\" + InDir);
			ImGui::ImageButton(tex->GetShaderResourceView(), {32.f, 32.f});

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
			{
				ImGui::SetDragDropPayload("MAP_Editor_DD", &tex, sizeof(tex));
				ImGui::EndDragDropSource();
			}
			ImGui::SameLine();
		}

		return ImGui::Selectable(((InCond ? "- " : "  ") + WText2Text(InDir) + "##ListEntry").c_str(), selected);
	}

	WText TGUI_FileBrowser::GetLabel() const
	{
		return L"FileBrowser##" + mOriginalPath;
	}

}
