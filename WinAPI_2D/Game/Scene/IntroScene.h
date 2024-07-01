#pragma once
#include "Component/Scene/UScene.h"

namespace LJG
{
	class FadeInImage;
}
namespace LJG
{
	class UAudio;
	class UImage;
	class TitleScreenImage;

	class IntroScene : public UScene
	{
	public:
		explicit IntroScene(const WText& InName);
		~IntroScene() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void LoadScene() override;
		void MoveScene(WTextView InNextScene) override;
		void EndScene() override;

	protected:
		UImage*           backgroundImage;
		TitleScreenImage* playerAnim;
		FadeInImage*      FadeInAnim;
		UAudio*           audio;
	};
}
