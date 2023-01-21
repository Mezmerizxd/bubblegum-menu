#include "MainScript.hpp"
#include "ScriptCallback.hpp"
#include "Lists.hpp"
//#include "Natives.hpp"
#include "Timer.hpp"
#include "Translation.hpp"
#include "CustomText.hpp"
#include "UI/GUI.hpp"
#include "UI/BoolOption.hpp"
#include "UI/ChooseOption.hpp"
#include "UI/NumberOption.hpp"
#include "UI/RegularOption.hpp"
#include "UI/SubOption.hpp"
#include "UI/RegularSubmenu.hpp"
#include "UI/PlayerSubmenu.hpp"
#include "bubblegum.hpp"
#include "long.hpp"

namespace Big
{
	enum Submenu : std::uint32_t
	{
		//MainMenu
		SubmenuHome,
		SelfMenu,
		SelfMenuAnimation,
		SelfMenuModelChanger,
		//PlayerList Sub Menus
		NetworkMenu,
		NetworkLobby,
		PlayerlistMenu,
		SelectedPlayerMenu,
		PlayerListDropMenu,
		//Weapon Sub Menus
		WeaponMenu,
		//Vehicle Spawn Sub Menus
		VehicleSpawnMenu,
		VehicleSuperCars,
		Sports,
		Sportss,
		SportClassic,
		Offroad,
		Sedans,
		Coupes,
		Muscle,
		Boats,
		Commercial,
		Compacts,
		Cycles,
		Emergency,
		Helicopters,
		Industrial,
		Military,
		Motorcycles,
		Planes,
		Service,
		SUV,
		Trailer,
		Trains,
		Utility,
		Vans,
		//Vehicle Sub Menus
		VehicleMenu,
		VehicleHornboostMenu,
		VehicleSettings,
		//Teleport Sub Menus
		TeleportMenu,
		TeleportIndoor,
		TeleportOutdoor,
		TeleportUnderwater,
		//Miscellaneous Sub Menus
		MiscellaneousMenu,
		//Protection Menu
		ProtectionsMenu,
		//Recovery Sub Menus
		RecoveryMenu,
		RecoveryLevelMenu,
		RecoveryDropMenu,
		RecoveryStatEditor,
		RecoveryOther,
		//Credits Sub Menus
		CreditsMenu,
		//Settings Sub Menus
		SettingsMenu,
		EditMenu,
		MenuInfo,
		EditMenuHeaderThemes
	};

	bool MainScript::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType MainScript::GetType()
	{
		return ScriptType::Game;
	}

	namespace Bubble {
		static bool SelfGodmode{};
		static bool SelfNoclip{};
		static bool SelfNeverWanted{};
		static bool SelfInvisible{};
		static bool SelfExplosiveMelee{};
		static bool SelfSuperJump{};
		static bool SelfFastRun{};
		static bool SelfFastSwim{};
		static bool SelfNoRagdoll{};
		static bool WeaponUnlimitedAmmo{};
		static bool WeaponDelete{};
		static bool WeaponExplosive{};
		static bool WeaponTeleport{};
		static bool WeaponMoneyGuns{};
		static bool WeaponGravity{};
		static bool WeaponAirstrike{};
		static bool VehicleSpawnUpgraded{};
		static bool VehicleSpawnInside{};
		static bool VehicleGodmode{};
		static bool VehicleHornboost{};
		static bool VehicleEditSettings{};
		static bool VehicleDriveOnWater{};
		static bool VehicleNoBikeFall{};
		static bool VehicleLowVehicle{};
		static bool VehicleDriftMode{};
		static std::int64_t HornboostSpeed;
		static float EngineTorque;
		static float EnginePower;
		static float VehicleLightIntesity;
		static int RecoveryLevelSet{};
		static bool RecoveryDropSelfMoney{};
		static std::int32_t RecoveryDropMoneyValue = 2500;
		static std::int32_t RecoveryDropMoneyDelay = 500;
		static std::int64_t RecoveryStatValue{};
		static bool ProtNonHostKick{};
		static bool ProtSendToSM{};
		static bool ProtCEOKick{};
		static bool ProtAntiAfk{};
		static bool ProtExplosive{};
		static bool ProtCEOBan{};
		static bool ProtSendToJob{};
		static bool ProtWeapon{};
		static bool ProtFreeze{};

