#include "GWorld.h"

namespace LJG
{
	void GWorld::SpawnWorld()
	{
	}

	void GWorld::Initialize()
	{
		mCamera = CreateDefaultSubObject<ACamera>(L"Camera");
		mCamera->SetOwnerActor(this);
		mCamera->SetProjection(Context::GetViewportSize().X, Context::GetViewportSize().Y);
	}
	void GWorld::Update(float DeltaTime) {}
	void GWorld::Render() {}
	void GWorld::Release() {}
	void GWorld::BeginScene() {}
	void GWorld::EndScene() {}
	void GWorld::MoveScene() {}

}

