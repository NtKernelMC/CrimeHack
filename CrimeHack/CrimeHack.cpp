#ifndef _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#endif
#pragma warning(disable : 4477)
#pragma warning(disable : 4244)
#pragma warning (disable : 4305)
#pragma warning (disable : 4018)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include "plugin.h"
#include "CPools.h"
#include "common.h"
#include "CGeneral.h"
#include "CTrain.h"
#include "CWorld.h"
#include "CRunningScript.h"
#include "extensions/ScriptCommands.h"
#include "CCam.h"
#include "CCamera.h"
#include <cmath>
#include <windows.h>
#include <thread>
#include <stdio.h>
#include <direct.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <tuple>
#include <mutex>
#include "Registry.h"
#include "xorstr.h"
#include "PebHider.h"
#include "MinHook.h"
#include <winternl.h>
#include "sigscan.h"
#include "resource.h"
#include "kthook/kthook.hpp" //github.com/KiN4StAt/kthook
#include <D3dx9tex.h>
#pragma comment(lib, "D3dx9.lib")
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
bool ColHack = false;
#include "PluginUtils.h"
#pragma comment(lib, "libMinHook.x86.lib")
#pragma comment(lib, "Winmm.lib")
using namespace plugin;
#include "GameHooks.h"
#include "InstallGameHooks.h"
extern "C" __declspec(dllexport) int NextHook(int code, WPARAM wParam, LPARAM lParam)
{
    return CallNextHookEx(NULL, code, wParam, lParam);
}
float VecLength(CVector vec) { return sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)); }
float getVehElementSpeed(CVehicle* theElement)
{
    if (theElement == nullptr) return 0.0f;
    float mult = 111.84681456f;
    CVector vecSpeed = theElement->m_vecMoveSpeed;
    return VecLength(vecSpeed * mult);
}
bool setVehElementSpeed(CVehicle* element, float speed)
{
    if (element == nullptr) return false;
    float acSpeed = getVehElementSpeed(element);
    if (acSpeed && acSpeed != 0)
    {
        float diff = speed / acSpeed;
        if (diff != diff) return false;
        CVector vel = element->m_vecMoveSpeed;
        element->m_vecMoveSpeed.x = vel.x * diff;
        element->m_vecMoveSpeed.y = vel.y * diff;
        element->m_vecMoveSpeed.z = vel.z * diff;
        return true;
    }
    return false;
}
void HackThread()
{
    VMProtectBegin("HackThread()");
    MakePreInit();
    VMProtectEnd();
    MH_Initialize();
    CEasyRegistry* reg = new CEasyRegistry(HKEY_CURRENT_USER, xorstr_("Software\\CR1M3H"), true);
    if (reg != nullptr)
    {
        LuaAllowed = reg->ReadInteger(xorstr_("AllowLua"));
        delete reg;
    }
    LogInFile(LOG_NAME, xorstr_("[PLUGIN] Crime Hack %s by NtKernelMC loaded!\n"), PLUGIN_VER);
    InstallDx9Hooks();
    std::thread tth(AirBreak); tth.detach();
    callGetThreadContext = (ptrGetThreadContext)GetProcAddress(GetModuleHandleA(xorstr_("kernel32.dll")), xorstr_("GetThreadContext"));
    if (callGetThreadContext != nullptr)
    {
        MH_CreateHook(callGetThreadContext, &hookGetThreadContext, reinterpret_cast<LPVOID*>(&callGetThreadContext));
        MH_EnableHook(MH_ALL_HOOKS);
    }
    if (*(BYTE*)HOOKPOS_PlayerCollision != 0xE9)
    {
        LogInFile(LOG_NAME, xorstr_("[LOG] Installed collision hook!\n"));
        MakeJump((DWORD)HOOKPOS_PlayerCollision, (DWORD)&HOOK_PlayerCollision, col_prologue, 6);
    }
    std::thread ReHook(ReHooker); ReHook.detach(); // поток для авто-восстановления хука если его снимет античит
    callLdrLoadDll = (ptrLdrLoadDll)GetProcAddress(GetModuleHandleA(xorstr_("ntdll.dll")), xorstr_("LdrLoadDll"));
    if (callLdrLoadDll != nullptr)
    {
        MH_CreateHook(callLdrLoadDll, &hkLdrLoadDll, reinterpret_cast<LPVOID*>(&callLdrLoadDll));
        MH_EnableHook(MH_ALL_HOOKS);
    }
    callLdrUnloadDll = (ptrLdrUnloadDll)GetProcAddress(GetModuleHandleA(xorstr_("ntdll.dll")), xorstr_("LdrUnloadDll"));
    if (callLdrLoadDll != nullptr)
    {
        MH_CreateHook(callLdrUnloadDll, &hkLdrUnloadDll, reinterpret_cast<LPVOID*>(&callLdrUnloadDll));
        MH_EnableHook(MH_ALL_HOOKS);
    }
    while (true)
    {
        if (GetAsyncKeyState(VK_F10) && GetModuleHandleA(xorstr_("client.dll")))
        {
            ShowMenu ^= true; NoScreen ^= true;
            if (ShowMenu) callForceCursorVisible(CoreECX, true, true);
            else callForceCursorVisible(CoreECX, false, false);
            Sleep(1000);
        }
        if (GetAsyncKeyState(VK_CONTROL) && SpeedHack && GetModuleHandleA(xorstr_("client.dll")))
        {
            CVehicle* veh = FindPlayerVehicle(0, false);
            if (veh != nullptr) setVehElementSpeed(veh, MaxSpd);
        }
        Sleep(150);
    }
}
class PlayerCloner 
{
public:
    PlayerCloner() 
    {
        DeleteFileA(xorstr_("texture.jpg")); DeleteFileA(xorstr_("Shrift.otf")); DeleteFileA(xorstr_("Alert.wav"));
        DropResource(xorstr_("texture.jpg"), MAKEINTRESOURCEA(IDR_RCDATA1), RT_RCDATA);
        DropResource(xorstr_("Shrift.otf"), MAKEINTRESOURCEA(IDR_RCDATA2), RT_RCDATA);
        DropResource(xorstr_("Alert.wav"), MAKEINTRESOURCEA(IDR_WAVE1), xorstr_("WAVE"));
        PebHider::RemovePeHeader(GetModuleHandleA(xorstr_("Crime.SA.dll")));
        PebHider::UnlinkModule(xorstr_("Crime.SA.dll"));
        std::thread th(HackThread);
        th.detach();
    }
} playerCloner;
