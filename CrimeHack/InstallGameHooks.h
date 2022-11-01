typedef NTSTATUS(__stdcall* ptrLdrLoadDll)(PWCHAR PathToFile, ULONG Flags, PUNICODE_STRING ModuleFileName, PHANDLE ModuleHandle);
ptrLdrLoadDll callLdrLoadDll = nullptr;
NTSTATUS __stdcall hkLdrLoadDll(PWCHAR PathToFile, ULONG Flags, PUNICODE_STRING ModuleFileName, PHANDLE ModuleHandle)
{
    NTSTATUS sts = callLdrLoadDll(PathToFile, Flags, ModuleFileName, ModuleHandle);
    std::wstring wstrModuleFileName = std::wstring(ModuleFileName->Buffer, ModuleFileName->Length);
    if (w_findStringIC(wstrModuleFileName, xorstr_(L"client.dll")) && !AllowTuning)
    {
        FuckArthemidaIntegrity(xorstr_("core.dll")); SigScan scan; MessageBeep(MB_ICONASTERISK);
        sendMTAChat = (f_SendChat)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x81\xEC\x00\x00\x00\x00\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xF0\x56\x57\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x80\x7D\x14\x00\x8B\x75\x0C\x8B\x7D\x08\x89\xB5\x00\x00\x00\x00\x0F\x85\x00\x00\x00\x00\x80\x7D\x10\x00\x75\x1A\x68\x00\x00\x00\x00\x57\xE8\x00\x00\x00\x00\x83\xC4\x08"),
        xorstr_("xxxxxx????xx????xxx????x????xxxxxxxxxxxxx????xxxxxxxxxxxx????xx????xxxxxxx????xx????xxx"));
        if (sendMTAChat) LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to ExecCommand!\n"));
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a signature for ExecCommand!\n"));
        callGetClosestRemotePlayer = (ptrGetClosestRemotePlayer)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x83\xE4\xF8\x83\xEC\x1C\x8B"),
        xorstr_("xxxxxxxxxx")); // 1.5.8-1.5.9
        if (callGetClosestRemotePlayer) LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to GetClosestRemotePlayer!\n"));
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a signature for GetClosestRemotePlayer!\n"));
        if (callProcessMessage == nullptr)
        {
            callProcessMessage = (ptrProcessMessage)scan.FindPattern(xorstr_("core.dll"),
            xorstr_("\x55\x8B\xEC\x81\xEC\x14\x02"), xorstr_("xxxxxxx"));
            if (callProcessMessage != nullptr)
            {
                LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to ProcessMessage!\n"));
                MH_CreateHook(callProcessMessage, &ProcessMessage, reinterpret_cast<LPVOID*>(&callProcessMessage));
                MH_EnableHook(MH_ALL_HOOKS);
            }
            else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a signature for ProcessMessage.\n"));
        }
        if (callForceCursorVisible == nullptr)
        {
            callForceCursorVisible = (ptrForceCursorVisible)scan.FindPattern(xorstr_("core.dll"),
            xorstr_("\x55\x8B\xEC\x8A\x45\x0C\xFF\x75\x08\x88\x81\x00\x00\x00\x00\x8B\x49\x0C\xE8\x00\x00\x00\x00\x5D\xC2\x08\x00"),
            xorstr_("xxxxxxxxxxx????xxxx????xxxx"));
            if (callForceCursorVisible != NULL)
            {
                LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to ForceCursorVisible!\n"));
                MH_CreateHook(callForceCursorVisible, &ForceCursorVisible, reinterpret_cast<LPVOID*>(&callForceCursorVisible));
                MH_EnableHook(MH_ALL_HOOKS);
            }
            else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a signature for ForceCursorVisible.\n"));
        }
        callSendBulletSyncFire = (ptrSendBulletSyncFire)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x51\x8B\x45\x08\x0F"), xorstr_("xxxxxxxx"));
        if (callSendBulletSyncFire != nullptr)
        {
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to SendBulletSyncFire!\n"));
            MH_RemoveHook(callSendBulletSyncFire);
            MH_CreateHook(callSendBulletSyncFire, &SendBulletSyncFire, reinterpret_cast<LPVOID*>(&callSendBulletSyncFire));
            MH_EnableHook(MH_ALL_HOOKS);
        }
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a signature for SendBulletSyncFire.\n"));
        callCClientStreamer = (ptrCClientStreamer)scan.FindPattern("client.dll",
        xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x83\xEC\x1C\x53\x56\x57\xA1\x00\x00\x00\x00\x33\xC5\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x8B\xF1\x89\x75\xF0\xF3"),
        xorstr_("xxxxxx????xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxx"));
        if (callCClientStreamer != nullptr)
        {
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to CClientStreamer!\n"));
            MH_CreateHook(callCClientStreamer, &CClientStreamer, reinterpret_cast<LPVOID*>(&callCClientStreamer));
            MH_EnableHook(MH_ALL_HOOKS);
        }
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a signature for CClientStreamer.\n"));
        callTakePlayerScreenShot = (ptrTakePlayerScreenShot)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x83\xEC\x60\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xF0\x56\x57\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x89"),
        xorstr_("xxxxxx????xxxxxxxxxxx????xxxxxxxxxxxxxxxxxx"));
        if (callTakePlayerScreenShot != nullptr)
        {
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to TakePlayerScreenShot!\n"));
            MH_RemoveHook(callTakePlayerScreenShot);
            MH_CreateHook(callTakePlayerScreenShot, &TakePlayerScreenShot, reinterpret_cast<LPVOID*>(&callTakePlayerScreenShot));
            MH_EnableHook(MH_ALL_HOOKS);
        }
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a sig for TakePlayerScreenShot.\n"));
        callAddDebugHook = (ptrAddDebugHook)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x81\xEC\xF8\x00\x00\x00\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xF0\x56\x57\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x8B\x75"),
        xorstr_("xxxxxx????xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxx"));
        if (callAddDebugHook != NULL)
        {
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to AddDebugHook!\n"));
            MH_RemoveHook(callAddDebugHook);
            MH_CreateHook(callAddDebugHook, &AddDebugHook, reinterpret_cast<LPVOID*>(&callAddDebugHook));
            MH_EnableHook(MH_ALL_HOOKS);
        }
        else
        {
            LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a sig for AddDebugHook! TERMINATING GAME...\n"));
            TerminateProcess(GetCurrentProcess(), 0x0);
        }
        callLuaLoadBuffer = (t_LuaLoadBuffer)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x83\xEC\x08\x56\x8B\x75\x0C\x57\xFF"), xorstr_("xxxxxxxxxxxx"));
        if (callLuaLoadBuffer != nullptr)
        {
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to Lua Engine!\n"));
            lua_only_once = false;
            MH_RemoveHook(callLuaLoadBuffer);
            MH_CreateHook(callLuaLoadBuffer, &hkLuaLoadBuffer, reinterpret_cast<LPVOID*>(&callLuaLoadBuffer));
            MH_EnableHook(MH_ALL_HOOKS);
            /*if (myRank.showTitle)
            {
                if (ranksThread != nullptr)
                {
                    TerminateThread(ranksThread, 0x0);
                    ranksThread = nullptr; ranksThreadID = NULL;
                }
                ranksThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SyncAllRanks, 0, 0, &ranksThreadID);
            }*/
        }
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a sig for Lua Engine.\n"));
		callGetHealth = (ptrGetHealth)scan.FindPattern(xorstr_("client.dll"), xorstr_("\x80\xB9\xC8"), xorstr_("xxx")); // 1.5.8
        if (callGetHealth == nullptr) callGetHealth = (ptrGetHealth)scan.FindPattern(xorstr_("client.dll"), 
        xorstr_("\x55\x8B\xEC\x51\x8B\x91\xAC\x01\x00\x00\x85\xD2\x74\x16\x8B\x02\x8B\xCA\x8B\x80\x3C"), 
        xorstr_("xxxxxxxxxxxxxxxxxxxxx")); // 1.5.9
		if (callGetHealth != nullptr)
		{
			MH_RemoveHook(callGetHealth);
			MH_CreateHook(callGetHealth, &GetHealth, reinterpret_cast<LPVOID*>(&callGetHealth));
			MH_EnableHook(MH_ALL_HOOKS);
            LogInFile(LOG_NAME, "[PLUGIN] Found address from signature to GetHealth!\n");
		}
        else LogInFile(LOG_NAME, "[ERROR] Can`t find a sig to GetHealth.\n");
        callTriggerServerEvent = (ptrTriggerServerEvent)scan.FindPattern("client.dll",
        "\x55\x8B\xEC\x51\x8B\x45\x04\x50\xE8\x00\x00\x00\x00\x83\xC4\x04\x84\xC0\x75\x0A\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x53\x56\x57",
        "xxxxxxxxx????xxxxxxxxxxxxxxxxxxxx");
        if (callTriggerServerEvent != nullptr)
        {
            MH_RemoveHook(callTriggerServerEvent);
            MH_CreateHook(callTriggerServerEvent, &TriggerServerEvent, reinterpret_cast<LPVOID*>(&callTriggerServerEvent));
            MH_EnableHook(MH_ALL_HOOKS);
            LogInFile(LOG_NAME, "[PLUGIN] Found address from signature to TriggerServerEvent!\n");
        }
        else LogInFile(LOG_NAME, "[ERROR] Can`t find a sig to TriggerServerEvent.\n");
        if (callRecalculateFrameRateLimit == nullptr)
        {
            callRecalculateFrameRateLimit = (ptrRecalculateFrameRateLimit)scan.FindPattern(xorstr_("core.dll"),
            xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x83\xEC\x50\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xF0\x56\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x8B\xF1"),
            xorstr_("xxxxxx????xxxxxxxxxxx????xxxxxxxxxxxxxxxxxx")); // 1.5.8
            if (callRecalculateFrameRateLimit == nullptr) callRecalculateFrameRateLimit = (ptrRecalculateFrameRateLimit)
            scan.FindPattern(xorstr_("core.dll"),
            xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x83\xEC\x50\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xF0\x56\x57\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x8B\xF1"),
            xorstr_("xxxxxx????xxxxxxxxxxx????xxxxxxxxxxxxxxxxxxx")); // 1.5.9
            if (callRecalculateFrameRateLimit != nullptr)
            {
                MH_RemoveHook(callRecalculateFrameRateLimit);
                MH_CreateHook(callRecalculateFrameRateLimit, &RecalculateFrameRateLimit, reinterpret_cast<LPVOID*>(&callRecalculateFrameRateLimit));
                MH_EnableHook(MH_ALL_HOOKS);
                LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to RecalculateFrameRateLimit!\n"));
            }
            else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a sig for RecalculateFrameRateLimit.\n"));
        }
        callStartGame = (ptrStartGame)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x81\xEC\xB4\x01"),
        xorstr_("xxxxxx????xxxxxxxxxxx"));
        if (callStartGame != nullptr)
        {
            MH_RemoveHook(callStartGame);
            MH_CreateHook(callStartGame, &StartGame, reinterpret_cast<LPVOID*>(&callStartGame));
            MH_EnableHook(MH_ALL_HOOKS);
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to StartGame!\n"));
        }
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a sig for StartGame.\n"));
        callGetRotationRadians = (ptrGetRotationRadians)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x83\xEC\x30\x53\x56\x8B\xF1\x8D"), xorstr_("xxxxxxxxxxx"));
        if (callGetRotationRadians != nullptr)
        {
            MH_RemoveHook(callGetRotationRadians);
            MH_CreateHook(callGetRotationRadians, &GetRotationRadians, reinterpret_cast<LPVOID*>(&callGetRotationRadians));
            MH_EnableHook(MH_ALL_HOOKS);
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to GetRotationRadians!\n"));
        }
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a sig for GetRotationRadians.\n"));
        callPedGetPosition = (ptrPedGetPosition)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x57\x8B\xF9\x8B\x8F\x00\x00\x00\x00\x85\xC9\x74\x2B\x8B\x41\x04\x83\xC1\x04\x8B\x40\x0C\x03\xC8\x8B\x01\xFF\x50\x10\x85\xC0\x74\x17\x8B\x48\x04\x83\xC0\x04\x8B\x49\x04\x03\xC8\x8B\x01\xFF\x90\x00\x00\x00\x00\x8B\xC8\xEB\x02"),
        xorstr_("xxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx")); // 1.5.8
        if (callPedGetPosition == nullptr) callPedGetPosition = (ptrPedGetPosition)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x57\x8B\xF9\x8B\x8F\xAC\x01\x00\x00\x85\xC9\x74\x29"),
        xorstr_("xxxxxxxxxxxxxxxx")); // 1.5.9
        if (callPedGetPosition != nullptr)
        {
            MH_RemoveHook(callPedGetPosition);
            MH_CreateHook(callPedGetPosition, &PedGetPosition, reinterpret_cast<LPVOID*>(&callPedGetPosition));
            MH_EnableHook(MH_ALL_HOOKS);
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to PedGetPosition!\n"));
        }
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a signature for PedGetPosition.\n"));
        callVehGetPosition = (ptrVehGetPosition)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x83\xEC\x2C\x53\x56\x57\xA1\x00\x00\x00\x00\x33\xC5\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x8B\xF9\x80\xBF\xA8"),
        xorstr_("xxxxxx????xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxx")); // 1.5.8
        if (callVehGetPosition == nullptr) callVehGetPosition = (ptrVehGetPosition)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x83\xEC\x2C\x53\x56\x57\xA1\x00\x00\x00\x00\x33\xC5\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x8B\xF9\x80\xBF\xB0"),
        xorstr_("xxxxxx????xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxx")); // 1.5.9
        if (callVehGetPosition != nullptr)
        {
            MH_RemoveHook(callVehGetPosition);
            MH_CreateHook(callVehGetPosition, &VehGetPosition, reinterpret_cast<LPVOID*>(&callVehGetPosition));
            MH_EnableHook(MH_ALL_HOOKS);
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to VehGetPosition!\n"));
        }
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a signature for VehGetPosition.\n"));
        callVehGetMoveSpeed = (ptrVehGetMoveSpeed)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x8B\xC1\x80"), xorstr_("xxxxxx"));
        if (callVehGetMoveSpeed != nullptr)
        {
            MH_RemoveHook(callVehGetMoveSpeed);
            MH_CreateHook(callVehGetMoveSpeed, &VehGetMoveSpeed, reinterpret_cast<LPVOID*>(&callVehGetMoveSpeed));
            MH_EnableHook(MH_ALL_HOOKS);
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to VehGetMoveSpeed!\n"));
        }
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a signature for VehGetMoveSpeed.\n"));
        callSetTrafficLightState = (ptrSetTrafficLightState)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x8B\x55\x08\x80\xFA\x0A"), xorstr_("xxxxxxxxx"));
        if (callSetTrafficLightState != nullptr)
        {
            MH_RemoveHook(callSetTrafficLightState);
            MH_CreateHook(callSetTrafficLightState, &SetTrafficLightState, reinterpret_cast<LPVOID*>(&callSetTrafficLightState));
            MH_EnableHook(MH_ALL_HOOKS);
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to SetTrafficLightState!\n"));
        }
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a signature for SetTrafficLightState.\n"));
        callSetTrafficLightsLocked = (ptrSetTrafficLightsLocked)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x8B\x00\x00\x00\x00\x00\xFF\x75\x08\x8B\x01\xFF\x90\x04\x02"),
        xorstr_("xxxx?????xxxxxxxxx")); // 1.5.8
        if (callSetTrafficLightsLocked == nullptr) callSetTrafficLightsLocked = (ptrSetTrafficLightsLocked)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x8B\x00\x00\x00\x00\x00\xFF\x75\x08\x8B\x01\xFF\x90\x10"),
        xorstr_("xxxx?????xxxxxxxx")); // 1.5.9
        if (callSetTrafficLightsLocked != nullptr)
        {
            MH_RemoveHook(callSetTrafficLightsLocked);
            MH_CreateHook(callSetTrafficLightsLocked, &SetTrafficLightsLocked, reinterpret_cast<LPVOID*>(&callSetTrafficLightsLocked));
            MH_EnableHook(MH_ALL_HOOKS);
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to SetTrafficLightsLocked!\n"));
        }
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a signature for SetTrafficLightsLocked.\n"));
        callSetElementPosition = (ptrSetElementPosition)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x83\xEC\x10\x57\x8B\x7D\x0C\x8D"), xorstr_("xxxxxxxxxxx")); // 1.5.9
        if (callSetElementPosition == nullptr) callSetElementPosition = (ptrSetElementPosition)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x83\xEC\x10\x57\x8B\x7D\x0C"), xorstr_("xxxxxxxxxx")); // 1.5.8
        if (callSetElementPosition != nullptr)
        {
            MH_RemoveHook(callSetElementPosition);
            MH_CreateHook(callSetElementPosition, &SetElementPosition, reinterpret_cast<LPVOID*>(&callSetElementPosition));
            MH_EnableHook(MH_ALL_HOOKS);
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to SetElementPosition!\n"));
        }
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a signature for SetElementPosition.\n"));
        /*callAddEventHandler = (ptrAddEventHandler)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x56\x8B\x75\x0C\x85\xF6\x75\x06\x89\x35\x00\x00\x00\x00\x8B\x00\x00\x00\x00\x00\x56\xE8\x00\x00\x00\x00\x85\xC0\x74\x28"), 
        xorstr_("xxxxxxxxxxxxxxxxxx?????xx????xxxx")); // 1.5.9
        if (callAddEventHandler != nullptr)
        {
            MH_RemoveHook(callAddEventHandler);
            MH_CreateHook(callAddEventHandler, &AddEventHandler, reinterpret_cast<LPVOID*>(&callAddEventHandler));
            MH_EnableHook(MH_ALL_HOOKS);
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to AddEventHandler!\n"));
        }
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a signature for AddEventHandler.\n"));
        callForceAddUpgrade = (ptrForceAddUpgrade)scan.FindPattern(xorstr_("client.dll"),
        xorstr_("\x55\x8B\xEC\x83\xEC\x08\x8D\x45\xFF"),
        xorstr_("xxxxxxxxx")); // 1.5.8
        if (callForceAddUpgrade != nullptr)
        {
            MH_RemoveHook(callForceAddUpgrade);
            MH_CreateHook(callForceAddUpgrade, &ForceAddUpgrade, reinterpret_cast<LPVOID*>(&callForceAddUpgrade));
            MH_EnableHook(MH_ALL_HOOKS);
            LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to ForceAddUpgrade!\n"));
        }
        else LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a signature for ForceAddUpgrade.\n"));*/
        AllowTuning = true;
    }
    return sts;
}
using PresentSignature = HRESULT(__stdcall*)(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);
using ResetSignature = HRESULT(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
std::uintptr_t find_device(std::uint32_t Len) 
{
    static std::uintptr_t base = [](std::size_t Len) 
    {
        std::string path_to(MAX_PATH, '\0');
        if (auto size = GetSystemDirectoryA(path_to.data(), MAX_PATH)) 
        {
            path_to.resize(size);
            path_to += "\\d3d9.dll";
            std::uintptr_t dwObjBase = reinterpret_cast<std::uintptr_t>(LoadLibraryA(path_to.c_str()));
            while (dwObjBase++ < dwObjBase + Len) 
            {
                if (*reinterpret_cast<std::uint16_t*>(dwObjBase + 0x00) == 0x06C7 &&
                *reinterpret_cast<std::uint16_t*>(dwObjBase + 0x06) == 0x8689 &&
                *reinterpret_cast<std::uint16_t*>(dwObjBase + 0x0C) == 0x8689) 
                {
                    dwObjBase += 2;
                    break;
                }
            }
            return dwObjBase;
        }
        return std::uintptr_t(0);
    }(Len);
    return base;
}
void* get_function_address(int VTableIndex) 
{
    return (*reinterpret_cast<void***>(find_device(0x128000)))[VTableIndex];
}
kthook::kthook_signal<PresentSignature> present_hook{ get_function_address(17) };
kthook::kthook_signal<ResetSignature> reset_hook{ get_function_address(16) };
LPDIRECT3DTEXTURE9 texture;
#include "DrawMenu.h" // Render our menu
std::optional<HRESULT> on_lost(const decltype(reset_hook)& hook, IDirect3DDevice9* device_ptr, D3DPRESENT_PARAMETERS* parameters) 
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    return std::nullopt;
}
void on_reset(const decltype(reset_hook)& hook, HRESULT& return_value, IDirect3DDevice9* device_ptr, D3DPRESENT_PARAMETERS* parameters)
{

}
void InstallDx9Hooks()
{
    present_hook.before += on_present;
    reset_hook.before += on_lost;
    reset_hook.after += on_reset;
}