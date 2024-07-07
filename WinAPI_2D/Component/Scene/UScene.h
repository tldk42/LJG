#pragma once
#include <nlohmann/json.hpp>
#include "Component/UObject.h"

namespace LJG
{
	class UScene : public UObject
	{
	public:
		UScene(const WText& InKey);
		~UScene();

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		virtual void LoadScene();
		virtual void MoveScene(WTextView InNextScene);
		virtual void EndScene();

	protected:
		nlohmann::json mSavedData;
	};

}