		void Toggle() {
			//		SELF		//
			if (SelfGodmode) { ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true); }else{ ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false); }
			if (SelfNeverWanted) {Entity player = PLAYER::PLAYER_PED_ID(); PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());PLAYER::SET_MAX_WANTED_LEVEL(0);PLAYER::SET_POLICE_IGNORE_PLAYER(player, SelfNeverWanted);PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, SelfNeverWanted);PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, SelfNeverWanted);}
			if (SelfNoRagdoll) {PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false);}else {PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), true);}
			if (SelfNoclip) { SelfNoClip(); }
			if (SelfSuperJump) {MISC::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_PED_ID());MISC::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());}
			if (SelfFastRun) { PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.49f); }else {PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.0f);}
			if (SelfFastSwim) {	PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.49f);}else{PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.0f);}
			//		WEAPON		//
			if (WeaponUnlimitedAmmo) { WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), true); }else { WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), false); }
			if (WeaponExplosive) { WeaponExplosiveAmmo(); }
			if (WeaponDelete) { WeaponDeleteGun(); }
			if (WeaponTeleport) { WeaponTeleportGun(); }
			if (WeaponMoneyGuns) { WeaponMoneyGun(); }
			if (WeaponGravity) { GarrysModGun(&WeaponGravity); }
			if (WeaponAirstrike) { WeaponAirstrikeGun(); }
			//		VEHICLE		//
			if (VehicleGodmode) {Ped playerPed = PLAYER::PLAYER_PED_ID();Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(playerPed);ENTITY::SET_ENTITY_INVINCIBLE(vehicle, VehicleGodmode);ENTITY::SET_ENTITY_PROOFS(vehicle, VehicleGodmode, VehicleGodmode, VehicleGodmode, VehicleGodmode, VehicleGodmode, VehicleGodmode, VehicleGodmode, VehicleGodmode);VEHICLE::SET_VEHICLE_STRONG(vehicle, VehicleGodmode);VEHICLE::SET_VEHICLE_CAN_BREAK(vehicle, !VehicleGodmode);VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(vehicle, !VehicleGodmode);VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicle, !VehicleGodmode);}
			if (VehicleDriveOnWater) { DriveOnWater(&VehicleDriveOnWater); }
			if (VehicleNoBikeFall){ PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), VehicleNoBikeFall); }
			if (VehicleLowVehicle) { LowerVehicle(); }
			if (VehicleDriftMode) { VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1); }else { VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0); }
			if (VehicleHornboost) {if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::PLAYER_ID())){Vehicle Vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false);NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Vehicle);if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Vehicle)){VEHICLE::SET_VEHICLE_FORWARD_SPEED(Vehicle, HornboostSpeed);}}}
			if (VehicleEditSettings) {
				VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), EnginePower);
				VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), EnginePower);
				VEHICLE::SET_VEHICLE_LIGHT_MULTIPLIER(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), VehicleLightIntesity);
			}
			else {
				VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 2.0);
				VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 2.0);
				VEHICLE::SET_VEHICLE_LIGHT_MULTIPLIER(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1.0);
			}
			//		RECOVERY		//
			if (RecoveryDropSelfMoney) { RecoveryDropCash(PLAYER::PLAYER_ID(), RecoveryDropMoneyDelay, RecoveryDropMoneyValue); }
			//		PROTECTION		//
		
		}
	}

	void MainScript::Initialize()
	{
		YTD();
		g_Settings.m_LogWindow = false;
		m_Initialized = true;
		using namespace UserInterface;
		using namespace Bubble;
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_JOINING"), "Thanks For Using " MenuName);
		//g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_TRANSP"), "Thanks For Using " MenuName);
		IconNotification("~r~Version: " MenuVersion, "~g~Menu Loaded.", MenuName);
		IconNotification("F8 / * To Open The menu.", "", "Controls");
		g_UiManager->AddSubmenu<RegularSubmenu>("Version " MenuVersion, SubmenuHome, [](RegularSubmenu* add){
				add->AddOption<SubOption>("Self", nullptr, SelfMenu);
				add->AddOption<SubOption>("Network", nullptr, NetworkMenu);
				add->AddOption<SubOption>("Weapons", nullptr, WeaponMenu);
				add->AddOption<SubOption>("Vehicle Spawner", nullptr, VehicleSpawnMenu);
				add->AddOption<SubOption>("Vehicle", nullptr, VehicleMenu);
				add->AddOption<SubOption>("Teleport", nullptr, TeleportMenu);
				//add->AddOption<SubOption>("Miscellaneous", nullptr, MiscellaneousMenu);
				//add->AddOption<SubOption>("Protections", nullptr, ProtectionsMenu);
				add->AddOption<SubOption>("Recovery", nullptr, RecoveryMenu);
				add->AddOption<SubOption>("Credits", nullptr, CreditsMenu);
				add->AddOption<SubOption>("Settings", nullptr, SettingsMenu);
			});
#pragma region Self
		//Self Menu
		g_UiManager->AddSubmenu<RegularSubmenu>("Self Menu", SelfMenu, [](RegularSubmenu* add){
				add->AddOption<BoolOption<bool>>("Godmode", nullptr, &SelfGodmode, BoolDisplay::OnOff);
				add->AddOption<BoolOption<bool>>("Never Wanted", nullptr, &SelfNeverWanted, BoolDisplay::OnOff);
				add->AddOption<RegularOption>("Max Health & Armour", nullptr, [] {ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 400); PED::ADD_ARMOUR_TO_PED(PLAYER::PLAYER_PED_ID(), 200); });
				add->AddOption<SubOption>("Animations", nullptr, SelfMenuAnimation);
				add->AddOption<BoolOption<bool>>("No Ragdoll", nullptr, &SelfNoRagdoll, BoolDisplay::OnOff);
				add->AddOption<BoolOption<bool>>("No-Clip", nullptr, &SelfNoclip, BoolDisplay::OnOff);
				add->AddOption<BoolOption<bool>>("Super Jump", nullptr, &SelfSuperJump, BoolDisplay::OnOff);
				add->AddOption<BoolOption<bool>>("Fast Run", nullptr, &SelfFastRun, BoolDisplay::OnOff);
				add->AddOption<BoolOption<bool>>("Fast Swim", nullptr, &SelfFastSwim, BoolDisplay::OnOff);
				add->AddOption<RegularOption>("Clean ped", nullptr, [] {PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::PLAYER_PED_ID()); PED::RESET_PED_VISIBLE_DAMAGE(PLAYER::PLAYER_PED_ID()); });
				add->AddOption<RegularOption>("Kill Yourself", nullptr, [] {ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0); });
		});
		//Animations
		g_UiManager->AddSubmenu<RegularSubmenu>("Animation", SelfMenuAnimation, [](RegularSubmenu* add) {
				add->AddOption<RegularOption>("Stop Animation", nullptr, [] {ClearAnimation(); });
				add->AddOption<RegularOption>("Sex Receiver", nullptr, [] {StartAnimation("rcmpaparazzo_2", "shag_loop_poppy"); });
				add->AddOption<RegularOption>("Sex Giver", nullptr, [] {StartAnimation("rcmpaparazzo_2", "shag_loop_a"); });
				add->AddOption<RegularOption>("Stripper Dance", nullptr, [] {StartAnimation("mini@strip_club@private_dance@part1", "priv_dance_p1"); });
				add->AddOption<RegularOption>("Pole Dance", nullptr, [] {StartAnimation("mini@strip_club@pole_dance@pole_dance1", "pd_dance_01"); });
				add->AddOption<RegularOption>("Push Ups", nullptr, [] {StartAnimation("amb@world_human_push_ups@male@base", "base"); });
				add->AddOption<RegularOption>("Sit Ups", nullptr, [] {StartAnimation("amb@world_human_sit_ups@male@base", "base"); });
				add->AddOption<RegularOption>("Celebrate", nullptr, [] {StartAnimation("rcmfanatic1celebrate", "celebrate"); });
				add->AddOption<RegularOption>("Electrocution", nullptr, [] {StartAnimation("ragdoll@human", "electrocute"); });
				add->AddOption<RegularOption>("Suicide", nullptr, [] {StartAnimation("mp_suicide", "pistol"); });
		});
