#pragma once
#include "Manager.h"

namespace LJG
{
	#define Manager_GUI GUIManager::Get()

	class TGUI_Base;

	class GUIManager : public ManagerBase<TGUI_Base, GUIManager>
	{
	public:
		static void Initialize();
		static void Update(float DeltaTime);
		static void Render();
		static void Release();

	private:
		static void SetDocking();

	private:
		friend class TSingleton<GUIManager>;
		GUIManager()  = default;
		~GUIManager() = default;

	public:
		GUIManager(const GUIManager&)            = delete;
		GUIManager& operator=(const GUIManager&) = delete;
	};
}
