#pragma once
#include <nlohmann/json.hpp>

#include "TGUI_Base.h"

// wstring, FVector2f에 대해서 저장할 수 있도록 지정
namespace nlohmann
{
	template <>
	struct adl_serializer<WText>
	{
		static void to_json(json& j, const WText& str)
		{
			j = LJG::WText2Text(str);
		}

		static void from_json(const json& j, WText& str)
		{
			str = LJG::Text2WText(j.get<Text>());
		}
	};

	template <>
	struct adl_serializer<FVector2f>
	{
		static void to_json(json& j, const FVector2f& str)
		{
			j = {str.X, str.Y};
		}

		static void from_json(const json& j, FVector2f& str)
		{
			str.X = j.get<std::array<float_t, 2>>()[0];
			str.Y = j.get<std::array<float_t, 2>>()[1];
		}
	};
}

namespace LJG
{
	using json = nlohmann::json;

	// 저장시 필요 데이터
	struct FMapData
	{
		Text      Key;// 키 이름
		WText     TexPath  = LR"()"; // 텍스처 경로
		FVector2f Position = FVector2f::ZeroVector;
		FVector2f Scale    = FVector2f::UnitVector;
		float     ZOrder   = 0.5f;
		float     Rotation = 0.f;
	};

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FMapData, Key, TexPath, Position, Scale, ZOrder, Rotation);


	class GUI_MapEditor : public TGUI_Base
	{
	public:
		explicit GUI_MapEditor(const WText& InKey);

	public:
		void         CheckResize() override;
		void         SavePointsToFile(const Text& filename);
		virtual void RenderCustomGUI() override;

	private:
		void ShowOptions();
		void ShowGridPanel();
		void HandleImage();
		void SaveJsonFile();
		bool LoadScene(const Text& FileName);

	private:
		Text                  mCurrentSceneName = "TestScene";
		std::vector<FMapData> mMapDatas;
		FMapData*             mSelectedData;

		ImVec2      mScrolling;
		ImVec2      mOrigin;
		ImVec2      mMouseCanvasPos;
		ImDrawList* mDrawList;

		float mGridSize = 64.f;

		bool  bEnableGrid;
		bool  bEnableContextMenu;
		bool  bAddingLine;
		float mZoom = 1.f;

		friend class GUI_Hierarchy;
	};
}