#pragma endregion
#pragma region Playerlist
		//Network
		g_UiManager->AddSubmenu<RegularSubmenu>("Network Menu", NetworkMenu, [](RegularSubmenu* add){
			add->AddOption<SubOption>("Players", nullptr, PlayerlistMenu);
		});
		//Player Menu
		g_UiManager->AddSubmenu<RegularSubmenu>("Players Menu", PlayerlistMenu, [](RegularSubmenu* add){
				for (std::uint32_t i = 0; i < 32; ++i)
				{
					if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
					{
						g_UiManager->DrawPlayerInfo(); //Shows Sub menu with player info in
						add->AddOption<SubOption>(PLAYER::GET_PLAYER_NAME(i), nullptr, SelectedPlayerMenu, [=]
							{
								g_SelectedPlayer = i;
							});
					}
				}
			});
		//Selected Player Menu
		g_UiManager->AddSubmenu<PlayerSubmenu>(&g_SelectedPlayer, SelectedPlayerMenu, [](PlayerSubmenu* add){
			add->AddOption<RegularOption>("Teleport To Player", nullptr, [] { NetworkTeleportPlayer(); });
			add->AddOption<RegularOption>("Explode Player", nullptr, [] { NetworkExplodePlayer(); });
			});
#pragma endregion
#pragma region Weapons
		//Weapon Menu
		g_UiManager->AddSubmenu<RegularSubmenu>("Weapons Menu", WeaponMenu, [](RegularSubmenu* add) {
				add->AddOption<RegularOption>("Give All Weapons", nullptr, [] {WeaponGiveWeapon(PLAYER::PLAYER_PED_ID()); });
				add->AddOption<BoolOption<bool>>("Unlimited Ammo", nullptr, &WeaponUnlimitedAmmo, BoolDisplay::OnOff);
				add->AddOption<BoolOption<bool>>("Explosive Ammo", nullptr, &WeaponExplosive, BoolDisplay::OnOff);
				add->AddOption<BoolOption<bool>>("Money Gun", nullptr, &WeaponMoneyGuns, BoolDisplay::OnOff);
				add->AddOption<BoolOption<bool>>("Gravity Gun", nullptr, &WeaponGravity, BoolDisplay::OnOff);
				add->AddOption<BoolOption<bool>>("Delete Gun", nullptr, &WeaponDelete, BoolDisplay::OnOff);
				add->AddOption<BoolOption<bool>>("Airstrike Gun", nullptr, &WeaponAirstrike, BoolDisplay::OnOff);
				add->AddOption<BoolOption<bool>>("Teleport Gun", nullptr, &WeaponTeleport, BoolDisplay::OnOff);
			});
