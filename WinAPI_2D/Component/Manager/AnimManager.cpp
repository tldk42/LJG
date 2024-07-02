#include "AnimManager.h"
#include <filesystem>
#include "Component/Animation/USpriteAnimation.h"

namespace LJG
{
	void AnimManager::LoadAllAnims()
	{
		mManagedList.try_emplace(L"cuphead_dash",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_dash_", 6, 12.f, true)));
		mManagedList.try_emplace(L"cuphead_dash_air",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_dash_air_", 6, 6.f, true)));
		mManagedList.try_emplace(L"cuphead_death_body",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_death_body_", 16, 16.f,
															  true)));
		mManagedList.try_emplace(L"cuphead_duck",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_duck_", 7, 7.f, true)));
		mManagedList.try_emplace(L"cuphead_duck_idle",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_duck_idle_", 5, 5.f,
															  true)));
		mManagedList.try_emplace(L"cuphead_duck_shoot",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_duck_shoot_", 3, 9.f,
															  true)));
		mManagedList.try_emplace(L"cuphead_ex_diagonal_up",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_ex_diagonal_up_", 15, 15.f,
															  true)));
		mManagedList.try_emplace(L"cuphead_ex_straight",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_ex_straight_", 15, 15.f,
															  true)));
		mManagedList.try_emplace(L"cuphead_ex_up",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_ex_up_", 15, 15.f, true)));
		mManagedList.try_emplace(L"cuphead_ghost",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_ghost_", 24, 24.f, true)));
		mManagedList.try_emplace(L"cuphead_hit",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_hit_", 6, 6.f, true)));
		mManagedList.try_emplace(L"cuphead_idle",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_idle_", 5, 12.f, true)));
		mManagedList.try_emplace(L"cuphead_intro_a",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_intro_a_", 28, 28.f,
															  true)));
		mManagedList.try_emplace(L"cuphead_jump",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_jump_", 8, 8.f, true)));
		mManagedList.try_emplace(L"cuphead_parry",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_parry_", 8, 8.f, true)));
		mManagedList.try_emplace(L"cuphead_run",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_run_", 16, 16.f, true)));
		mManagedList.try_emplace(L"cuphead_run_shoot",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_run_shoot_", 16, 16.f,
															  true)));
		mManagedList.try_emplace(L"cuphead_run_shoot_diagonal_up",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_run_shoot_diagonal_up_", 16,
															  16.f, true)));
		mManagedList.try_emplace(L"cuphead_shoot_straight",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_shoot_straight_", 3, 9.f,
															  true)));
		mManagedList.try_emplace(L"cuphead_shoot_up",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_shoot_up_", 3, 9.f, true)));
		mManagedList.try_emplace(L"projectile_shoot",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/PeaShoottSheet_", 8, 8.f, true)));
		mManagedList.try_emplace(L"cuphead_title_screen",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/cuphead_title_screen_", 34, 34.f, true)));
		mManagedList.try_emplace(L"transition_fade",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Anim/IrisTransitionSheet_", 17, 17.f, true)));

		#pragma region °³±¸¸®
		mManagedList.try_emplace(L"shortFrog_idle",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Sprite/Game_1/Ribby/Idle/shortFrog_idle2_",
															  13, 13.f, true)));
		mManagedList.try_emplace(L"shortFrog_intro",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(L"rsc/CupHead/Sprite/Game_1/Ribby/Intro/shortFrog_intro_",
															  15, 15.f, true)));

		mManagedList.try_emplace(L"tallfrog_intro",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 L"rsc/CupHead/Sprite/Game_1/Croaks - Slot Machine/Intro/tallfrog_intro_",
										 15, 15.f, true)));
		mManagedList.try_emplace(L"tallfrog_idle",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 L"rsc/CupHead/Sprite/Game_1/Croaks - Slot Machine/Idle/tallfrog_idle2_",
										 18, 18.f, true)));
		#pragma endregion
	}
}
