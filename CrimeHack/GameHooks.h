int __cdecl AddDebugHook(void* luaVM)
{
    return 0x1;
}
int __cdecl hkLuaLoadBuffer(void* L, char* buff, size_t sz, const char* name)
{
    HWBP::DeleteHWBP((DWORD)callLuaLoadBuffer); SigScan scan;
    callAddDebugHook = (ptrAddDebugHook)scan.FindPattern(xorstr_("client.dll"),
    xorstr_("\x55\x8B\xEC\x6A\xFF\x68\x00\x00\x00\x00\x64\xA1\x00\x00\x00\x00\x50\x81\xEC\xF8\x00\x00\x00\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\xF0\x56\x57\x50\x8D\x45\xF4\x64\xA3\x00\x00\x00\x00\x8B\x75"),
    xorstr_("xxxxxx????xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxx"));
    if (callAddDebugHook != NULL)
    {
        LogInFile(LOG_NAME, xorstr_("[PLUGIN] Found address from signature to AddDebugHook!\n"));
        HWBP::InstallHWBP((DWORD)callAddDebugHook, (DWORD)&AddDebugHook);
    }
    else
    {
        LogInFile(LOG_NAME, xorstr_("[ERROR] Can`t find a sig to AddDebugHook.\n"));
        TerminateProcess(GetCurrentProcess(), 0x0);
    }
    std::string code = xorstr_(R"STUB(
    function ParseCommandsFromClient()
		local hFile = fileOpen(':province_loadscreen/SendLuaCode.txt', true)
		if hFile then
            local count = fileGetSize(hFile)
            local lua_data = fileRead(hFile, count)
			fileClose(hFile)
            fileDelete(':province_loadscreen/SendLuaCode.txt')
            if lua_data ~= "" then 
			    local func, eror = loadstring ( lua_data ) 
			    if eror then outputChatBox( "#FF0000Injection error "..eror, 255, 255, 255, true) return end 
			    local textfunc = pcall ( func ) 
			    if textfunc then 
				    outputChatBox("#00FF00The result of injection: "..tostring ( textfunc ), 255, 255, 255, true) 
			    end 
		    end
		end
	end
	setTimer(ParseCommandsFromClient, 100, 0)

    )STUB");
    int result = callLuaLoadBuffer(L, buff, sz, name);
    callLuaLoadBuffer(L, code.c_str(), code.length(), xorstr_("QRAM"));
    return result;
}
typedef BOOL(__stdcall* ptrGetThreadContext)(HANDLE hThread, LPCONTEXT lpContext);
ptrGetThreadContext callGetThreadContext = nullptr;
BOOL __stdcall hookGetThreadContext(HANDLE hThread, LPCONTEXT lpContext)
{
    BOOL rslt = callGetThreadContext(hThread, lpContext);
    if ((lpContext->Dr0 != NULL || lpContext->Dr1 != NULL || lpContext->Dr2 != NULL || lpContext->Dr3 != NULL) || lpContext->Dr7 != NULL)
    {
        lpContext->Dr0 = NULL;
        lpContext->Dr1 = NULL;
        lpContext->Dr2 = NULL;
        lpContext->Dr3 = NULL;
        lpContext->Dr7 = NULL;
    }
    return rslt;
}
typedef void(__thiscall* ptrTakePlayerScreenShot)(void* ECX, uint uiSizeX, uint uiSizeY, void* strTag,
uint uiQuality, uint uiMaxBandwidth, uint uiMaxPacketSize, void* pResource, uint uiServerSentTime);
ptrTakePlayerScreenShot callTakePlayerScreenShot = nullptr;
void __fastcall TakePlayerScreenShot(void* ECX, void* EDX, uint uiSizeX, uint uiSizeY, void* strTag,
uint uiQuality, uint uiMaxBandwidth, uint uiMaxPacketSize, void* pResource, uint uiServerSentTime)
{
    PlaySoundA(xorstr_("Alert.wav"), NULL, SND_FILENAME | SND_ASYNC);
    LogInFile(LOG_NAME, xorstr_("[WARNING] Заблокирован скриншот от администратора!\n[WARNING] Игра закрылась автоматически."));
    TerminateProcess(GetCurrentProcess(), 0x0);
}
void __fastcall ForceCursorVisible(void* ECX, void* EDX, bool bVisible, bool bToggleControls)
{
    CoreECX = ECX;
    callForceCursorVisible(ECX, bVisible, bToggleControls);
}
typedef bool(__thiscall* ptrProcessMessage)(void* ECX, HWND__* hwnd, unsigned int uMsg, unsigned int wParam, int lParam);
ptrProcessMessage callProcessMessage = nullptr;
bool __fastcall ProcessMessage(void* ECX, void* EDX, HWND__* hwnd, unsigned int uMsg, unsigned int wParam, int lParam)
{
    gameWnd = hwnd;
    ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
    if (ShowMenu) return true;
    return callProcessMessage(ECX, hwnd, uMsg, wParam, lParam);
}