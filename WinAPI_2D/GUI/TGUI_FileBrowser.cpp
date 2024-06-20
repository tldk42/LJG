#include "TGUI_FileBrowser.h"

#include <filesystem>
#include <imgui.h>
#include <imgui_stdlib.h>

#include "imgui_filebrowser.h"
#include "DirectX/Context.h"
#include "Helper/EngineHelper.h"


namespace LJG
{

	void TGUI_FileBrowser::CheckResize()
	{
		if (ImGui::IsWindowDocked())
		{
			const ImVec2 currentSize = ImGui::GetContentRegionAvail();

			if (mCachedSize.x != currentSize.x || mCachedSize.y != currentSize.y)
			{
				Context::Get()->SetViewport(Context::GetViewportSize().X, GetWindowHeight() - currentSize.y);

				mCachedSize = currentSize;
			}
		}

	}

	void TGUI_FileBrowser::RenderCustomGUI()
	{
		ImGui::GetIO().NavActive        = false;
		ImGui::GetIO().WantCaptureMouse = true;

		ImGui::Begin("FileBrowser", &bExit, ImGuiWindowFlags_MenuBar);

		CheckResize();

		if (ImGui::Button("Pick File"))
		{
			ImGui::OpenFileBrowser("rsc/");
		}
		std::string result;
		if (ImGui::FetchFileBrowserResult("rsc/", result))
		{
			// Do something with the result
		}

		ImGui::End();
	}

	bool TGUI_FileBrowser::Open_Internal(const WText& InPath, EFileBrowserOption InOption, const std::set<WText>& InExtent)
	{
		if (bIsOpen)
		{
			return mOriginalPath == InPath;
		}

		auto directory = InPath;

		if (!std::filesystem::is_directory(GetRelative(directory)))
		{
			const auto dirPath = std::filesystem::path(directory);
			if (dirPath.has_parent_path())
			{
				directory = dirPath.parent_path().wstring();
			}
		}

		bIsOpen            = true;
		mOriginalPath      = InPath;
		mFileBrowserOption = InOption;
		mExtent            = InExtent;

		TryApplyPath(directory);

		ImGui::OpenPopup(WText2Text(GetLabel()).c_str());

		return true;
	}

	bool TGUI_FileBrowser::Fetch_Internal(const WText& InPath, WText& OutSelectedPath)
	{
		return true;
	}

	bool TGUI_FileBrowser::TryApplyPath(const WText& InText)
	{
		std::filesystem::path path(GetRelative(InText));
		if (!std::filesystem::exists(path))
		{
			return false;
		}

		// mPath       = GetLocal(path.wstring());
		mEditedPath = L"";

		Refresh();

		return true;
	}

	void TGUI_FileBrowser::Refresh()
	{
		const std::filesystem::path path(GetRelative(mPath));

		if (!std::filesystem::exists(path))
		{
			// TryPopPath();
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
			else if (mFileBrowserOption != EFileBrowserOption::Directory)
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

		mSelected.clear();
		mRenameResult.clear();
		mNavigationGuess.clear();
		bNewEntry = false;

		// RefreshGuess();
	}

	WText TGUI_FileBrowser::GetLabel() const
	{
		return L"FileBrowser##" + mOriginalPath;
	}

	WTextView TGUI_FileBrowser::GetRelative(const WText& InPath)
	{
		return L"rsc/" + InPath;
	}
}
