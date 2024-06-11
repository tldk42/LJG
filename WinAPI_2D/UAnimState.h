#pragma once
#include "UObject.h"

namespace LJG
{
	class UAnimState : public UObject
	{
	public:
		UAnimState(const std::wstring& InStateName);
		~UAnimState() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void AddAnimation(const std::wstring& InAnimName, UAnimation2D* InAnimation);
		void SetState(const std::wstring& InState);

	private:
		std::wstring                                     mStateName; // 상태 머신 이름
		std::wstring                                     mCurrentState;
		std::unordered_map<std::wstring, UAnimation2DSPtr> mAnimSet; // 재생될 애님 목록
	};
}
