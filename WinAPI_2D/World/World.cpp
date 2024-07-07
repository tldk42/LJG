#include "World.h"

#include "AHUD.h"
#include "Camera.h"
#include "InputManager.h"
#include "AI/BehaviorTree.h"
#include "Component/UImage.h"
#include "Component/Actor/APlayerCharacter.h"
#include "Component/Manager/AnimManager.h"
#include "Component/Manager/GUIManager.h"
#include "Component/Manager/SceneManager.h"
#include "Component/Manager/SoundManager.h"
#include "GUI/GUI_FileBrowser.h"
#include "GUI/GUI_Hierarchy.h"
#include "GUI/GUI_Inspector.h"
#include "GUI/GUI_MapEditor.h"
#include "GUI/GUI_Inspector_MapEdit.h"

namespace LJG
{
	class UImage;

	void World::SpawnGameMode()
	{
		// GUI »ý¼º
		GUI_Inspector*         gui         = Manager_GUI.CreateOrLoad<GUI_Inspector>(L"Inspector");
		GUI_Inspector_MapEdit* mapInspec   = Manager_GUI.CreateOrLoad<GUI_Inspector_MapEdit>(L"MapInspector");
		GUI_FileBrowser*       fileBrowser = Manager_GUI.CreateOrLoad<GUI_FileBrowser>(L"FileBrowser");
		GUI_MapEditor*         mapEditor   = Manager_GUI.CreateOrLoad<GUI_MapEditor>(L"MapEditor");
		GUI_Hierarchy*         hierarchy   = Manager_GUI.CreateOrLoad<GUI_Hierarchy>(L"Hierarchy");

		Manager_Scene.MoveScene(L"Tutorial");
	}

	void World::Initialize()
	{
		Manager_Input.Initialize();
		Manager_Audio.Initialize();
		Manager_Anim.LoadAllAnims();

		Manager_Scene.Initialize();

		// LocalPlayer.Initialize();
		MainCam.Initialize();
		Manager_Object.Initialize();

		SpawnGameMode();

		OnDebugModeChanged.Bind(std::bind(&GUIManager::ToggleGUI, &Manager_GUI));

		Manager_Input.AddInputBinding(EKeyCode::F1, EKeyState::Down,
									  [&](float_t DeltaTime){ OnDebugModeChanged.Execute(); });

	}

	void World::Update(float DeltaTime)
	{
		Manager_Input.Update(DeltaTime);
		Manager_Audio.Update(DeltaTime);

		Manager_Scene.Update(DeltaTime);

		MainCam.Update(DeltaTime);

		Manager_GUI.Update(DeltaTime);
	}

	void World::Render()
	{
		Manager_Scene.Render();

		MainCam.Render();

		Manager_GUI.Render();
	}

	void World::Release()
	{
		// LocalPlayer.Release();
		MainCam.Release();

		Manager_Audio.Release();

		Manager_Scene.Release();

		if (bDebug)
			Manager_GUI.Release();
	}

	void World::MoveScene(const WText& InSceneName)
	{
		//TODO : Move
		Manager_Scene.MoveScene(InSceneName);
	}

}