#pragma endregion
#pragma region Vehicle Spawner
		//Vehicle Spawn Menu
		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Spawner", VehicleSpawnMenu, [](RegularSubmenu* add) {
			add->AddOption<BoolOption<bool>>("Spawn Inside Vehicle", nullptr, &VehicleSpawnInside, BoolDisplay::OnOff);
			add->AddOption<BoolOption<bool>>("Spawn Vehicle Upgraded", nullptr, &VehicleSpawnUpgraded, BoolDisplay::OnOff);
			add->AddOption<SubOption>("Super", nullptr, VehicleSuperCars);
			add->AddOption<SubOption>("Sports", nullptr, Sportss);
			add->AddOption<SubOption>("Sports Classics", nullptr, SportClassic);
			add->AddOption<SubOption>("Offroad", nullptr, Offroad);
			add->AddOption<SubOption>("Sedans", nullptr, Sedans);
			add->AddOption<SubOption>("Coupes", nullptr, Coupes);
			add->AddOption<SubOption>("Muscle", nullptr, Muscle);
			add->AddOption<SubOption>("Boats", nullptr, Boats);
			add->AddOption<SubOption>("Commerical", nullptr, Commercial);
			add->AddOption<SubOption>("Compacts", nullptr, Compacts);
			add->AddOption<SubOption>("Cycles", nullptr, Cycles);
			add->AddOption<SubOption>("Emergency", nullptr, Emergency);
			add->AddOption<SubOption>("Helicopters", nullptr, Helicopters);
			add->AddOption<SubOption>("Industrial", nullptr, Industrial);
			add->AddOption<SubOption>("Military", nullptr, Military);
			add->AddOption<SubOption>("Motorcycles", nullptr, Motorcycles);
			add->AddOption<SubOption>("Planes", nullptr, Planes);
			add->AddOption<SubOption>("Service", nullptr, Service);
			add->AddOption<SubOption>("SUV", nullptr, SUV);
			add->AddOption<SubOption>("Trailer", nullptr, Trailer);
			add->AddOption<SubOption>("Trains", nullptr, Trains);
			add->AddOption<SubOption>("Utility", nullptr, Utility);
			add->AddOption<SubOption>("Vans", nullptr, Vans);
			});

		g_UiManager->AddSubmenu<RegularSubmenu>("Super", VehicleSuperCars, [](RegularSubmenu* add) {for (auto car : SuperCars) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Sports", Sportss, [](RegularSubmenu* add) {for (auto car : Sportss1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Sports Classics", SportClassic, [](RegularSubmenu* add) {for (auto car : SportsClassics1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Offroad", Offroad, [](RegularSubmenu* add) {for (auto car : OffRoad1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Sedans", Sedans, [](RegularSubmenu* add) {for (auto car : Sedans1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Coupes", Coupes, [](RegularSubmenu* add) {for (auto car : Coupes1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Muscle", Muscle, [](RegularSubmenu* add) {for (auto car : Muscle1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Boats", Boats, [](RegularSubmenu* add) {for (auto car : Boats1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Commercial", Commercial, [](RegularSubmenu* add) {for (auto car : Commercial1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Compacts", Compacts, [](RegularSubmenu* add) {for (auto car : Compacts1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Cycles", Cycles, [](RegularSubmenu* add) {for (auto car : Cycles1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Emergency", Emergency, [](RegularSubmenu* add) {for (auto car : Emergency1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Helicopters", Helicopters, [](RegularSubmenu* add) {for (auto car : Helicopters1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Industrial", Industrial, [](RegularSubmenu* add) {for (auto car : Industrial1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Military", Military, [](RegularSubmenu* add) {for (auto car : Military1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Motorcycles", Motorcycles, [](RegularSubmenu* add) {for (auto car : Motorcycles1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Planes", Planes, [](RegularSubmenu* add) {for (auto car : Planes1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Service", Service, [](RegularSubmenu* add) {for (auto car : Service1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("SUV", SUV, [](RegularSubmenu* add) {for (auto car : SUVs1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Trailer", Trailer, [](RegularSubmenu* add) {for (auto car : Trailer1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Trains", Trains, [](RegularSubmenu* add) {for (auto car : Trains1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Utility", Utility, [](RegularSubmenu* add) {for (auto car : Utility1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
		g_UiManager->AddSubmenu<RegularSubmenu>("Vans", Vans, [](RegularSubmenu* add) {for (auto car : Vans1) { add->AddOption<RegularOption>(car, nullptr, [=] {g_CallbackScript->AddCallback<ModelCallback>(car, [=] {Spawn(car, VehicleSpawnUpgraded, VehicleSpawnInside); }); }); }});
#pragma endregion
#pragma region Vehicle
		//Vehicle Menu
		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Menu", VehicleMenu, [](RegularSubmenu* add) {
				add->AddOption<BoolOption<bool>>("Vehicle Godmode", nullptr, &VehicleGodmode, BoolDisplay::OnOff);
				add->AddOption<RegularOption>("Fix Vehicle", nullptr, [] {uint32_t Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID())); VEHICLE::SET_VEHICLE_FIXED(Vehicle); VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(Vehicle); VEHICLE::SET_VEHICLE_DIRT_LEVEL(Vehicle, 0); });
				add->AddOption<RegularOption>("Max Vehicle", nullptr, [] {VehicleMaxUpgrade(); });
				add->AddOption<RegularOption>("Delete Vehicle", nullptr, [] {VehicleDeleteVehicle(); });
				add->AddOption<SubOption>("Hornboost", nullptr, VehicleHornboostMenu);
				add->AddOption<SubOption>("Vehicle Settings", nullptr, VehicleSettings);
				add->AddOption<BoolOption<bool>>("No Bike Fall", nullptr, &VehicleNoBikeFall, BoolDisplay::OnOff);
				add->AddOption<BoolOption<bool>>("Lower Vehicle", nullptr, &VehicleLowVehicle, BoolDisplay::OnOff);
				add->AddOption<BoolOption<bool>>("Drift Mode", nullptr, &VehicleDriftMode, BoolDisplay::OnOff);
				add->AddOption<RegularOption>("Boost Forward", nullptr, [] {VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 100.0f); });
				add->AddOption<RegularOption>("Boost Backward", nullptr, [] {VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), -500.0f); });
				add->AddOption<RegularOption>("Open Doors", nullptr, [] {for (int i = 0; i < 7; ++i) {VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), i, false, false);} });
				add->AddOption<RegularOption>("Close Doors", nullptr, [] {VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true); });
			});
		g_UiManager->AddSubmenu<RegularSubmenu>("Hornboost", VehicleHornboostMenu, [](RegularSubmenu* add) {
				add->AddOption<BoolOption<bool>>("Enable Hornboost", nullptr, &VehicleHornboost, BoolDisplay::OnOff);
				add->AddOption<NumberOption<std::int64_t>>("Hornboost Speed", nullptr, &HornboostSpeed, 0, 1000, 10);
				add->AddOption<RegularOption>("Set 10", nullptr, [] { HornboostSpeed = 10; });
				add->AddOption<RegularOption>("Set 20", nullptr, [] { HornboostSpeed = 20; });
				add->AddOption<RegularOption>("Set 30", nullptr, [] { HornboostSpeed = 30; });
				add->AddOption<RegularOption>("Set 40", nullptr, [] { HornboostSpeed = 40; });
				add->AddOption<RegularOption>("Set 50", nullptr, [] { HornboostSpeed = 50; });
				add->AddOption<RegularOption>("Set 100", nullptr, [] { HornboostSpeed = 100; });
				add->AddOption<RegularOption>("Set 200", nullptr, [] { HornboostSpeed = 200; });
			});
		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Settings", VehicleSettings, [](RegularSubmenu* add) {
				add->AddOption<BoolOption<bool>>("Enable Custom Settings", nullptr, &VehicleEditSettings, BoolDisplay::OnOff);
				add->AddOption<NumberOption<float>>("Engine Toque", nullptr, &EngineTorque, 0, 1000, 1);
				add->AddOption<NumberOption<float>>("Engine Power", nullptr, &EnginePower, 0, 1000, 1);
				add->AddOption<NumberOption<float>>("Light Intesity", nullptr, &VehicleLightIntesity, 0, 1000, 1);
			});
#pragma endregion
#pragma region Teleport
		//Teleport Menu
		g_UiManager->AddSubmenu<RegularSubmenu>("Teleport", TeleportMenu, [](RegularSubmenu* add) {
				add->AddOption<RegularOption>("Teleport To Waypoint", nullptr, [] {teleport_to_marker(); });
				add->AddOption<SubOption>("Indoor Locations", nullptr, TeleportIndoor);
				add->AddOption<SubOption>("Outdoor Locations", nullptr, TeleportOutdoor);
				add->AddOption<SubOption>("Underwater Locations", nullptr, TeleportUnderwater);
			});
		//Indoor
		g_UiManager->AddSubmenu<RegularSubmenu>("Indoor", TeleportIndoor, [](RegularSubmenu* add) {
			add->AddOption<RegularOption>("Strip Club DJ Booth", nullptr, [] {TeleportToCoords(126.135, -1278.583, 29.270); });
			add->AddOption<RegularOption>("Blaine County Savings Bank", nullptr, [] {TeleportToCoords(-109.299, 6464.035, 31.627); });
			add->AddOption<RegularOption>("Police Station", nullptr, [] {TeleportToCoords(436.491, -982.172, 30.699); });
			add->AddOption<RegularOption>("Humane Labs Entrance", nullptr, [] {TeleportToCoords(3619.749, 2742.740, 28.690); });
			add->AddOption<RegularOption>("Burnt FIB Building", nullptr, [] {TeleportToCoords(160.868, -745.831, 250.063); });
			add->AddOption<RegularOption>("10 Car Garage Back Room", nullptr, [] {TeleportToCoords(223.193, -967.322, 99.000); });
			add->AddOption<RegularOption>("Humane Labs Tunnel", nullptr, [] {TeleportToCoords(3525.495, 3705.301, 20.992); });
			add->AddOption<RegularOption>("Ammunation Office", nullptr, [] {TeleportToCoords(12.494, -1110.130, 29.797); });
			add->AddOption<RegularOption>("Ammunation Gun Range", nullptr, [] {TeleportToCoords(22.153, -1072.854, 29.797); });
			add->AddOption<RegularOption>("Trevor's Meth Lab", nullptr, [] {TeleportToCoords(1391.773, 3608.716, 38.942); });
			add->AddOption<RegularOption>("Pacific Standard Bank Vault", nullptr, [] {TeleportToCoords(255.851, 217.030, 101.683); });
			add->AddOption<RegularOption>("Lester's House", nullptr, [] {TeleportToCoords(1273.898, -1719.304, 54.771); });
			add->AddOption<RegularOption>("Floyd's Apartment", nullptr, [] {TeleportToCoords(-1150.703, -1520.713, 10.633); });
			add->AddOption<RegularOption>("IAA Office", nullptr, [] {TeleportToCoords(117.220, -620.938, 206.047); });
			add->AddOption<RegularOption>("Pacific Standard Bank", nullptr, [] {TeleportToCoords(235.046, 216.434, 106.287); });
			add->AddOption<RegularOption>("Fort Zancudo ATC entrance", nullptr, [] {TeleportToCoords(-2344.373, 3267.498, 32.811); });
			add->AddOption<RegularOption>("Fort Zancudo ATC top floor", nullptr, [] {TeleportToCoords(-2358.132, 3249.754, 101.451); });
			add->AddOption<RegularOption>("Torture Room", nullptr, [] {TeleportToCoords(147.170, -2201.804, 4.688); });

			});
		//Outdoor
		g_UiManager->AddSubmenu<RegularSubmenu>("Outdoor", TeleportOutdoor, [](RegularSubmenu* add) {
			add->AddOption<RegularOption>("Main LS Customs", nullptr, [] {TeleportToCoords(-365.425, -131.809, 37.873); });
			add->AddOption<RegularOption>("Very High Up", nullptr, [] {TeleportToCoords(-129.964, 8130.873, 6705.307); });
			add->AddOption<RegularOption>("IAA Roof", nullptr, [] {TeleportToCoords(134.085, -637.859, 262.851); });
			add->AddOption<RegularOption>("FIB Roof", nullptr, [] {TeleportToCoords(150.126, -754.591, 262.865); });
			add->AddOption<RegularOption>("Maze Bank Roof", nullptr, [] {TeleportToCoords(-75.015, -818.215, 326.176); });
			add->AddOption<RegularOption>("Top of Mount Chilad", nullptr, [] {TeleportToCoords(450.718, 5566.614, 806.183); });
			add->AddOption<RegularOption>("Most Northerly Point", nullptr, [] {TeleportToCoords(24.775, 7644.102, 19.055); });
			add->AddOption<RegularOption>("Vinewood Bowl Stage", nullptr, [] {TeleportToCoords(686.245, 577.950, 130.461); });
			add->AddOption<RegularOption>("Sisyphus Theater Stage", nullptr, [] {TeleportToCoords(205.316, 1167.378, 227.005); });
			add->AddOption<RegularOption>("Galileo Observatory Roof", nullptr, [] {TeleportToCoords(-438.804, 1076.097, 352.411); });
			add->AddOption<RegularOption>("Kortz Center", nullptr, [] {TeleportToCoords(-2243.810, 264.048, 174.615); });
			add->AddOption<RegularOption>("Chumash Historic Family Pier", nullptr, [] {TeleportToCoords(-3426.683, 967.738, 8.347); });
			add->AddOption<RegularOption>("Paleto Bay Pier", nullptr, [] {TeleportToCoords(275.522, 6635.835, 7.425); });
			add->AddOption<RegularOption>("God's thumb", nullptr, [] {TeleportToCoords(-1006.402, 6272.383, 1.503); });
			add->AddOption<RegularOption>("Calafia Train Bridge", nullptr, [] {TeleportToCoords(-517.869, 4425.284, 89.795); });
			add->AddOption<RegularOption>("Altruist Cult Camp", nullptr, [] {TeleportToCoords(-1170.841, 4926.646, 224.295); });
			add->AddOption<RegularOption>("Maze Bank Arena Roof", nullptr, [] {TeleportToCoords(-324.300, -1968.545, 67.002); });
			add->AddOption<RegularOption>("Marlowe Vineyards", nullptr, [] {TeleportToCoords(-1868.971, 2095.674, 139.115); });
			add->AddOption<RegularOption>("Hippy Camp", nullptr, [] {TeleportToCoords(2476.712, 3789.645, 41.226); });
			add->AddOption<RegularOption>("Devin Weston's House", nullptr, [] {TeleportToCoords(-2639.872, 1866.812, 160.135); });
			add->AddOption<RegularOption>("Abandon Mine", nullptr, [] {TeleportToCoords(-595.342, 2086.008, 131.412); });
			add->AddOption<RegularOption>("Weed Farm", nullptr, [] {TeleportToCoords(2208.777, 5578.235, 53.735); });
			add->AddOption<RegularOption>("Stab City", nullptr, [] {TeleportToCoords(126.975, 3714.419, 46.827); });
			add->AddOption<RegularOption>("Del Perro Pier", nullptr, [] {TeleportToCoords(-1850.127, -1231.751, 13.017); });
			});
		//Underwater
		g_UiManager->AddSubmenu<RegularSubmenu>("Underwater", TeleportUnderwater, [](RegularSubmenu* add) {
			add->AddOption<RegularOption>("Sunken Body", nullptr, [] {TeleportToCoords(-3161.078, 3001.998, -37.974); });
			add->AddOption<RegularOption>("Underwater WW2 Tank", nullptr, [] {TeleportToCoords(4201.633, 3643.821, -39.016); });
			add->AddOption<RegularOption>("Dead Sea Monster", nullptr, [] {TeleportToCoords(-3373.726, 504.714, -24.656); });
			add->AddOption<RegularOption>("Underwater UFO", nullptr, [] {TeleportToCoords(762.426, 7380.371, -111.377); });
			add->AddOption<RegularOption>("Underwater Hatch", nullptr, [] {TeleportToCoords(4273.950, 2975.714, -170.746); });
			add->AddOption<RegularOption>("Sunken Plane", nullptr, [] {TeleportToCoords(-942.350, 6608.752, -20.912); });

			});
#pragma endregion
#pragma region Miscellaneous
		g_UiManager->AddSubmenu<RegularSubmenu>("Miscellaneous", MiscellaneousMenu, [](RegularSubmenu* add) {

			});
#pragma endregion
#pragma region Protections
		g_UiManager->AddSubmenu<RegularSubmenu>("Protections", ProtectionsMenu, [](RegularSubmenu* add)
			{
			});
#pragma endregion
#pragma region Recovery
		//Recovery Menu
		g_UiManager->AddSubmenu<RegularSubmenu>("Recovery Menu", RecoveryMenu, [](RegularSubmenu* add) {
				add->AddOption<SubOption>("Level Menu", nullptr, RecoveryLevelMenu);
				add->AddOption<SubOption>("Drop Menu", nullptr, RecoveryDropMenu);
				add->AddOption<SubOption>("Stats Editor", nullptr, RecoveryStatEditor);
				add->AddOption<SubOption>("Other", nullptr, RecoveryOther);
			});
		//Level Menu
		g_UiManager->AddSubmenu<RegularSubmenu>("Level Menu", RecoveryLevelMenu, [](RegularSubmenu* add) {
				add->AddOption<ChooseOption<const char*, std::size_t>>("Character", nullptr, &Lists::SelectCharacterLEVEL, &Lists::SelectCharacterPosLEVEL);
				add->AddOption<NumberOption<std::int32_t>>("Level", nullptr, &RecoveryLevelSet, 0, 8000, 1);
				add->AddOption<RegularOption>("Set Level", nullptr, [] {RecoverySetLevel(Lists::SelectCharacterPosLEVEL, RecoveryLevelSet); });
			});
		//Money Menu
		g_UiManager->AddSubmenu<RegularSubmenu>("Money Menu", RecoveryDropMenu, [](RegularSubmenu* add) {
				add->AddOption<BoolOption<bool>>("Drop Money", nullptr, &RecoveryDropSelfMoney, BoolDisplay::OnOff);
				add->AddOption<NumberOption<int32_t>>("Drop Amount", nullptr, &RecoveryDropMoneyValue, 0, 2500, 10);
				add->AddOption<NumberOption<int32_t>>("Drop Delay", nullptr, &RecoveryDropMoneyDelay, 0, 5000, 10);
			});
		//Stats Editor
		g_UiManager->AddSubmenu<RegularSubmenu>("Stat Editor", RecoveryStatEditor, [](RegularSubmenu* add) {
				add->AddOption<NumberOption<std::int64_t>>("Value", nullptr, &RecoveryStatValue, 0, 1000, 10);
				add->AddOption<RegularOption>("Set Kills", nullptr, [] {EditStat("MPPLY_KILLS_PLAYERS", RecoveryStatValue); });
				add->AddOption<RegularOption>("Set Peds Kills", nullptr, [] {EditStat("MP0_KILLS_INNOCENTS", RecoveryStatValue); });
				add->AddOption<RegularOption>("Set Cops Kills", nullptr, [] {EditStat("MP0_KILLS_COP", RecoveryStatValue); });
				add->AddOption<RegularOption>("Set Gang Members Kills", nullptr, [] {EditStat("MP0_KILLS_ENEMY_GANG_MEMBERS", RecoveryStatValue); });
			});
		//Other
		g_UiManager->AddSubmenu<RegularSubmenu>("Other", RecoveryOther, [](RegularSubmenu* add) {
			add->AddOption<RegularOption>("Max Stats", nullptr, [] {STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, true); });
			add->AddOption<RegularOption>("Max Snacks", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), 99999999, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NO_BOUGHT_HEALTH_SNACKS"), 99999999, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NO_BOUGHT_EPIC_SNACKS"), 99999999, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), 99999999, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_OF_ORANGE_BOUGHT"), 99999999, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_NUMBER_OF_BOURGE_BOUGHT"), 99999999, true); });
			add->AddOption<RegularOption>("Unlock Heist Items", nullptr, [] {UnlockHeist(); });
			add->AddOption<RegularOption>("Remove BadSport", nullptr, [] { STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_BAD_SPORT_BITSET"), 0, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_WAS_I_BAD_SPORT"), 0, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_OVERALL_BADSPORT"), 0, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_CHAR_IS_BADSPORT"), 0, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_BECAME_BADSPORT_NUM"), 0, true); STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_MPPLY_DESTROYED_PVEHICLES"), 0, true); });
			add->AddOption<RegularOption>("Remove Reports", nullptr, [] {RemoveReports(); });
			});
