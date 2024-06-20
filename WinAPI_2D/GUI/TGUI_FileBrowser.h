#pragma once
#include "TGUI_Base.h"

namespace LJG
{

	class TGUI_FileBrowser : public TGUI_Base
	{
	public:
		TGUI_FileBrowser() = default;

	public:
		virtual void CheckResize() override;
		virtual void RenderCustomGUI() override;

	private:
		
		bool Open_Internal(const WText& InPath, EFileBrowserOption InOption, const std::set<WText>& InExtent);
		bool Fetch_Internal(const WText& InPath, WText& OutSelectedPath);

		
		bool TryApplyPath(const WText& InText);
		void  Refresh();

		
		WText GetLabel() const;
		WTextView GetRelative(const WText& InPath);



	protected:
		bool bIsOpen;
		bool bNewEntry;

		WText mOriginalPath;
		WText mPath;
		WText mNavigationGuess;
		WText mEditedPath;
		WText mSelected;
		WText mRenameResult;

		std::set<WText>    mExtent;
		EFileBrowserOption mFileBrowserOption;

		std::vector<WText> mDirectories;
		std::vector<WText> mFiles;
	};
}
