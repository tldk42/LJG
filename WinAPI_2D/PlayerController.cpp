#include "PlayerController.h"

#include "InputManager.h"
#include "USprite2D.h"

LJG::PlayerController::PlayerController(const std::wstring& InTextureFile)
	: UObject(InTextureFile) {}

LJG::PlayerController::~PlayerController()
{
	PlayerController::Release();
}

void LJG::PlayerController::Initialize()
{
	UObject::Initialize();
}

void LJG::PlayerController::Update(float DeltaTime)
{
	UObject::Update(DeltaTime);

	if (InputManager::IsKeyPressed(EKeyCode::D))
	{
		AddMovementInput({DeltaTime, 0.f});
	}
	if (InputManager::IsKeyPressed(EKeyCode::S))
	{
		AddMovementInput({0.f, -DeltaTime});
	}
	if (InputManager::IsKeyPressed(EKeyCode::W))
	{
		AddMovementInput({0.f, DeltaTime});
	}
	if (InputManager::IsKeyPressed(EKeyCode::A))
	{
		AddMovementInput({-DeltaTime, 0.f});
	}
}

void LJG::PlayerController::Render()
{
	UObject::Render();
}

void LJG::PlayerController::Release()
{
	UObject::Release();
}

void LJG::PlayerController::AddMovementInput(const FVector2f& MovementInputAmount) const
{
	mVertexMesh->AddWorldLocation(MovementInputAmount);
}
