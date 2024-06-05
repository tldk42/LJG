#include "PlayerController.h"

#include "InputManager.h"

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

	if (InputManager::Get()->IsKeyDown(EKeyCode::D))
	{
		AddMovementInput({DeltaTime, 0.f});
	}
	if (InputManager::Get()->IsKeyDown(EKeyCode::S))
	{
		AddMovementInput({0.f, -DeltaTime});
	}
	if (InputManager::Get()->IsKeyDown(EKeyCode::W))
	{
		AddMovementInput({0.f, DeltaTime});
	}
	if (InputManager::Get()->IsKeyDown(EKeyCode::A))
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
