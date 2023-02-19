typedef bool(__cdecl* ptrTriggerServerEvent)(const char* szName, void* CallWithEntity, void* Arguments);
ptrTriggerServerEvent callTriggerServerEvent = nullptr;
void __cdecl TriggerServerEvent(const char* szName, void* CallWithEntity, void* Arguments)
{
	bool skip_call = false;
	LogInFile(xorstr_("Trigger.log"), xorstr_("[EVENT]: %s\n"), szName);
	if ((findStringIC(szName, xorstr_("trafficlights:addFine")) || findStringIC(szName, xorstr_("police:check"))) && AntiRed) skip_call = true;
	if (findStringIC(szName, xorstr_("newGps:Teleportation"))) skip_call = true;
	if (findStringIC(szName, xorstr_("SetPlayerCarDamage"))) skip_call = true;
	if (findStringIC(szName, xorstr_("carshop:updateHpInfo"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ac:snd_adm_sp"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ac:b_ch"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ac:snd_adm_jt"))) skip_call = true;
	if (findStringIC(szName, xorstr_("system:updateTlme"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ac:xoxoxo"))) skip_call = true;
	if (findStringIC(szName, xorstr_("festival:initSoundz"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ac:snd_adm_fstammo"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ac:exp"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ac:snd_prj_info"))) skip_call = true;
	if (findStringIC(szName, xorstr_("skybox:checkRainUpdate"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ac:b_rckt"))) skip_call = true;
	if (findStringIC(szName, xorstr_("radial:getSlotContent"))) skip_call = true;
	// another hidden AC events
	if (findStringIC(szName, xorstr_("ot:checkTramsOnLine"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ot:checkBusOnLine"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ot:checkTrollOnLine"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ot:checkCarOnLine"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ot:checkSubOnLine"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ot:checkAirOnLine"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ot:checkWaterOnLine"))) skip_call = true;
	if (findStringIC(szName, xorstr_("menu:timestampCoroutine"))) skip_call = true;
	if (findStringIC(szName, xorstr_("menu:timestampUpd"))) skip_call = true;
	if (findStringIC(szName, xorstr_("menu:gpsCheckpoint"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ot:checkRiverboatOnLine"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ot:updateOTTimer"))) skip_call = true;
	if (findStringIC(szName, xorstr_("ot:resetOTTimer"))) skip_call = true;
	if (findStringIC(szName, xorstr_("menu:getMenuID"))) skip_call = true;
	if (findStringIC(szName, xorstr_("carsystem:getVehState"))) skip_call = true;
	if (findStringIC(szName, xorstr_("carsystem:getMileage"))) skip_call = true;
	if (findStringIC(szName, xorstr_("carsystem:checkPassenger"))) skip_call = true;
	if (findStringIC(szName, xorstr_("carshop:getPanelState"))) skip_call = true;
	if (findStringIC(szName, xorstr_("carshop:getDoorLockedState"))) skip_call = true;
	if (findStringIC(szName, xorstr_("carshop:lockDoorHood"))) skip_call = true;
	if (findStringIC(szName, xorstr_("docs:getSpecialData"))) skip_call = true;
	if (findStringIC(szName, xorstr_("docs:getOchsStatus"))) skip_call = true;
	if (findStringIC(szName, xorstr_("docs:askWorkStatus"))) skip_call = true;
	if (findStringIC(szName, xorstr_("docs:askRestStatus"))) skip_call = true;
	if (findStringIC(szName, xorstr_("bus:initRouteValue"))) skip_call = true;
	if (findStringIC(szName, xorstr_("police:getCuffed"))) skip_call = true;
	if (findStringIC(szName, xorstr_("medic:getCouch"))) skip_call = true;
	if (findStringIC(szName, xorstr_("lift:getElevator"))) skip_call = true;
	//if (findStringIC(szName, xorstr_("autoschool:clearSecretKey"))) skip_call = true;
	if (!skip_call) callTriggerServerEvent(szName, CallWithEntity, Arguments);
}
typedef void (__cdecl *ptrEmbedChunkName)(std::string strChunkName, const char** pcpOutBuffer, unsigned int* puiOutSize);
ptrEmbedChunkName callEmbedChunkName = nullptr;
void __cdecl EmbedChunkName(std::string strChunkName, const char** pcpOutBuffer, unsigned int* puiOutSize)
{
	callEmbedChunkName(strChunkName, pcpOutBuffer, puiOutSize);
	std::string clean_name = CleanScriptName(strChunkName);
	//if (findStringIC(strChunkName, xorstr_("province_autoschool")))
	//{
		static bool just_once = false;
		char cwd[500]; memset(cwd, 0, sizeof(cwd));
		_getcwd(cwd, sizeof(cwd)); strcat(cwd, xorstr_("\\DumpedScripts"));
		if (!just_once)
		{
			if (!IsDirectoryExists(cwd)) CreateDirectoryA(cwd, 0);
			else
			{
				std::filesystem::remove_all(cwd);
					CreateDirectoryA(cwd, 0);
			}
			just_once = true;
		}
		std::string script_path = cwd + std::string(xorstr_("\\")) + clean_name;
		FILE* hFile = fopen(script_path.c_str(), xorstr_("wb"));
		if (hFile != nullptr)
		{
			fwrite(*pcpOutBuffer, 1, *puiOutSize, hFile);
			fclose(hFile);
		}
	//}
}
HANDLE ordSpm = nullptr;
HANDLE ordGet = nullptr;
void OrderSpammer()
{
	while (true)
	{
		if (GetModuleHandleA(xorstr_("client.dll")) && OrderSpam)
		{
			char prepared_path[600]; memset(prepared_path, 0, sizeof(prepared_path));
			sprintf(prepared_path, xorstr_("%s\\ExecCMD.txt"), GetGamePath().c_str());
			FILE* hFile = fopen(prepared_path, xorstr_("a+"));
			if (hFile)
			{
				fprintf(hFile, xorstr_("%d\n%s"), 9099, xorstr_("NONE"));
				fclose(hFile);
			}
			CPed* ped = FindPlayerPed(-1);
			if (ped != nullptr) ped->m_fHealth = 200.0f;
			while (!findStringIC(ReadLastLogLine(), xorstr_("Уведомление: Вы прибыли в указанное место, удачного Вам дня."))) Sleep(30);
		}
		Sleep(65);
	}
}
void OrderAccept()
{
	while (true)
	{
		if (GetModuleHandleA(xorstr_("client.dll")) && FakeTaxi)
		{
			while (!findStringIC(ReadLastLogLine(), xorstr_("Уведомление: Обновлён список заказов."))) Sleep(30);
			char prepared_path[600]; memset(prepared_path, 0, sizeof(prepared_path));
			sprintf(prepared_path, xorstr_("%s\\ExecCMD.txt"), GetGamePath().c_str());
			FILE* hFile = fopen(prepared_path, xorstr_("a+"));
			if (hFile)
			{
				fprintf(hFile, xorstr_("%d\n%s"), 10100, inp_txt20);
				fclose(hFile);
			}
			CPed* ped = FindPlayerPed(-1);
			if (ped != nullptr) ped->m_fHealth = 200.0f;
			while (!findStringIC(ReadLastLogLine(), xorstr_("отправляйтесь к месту заказа"))) Sleep(30);
			hFile = fopen(prepared_path, xorstr_("a+"));
			if (hFile)
			{
				fprintf(hFile, xorstr_("%d\n%s"), 10200, xorstr_("NONE"));
				fclose(hFile);
			}
		}
		Sleep(65);
	}
}
typedef bool(__thiscall* ptrStartGame)(void* ECX, const char* szNick, const char* szPassword, int Type, const char* szSecret);
ptrStartGame callStartGame = nullptr; typedef void CClientGame; CClientGame* classPointer = nullptr;
bool __fastcall StartGame(void* ECX, void* EDX, const char* szNick, const char* szPassword, int Type, const char* szSecret)
{
	AllowTuning = false;
	classPointer = ECX; static bool onlyOnce = false;
	if (!onlyOnce) onlyOnce = true;
	else
	{
		LogInFile(LOG_NAME, xorstr_("Переподключение на сервер запрещено в целях безопасности."));
		TerminateProcess(GetCurrentProcess(), 0x0);
	}
	return callStartGame(ECX, szNick, szPassword, Type, szSecret);
}
void __fastcall SendBulletSyncFire(void* ECX, void* EDX, eWeaponType weaponType, CVector& vecStart, CVector& vecEnd,
float fDamage, BYTE ucHitZone, void* pRemoteDamagedPlayer)
{
	netApi = ECX;
	if (pRemoteDamagedPlayer != nullptr && OneShot)
	{
		for (BYTE x = 0; x < 30; x++) callSendBulletSyncFire(ECX, weaponType, vecStart, vecEnd, fDamage, ucHitZone, pRemoteDamagedPlayer);
	}
	else callSendBulletSyncFire(ECX, weaponType, vecStart, vecEnd, fDamage, ucHitZone, pRemoteDamagedPlayer);
}
void AirBreak()
{
	while (true)
	{
		if (!GetModuleHandleA(xorstr_("client.dll"))) continue;
		static float coordsXforPed = 0.0f;
		static float coordsYforPed = 0.0f;
		static float coordsZforPed = 0.0f;
		static float coordsXforCar = 0.0f;
		static float coordsYforCar = 0.0f;
		static float coordsZforCar = 0.0f;
		static float airSpeed = 0.05f;
		if (GetAsyncKeyState(VK_LSHIFT) && airBrake && AirAllowed)
		{
			airSpeed += 0.02f;
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_LCONTROL) && airBrake && AirAllowed)
		{
			airSpeed -= 0.02f;
			if (airSpeed < 0.05f) airSpeed = 0.05f;
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_RSHIFT) & 1 && AirAllowed)
		{
			if (airBrake) airBrake = false;
			else
			{
				if (*(DWORD*)(0xBA18FC) == 0)
				{
					DWORD PEDSELF = *(DWORD*)0xB6F5F0; //0xB6F5F0
					DWORD MyMatrix = *(DWORD*)(PEDSELF + 0x14);
					coordsXforPed = *(float*)(MyMatrix + 0x30);
					coordsYforPed = *(float*)(MyMatrix + 0x34);
					coordsZforPed = *(float*)(MyMatrix + 0x38);
				}
				if (*(DWORD*)(0xBA18FC) > 0)
				{
					coordsZforCar = 0;
					DWORD CARSELF = *(DWORD*)0xBA18FC; //0xBA18FC
					DWORD car = *(DWORD*)(CARSELF + 0x14);
					coordsXforCar = *(float*)(car + 0x30);
					coordsYforCar = *(float*)(car + 0x34);
					coordsZforCar = *(float*)(car + 0x38);
				}
				airBrake = true;
			}
		}
		if (airBrake && AirAllowed)
		{
			float angle = *(float*)(0xB6F258);
			float airBrkX = 0.0f, airBrkY = 0.0f, airBrkZ = 0.0f;
			if (GetAsyncKeyState(0x57)) // VK_W
			{
				airBrkX = airBrkX - airSpeed * sin(-(angle - 1.5708));
				airBrkY = airBrkY - airSpeed * cos(-(angle - 1.5708));
			}
			if (GetAsyncKeyState(0x53)) // VK_S
			{
				airBrkX = airBrkX + airSpeed * sin(-(angle - 1.5708));
				airBrkY = airBrkY + airSpeed * cos(-(angle - 1.5708));
			}

			if (GetAsyncKeyState(0x41)) // VK_A
			{
				airBrkX = airBrkX - airSpeed * sin(-angle);
				airBrkY = airBrkY - airSpeed * cos(-angle);
			}

			if (GetAsyncKeyState(0x44)) // VK_D
			{
				airBrkX = airBrkX + airSpeed * sin(-angle);
				airBrkY = airBrkY + airSpeed * cos(-angle);
			}

			if (GetAsyncKeyState(VK_UP))
			{
				airBrkZ += airSpeed;
			}

			if (GetAsyncKeyState(VK_DOWN))
			{
				airBrkZ -= airSpeed;
			}

			if (*(DWORD*)(0xBA18FC) > 0)
			{ //машина
				DWORD CARSELF = *(DWORD*)0xBA18FC; //0xBA18FC
				DWORD car = *(DWORD*)(CARSELF + 0x14);

				//скорость 0
				*(float*)(CARSELF + 0x44) = 0;
				*(float*)(CARSELF + 0x48) = 0;
				*(float*)(CARSELF + 0x4C) = 0;

				//полёт
				coordsXforCar += airBrkX;
				coordsYforCar += airBrkY;
				coordsZforCar += airBrkZ;

				*(float*)(car + 0x30) = coordsXforCar;
				*(float*)(car + 0x34) = coordsYforCar;
				*(float*)(car + 0x38) = coordsZforCar;

				*(float*)(CARSELF + 0x50) = 0;
				*(float*)(CARSELF + 0x54) = 0;
				*(float*)(CARSELF + 0x58) = 0;

				//антипереворот
				*(float*)(car + 0x0) = sin(-(angle));
				*(float*)(car + 0x4) = cos(-(angle));
				*(float*)(car + 0x8) = 0;

				//поворот
				*(float*)(car + 0x10) = sin(-(angle + 1.5708));
				*(float*)(car + 0x14) = cos(-(angle + 1.5708));
				*(float*)(car + 0x18) = 0;

			}
			if (*(DWORD*)(0xBA18FC) == 0)
			{
				DWORD PEDSELF = *(DWORD*)0xB6F5F0; //0xB6F5F0
				DWORD MyMatrix = *(DWORD*)(PEDSELF + 0x14);
				//гравитация
				*(float*)(PEDSELF + 0x44) = 0;
				*(float*)(PEDSELF + 0x48) = 0;
				*(float*)(PEDSELF + 0x4C) = 0;

				//анти аним
				*(BYTE*)(PEDSELF + 0x46C) = 3;

				//полёт
				coordsXforPed += airBrkX;
				coordsYforPed += airBrkY;
				coordsZforPed += airBrkZ;

				*(float*)(MyMatrix + 0x30) = coordsXforPed;
				*(float*)(MyMatrix + 0x34) = coordsYforPed;
				*(float*)(MyMatrix + 0x38) = coordsZforPed;
				
			}
		}
		Sleep(1);
	}
}
void __stdcall ReHooker()
{
	while (true)
	{
		if (*(BYTE*)HOOKPOS_PlayerCollision != 0xE9 && GetModuleHandleA(xorstr_("client.dll")))
		{
			MakeJump((DWORD)HOOKPOS_PlayerCollision, (DWORD)&HOOK_PlayerCollision, col_prologue, 6);
		}
		Sleep(100);
	}
}
typedef NTSTATUS(__stdcall* ptrLdrUnloadDll)(HANDLE ModuleHandle);
ptrLdrUnloadDll callLdrUnloadDll = nullptr;
NTSTATUS __stdcall hkLdrUnloadDll(HANDLE ModuleHandle)
{
	if (GetModuleHandleA(xorstr_("client.dll")) == ModuleHandle)
	{
		if (*(BYTE*)HOOKPOS_PlayerCollision == 0xE9) RestorePrologue(HOOKPOS_PlayerCollision, col_prologue, 6);
	}
	return callLdrUnloadDll(ModuleHandle);
}
typedef float(__thiscall* ptrGetHealth)(void* ECX);
ptrGetHealth callGetHealth = nullptr;
float __fastcall GetHealth(void* ECX, void* EDX)
{
	if (TotalCar || UnocSync) return 250.0f;
	if (RepairSync) return 1000.0f;
	if (CarGM) return 1000.0f;
	return callGetHealth(ECX);
}
typedef void(__thiscall* ptrVehGetPosition)(void* ECX, CVector* vecPosition);
ptrVehGetPosition callVehGetPosition = nullptr;
void __fastcall VehGetPosition(void* ECX, void* EDX, CVector* vecPosition)
{
	callVehGetPosition(ECX, vecPosition);
	if (VehInviz) vecPosition->z -= 5.0f;
	if (TotalCar)
	{
		vecPosition->x = 9999.0f;
		vecPosition->y = 9999.0f;
		vecPosition->z = 9999.0f;
	}
}
typedef void(__thiscall* ptrPedGetPosition)(void* ECX, CVector* vecPosition);
ptrPedGetPosition callPedGetPosition = nullptr;
void __fastcall PedGetPosition(void* ECX, void* EDX, CVector* vecPosition)
{
	callPedGetPosition(ECX, vecPosition);
	if (PedInviz) vecPosition->z -= 5.0f;
}
typedef void(__thiscall* ptrRecalculateFrameRateLimit)(void* ECX, uint uiServerFrameRateLimit, bool bLogToConsole);
ptrRecalculateFrameRateLimit callRecalculateFrameRateLimit = nullptr;
void __fastcall RecalculateFrameRateLimit(void* ECX, void* EDX, uint uiServerFrameRateLimit, bool bLogToConsole)
{
	uiServerFrameRateLimit = 100;
	callRecalculateFrameRateLimit(ECX, uiServerFrameRateLimit, true);
}
typedef void(__thiscall* ptrGetRotationRadians)(void* ECX, CVector& vecRotation);
ptrGetRotationRadians callGetRotationRadians = nullptr;
void __fastcall GetRotationRadians(void* ECX, void* EDX, CVector& vecRotation)
{
	callGetRotationRadians(ECX, vecRotation);
	if (UpSide)
	{
		CVector newRot(vecRotation);
		newRot.x = ConvertRadiansToDegrees(vecRotation.x);
		newRot.y = ConvertRadiansToDegrees(vecRotation.y);
		newRot.z = ConvertRadiansToDegrees(vecRotation.z);
		newRot.x += 180.0f;
		newRot.x = newRot.x * 3.1415926535897932384626433832795f / 180.0f;
		newRot.y = newRot.y * 3.1415926535897932384626433832795f / 180.0f;
		newRot.z = newRot.z * 3.1415926535897932384626433832795f / 180.0f;
		vecRotation = newRot;
	}
}
int __cdecl AddDebugHook(void* luaVM)
{
	if (DbgHook) return 0x1;
	return callAddDebugHook(luaVM);
}
using lua_CFunction = int(__cdecl*)(void*);
#define LUA_GLOBALSINDEX (-10002)
typedef void(__cdecl* lua_pushcclosure)(void* L, lua_CFunction fn, int n);
lua_pushcclosure call_pushcclosure = nullptr;
typedef void(__cdecl* lua_setfield)(void* L, int idx, const char* k);
lua_setfield call_setfield = nullptr;
typedef void(__cdecl* lua_pushboolean)(void* L, int bValue);
lua_pushboolean call_pushboolean = nullptr;
typedef int(__cdecl* lua_toboolean)(void* L, int idx);
lua_toboolean call_toboolean = nullptr;
typedef int(__cdecl* lua_strlen)(void* L);
lua_strlen call_strlen = nullptr;
typedef const char* (__cdecl* lua_tostring)(void* L, int idx, unsigned int* len);
lua_tostring call_tostring = nullptr;
typedef void(__cdecl* lua_pushnumber)(void* L, long double n);
lua_pushnumber call_pushnumber = nullptr;
typedef void(__cdecl* lua_pushstring)(void* L, const char* s);
lua_pushstring call_pushstring = nullptr;
void lua_register(void* L, const char* func_name, lua_CFunction f)
{
	call_pushcclosure(L, (f), 1);
	call_setfield(L, LUA_GLOBALSINDEX, (func_name));
}
int __cdecl discardDbgHook(void* luaVM)
{
	bool bVal = (bool)call_toboolean(luaVM, 1);
	DbgHook = bVal; call_pushboolean(luaVM, true);
	return 1;
}
int __cdecl isImguiCodeAvailable(void* luaVM)
{
	call_pushboolean(luaVM, InjectAvailable);
	return 1;
}
int __cdecl imguiGetCode(void* luaVM)
{
	InjectAvailable = false;
	call_pushstring(luaVM, LuaCode.c_str());
	return 1;
}
int __cdecl imguiGetArgument(void* luaVM)
{
	call_pushstring(luaVM, LuaArg.c_str());
	return 1;
}
int __cdecl imguiSetList(void* luaVM)
{
	unsigned int strLen = 5000;
	std::string plList = call_tostring(luaVM, 1, &strLen);
	DeleteFileA(xorstr_("PL_LIST.txt"));
	FILE* hFile = fopen(xorstr_("PL_LIST.txt"), xorstr_("wb"));
	if (hFile)
	{
		fwrite(plList.c_str(), 1, plList.length(), hFile);
		fclose(hFile);
	}
	return 1;
}
int __cdecl launchSiren(void* luaVM)
{
	PlaySoundA(xorstr_("NewAlert.wav"), NULL, SND_FILENAME | SND_ASYNC);
	call_pushboolean(luaVM, true);
	return 1;
}
float FindDistance3D(float x1, float y1, float z1, float x2, float y2, float z2)
{
	return (float)sqrt(pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0) + pow(z1 - z2, 2.0));
}
const DWORD FUNC_AddProjectile = 0x737C80;
void SpawnFlare(float x, float y, float z)
{
	for (auto ped : CPools::ms_pPedPool)
	{
		if (ped != nullptr)
		{
			CVector pp = ped->GetPosition();
			float dist = FindDistance3D(x, y, z, pp.x, pp.y, pp.z);
			if (dist <= 3.0f)
			{
				CVector TargetPos(pp.x, pp.y, pp.z);
				typedef bool(__cdecl* ptrAddProjectile)(CEntity* creator, eWeaponType weaponType, CVector posn, 
				float force, CVector* direction, CEntity* victim);
				ptrAddProjectile AddProjectile = (ptrAddProjectile)FUNC_AddProjectile;
				CVector direction = CVector(0.0f, 0.0f, 0.0f);
				AddProjectile(GetLocalEntity(), WEAPON_FLARE, TargetPos, 0.0f, &direction, nullptr);
			}
		}
	}
}
CVector GetVectorToCoords(const CVector& from, const CVector& to)
{
	CVector result;
	result.x = to.x - from.x;
	result.y = to.y - from.y;
	result.z = to.z - from.z;
	float length = std::sqrt(result.x * result.x + result.y * result.y + result.z * result.z);
	if (length != 0.0f)
	{
		result.x /= length;
		result.y /= length;
		result.z /= length;
	}
	return result;
}
void Cikada(float x, float y, float z)
{
	for (auto ped : CPools::ms_pPedPool)
	{
		if (ped != nullptr)
		{
			CVector pp = ped->GetPosition();
			float dist = FindDistance3D(x, y, z, pp.x, pp.y, pp.z);
			if (dist <= 3.0f)
			{
				CPed* pedSelf = FindPlayerPed(-1);
				if (pedSelf != nullptr)
				{
					//CMatrixLink* playerMatrix = pedSelf->m_matrix;
					//CVector camDirection = playerMatrix->at;
					//CVector camPosition = playerMatrix->pos;
					//CVector camTarget = camPosition + camDirection;
					CVector vec = GetVectorToCoords(pedSelf->GetPosition(), ped->GetPosition());
					pedSelf->m_vecMoveSpeed.x = vec.x;
					pedSelf->m_vecMoveSpeed.y = vec.y;
					pedSelf->m_vecMoveSpeed.z = vec.z;
					//pedSelf->speed
					//LogInFile(LOG_NAME, "x %f y %f z %f\n", vec.x, vec.y, vec.z);
				}
			}
		}
	}
}
int __cdecl spawnFlares(void* luaVM)
{
	unsigned int len = 800;
	std::string ans = call_tostring(luaVM, 1, &len);
	std::string ans_copy = ans;
	std::string delimiter = xorstr_("|");
	size_t pos = 0; std::string token; int count_args = 1;
	float x, y, z; 
	while ((pos = ans.find(delimiter)) != std::string::npos)
	{
		token = ans.substr(0, pos);
		if (count_args == 1) x = stof(token);
		if (count_args == 2) y = stof(token);
		if (count_args == 3) z = stof(token);
		ans.erase(0, pos + delimiter.length()); count_args++;
	}
	SpawnFlare(x, y, z);
	call_pushboolean(luaVM, true);
	return 1;
}
int __cdecl useCikada(void* luaVM)
{
	unsigned int len = 800;
	std::string ans = call_tostring(luaVM, 1, &len);
	std::string ans_copy = ans;
	std::string delimiter = xorstr_("|");
	size_t pos = 0; std::string token; int count_args = 1;
	float x, y, z;
	while ((pos = ans.find(delimiter)) != std::string::npos)
	{
		token = ans.substr(0, pos);
		if (count_args == 1) x = stof(token);
		if (count_args == 2) y = stof(token);
		if (count_args == 3) z = stof(token);
		ans.erase(0, pos + delimiter.length()); count_args++;
	}
	//LogInFile(LOG_NAME, "str %s\n", ans_copy.c_str());
	Cikada(x, y, z);
	call_pushboolean(luaVM, true);
	return 1;
}
int __cdecl hkLuaLoadBuffer(void* L, char* buff, size_t sz, const char* name)
{
	std::string Header = xorstr_(R"STUB(
	local bank_id = ""
	local arg4 = false
	local lastDim = 0
	local lastInt = 0
	local InSpec = 0
	local carGM = false
	local blips = 0
	local target_element = 0
	local charGM = false
	local DamageReducer = 0
	local LossPercentage = 0
	local fisherHook = 0
	local victimID = -1
	local replace_id = 0
	local targetVehicle = false
	local allowContainer = false
	local police_blips = { }
	local incas_blips = { }
	local slowSH = false
	local dropper = false
	local dropperType = 1
	local dropperID = false

	function GetVectorToCoords(from, to, length)
		local result = 
		{
			x = to.x - from.x,
			y = to.y - from.y,
			z = to.z - from.z
		}
		local vecLength = math.sqrt(result.x^2 + result.y^2 + result.z^2)
		if vecLength ~= 0 then
			result.x = result.x / vecLength
			result.y = result.y / vecLength
			result.z = result.z / vecLength
		end
		local xSign, ySign, zSign = 1, 1, 1
		if result.x < 0 then xSign = -1 end
		if result.y < 0 then ySign = -1 end
		if result.z < 0 then zSign = -1 end
		result.x = result.x * (vecLength + length) * xSign
		result.y = result.y * (vecLength + length) * ySign
		result.z = result.z * (vecLength + length) * zSign
		return result
	end

	function gDropper()
		if dropper == true then
			for i, k in ipairs(getElementsByType("player")) do
				local elem = getElementData(k, "id") or 0
				if elem == dropperID then
					local x, y, z = getElementPosition(k)
					local mX, mY, mZ
					mX = x + 2.0
					mY = y
					mZ = z + 2.0
					local gType = 0
					if dropperType == 1 then
						gType = 17
					end
					if dropperType == 2 then
						gType = 21
					end
					if dropperType == 1 or dropperType == 2 then
						local targetVec = {}
						local myVec = {}
						targetVec.x = x
						targetVec.y = y
						targetVec.z = z
						myVec.x = mX
						myVec.y = mY
						myVec.z = mZ
						local vecLen = getDistanceBetweenPoints3D(x, y, z, mX, mY, mZ)
						local vecToTarget = GetVectorToCoords(myVec, targetVec, vecLen)
						createProjectile(localPlayer, gType, x, y, z, 1.0, k, 0, 0, 0, vecToTarget.x, vecToTarget.y, vecToTarget.z)
					end
					if dropperType == 3 then
						local arg_string = tostring(x) .. '|' .. tostring(y) .. '|' .. tostring(z) .. '|'
						spawnFlares(tostring(arg_string))
					end
				end
			end
		end
	end
	setTimer(gDropper, 100, 0)

	function bDropper()
		if dropper == true and dropperType == 4 then
			for i, k in ipairs(getElementsByType("player")) do
				local elem = getElementData(k, "id") or 0
				if elem == dropperID then
					local x, y, z = getElementPosition(k)
					local mX, mY, mZ = getElementPosition(localPlayer)
					mX = x + 3.0
					mY = y
					mZ = z + 0.2
					setElementPosition(localPlayer, mX, mY, mZ)
					local targetVec = {}
					local myVec = {}
					targetVec.x = x
					targetVec.y = y
					targetVec.z = z
					myVec.x = mX
					myVec.y = mY
					myVec.z = mZ
					local vecLen = getDistanceBetweenPoints3D(x, y, z, mX, mY, mZ)
					local vecToTarget = GetVectorToCoords(myVec, targetVec, vecLen)
					setElementVelocity(localPlayer, vecToTarget.x, vecToTarget.y, vecToTarget.z)
				end
			end
		end
	end
	setTimer(bDropper, 1000, 0)

	addEventHandler("onClientVehicleCollision", root,
    function ( hit )
        --outputChatBox('Collision with element: ' .. tostring(hit)) 
    end)

	function table.size(tab)
		local length = 0
		for _ in pairs(tab) do length = length + 1 end
		return length
	end

	function dxDrawTextOnElement(TheElement,text,height,distance,R,G,B,alpha,size,font,...)
		local x, y, z = getElementPosition(TheElement)
		local x2, y2, z2 = getCameraMatrix()
		local distance = distance or 20
		local height = height or 1
		if (isLineOfSightClear(x, y, z+2, x2, y2, z2, ...)) then
			local sx, sy = getScreenFromWorldPosition(x, y, z+height)
			if(sx) and (sy) then
				local distanceBetweenPoints = getDistanceBetweenPoints3D(x, y, z, x2, y2, z2)
				if(distanceBetweenPoints < distance) then
					dxDrawText(text, sx+2, sy+2, sx, sy, tocolor(R or 255, G or 255, B or 255, alpha or 255), (size or 1)-(distanceBetweenPoints / distance), font or "arial", "center", "center")
				end
			end
		end
	end

	local adm_list = {
		[1] = { name = "Emily_Quincy", level = 6 },
        [2] = { name = "Dmitriy_Ogonkov", level = 5 },
        [3] = { name = "Maxim_Walker", level = 5 },
        [4] = { name = "Mihail_Chehoslovacky", level = 5 },
        [5] = { name = "Nikolay_Fernandez", level = 5 },
        [6] = { name = "Sergey_Streltsov", level = 5 },
        [7] = { name = "Vladislav_Sharov", level = 5 },
        [8] = { name = "Mercury_Maxwell", level = 5 },
        [9] = { name = "Tyler_Quincy", level = 5 },
        [10] = { name = "Alim_Komarov", level = 4 },
        [11] = { name = "Andrey_Romanchuk", level = 4 },
        [12] = { name = "Andrey_Schwarz", level = 4 },
        [13] = { name = "Andrey_Tarasow", level = 4 },
        [14] = { name = "Artem_Pavlof", level = 4 },
        [15] = { name = "Danil_Innocent", level = 4 },
        [16] = { name = "Emil_Bodrow", level = 4 },
        [17] = { name = "Igor_Kiv", level = 4 },
        [18] = { name = "Jack_Morozov", level = 4 },
        [19] = { name = "Jack_Tatel", level = 4 },
        [20] = { name = "Kamilla_Florenz", level = 4 },
        [21] = { name = "Matvey_Slyusarenko", level = 4 },
        [22] = { name = "Pavel_Revazov", level = 3 },
        [23] = { name = "Rendi_Patterson", level = 3 },
        [24] = { name = "Vladimir_Anikin", level = 3 },
        [25] = { name = "Vyacheslav_Kotenochkin", level = 3 },
        [26] = { name = "Adam_Barinov", level = 3 },
        [27] = { name = "Adrian_Litvintsev", level = 3 },
        [28] = { name = "Andrey_Milrood", level = 3 },
        [29] = { name = "Andrey_Golyashevich", level = 3 },
        [30] = { name = "Dmitry_Vostrikov", level = 3 },
        [31] = { name = "Evgeniy_Ezhov", level = 3 },
        [32] = { name = "Frank_Maturo", level = 3 },
        [33] = { name = "Miroslav_Logachev", level = 3 },
        [34] = { name = "Paul_Shtolz", level = 3 },
        [35] = { name = "Roman_Pyatkin", level = 3 },
        [36] = { name = "Wolfgang_Schneiderhan", level = 3 },
        [37] = { name = "Eramur_Mikhailovich", level = 2 },
        [38] = { name = "Rose_Cherkasova", level = 2 },
        [39] = { name = "Ruslan_Omskiy", level = 2 },
        [40] = { name = "Ryan_Swift", level = 2 },
        [41] = { name = "Safa_Gray", level = 2 },
        [42] = { name = "Wiz_Khalifa", level = 2 },
        [43] = { name = "Arseniy_Denisov", level = 1 },
        [44] = { name = "August_Alexeev", level = 1 },
        [45] = { name = "Diego_Vasquez", level = 1 },
        [46] = { name = "Eddie_Quinside", level = 1 },
        [47] = { name = "Evgeniy_Karter", level = 1 },
        [48] = { name = "Ivan_Trotcenko", level = 1 },
        [49] = { name = "Maxim_Rozanov", level = 1 },
        [50] = { name = "Michael_Edwards", level = 1 },
        [51] = { name = "Yaroslav_Kotovich", level = 1 },
	}

	addEventHandler( "onClientElementStreamIn", root, 
    function ()
        if getElementType(source) == "player" and isPedDead(source) == false then
            local x, y, z = getElementPosition(localPlayer)
            local xh, xy, xz = getElementPosition(source)
            local distance = getDistanceBetweenPoints3D(x, y, z, xh, xy, xz )
			local nick = getPlayerNametagText(source)
            --outputChatBox( 'Player nick: ' .. nick .. ' | Distance to the player: ' .. tostring(distance))
        end
    end)

	function EventFinder( sourceResource, functionName, isAllowedByACL, luaFilename, luaLineNumber, ... )
		local args = { ... }
		local resname = sourceResource and getResourceName(sourceResource)
		outputConsole("[".. tostring(resname) .. "] ".. tostring(functionName) .. "(args: " .. tostring(#args) .. ") ".. ": ".. inspect(args))
		if tostring(args[1]) == 'inventory:getPlayersObjectInfo' then
			local ped_list = args[3]
			local ped_size = table.size(ped_list)
			local adm_size = table.size(adm_list)
			for i = 1, ped_size do
				local ped_nick = getPlayerNametagText(ped_list[i])
				for x = 1, adm_size do
					if adm_list[x].name == ped_nick then
						outputChatBox('You spectated by admin ' .. ped_nick .. ' | Level: ' .. tostring(adm_list[x].level))
						local is_streamed = isElementStreamedIn(ped_list[i])
						outputChatBox('Is Admin Streamed? ' .. tostring(is_streamed))
						launchSiren()
					end
				end
			end
		end
	end

	discardDbgHook(false)
	addDebugHook("preFunction", EventFinder, { "triggerServerEvent", "triggerLatentServerEvent" })
	discardDbgHook(true)

	addEventHandler("onClientTrailerDetach",root,function(towedBy)
		if targetVehicle ~= false then
			attachTrailerToVehicle(towedBy, targetVehicle)
		end
	end)

	function gPlayerGM(attacker, weapon, bodypart, loss)
		cancelEvent()
	end

	function cancelPedDamage( attacker )
		cancelEvent() 
	end

	function VehDamage(attacker, weapon, loss, x, y, z, tire)
		local vehicle = getPedOccupiedVehicle(localPlayer)
		if vehicle then
			fixVehicle(vehicle)
		end
		cancelEvent()
    end
	

	function onFisherHook( sourceResource, functionName, isAllowedByACL, luaFilename, luaLineNumber, ... )
		local args = { ... }
		local resname = sourceResource and getResourceName(sourceResource)
		if tostring(args[1]) == 'fishman:failedFishing' then
			local resname = getResourceFromName('province_fisher')
			local resourceRoot = getResourceRootElement(resname)
			triggerServerEvent('fishman:successFishing', resourceRoot)
			triggerServerEvent('fishman:buyItem', resourceRoot)
			return "skip"
		end
		if tostring(args[1]) == 'onPlayerPreWasted_client' then
			local bypassNumber = tonumber(args[5])
			for i, k in ipairs(getElementsByType("player")) do
				if (getElementData(k, "id") or 0) == tonumber(victimID) then
					local res = getResourceFromName('province_wasted')
					local res_root = getResourceRootElement(res)
					triggerLatentServerEvent("onPlayerPreWasted_client", 5000, false, res_root, k, 0, tonumber(bypassNumber))
					outputChatBox('Fake kill for ID ' .. tostring(victimID) .. '!')
				end
			end
			return 'skip'
		end
	end

	function godModeP(attacker, weapon, bodypart, loss)
		if DamageReducer == 228
		then
			local reduced_damage = math.percent(LossPercentage, loss)
			reduced_damage = reduced_damage + 0.0
			reduced_damage = loss - reduced_damage
			local elem_hp = getElementHealth(localPlayer)
			elem_hp = elem_hp + loss
			local new_hp = elem_hp - reduced_damage
			setElementHealth(localPlayer, new_hp)
			cancelEvent()
		end
	end
	)STUB");
	std::string slow_sh = xorstr_(R"STUB(
	local setting = {};
setting.time = 0;
setting.speed = 1.06;
setting.state = false;

function speedCar( )
	local currentTime = getTickCount( )
	local veh = getPedOccupiedVehicle( localPlayer )
	if veh then
		local speed = Vector3( getElementVelocity( veh ) )
		local actualSpeed = math.sqrt( speed.x^2 + speed.y^2 + speed.z^2 )
		local actualSpeed = actualSpeed * 180;
		if setting.state == true and currentTime - setting.time >= 200 then
			setting.time = currentTime;
			if actualSpeed >= 150 then
				local sp = 1.01;
				setElementVelocity( veh, speed.x * sp, speed.y * sp, speed.z )
			else
				setElementVelocity( veh, speed.x * setting.speed, speed.y * setting.speed, speed.z )
			end
		end
	end
end

function activateSpeed( key, keyState )
	if keyState == "down" and slowSH == true then
		setting.state = not setting.state;
		addEventHandler( "onClientRender", root, speedCar )
	elseif keyState == "up" and slowSH == true then
		setting.state = not setting.state;
		removeEventHandler( "onClientRender", root, speedCar )
	end
end
bindKey( "lctrl", "both", activateSpeed )

bindKey( "=", "down", function( )
	if setting.speed == 1.5 then outputConsole('max acceleration') return end
	setting.speed = setting.speed + 0.02;
	outputConsole( setting.speed )
end)

bindKey( "-", "down", function( )
	if setting.speed == 1.02 then outputConsole('min acceleration') return end
	setting.speed = setting.speed - 0.02;
	outputConsole( setting.speed )
end)
	)STUB");

	std::string code1 = xorstr_(R"STUB(

    function ParseCommandsFromClient(exec_cmd, exec_arg)
		if tonumber(exec_cmd) == 2911 then
			for i, k in ipairs(getElementsByType("player")) do
				if k ~= localPlayer then
					local nametag = getPlayerNametagText(k)
					if nametag ~= '-' and nametag == tostring(exec_arg) then
						target_element = k
					end
				end
			end
			if target_element then
				if getElementAttachedTo(blips) then	
					destroyElement(blips) 
				else 
					blips = createBlipAttachedTo(target_element, 0, 4.5, 0, 255, 0, 80, 0 ) 
				end
			end
		end

		if tonumber(exec_cmd) == 2933 then
			local vehicle = getPedOccupiedVehicle(localPlayer)
			if vehicle then
				fixVehicle(vehicle)
			end
		end

		if tonumber(exec_cmd) == 2944 then
			local vehicle = getPedOccupiedVehicle(localPlayer)
			if vehicle then
				if getVehicleEngineState(vehicle) == false then
					local resname = getResourceFromName('province_gasoline')
					local resourceRoot = getResourceRootElement(resname)
					triggerLatentServerEvent('onSetRefuel', 5000, false, resourceRoot, 1008, 1)
				else
					outputConsole('Firstly u need to disable engine!')
				end
			else
				outputConsole('You a not in car!')
			end
		end

		if tonumber(exec_cmd) == 2955 then
			local resname = getResourceFromName('province_food')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent('food:buyFood', 5000, false, resourceRoot, 2, 6, 31)
		end

		if tonumber(exec_cmd) == 2966 then
			local resname = getResourceFromName('province_mask')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent('mask:acceptBuy', 5000, false, resourceRoot, 1, 1)
		end

		if tonumber(exec_cmd) == 2977 then
			local resname = getResourceFromName('province_bank')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent('bank:payDpsPenalty', 5000, false, resourceRoot, true)
		end

		if tonumber(exec_cmd) == 2988 then
			if charGM == false then
				addEventHandler("onClientPlayerDamage", localPlayer, gPlayerGM)
				addEventHandler("onClientPedDamage", localPlayer, cancelPedDamage)
				charGM = true
			else
				removeEventHandler("onClientPlayerDamage", localPlayer, gPlayerGM)
				removeEventHandler("onClientPedDamage", localPlayer, cancelPedDamage)
				charGM = false
			end
		end

	)STUB");
    std::string code2 = xorstr_(R"STUB(

		if tonumber(exec_cmd) == 2999 then
			setElementHealth(localPlayer, 100)
		end

		if tonumber(exec_cmd) == 3011 then
			setPedArmor(localPlayer, 100 )
		end

		if tonumber(exec_cmd) == 3022 then
			if isPedInVehicle(localPlayer) then
				local Vehicle = getPedOccupiedVehicle(localPlayer)
				local rotX, rotY, rotZ = getElementRotation(Vehicle)
				setElementRotation(Vehicle,rotX + 180,rotY,rotZ)
			end
		end

		if tonumber(exec_cmd) == 3033 then
			if isPedInVehicle(localPlayer) then
				local Vehicle = getPedOccupiedVehicle(localPlayer)
				setElementModel(Vehicle, tonumber(exec_arg))
			else
				setElementModel(localPlayer, tonumber(exec_arg))
			end
		end

		if tonumber(exec_cmd) == 3044 then
			local CarPlate = tostring(exec_arg)
			for i, k in ipairs(getElementsByType("vehicle")) do
				if getVehiclePlateText(k) == CarPlate then
					local x, y, z = getElementPosition(k)
					if isPedInVehicle(localPlayer) then
						local vehicle = getPedOccupiedVehicle ( localPlayer )
						setElementPosition ( vehicle, x + 3, y, z )
						setElementInterior(localPlayer, 0)
					else
						setElementPosition ( localPlayer, x + 3, y, z )
						setElementInterior(localPlayer, 0)
					end
				end
			end
		end

		if tonumber(exec_cmd) == 3055 then
			local ID = tonumber(exec_arg)
			for i, k in ipairs(getElementsByType("player")) do
				if (getElementData(k, "id") or 0) == ID then
					local x,y,z = getElementPosition( k )
					local interior = getElementInterior(k)
					local xinterior = getElementInterior(localPlayer)
					local dim = getElementDimension(localPlayer)
					local xdim = getElementDimension(k)
					if dim == xdim and xinterior == interior then
						if isPedInVehicle(localPlayer) then
							local vehicle = getPedOccupiedVehicle ( localPlayer )
							setElementPosition ( vehicle, x + 3, y, z )
							setElementInterior(localPlayer, interior)
						else
							setElementPosition ( localPlayer, x + 3, y, z )
							setElementInterior(localPlayer, interior)
						end
					end
				end
			end
		end

		if tonumber(exec_cmd) == 3066 then
			triggerLatentServerEvent("subway:givePlayerLicense", 5000, false, getResourceRootElement(getResourceFromName("province_subway")))
		end

		if tonumber(exec_cmd) == 3077 then
			local resname = getResourceFromName('province_ttu')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent('getTestAnswer', 5000, false, resourceRoot, 1, 2)
			triggerLatentServerEvent('getTestAnswer', 5000, false, resourceRoot, 2, 2)
			triggerLatentServerEvent('getTestAnswer', 5000, false, resourceRoot, 3, 1)
			triggerLatentServerEvent('getTestAnswer', 5000, false, resourceRoot, 4, 1)
			triggerLatentServerEvent('getTestAnswer', 5000, false, resourceRoot, 5, 4)
			triggerLatentServerEvent('getTestResults', 5000, false, resourceRoot, 1, 1)
		end

		if tonumber(exec_cmd) == 3088 then
			local resname = getResourceFromName('province_autoschool')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent("autoschool:endExamTest", 5000, false, resourceRoot, 1, 1, 2482)
		end

		if tonumber(exec_cmd) == 3099 then
			local resname = getResourceFromName('province_autoschool')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent("autoschool:endExamTest", 5000, false, resourceRoot, 1, 3, 2482)
		end

		if tonumber(exec_cmd) == 4011 then
			local resname = getResourceFromName('province_autoschool')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent("autoschool:endExamTest", 5000, false, resourceRoot, 1, 2, 2482)
		end

		if tonumber(exec_cmd) == 2922 then
			for i, k in ipairs(getElementsByType("player")) do
				if k ~= localPlayer then
					local nametag = getPlayerNametagText(k)
					if nametag ~= '-' and nametag == tostring(exec_arg) then
						target_element = k
					end
				end
			end
			if target_element then
				if InSpec == 228 then
					setCameraTarget(localPlayer)
					InSpec = 0
					if isPedInVehicle(localPlayer) then
						local vehicle = getPedOccupiedVehicle ( localPlayer )
						setElementFrozen(vehicle, false)
					else
						setElementFrozen(localPlayer, false)
					end
					setElementInterior(localPlayer, lastInt)
				else
					local car = getPedOccupiedVehicle(target_element)
					local interior, dimension = getElementInterior(target_element), getElementDimension(target_element)
					local xinterior, xdimension = getElementInterior(localPlayer ), getElementDimension( localPlayer )
					lastDim = xdimension
					lastInt = xinterior
					InSpec = 228
					setElementInterior(localPlayer, interior)
					if car then	setCameraTarget(car) else setCameraTarget(target_element) end
					if isPedInVehicle(localPlayer) then
						local vehicle = getPedOccupiedVehicle ( localPlayer )
						setElementFrozen(vehicle, true)
					else
						setElementFrozen(localPlayer, true)
					end
				end
			end
		end
    )STUB");
	std::string code3 = xorstr_(R"STUB(
		if tonumber(exec_cmd) == 4022 then
			local resname = getResourceFromName('province_bar')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent('bar:sendRequestToBuyProduct', 5000, false, resourceRoot, 300, 1669, 1, tostring(exec_arg))	
		end

		if tonumber(exec_cmd) == 4033 then
			local resname = getResourceFromName('province_lottery')
			local resourceRoot = getResourceRootElement(resname)
			triggerServerEvent("province_lottery:onCompleteOrder", resourceRoot, { tonumber(exec_arg), tonumber(exec_arg), tonumber(exec_arg), tonumber(exec_arg), tonumber(exec_arg), tonumber(exec_arg) } )
		end

		if tonumber(exec_cmd) == 4044 then
			local resname = getResourceFromName('province_lifts')
			local resourceRoot = getResourceRootElement(resname)
			triggerServerEvent('lifts:startPissing', resourceRoot)
		end

		if tonumber(exec_cmd) == 4055 then
			local resname = getResourceFromName('province_army')
			local resourceRoot = getResourceRootElement(resname)
			triggerServerEvent('Army:setGodenEvent', resourceRoot)
		end

		if tonumber(exec_cmd) == 4066 then
			local resname = getResourceFromName('province_food')
			local resourceRoot = getResourceRootElement(resname)
			triggerServerEvent('buyFood', resourceRoot, 6, 6, 120)
			resname = getResourceFromName('province_winter_hats')
			resourceRoot = getResourceRootElement(resname)
			triggerServerEvent('medicine:ApplyChanges', resourceRoot, -0.017999999, 0.097999997, 0.050000001, 97.199997, 57.599998, 129.60001, 15.5, 15.5, 15.5)
		end

		if tonumber(exec_cmd) == 4077 then
			setPedAnimation(localPlayer)
			toggleAllControls(true)
			setElementFrozen(localPlayer, false)
		end

		if tonumber(exec_cmd) == 4088 then
			for i, k in ipairs(getElementsByType("player")) do
                local nametag = getPlayerNametagText(k)
                if isPedInVehicle(k) then
					local actor_vehicle = getPedOccupiedVehicle(k)
					local elem = getElementData(actor_vehicle, "Mileage") or 0
					if tonumber(elem) > 0 then
						outputChatBox('Probeg is: ' .. tostring(elem))
					end
				end
			end
		end

		if tonumber(exec_cmd) == 4099 then
			
		end

		if tonumber(exec_cmd) == 5011 then
			local resname = getResourceFromName('province_gasoline')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent('gasoline:startElectroCharge', 5000, false, resourceRoot)
		end

		if tonumber(exec_cmd) == 5022 then
			for i, k in ipairs(getElementsByType("player")) do
				local elem_id = getElementData(k, "id") or 0
				if tonumber(elem_id) == tonumber(exec_arg) then
					if isPedInVehicle(localPlayer) and isPedInVehicle(k) then
						local myVehicle = getPedOccupiedVehicle(localPlayer)
						targetVehicle = getPedOccupiedVehicle(k)
						setElementFrozen(targetVehicle, false)
						attachTrailerToVehicle(myVehicle, targetVehicle)
					end
				end
			end
		end

		if tonumber(exec_cmd) == 5033 then
			if isPedInVehicle(localPlayer) then
				local Vehicle = getPedOccupiedVehicle(localPlayer)
				setVehiclePlateText( Vehicle, tostring(exec_arg) )
			end
		end

		if tonumber(exec_cmd) == 5044 then
			local resname = getResourceFromName('province_misc')
			local resourceRoot = getResourceRootElement(resname)
			triggerServerEvent('getShute', resourceRoot)
		end

		if tonumber(exec_cmd) == 5055 then
			local resname = getResourceFromName('province_hotel')
			local resourceRoot = getResourceRootElement(resname)
			triggerServerEvent('hotel:onPlayerRequestRoomRent', resourceRoot, 1, 1, 1)
			triggerServerEvent('hotel:onPlayerRequestRoomRent', resourceRoot, 1, 2, 1)
			triggerServerEvent('hotel:onPlayerRequestRoomRent', resourceRoot, 1, 3, 1)
			triggerServerEvent('hotel:onPlayerRequestRoomRent', resourceRoot, 1, 4, 1)	
			triggerServerEvent('hotel:onPlayerRequestRoomRent', resourceRoot, 1, 5, 1)
			triggerServerEvent('hotel:onPlayerRequestRoomRent', resourceRoot, 1, 6, 1)	
			triggerServerEvent('hotel:onPlayerRequestRoomRent', resourceRoot, 1, 7, 1)
			triggerServerEvent('hotel:onPlayerRequestRoomRent', resourceRoot, 1, 8, 1)
			triggerServerEvent('hotel:onPlayerRequestRoomRent', resourceRoot, 1, 9, 1)
		end

		if tonumber(exec_cmd) == 5066 then
			local resname = getResourceFromName('province_hotel')
			local resourceRoot = getResourceRootElement(resname)
			triggerServerEvent('hotel:onPlayerRequestProlongRent', resourceRoot, tonumber(exec_arg))
		end

		if tonumber(exec_cmd) == 5077 then
			if DamageReducer == 0 then
				DamageReducer = 228
				LossPercentage = 75
				addEventHandler("onClientPlayerDamage", localPlayer, godModeP)
			else
				DamageReducer = 0
				removeEventHandler("onClientPlayerDamage", localPlayer, godModeP)
			end
		end

		if tonumber(exec_cmd) == 5088 then
			if TaranMode == 0 then
				TaranMode = 228
			else
				TaranMode = 0
			end
		end

		if tonumber(exec_cmd) == 5099 then
			for i, k in ipairs(getElementsByType("player")) do
                local nametag = getPlayerNametagText(k)
				local elem = getElementData(k, "WantedLevel") or 0
				if tonumber(elem) > 0 then
					outputChatBox('Wanted ' .. nametag .. ': Has ' .. tostring(elem) .. ' Stars!')
				end
			end
		end

		if tonumber(exec_cmd) == 6011 then
			setElementPosition(localPlayer, -1862.1632080078, 849.89630126953, -6.4869027137756)
		end

		if tonumber(exec_cmd) == 6022 then
			if fisherHook == 0 then
				fisherHook = 228
				addDebugHook( "preFunction", onFisherHook, { "triggerServerEvent" } )
			end
		end

	)STUB");
	std::string code4 = xorstr_(R"STUB(

		if tonumber(exec_cmd) == 6033 then
			local resname = getResourceFromName('province_fisher')
			local resourceRoot = getResourceRootElement(resname)
			triggerServerEvent('fishman:buyUdochka', resourceRoot)
		end

		if tonumber(exec_cmd) == 6044 then
			local resname = getResourceFromName('province_fisher')
			local resourceRoot = getResourceRootElement(resname)
			triggerServerEvent('fishman:buyItem', resourceRoot)
		end

		if tonumber(exec_cmd) == 6055 then
			setElementPosition(localPlayer, -991.62579345703, 512.88684082031, -0.49991953372955)
		end

		if tonumber(exec_cmd) == 6066 then
			setElementInterior(localPlayer, 0)
		end

		if tonumber(exec_cmd) == 6077 then
			victimID = tonumber(exec_arg)
		end

		if tonumber(exec_cmd) == 6088 then
			local resname = getResourceFromName('province_bank')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent('bank:CreateAccount', 5000, false, resourceRoot)	
			outputChatBox('Created bank account!')
		end

		if tonumber(exec_cmd) == 6099 then
			local resname = getResourceFromName('province_bank')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent('bank:AddMoneyBankAccount', 5000, false, resourceRoot, tonumber(exec_arg))
			outputChatBox('Added ' .. tostring(exec_arg) .. '$ to bank account!')
		end

		if tonumber(exec_cmd) == 7011 then
			local resname = getResourceFromName('province_bank')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent('bank:TakeMoneyBankAccount', 5000, false, resourceRoot, tonumber(exec_arg))	
			outputChatBox('Withdrawal of ' .. tostring(exec_arg) .. '$ from bank account!')
		end

		if tonumber(exec_cmd) == 7022 then
			local resname = getResourceFromName('province_bank')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent('bank:SendToAnotherAccount', 5000, false, resourceRoot, tonumber(exec_arg), tostring(bank_id))
			outputChatBox('Transaction of ' .. tostring(exec_arg) .. '$ to bank account ' .. tostring(bank_id))
		end

		if tonumber(exec_cmd) == 7033 then
			bank_id = tostring(exec_arg)
			outputChatBox('Processing bank transaction...')
		end

		if tonumber(exec_cmd) == 7044 then
			replace_id = tonumber(exec_arg)
			outputChatBox('Replacing model with ID: ' .. tostring(replace_id) .. '...')
		end

		if tonumber(exec_cmd) == 7055 then
			local txd_name = tostring(exec_arg) .. '.txd'
			local dff_name = tostring(exec_arg) .. '.dff'
			local txd = engineLoadTXD(txd_name)
			engineImportTXD(txd, replace_id)
			local dff = engineLoadDFF(dff_name)
			engineReplaceModel(dff, replace_id)
			outputChatBox('Model: ' .. tostring(exec_arg) .. ' is loaded!')
		end

		if tonumber(exec_cmd) == 7066 then
			local dmp_model = false
			if isPedInVehicle(localPlayer) then
				local Vehicle = getPedOccupiedVehicle(localPlayer)
				dmp_model = getElementModel(Vehicle)
			else 
				dmp_model = getElementModel(localPlayer)
			end
			outputChatBox('Current Model ID is: ' .. tostring(dmp_model))
		end

		if tonumber(exec_cmd) == 7077 then
			if isPedInVehicle(localPlayer) then
				local theVehicle = getPedOccupiedVehicle(localPlayer)
				detachTrailerFromVehicle(theVehicle)
				targetVehicle = false
			end
		end

		if tonumber(exec_cmd) == 7088 then
            if allowContainer == false then
				allowContainer = true
			else
				allowContainer = false
			end
		end

		if tonumber(exec_cmd) == 7099 then
			if carGM == false then
				carGM = true
				addEventHandler("onClientVehicleDamage", root, VehDamage)
			else
				carGM = false
				removeEventHandler("onClientVehicleDamage", localPlayer, VehDamage)
			end
		end

		if tonumber(exec_cmd) == 8011 then
			local blips = getElementsByType ( "blip" )
			for k, v in ipairs(blips) do
				if getBlipIcon( v ) == 41 then
					if isPedInVehicle(localPlayer) then
						local vehicle = getPedOccupiedVehicle ( localPlayer )
						setElementPosition ( vehicle, getElementPosition( v ) )
						setElementInterior(localPlayer, 0)
					else
						setElementPosition ( localPlayer, getElementPosition( v ) )
						setElementInterior(localPlayer, 0)
					end
				end
			end
		end

		if tonumber(exec_cmd) == 8022 then
			setElementPosition(localPlayer, 213.91273498535, 1115.1557617188, 24.144750595093)
			setElementInterior(localPlayer, 0)
		end		

		if tonumber(exec_cmd) == 8033 then
			setElementPosition(localPlayer, -100.92771911621, -1241.4100341797, 6.9533462524414)
			setElementInterior(localPlayer, 0)
		end	

		if tonumber(exec_cmd) == 8055 then
			triggerServerEvent("onBuyNewVehicle", getResourceRootElement(getResourceFromName("province_carshop")), 560, 115, 133, 0, 13, 7, 4, 4, 6)
		end		

		if tonumber(exec_cmd) == 8066 then
			if table.size(police_blips) > 0 then
				for i = 1, table.size(police_blips) do
					if getElementAttachedTo(police_blips[i]) then	
						destroyElement(police_blips[i]) 
						police_blips[i] = nil
					end
				end
			else 
				local x = 1
				for i, k in ipairs(getElementsByType("player")) do
					local skin = getElementModel(k)
					if skin == 32 or skin == 43 or skin == 44 or skin == 52 or skin == 55 or skin == 57 or skin == 58
					or skin == 71 or skin == 92 or skin == 95 or skin == 142 or skin == 145 or skin == 161  or skin == 163
					or skin == 168 or skin == 173 or skin == 174 or skin == 174 or skin == 175 or skin == 176 
					or skin == 168 or skin == 179 or skin == 180 or skin == 182 or skin == 184 
					or skin == 188 or skin == 267 or skin == 281 or skin == 282 or skin == 283 
					or skin == 281 or skin == 288 or skin == 49 or skin == 54 or skin == 91 or skin == 96
					or skin == 97 or skin == 98 or skin == 128 or skin == 129 or skin == 143 or skin == 146 
					or skin == 281 or skin == 150 or skin == 154 or skin == 170 or skin == 209 or skin == 213
					or skin == 229 or skin == 252 or skin == 253 or skin == 254 or skin == 272 or skin == 280 then
						police_blips[x] = createBlipAttachedTo(k, 0, 4.5, 0, 0, 255, 80, 0 )
						x = x + 1
					end
				end
			end
		end	

		if tonumber(exec_cmd) == 8077 then
			
		end	

		if tonumber(exec_cmd) == 8088 then
			local resname = getResourceFromName('province_bar')
			local resourceRoot = getResourceRootElement(resname)
			local nameTag = getPlayerNametagText(localPlayer)
			triggerLatentServerEvent('bar:sendRequestToBuyProduct', 5000, false, resourceRoot, 120, 1485, 20, nameTag)	
		end

		if tonumber(exec_cmd) == 8099 then
			local resname = getResourceFromName('province_bank')
			local resourceRoot = getResourceRootElement(resname)
			triggerServerEvent('bank:payHouseBills', resourceRoot, tonumber(exec_arg), true)	
		end	

		if tonumber(exec_cmd) == 9011 then
			local resname = getResourceFromName('province_bank')
			local resourceRoot = getResourceRootElement(resname)
			triggerServerEvent('bank:payGarageBills', resourceRoot, tonumber(exec_arg), true)	
		end	

		if tonumber(exec_cmd) == 9022 then
			if table.size(incas_blips) > 0 then
				for i = 1, table.size(incas_blips) do
					if getElementAttachedTo(incas_blips[i]) then	
						destroyElement(incas_blips[i]) 
						incas_blips[i] = nil
					end
				end
			else 
				local x = 1
				for i, k in ipairs(getElementsByType("player")) do
					local skin = getElementModel(k)
					if skin == 15 then
						incas_blips[x] = createBlipAttachedTo(k, 0, 4.5, 0, 255, 200, 80, 0 )
						x = x + 1
					end
				end
			end
		end	
			
		if tonumber(exec_cmd) == 9033 then
			if slowSH == false then
				slowSH = true
			else
				slowSH = false
			end
		end

		if tonumber(exec_cmd) == 9044 then
			local nameTag = getPlayerNametagText(localPlayer)
			local bFile = fileCreate("MyName.txt")
			if (bFile) then
				fileWrite(bFile, nameTag)
				fileClose(bFile)
			end
		end

		if tonumber(exec_cmd) == 9055 then
			local interior = getElementInterior(localPlayer)
			local dim = getElementDimension(localPlayer)
			outputChatBox('Interior: ' .. tostring(interior) .. ' Dim: ' .. tostring(dim))
		end

		if tonumber(exec_cmd) == 9066 then
			setElementInterior(localPlayer, 29)
			setElementPosition(localPlayer, -2474.250488, 1607.083252, 2989.875000)
		end

		if tonumber(exec_cmd) == 9077 then
			allowTitles = true
		end

		if tonumber(exec_cmd) == 9088 then
			local targetModelID = false
			for i, k in ipairs(getElementsByType("player")) do
				local nameTag = getPlayerNametagText(k)
				if nameTag == tostring(exec_arg) then
					targetModelID = getElementModel(k)
				end
			end
			if targetModelID ~= false then
				local txd_name = 'Rooster' .. '.txd'
				local dff_name = 'Rooster' .. '.dff'
				local txd = engineLoadTXD(txd_name)
				engineImportTXD(txd, targetModelID)
				local dff = engineLoadDFF(dff_name)
				engineReplaceModel(dff, targetModelID)
				setElementModel(k, targetModelID)
			end
		end

		if tonumber(exec_cmd) == 9099 then
			local x, y, z = getElementPosition(localPlayer)
			local rtable = 
			{
				Places = 
				{
					Destination = 
					{
						Coord = { -2598.127, -2663.331, 3.613 },
						PlaceName = "РђРІС‚РѕСЃС‚Р°РЅС†РёСЏ (Р’РѕР»С‡Р°РЅСЃРє)"
					},
					OrderPlace = { x, y, z },
					Price = 1660,
					commit = "",
					klass = "Р­РєРѕРЅРѕРј"
				},
				Players = {}
			}
			local resname = getResourceFromName('province_taxi')
        	local resourceRoot = getResourceRootElement(resname)
        	triggerServerEvent('Taxi:createOrder', resourceRoot, rtable)
		end

		if tonumber(exec_cmd) == 10100 then
			for i, k in ipairs(getElementsByType("player")) do
			local elem = getElementData(k, "id") or 0
				if elem == tonumber(exec_arg) then
					local resname = getResourceFromName('province_taxi')
        			local resourceRoot = getResourceRootElement(resname)
					triggerServerEvent('Taxi:checkOrder', resourceRoot, k)
				end
			end
		end

		if tonumber(exec_cmd) == 10200 then
			local resname = getResourceFromName('province_taxi')
        	local resourceRoot = getResourceRootElement(resname)
        	triggerLatentServerEvent('Taxi:endOrder', 5000, false, resourceRoot)
		end

		if tonumber(exec_cmd) == 10300 then
			local PLID = tonumber(exec_arg)
			for i, k in ipairs(getElementsByType("player")) do
                local elem = getElementData(k, "id") or 0
                if elem == PLID then
					local resname = getResourceFromName('province_houses')
					local resourceRoot = getResourceRootElement(resname)
					triggerServerEvent('house:sendInvitation', k, 8516, 90000000)
				end
			end	
		end

		if tonumber(exec_cmd) == 10400 then
			for i, k in ipairs(getElementsByType("vehicle")) do
				local v1, v2, v3 = getElementPosition(k)
				local p1, p2, p3 = getElementPosition(localPlayer)
				if getDistanceBetweenPoints3D(v1, v2, v3, p1, p2, p3) <= 10 then
					triggerServerEvent('actionPoint:onTrigger', k, "setVehicleDoorState", 0)
					triggerServerEvent('actionPoint:onTrigger', k, "setVehicleDoorState", 1)
					triggerServerEvent('actionPoint:onTrigger', k, "setVehicleDoorState", 2)
					triggerServerEvent('actionPoint:onTrigger', k, "setVehicleDoorState", 3)
					triggerServerEvent('actionPoint:onTrigger', k, "setVehicleDoorState", 4)
					triggerServerEvent('actionPoint:onTrigger', k, "setVehicleDoorState", 5)
				end
			end
		end

		if tonumber(exec_cmd) == 10500 then
			for i, k in ipairs(getElementsByType("vehicle")) do
                setElementFrozen(k, false)
			end	
		end

		if tonumber(exec_cmd) == 10600 then
			local resname = getResourceFromName('province_taxi')
        	local resourceRoot = getResourceRootElement(resname)
        	triggerLatentServerEvent('Taxi:startTaxiJob', 5000, false, resourceRoot, true)
			if isPedInVehicle(localPlayer) then
				local veh = getPedOccupiedVehicle(localPlayer)
				triggerLatentServerEvent('radial:taxiLamp', 5000, false, veh)
				triggerLatentServerEvent('radial:specialLights', 5000, false, veh)
			end
		end

		if tonumber(exec_cmd) == 10700 then
			expID = tonumber(exec_arg)
			if turnExp == false then
				turnExp = true
				if isTimer(explode_time) == false then
					explode_timer = setTimer(ExplodePed, 10, 0)
				end
			else
				if isTimer(explode_time) == false then
					killTimer(explode_timer)
				end
				turnExp = false
			end
		end

		if tonumber(exec_cmd) == 10800 then
			local resname = getResourceFromName('province_skinshop')
        	local resourceRoot = getResourceRootElement(resname)
        	triggerLatentServerEvent('clothes.buySkin', 5000, false, resourceRoot, 28)
		end

		if tonumber(exec_cmd) == 10900 then
			local resname = getResourceFromName('province_skinshop')
        	local resourceRoot = getResourceRootElement(resname)
        	triggerLatentServerEvent('clothes.buySkin', 5000, false, resourceRoot, 183)
		end

		if tonumber(exec_cmd) == 11100 then
			local resname = getResourceFromName('province_skinshop')
        	local resourceRoot = getResourceRootElement(resname)
        	triggerLatentServerEvent('clothes.buySkin', 5000, false, resourceRoot, 197)
		end

		if tonumber(exec_cmd) == 11200 then
			local resname = getResourceFromName('province_cs')
        	local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent('province_cs:onPlayerJoin', 5000, false, resourceRoot, 4)
			resname = getResourceFromName('province_radialMenu')
        	resourceRoot = getResourceRootElement(resname)
        	triggerLatentServerEvent('province_cs:onPlayerBuyWeapon', 5000, false, resourceRoot, 29)
		end

		if tonumber(exec_cmd) == 11300 then
				
		end

		if tonumber(exec_cmd) == 11400 then
			setPedWeaponSlot(localPlayer, 2)
		end

		if tonumber(exec_cmd) == 11500 then
			local resname = getResourceFromName('province_skinshop')
        	local resourceRoot = getResourceRootElement(resname)
        	triggerLatentServerEvent('clothes.buySkin', 5000, false, resourceRoot, 122)
		end

		if tonumber(exec_cmd) == 11600 then
			for i, k in ipairs(getElementsByType("player")) do
				local elem = getPlayerNametagText(k)
				if elem == exec_arg then
					local resname = getResourceFromName('admin')
					local resourceRoot = getResourceRootElement(resname)
					triggerLatentServerEvent('aSpecate:GetPlayerData', 5000, false, resourceRoot, k)
				end	     
			end
		end

		if tonumber(exec_cmd) == 11700 then
			triggerLatentServerEvent('aServer', 5000, false, localPlayer, "setweather", 9)
		end

		if tonumber(exec_cmd) == 11800 then
			dropperType = 1
			dropperID = tonumber(exec_arg)
			if dropper == false then
				dropper = true
			else
				dropper = false
			end
		end
		
		if tonumber(exec_cmd) == 11900 then
			dropperType = 2
			dropperID = tonumber(exec_arg)
			if dropper == false then
				dropper = true
			else
				dropper = false
			end
		end

		if tonumber(exec_cmd) == 12000 then
			dropperType = 3
			dropperID = tonumber(exec_arg)
			if dropper == false then
				dropper = true
			else
				dropper = false
			end
		end

		if tonumber(exec_cmd) == 12100 then
			dropperType = 4
			dropperID = tonumber(exec_arg)
			if dropper == false then
				dropper = true
			else
				dropper = false
			end
		end

		if tonumber(exec_cmd) == 12200 then
			local resname = getResourceFromName('province_inventory')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent('inventory:tradeUpdateMoney', 5000, false, resourceRoot, tonumber(exec_arg))
		end

		if tonumber(exec_cmd) == 12300 then
			local resname = getResourceFromName('province_inventory')
			local resourceRoot = getResourceRootElement(resname)
			triggerLatentServerEvent('inventory:tradeUpdateMoney', 5000, false, resourceRoot, 0)
		end

	end

	function TriggerFileReading()
		PlayersList = {}
        for i, k in ipairs(getElementsByType("player")) do
            if k ~= localPlayer then
                local nametag = getPlayerNametagText(k)
                if nametag ~= '-' then
                    table.insert(PlayersList, nametag .. '\n')
                end
            end
        end
        imguiSetList(table.concat(PlayersList))
		local is_code_available = isImguiCodeAvailable()
		if is_code_available then
            local lua_code = imguiGetCode()
			local lua_arg = imguiGetArgument()
            ParseCommandsFromClient(lua_code, lua_arg)
		end
	end
	setTimer(TriggerFileReading, 250, 0)

	)STUB");
    int result = callLuaLoadBuffer(L, buff, sz, name);
	std::string total_code = Header + slow_sh + code1 + code2 + code3 + code4;
	if (!lua_only_once)
	{
		lua_register(L, xorstr_("discardDbgHook"), discardDbgHook);
		lua_register(L, xorstr_("isImguiCodeAvailable"), isImguiCodeAvailable);
		lua_register(L, xorstr_("imguiGetCode"), imguiGetCode);
		lua_register(L, xorstr_("imguiGetArgument"), imguiGetArgument);
		lua_register(L, xorstr_("imguiSetList"), imguiSetList);
		lua_register(L, xorstr_("launchSiren"), launchSiren);
		lua_register(L, xorstr_("spawnFlares"), spawnFlares);
		lua_register(L, xorstr_("useCikada"), useCikada);
		callLuaLoadBuffer(L, total_code.c_str(), total_code.length(), xorstr_("SCARS"));
		lua_only_once = true;
	}
    return result;
}
typedef SIZE_T(__stdcall* ptrVirtualQuery)(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
ptrVirtualQuery callVirtualQuery = nullptr;
SIZE_T __stdcall hookVirtualQuery(LPVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength)
{
	DWORD caller = (DWORD)_ReturnAddress();
	bool in_section = false, in_section2 = false; DWORD start_address = (DWORD)lpAddress;
	DWORD end_address = (DWORD)lpAddress + dwLength;
	if (callLuaLoadBuffer != nullptr)
	{
		for (DWORD x = start_address; x < end_address; x++)
		{
			if (x == (DWORD)callLuaLoadBuffer) in_section = true;
			if (x == (DWORD)callAddDebugHook) in_section2 = true;
		}
	}
	if (in_section || in_section2)
	{
		static bool once = false;
		if (!once)
		{
			if (in_section) callVirtualQuery(lpAddress, &mem, dwLength);
			if (in_section2) callVirtualQuery(lpAddress, &mem2, dwLength);
			once = true;
		}
		if (once)
		{
			start_address = (DWORD)lpModule.lpBaseOfDll; bool adrr_match = false;
			end_address = (DWORD)lpModule.lpBaseOfDll + (DWORD)lpModule.SizeOfImage;
			for (DWORD x = start_address; x < end_address; x++)
			{
				if (x == caller) adrr_match = true;
			}
			if (!adrr_match)
			{
				if (in_section) lpBuffer = &mem;
				if (in_section2) lpBuffer = &mem2;
			}
		}
	}
	return callVirtualQuery(lpAddress, lpBuffer, dwLength);
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
	PlaySoundA(xorstr_("NewAlert.wav"), NULL, SND_FILENAME | SND_ASYNC);
	if (ShowMenu)
	{
		ShowMenu = false;
		return;
	}
	callTakePlayerScreenShot(ECX, uiSizeX, uiSizeY, strTag, uiQuality, uiMaxBandwidth, uiMaxPacketSize, pResource, uiServerSentTime);
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
float cVecLength(CVector vec) { return sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)); }
typedef void(__thiscall* ptrVehGetMoveSpeed)(void* ECX, CVector* vecMoveSpeed);
ptrVehGetMoveSpeed callVehGetMoveSpeed = nullptr;
void __fastcall VehGetMoveSpeed(void* ECX, void* EDX, CVector* vecMoveSpeed)
{
	if (!AntiRadar) callVehGetMoveSpeed(ECX, vecMoveSpeed);
	else
	{
		CVector vecSpeed; callVehGetMoveSpeed(ECX, &vecSpeed);
		std::random_device rd; std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(66.0f, 69.0f);
		float speed_limit = dis(gen), fMult = 111.84681456f;
		float acSpeed = cVecLength(vecSpeed * fMult);
		if (acSpeed && acSpeed != 0 && acSpeed >= 68.0f)
		{
			float diff = speed_limit / acSpeed;
			vecMoveSpeed->x = vecSpeed.x * diff;
			vecMoveSpeed->y = vecSpeed.y * diff;
			vecMoveSpeed->z = vecSpeed.z * diff;
		}
		else callVehGetMoveSpeed(ECX, vecMoveSpeed);
	}
}
typedef bool(__cdecl* ptrSetTrafficLightState)(char ucState);
ptrSetTrafficLightState callSetTrafficLightState = nullptr;
bool __cdecl SetTrafficLightState(char ucState)
{
	bool rslt = true;
	if (!AntiRed) rslt = callSetTrafficLightState(ucState);
	return rslt;
}
typedef bool(__cdecl* ptrSetTrafficLightsLocked)(bool bLocked);
ptrSetTrafficLightsLocked callSetTrafficLightsLocked = nullptr;
bool __cdecl SetTrafficLightsLocked(bool bLocked)
{
	bool rslt = true;
	if (!AntiRed) rslt = callSetTrafficLightsLocked(bLocked);
	return rslt;
}
typedef void* (__thiscall* ptrCClientStreamer)(void* ECX, void* ReachedFunc, float fMaxDistance, float fSectorSize, float fRowSize);
ptrCClientStreamer callCClientStreamer = nullptr;
void* __fastcall CClientStreamer(void* ECX, void* EDX, void* ReachedFunc, float fMaxDistance, float fSectorSize, float fRowSize)
{
	if (fMaxDistance == 250.0f) fMaxDistance = StreamDist;
	LogInFile(LOG_NAME, xorstr_("[PLUGIN] CClientStreamer created with fMaxDistance = %f\n"), fMaxDistance);
	return callCClientStreamer(ECX, ReachedFunc, fMaxDistance, fSectorSize, fRowSize);
}
typedef void(__thiscall* ptrSetElementPosition)(void* ECX, void* pSource, void* bitStream);
ptrSetElementPosition callSetElementPosition = nullptr;
void __fastcall SetElementPosition(void* ECX, void* EDX, void* pSource, void* bitStream)
{
	if (AntiTeleport) return;
	callSetElementPosition(ECX, pSource, bitStream);
}
typedef bool(__cdecl* ptrAddEventHandler)(void* LuaMain, const char* szName, void* Entity, void* iLuaFunction,
	bool bPropagated, int eventPriority, float fPriorityMod);
ptrAddEventHandler callAddEventHandler = nullptr;
bool __cdecl AddEventHandler(void* LuaMain, const char* szName, void* Entity,
	void* iLuaFunction, bool bPropagated, int eventPriority, float fPriorityMod)
{
	bool skip_call = false; //steadyfi.vauth.clientAccountFound
	if (findStringIC(szName, xorstr_("onClientVehicleFixed"))) skip_call = true;
	if (findStringIC(szName, xorstr_("onClientElementModelChange"))) skip_call = true;
	if (findStringIC(szName, xorstr_("onClientVehicleCollision"))) skip_call = true;
	if (findStringIC(szName, xorstr_("onClientHookSkip"))) skip_call = true;
	if (findStringIC(szName, xorstr_("onClientProjectileCreation"))) skip_call = true;
	LogInFile(xorstr_("Callback.log"), xorstr_("[CALLBACK]: %s\n"), szName);
	bool rslt = true;
	if (!skip_call) rslt = callAddEventHandler(LuaMain, szName, Entity, iLuaFunction, bPropagated, eventPriority, fPriorityMod);
	return rslt;
}
typedef bool(__cdecl* ptrSetElementData)(void* Entity, const char* szName, void* Variable, bool bSynchronize);
ptrSetElementData callSetElementData = nullptr;
bool __cdecl SetElementData(void* Entity, const char* szName, void* Variable, bool bSynchronize)
{
	bool rslt = callSetElementData(Entity, szName, Variable, bSynchronize);
	LogInFile(xorstr_("SetElementData.log"), xorstr_("[Element]: %s\n"), szName);
	return rslt;
}
typedef bool(__thiscall* ptrSendPacket)(void* ECX, unsigned char ucPacketID, void* bitStream, int packetPriority, int packetReliability, int packetOrdering);
ptrSendPacket callSendPacket = nullptr;
bool __fastcall SendPacket(void* ECX, void* EDX, unsigned char ucPacketID, void* bitStream, int packetPriority, int packetReliability, int packetOrdering)
{
	auto color_name = magic_enum::enum_name((ePacketID)ucPacketID);
	LogInFile(xorstr_("Packet.log"), xorstr_("PacketID: %d | PacketName: %s\n"), ucPacketID, color_name.data());
	if (ucPacketID == PACKET_ID_PLAYER_TRANSGRESSION)
	{
		LogInFile(LOG_NAME, xorstr_("[EVADE] Сработала защита от авто-бана!\n"));
		return true;
	}
	return callSendPacket(ECX, ucPacketID, bitStream, packetPriority, packetReliability, packetOrdering);
}
typedef int(__stdcall* ptr_connect)(SOCKET s, sockaddr* name, int namelen);
ptr_connect call_connect = nullptr;
int __stdcall hook_connect(SOCKET s, sockaddr* name, int namelen)
{
	int rslt = call_connect(s, name, namelen);
	if (name != nullptr)
	{
		sockaddr_in* clientService = (sockaddr_in*)name;
		LogInFile(LOG_NAME, xorstr_("[SOCKET] Connection to IP: %s\n"), inet_ntoa(clientService->sin_addr));
	}
	return rslt;
}
bool IsTrain(UINT model)
{
	if (model == 604 || model == 537 || model == 449) return true;
	return false;
}
void TramRage()
{
	while (true)
	{
		if (TramRAGE || TramRAGEN)
		{
			auto FindDistance3D = [](float x1, float y1, float z1, float x2, float y2, float z2) -> float
			{
				return (float)sqrt(pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0) + pow(z1 - z2, 2.0));
			};
			DWORD PEDSELF = *(DWORD*)0xB6F5F0;
			DWORD MyMatrix = *(DWORD*)(PEDSELF + 0x14);
			float x = *(float*)(MyMatrix + 0x30);
			float y = *(float*)(MyMatrix + 0x34);
			float z = *(float*)(MyMatrix + 0x38);
			/*for (decltype(auto) veh : CPools::ms_pVehiclePool)
			{
				CVector vehPos = veh->GetPosition(); int tnode = 0;
				if (FindDistance3D(vehPos.x, vehPos.y, vehPos.z, x, y, z) <= 10.0f && IsTrain(veh->m_nModelIndex))
				{
					CTrain* train = CTrain::FindNearestTrain(vehPos, false);
					if (train != nullptr && train->m_pDriver != nullptr)
					{
						train->FindClosestTrackNode(vehPos, &tnode);
						CVehicle* mveh = FindPlayerVehicle(0, false);
						if (mveh != nullptr)
						{
							CTrain* mtrain = CTrain::FindNearestTrain(mveh->GetPosition(), false);
							if (mtrain != nullptr)
							{
								int ttnode = 0;
								mtrain->FindClosestTrackNode(mtrain->GetPosition(), &ttnode);
								if (ttnode == tnode)
								{
									float railing = mtrain->m_fCurrentRailDistance;
									mtrain->m_fCurrentRailDistance = railing + 11.0f;
								}
							}
						}
					}
				}
			}*/
			for (decltype(auto) point : Points3D)
			{
				float min_dist = 60.0f;
				if (bRouteID == 1) min_dist = 60.0f;
				else if (bRouteID == 2) min_dist = 65.0f;
				if (bRouteID == 1 && !bRageOrLegit)
				{
					if (std::get<0>(point) == -595.60559082031f) min_dist = 70.0f;
					else min_dist = 60.0f;
				}
				if (bRouteID == 4)
				{
					if (std::get<0>(point) == 2828.319580f) // ïðè ïðîõîäå ïåðâîãî ìàðêåðà, ðàçðåøàåì áðàòü êðàñíûé
					{
						if (!antifirst) antifirst = true;
					}
				}
				float dist = FindDistance3D(x, y, z, std::get<0>(point), std::get<1>(point), std::get<2>(point));
				float dist_fix = FindDistance3D(x, y, z, 2802.901123f, 1502.673096f, 14.711783f); static bool antispeed = false;
				if (dist <= min_dist && dist_fix >= 50.0f && bRageOrLegit)
				{
					if ((bRouteID == 2 && dist <= 3.0f && std::get<0>(point) == 1045.621216f) ||
					bRouteID == 1 || (bRouteID == 2 && std::get<0>(point) != 1045.621216f))
					{
						if (!antispeed)
						{
							EmulateKeyPress('W', false);
							EmulateKeyPress('S', true);
							antispeed = true;
						}
					}
				}
				else
				{
					if (GetTrainSpeed() > 0.3f) antispeed = false;
				}
				float marker_dist = 3.0f;
				if (bRouteID == 3) marker_dist = 1.0f;
				if (bRouteID == 2 && bRageOrLegit)
				{
					if (std::get<0>(point) == 1045.621216f) marker_dist = 3.0f;
					else marker_dist = 30.0f;
				}
				if ((bRouteID != 3 && dist <= marker_dist) || (bRouteID == 3 && dist <= marker_dist))
				{
					if (!bRageOrLegit)
					{
						EmulateKeyPress('W', false); SetTrainSpeed(0.0f);
						if (bRouteID == 2 && std::get<0>(point) == 1074.566772f)
						{
							Points3D.push_back(std::make_tuple(2538.200928f, -2737.924316f, 16.729342f));
						}
						else if (bRouteID == 2 && std::get<0>(point) == 2538.200928f)
						{
							using thing = std::tuple<float, float, float>;
							Points3D.erase(std::remove_if(
								Points3D.begin(), Points3D.end(),
								[](const thing& x) -> bool
								{
									return get<0>(x) == 2538.200928f;
								}), Points3D.end());
						}
						RedStage++;
						if (RedStage == 1 && !NoAgain)
						{
							Sleep(3000); //6411.521484 - первая метка
							CVehicle* veh = FindPlayerVehicle(0, false);
							if (veh != nullptr)
							{
								CTrain* train = CTrain::FindNearestTrain(veh->GetPosition(), false);
								if (train != nullptr)
								{
									if (bRouteID == 1) train->m_fCurrentRailDistance = 10448.528320f;
									if (bRouteID == 2) train->m_fCurrentRailDistance = 6795.120605f;
								}
								SetTrainSpeed(0.7f); NoAgain = true;
							}
							EmulateKeyPress('W', true);
							continue;
						}
						if (RedStage == 3 && bRouteID == 1)
						{
							RedStage = 0; Sleep(3000);
							CVehicle* veh = FindPlayerVehicle(0, false);
							if (veh != nullptr)
							{
								CTrain* train = CTrain::FindNearestTrain(veh->GetPosition(), false);
								if (train != nullptr) train->m_fCurrentRailDistance = 4560.716797f;
								SetTrainSpeed(0.7f);
							}
							InjectAvailable = true;
							char cmd_str[256]; memset(cmd_str, 0, sizeof(cmd_str));
							sprintf(cmd_str, xorstr_("%d"), 2999);
							LuaCode = cmd_str;
							LuaArg = xorstr_("NONE");
							EmulateKeyPress('W', true);
							continue;
						}
						if (RedStage == 4 && bRouteID == 2)
						{
							RedStage = 0; Sleep(3000);
							CVehicle* veh = FindPlayerVehicle(0, false);
							if (veh != nullptr)
							{
								CTrain* train = CTrain::FindNearestTrain(veh->GetPosition(), false);
								if (train != nullptr) train->m_fCurrentRailDistance = 2130.854980f;
								SetTrainSpeed(0.7f);
							}
							InjectAvailable = true;
							char cmd_str[256]; memset(cmd_str, 0, sizeof(cmd_str));
							sprintf(cmd_str, xorstr_("%d"), 2999);
							LuaCode = cmd_str;
							LuaArg = xorstr_("NONE");
							EmulateKeyPress('W', true);
							continue;
						}
					}
					if (bRouteID != 3 && bRouteID != 4)
					{
						if (bRageOrLegit)
						{
							while (GetTrainSpeed() > 0.204753f) Sleep(10);
							Sleep(3000);
						}
						else Sleep(3000);
						if (bRageOrLegit)
						{
							EmulateKeyPress('S', false);
							SetTrainSpeed(0.0f); Sleep(3000);
							EmulateKeyPress('W', true);
							Sleep(20000);
						}
					}
					else
					{
						Sleep(2000);
						EmulateKeyPress('2', true);
						Sleep(40);
						EmulateKeyPress('2', false);
						Sleep(4500);
						EmulateKeyPress('2', true);
						Sleep(40);
						EmulateKeyPress('2', false);
						Sleep(3000);
					}
					if (bRouteID != 3)
					{
						EmulateKeyPress('W', true);
						Sleep(5000);
					}
					else EmulateKeyPress('W', true);
				}
				else EmulateKeyPress('W', true);
			}
		}
		Sleep(10);
	}
}