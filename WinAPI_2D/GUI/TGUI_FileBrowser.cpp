#include "TGUI_FileBrowser.h"

#include <filesystem>
#include <imgui.h>
#include <imgui_stdlib.h>

#include "imgui_filebrowser.h"
#include "DirectX/Context.h"
#include "Helper/EngineHelper.h"


namespace LJG
{
	namespace fs = std::filesystem;

	TGUI_FileBrowser::TGUI_FileBrowser(const WText& InKey)
		: TGUI_Base(InKey),
		  mPath(L"./") {}

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


		ImGui::End();
	}

	bool TGUI_FileBrowser::Open_Internal(const WText& InPath, EFileBrowserOption InOption, const std::set<WText>& InExtent)
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

		ImGui::OpenPopup(WText2Text(GetLabel()).c_str());

		return true;
	}

	bool TGUI_FileBrowser::Fetch_Internal(const WText& InPath, WText& OutSelectedPath)
	{


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

	void TGUI_FileBrowser::EditContent()
	{
		if (ImGui::Button("New", {100.f, 0.f}))
		{
			Refresh();

			WText newFileName = L"새폴더";
		}

	}

	WText TGUI_FileBrowser::GetLabel() const
	{
		return L"FileBrowser##" + mOriginalPath;
	}

}
