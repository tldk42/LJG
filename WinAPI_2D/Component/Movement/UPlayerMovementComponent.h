#pragma once
#include "UPawnMovementComponent2D.h"

namespace LJG
{

	class UPlayerMovementComponent : public UPawnMovementComponent2D
	{
	public:
		UPlayerMovementComponent();
		~UPlayerMovementComponent() override;

	public:
		void Update(float DeltaTime) override;

	public:
		void Dash();

	public:
		[[nodiscard]] inline bool IsDashing() const { return bIsDashing; }

	private:
		void HandleDash(const float_t DeltaTime) const;

	private:
		bool    bIsDashing;
		float_t mDashPower;
	};
}
