#pragma once
#pragma warning(disable : 4731)
#define HOOKPOS_PlayerCollision 0x0054BCEE
#define AGENT_NAME xorstr_("CR1M3H")
#define LOG_NAME xorstr_("CrimeHack.log")
#define PLUGIN_VER xorstr_("V1.2 ALPHA")
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <direct.h>
#include <algorithm>
#include <optional>
#include <ctime>
#include <cwctype>
#include <codecvt>
#include "xorstr.h"
#include "MD5.h"
#include "VMProtectSDK.h"
#include <comdef.h>
#include "Collision.h"
#include <wininet.h>
#include "HWBP.h"
#include <Wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Wininet.lib")
bool SpeedHack = false;
float MaxSpd = 250.0f;
bool airBrake = false;
bool TotalCar = false;
char upd_txt[3000];
bool AirAllowed = false;
bool CarGM = false;
bool LuaAllowed = false;
bool DeadlyAura = false;
bool SilentAIM = false;
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
bool ShowMenu = false;
char LuaCode[10000];
bool DbgHook = true;
std::vector<std::string> PlayersList;
std::string ActorNick, VictimNick;
std::string LastVictimID;
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
			std::string host_lnk = xorstr_("kuprey123.beget.tech");
			char params[3000]; memset(params, 0, sizeof(params));
			sprintf(params, xorstr_("hwid=%s"), total_hwid.c_str());
			std::string sc_ans = SendInetRequest(P_HTTP, M_GET, host_lnk, xorstr_("crime_hack/security.php"), std::string(params), true);
			if (sc_ans.find(total_hwid) != std::string::npos)
			{
				LogInFile(LOG_NAME, xorstr_("[PLUGIN] Пошел нахуй :)\n"));
				delete reg; DeadCode();
			}
			memset(params, 0, sizeof(params));
			sprintf(params, xorstr_("soft_ver=%s"), PLUGIN_VER);
			sc_ans = SendInetRequest(P_HTTP, M_GET, host_lnk, xorstr_("crime_hack/check_update.php"), std::string(params), true);
			memset(upd_txt, 0, sizeof(upd_txt));
			strcpy(upd_txt, sc_ans.c_str());
			if (LF_Key.find(RegisteredKey.c_str()) == std::string::npos)
			{
				if (DM_Key.find(RegisteredKey.c_str()) == std::string::npos)
				{
					LogInFile(LOG_NAME, xorstr_("[PLUGIN] HWID: %s\n"), total_hwid.c_str());
					delete reg; DeadCode();
				}
				else CreateMutexA(NULL, FALSE, xorstr_("RBHVG5LBM1XT5J"));
			}
			else CreateMutexA(NULL, FALSE, xorstr_("RBZVX5S1MXAZ4A"));
		}
		else
		{
			LogInFile(LOG_NAME, xorstr_("[PLUGIN] HWID: %s\n"), total_hwid.c_str());
			reg->WriteString(xorstr_("RegisteredKey"), xorstr_("NONE"));
			delete reg; DeadCode();
		}
		if (reg != nullptr) delete reg;
	}
	VMProtectEnd();
}
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