#pragma once
#include <nlohmann/json.hpp>
#include "CommonInclude.h"

namespace LJG
{
	class UScene : public ICoreAPI
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

		inline const WText& GetName() const { return mSceneFile; }

	protected:
		WText          mSceneFile;
		nlohmann::json mSavedData;
	};

}