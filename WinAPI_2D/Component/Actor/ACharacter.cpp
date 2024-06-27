#include "ACharacter.h"



namespace LJG
{

	ACharacter::ACharacter(const WText& InKey)
		: APawn(InKey)
	{}

	ACharacter::~ACharacter() {}

	void ACharacter::Initialize()
	{
		APawn::Initialize();
	}

	void ACharacter::Update(float DeltaTime)
	{
		APawn::Update(DeltaTime);


	}
	
}
