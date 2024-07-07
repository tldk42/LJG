#include "ExitDoor.h"

#include "InputManager.h"
#include "Component/UImage.h"
#include "Component/Manager/SceneManager.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{

	ExitDoor::ExitDoor(const WText& InKey)
		: AInteractObject(InKey)
	{
		mDoor = CreateDefaultSubObject<UImage>(InKey, L"rsc/CupHead/Texture2D/tutorial_exit_door.png", 0.4f);
		mBoxComponent->SetScale({100, 150.f});
		mBoxComponent->OnCollisionEnter_Delegate.Bind(
			std::bind(&ExitDoor::OnBeginInteract, this, std::placeholders::_1));
		mBoxComponent->OnCollisionExit_Delegate.Bind(
			std::bind(&ExitDoor::OnEndInteract, this, std::placeholders::_1));
	}

	ExitDoor::~ExitDoor() {}

	void ExitDoor::Initialize()
	{
		AInteractObject::Initialize();
	}

	void ExitDoor::Update(float DeltaTime)
	{
		AInteractObject::Update(DeltaTime);


		if (bCanEnter && Manager_Input.IsKeyDown(EKeyCode::M))
		{
			Manager_Scene.MoveScene(L"Game_2");
		}
	}

	void ExitDoor::Render()
	{
		AInteractObject::Render();
	}

	void ExitDoor::Release()
	{
		AInteractObject::Release();
	}

	void ExitDoor::OnBeginInteract(FHitResult_Box2D& HitResult)
	{
		bCanEnter = true;
	}

	void ExitDoor::OnEndInteract(FHitResult_Box2D& HitResult)
	{
		bCanEnter = false;
	}

	void ExitDoor::SetWorldLocation(const FVector2f& InLocation)
	{
		mDoor->SetWorldLocation(InLocation);
		mBoxComponent->SetWorldLocation(InLocation);
	}

	void ExitDoor::SetScale(const FVector2f& InScale)
	{
		mDoor->SetScale(InScale);
		mBoxComponent->SetScale(InScale);
	}
}
