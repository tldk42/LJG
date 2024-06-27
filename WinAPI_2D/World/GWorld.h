#pragma once
#include "Component/Manager/Manager.h"


namespace LJG
{
	class UScene;
	class ACamera;

	class GWorld : public TSingleton<GWorld>
	{
	public:
		static void SpawnWorld();

	public:
		void BeginScene();
		void EndScene();
		void MoveScene();

	protected:
		std::unordered_map<WText, UScene*> mScenes;
		ACamera*                           mWorldCamera;

	};
}
