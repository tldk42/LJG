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
		const WText RibbyPath = L"rsc/CupHead_re/Ribby/";

		//================================================ Ribby =========================================================//
		mManagedList.try_emplace(L"shortFrog_idle",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(RibbyPath + L"Idle/shortFrog_idle_",
															  36, 36.f, true)));
		mManagedList.try_emplace(L"shortFrog_intro",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(RibbyPath + L"Intro/shortFrog_intro_",
															  15, 15.f, true)));

		mManagedList.try_emplace(L"shortfrog_fist",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Fist Attack/Fists/Normal/shortfrog_fist_",
										 15, 15.f, true)));
		mManagedList.try_emplace(L"shortfrog_fist_pink",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Fist Attack/Fists/Pink/shortfrog_fist_p_",
										 15, 15.f, true)));


		mManagedList.try_emplace(L"shortFrog_fist_start",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Fist Attack/Start/shortFrog_fist_start_",
										 22, 22.f, true)));
		mManagedList.try_emplace(L"shortFrog_fist_loop",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Fist Attack/Loop/shortFrog_fist_loop_",
										 8, 15.f, true)));
		mManagedList.try_emplace(L"shortFrog_fist_end",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Fist Attack/End/shortFrog_fist_end_",
										 9, 9.f, true)));

		mManagedList.try_emplace(L"shortFrog_roll_intro_start",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Roll/Intro/shortFrog_roll_intro_start_",
										 5, 10.f, true)));
		mManagedList.try_emplace(L"shortFrog_roll_intro_loop",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Roll/Intro/Loop/shortFrog_roll_intro_loop_",
										 3, 6.f, true)));
		mManagedList.try_emplace(L"shortFrog_roll_intro_end",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Roll/Intro/shortFrog_roll_intro_end_",
										 6, 12.f, true)));
		mManagedList.try_emplace(L"shortFrog_roll_loop",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Roll/Roll Loop/shortFrog_roll_",
										 8, 16.f, true)));
		mManagedList.try_emplace(L"shortFrog_roll_end",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Roll/Crash/shortFrog_roll_end_",
										 16, 16.f, true)));

		mManagedList.try_emplace(L"shortFrog_clap_intro_start",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Clap Attack/shortFrog_clap_intro_start_",
										 7, 7.f, true)));
		mManagedList.try_emplace(L"shortFrog_clap_intro_loop",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Clap Attack/shortFrog_clap_intro_loop_",
										 3, 6.f, true)));
		mManagedList.try_emplace(L"shortFrog_clap_loop",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Clap Attack/shortFrog_clap_loop_",
										 11, 11.f, true)));

		mManagedList.try_emplace(L"shorfrog_clap_ball_blue",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Clap Attack/Ball/shorfrog_clap_ball_b_",
										 1, 1.f, true)));
		mManagedList.try_emplace(L"shorfrog_clap_ball_yellow",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Clap Attack/Ball/shorfrog_clap_ball_y_",
										 1, 1.f, true)));
		mManagedList.try_emplace(L"shorfrog_clap_ball_green",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 RibbyPath + L"Clap Attack/Ball/shorfrog_clap_ball_g_",
										 1, 1.f, true)));
		//================================================ Ribby =========================================================//


		//================================================ Croaks =========================================================//
		const WText CroaksPath = L"rsc/CupHead_re/Croaks/";

		mManagedList.try_emplace(L"tallfrog_intro",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Intro/tallfrog_intro_",
										 15, 15.f, true)));
		mManagedList.try_emplace(L"tallfrog_idle",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Idle/tallfrog_idle_",
										 36, 36.f, true)));

		mManagedList.try_emplace(L"tallfrog_spit_start",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Spit/Start/tallfrog_spit_start_",
										 14, 14.f, true)));
		mManagedList.try_emplace(L"tallfrog_spit_loop",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Spit/Loop/tallfrog_spit_loop_",
										 8, 8.f, true)));
		mManagedList.try_emplace(L"tallfrog_spit_end",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Spit/End/tallfrog_spit_end_",
										 3, 3.f, true)));

		mManagedList.try_emplace(L"tallfrog_fan_intro",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Fan/Intro/tallfrog_fan_",
										 23, 23.f, true)));

		mManagedList.try_emplace(L"tallfrog_fan_loop1",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Fan/Loop 1/tallfrog_fan_Loop1_",
										 5, 5.f, true)));

		mManagedList.try_emplace(L"tallfrog_fan_loop2",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Fan/Loop 2/tallfrog_fan_Loop2_",
										 4, 4.f, true)));
		mManagedList.try_emplace(L"tallfrog_fan_outro",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Fan/Outro/tallfrog_fan_outro_",
										 14, 14.f, true)));


		mManagedList.try_emplace(L"tallfrog_fan_wind",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Fan/Wind/tallfrog_fan_wind_",
										 9, 9.f, true)));
		//================================================ Croaks =========================================================//

		//================================================ Firefly ========================================================//
		mManagedList.try_emplace(L"firefly_down",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Firefly/Down/tallfrog_firefly_down_",
										 4, 4.f, true)));

		mManagedList.try_emplace(L"firefly_up",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Firefly/Up/tallfrog_firefly_up_",
										 4, 4.f, true)));

		mManagedList.try_emplace(L"firefly_left",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Firefly/Left/tallfrog_firefly_left_",
										 4, 4.f, true)));

		mManagedList.try_emplace(L"firefly_idle",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Firefly/Idle/tallfrog_firefly_idle_",
										 10, 10.f, true)));

		mManagedList.try_emplace(L"firefly_dead",
								 std::make_unique<FAnimData>(
									 AnimUtil::LoadAnimations(
										 CroaksPath + L"Firefly/Death/tallfrog_firefly_death_",
										 9, 9.f, true)));
		//================================================ Firefly ========================================================//


		//============================================== Slot Machine =====================================================//
		// mManagedList.try_emplace(L"tallfrog_morph_start",
		// 						 std::make_unique<FAnimData>(
		// 							 AnimUtil::LoadAnimations(
		// 								 CroaksPath + L"Slot Machine/Morph/Intro/tallfrog_morph_start_",
		// 								 3, 9.f, true)));
		//
		// mManagedList.try_emplace(L"tallfrog_morph_loop",
		// 						 std::make_unique<FAnimData>(
		// 							 AnimUtil::LoadAnimations(
		// 								 CroaksPath + L"Slot Machine/Morph/Intro/Loop/tallfrog_morph_loop_",
		// 								 3, 9.f, true)));
		//
		// mManagedList.try_emplace(L"tallfrog_morph_end",
		// 						 std::make_unique<FAnimData>(
		// 							 AnimUtil::LoadAnimations(
		// 								 CroaksPath + L"Slot Machine/Morph/Intro/Outro/tallfrog_morph_end_",
		// 								 25, 25.f, true)));
		//
		// mManagedList.try_emplace(L"firefly_dead",
		// 						 std::make_unique<FAnimData>(
		// 							 AnimUtil::LoadAnimations(
		// 								 CroaksPath + L"Firefly/Death/tallfrog_firefly_death_",
		// 								 9, 9.f, true)));

		//============================================== Slot Machine =====================================================//

#pragma endregion
	}
}
