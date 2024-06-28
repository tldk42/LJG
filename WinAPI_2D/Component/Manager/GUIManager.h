#pragma once
#include "Manager.h"
#include "GUI/TGUI_Base.h"

namespace LJG
{
	#define Manager_GUI GUIManager::Get()

	class GUIManager : public ManagerBase<TGUI_Base, GUIManager>
	{
	public:
		void Initialize();
		void Update(float DeltaTime);
		void Render();
		void Release();

	public:
		void ToggleGUI();

	private:
		static void SetDocking();

	private:
		bool bEnableGUI;

	private:
		friend class TSingleton<GUIManager>;
		GUIManager()  = default;
		~GUIManager() = default;

	public:
		GUIManager(const GUIManager&)            = delete;
		GUIManager& operator=(const GUIManager&) = delete;
	};
}