#pragma endregion
#pragma region Credits
		//Credits Menu
		g_UiManager->AddSubmenu<RegularSubmenu>("Credits Menu", CreditsMenu, [](RegularSubmenu* add) {
			add->AddOption<RegularOption>("Menu Owner: " MenuOwner, nullptr, [] {notifyBottom("Menu Owner: " MenuOwner); });
			add->AddOption<RegularOption>("Menu Devs: " MenuDeveloper, nullptr, [] {notifyBottom("Menu Developers: " MenuDeveloper); });
			});
#pragma endregion
#pragma region Settings
		//Settings 
		g_UiManager->AddSubmenu<RegularSubmenu>("Settings Menu", SettingsMenu, [](RegularSubmenu* add)
		{
			add->AddOption<RegularOption>("Un-Inject", "Removes The Mod Menu", [] { g_Running = false; });
			add->AddOption<RegularOption>(std::move(RegularOption("GTA Version").SetRightText(g_GameVariables->m_GameBuild)));
			add->AddOption<SubOption>("Edit Menu", nullptr, EditMenu);
			add->AddOption<BoolOption<std::atomic_bool>>("Log Window", nullptr, &g_Settings.m_LogWindow, BoolDisplay::OnOff);
			//add->AddOption<BoolOption<bool>>("Rainbow Menu", nullptr, &RainbowMenuSet, BoolDisplay::OnOff);
		});	
		//Edit Menu
		g_UiManager->AddSubmenu<RegularSubmenu>("Edit Menu", EditMenu, [](RegularSubmenu* add) {
			add->AddOption<SubOption>("Themes", nullptr, EditMenuHeaderThemes);
			add->AddOption<NumberOption<std::int32_t>>("Open Delay", nullptr, &g_UiManager->m_OpenDelay, 10, 1000, 10, 0);
			add->AddOption<NumberOption<std::int32_t>>("Back Delay", nullptr, &g_UiManager->m_BackDelay, 10, 1000, 10, 0);
			add->AddOption<NumberOption<std::int32_t>>("Enter Delay", nullptr, &g_UiManager->m_EnterDelay, 10, 1000, 10, 0);
			add->AddOption<NumberOption<std::int32_t>>("Vertical Delay", nullptr, &g_UiManager->m_VerticalDelay, 10, 1000, 10, 0);
			add->AddOption<NumberOption<std::int32_t>>("Horizontal Delay", nullptr, &g_UiManager->m_HorizontalDelay, 0.0f, 1000.100f, 1.0f, 0);
			});
		g_UiManager->AddSubmenu<RegularSubmenu>("Themes", EditMenuHeaderThemes, [](RegularSubmenu* add) {
			add->AddOption<ChooseOption<const char*, std::size_t>>("Header", nullptr, &g_UiManager->SelectedEditHeader, &g_UiManager->SelectedEditHeaderPos);
			});
#pragma endregion
	}
	
	void MainScript::Destroy()
	{
		g_UiManager.reset();
	}

	void MainScript::Tick()
	{
		Big::Bubble::Toggle();
		g_UiManager->OnTick();
		g_UiManager->m_HeaderPicture = g_UiManager->SelectedEditHeader[g_UiManager->SelectedEditHeaderPos];
	}
}
