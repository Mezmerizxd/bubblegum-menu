#include "enums.hpp"
#include "MainScript.hpp"
#include "ScriptCallback.hpp"
#include "Lists.hpp"
#include "Natives.hpp"
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
#include "Hooking.hpp"
int IconNotification(const char* text, const char* text2, const char* Subject);
float degToRad(float degs);
void teleport_to_marker();
void teleport_to_coords(Big::Entity e, Big::NativeVector3 coords);
Big::NativeVector3 get_blip_marker();
void KeyPress(DWORD key, DWORD pressTime);
void ClearAnimation();
bool RequestNetworkControl(uint32_t vehID);
Big::NativeVector3 rot_to_direction(Big::NativeVector3* rot);
Big::NativeVector3 add(Big::NativeVector3* vectorA, Big::NativeVector3* vectorB);
Big::NativeVector3 multiply(Big::NativeVector3* vector, float x);
float get_distance(Big::NativeVector3* pointA, Big::NativeVector3* pointB);
void notifyBottom(char* fmt, ...);
void notifyBottom(std::string str);
void WAIT(DWORD ms);



namespace Big::Bubble {
	void SelfNoClip();
	void WeaponGiveWeapon(uint32_t Player);
	void WeaponMoneyGun();
	void WeaponDeleteGun();
	void WeaponExplosiveAmmo();
	void WeaponTeleportGun();
	void WeaponAirstrikeGun();
	void GarrysModGun(bool onOff);
	void NetworkTeleportPlayer();
	void NetworkExplodePlayer();
	void Spawn(const char* modelName, bool max, bool SpawnIn);
	void VehicleMaxUpgrade();
	void VehicleDeleteVehicle();
	void DriveOnWater(bool onOff);
	void LowerVehicle();
	void TeleportToCoords(double x, double y, double z);
	void RecoverySetLevel(int character, int level);
	void RecoveryDropCash(uint32_t Splayer, int Delay, int Amount);
	void EditStat(const char* STAT, int value);
	void UnlockHeist();
	void RemoveReports();
	void StartAnimation(const char* animation, const char* animationId);
}

#define VK_NOTHING	0x00				/*NULL*/
#define VK_KEY_0	0x30                //('0')	0
#define VK_KEY_1	0x31                //('1')	1
#define VK_KEY_2	0x32                //('2')	2
#define VK_KEY_3	0x33                //('3')	3
#define VK_KEY_4	0x34                //('4')	4
#define VK_KEY_5	0x35                //('5')	5
#define VK_KEY_6	0x36                //('6')	6
#define VK_KEY_7	0x37                //('7')	7
#define VK_KEY_8	0x38                //('8')	8
#define VK_KEY_9	0x39                //('9')	9
#define VK_KEY_A	0x41                //('A')	A
#define VK_KEY_B	0x42                //('B')	B
#define VK_KEY_C	0x43                //('C')	C
#define VK_KEY_D	0x44                //('D')	D
#define VK_KEY_E	0x45                //('E')	E
#define VK_KEY_F	0x46                //('F')	F
#define VK_KEY_G	0x47                //('G')	G
#define VK_KEY_H	0x48                //('H')	H
#define VK_KEY_I	0x49                //('I')	I
#define VK_KEY_J	0x4A                //('J')	J
#define VK_KEY_K	0x4B                //('K')	K
#define VK_KEY_L	0x4C                //('L')	L
#define VK_KEY_M	0x4D                //('M')	M
#define VK_KEY_N	0x4E                //('N')	N
#define VK_KEY_O	0x4F                //('O')	O
#define VK_KEY_P	0x50                //('P')	P
#define VK_KEY_Q	0x51                //('Q')	Q
#define VK_KEY_R	0x52                //('R')	R
#define VK_KEY_S	0x53                //('S')	S
#define VK_KEY_T	0x54                //('T')	T
#define VK_KEY_U	0x55                //('U')	U
#define VK_KEY_V	0x56                //('V')	V
#define VK_KEY_W	0x57                //('W')	W
#define VK_KEY_X	0x58                //('X')	X
#define VK_KEY_Y	0x59                //('Y')	Y
#define VK_KEY_Z	0x5A                //('Z')	Z
