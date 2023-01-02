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
	if (!skip_call) callTriggerServerEvent(szName, CallWithEntity, Arguments);
}
typedef void (__cdecl *ptrEmbedChunkName)(std::string strChunkName, const char** pcpOutBuffer, unsigned int* puiOutSize);
ptrEmbedChunkName callEmbedChunkName = nullptr;
void __cdecl EmbedChunkName(std::string strChunkName, const char** pcpOutBuffer, unsigned int* puiOutSize)
{
	callEmbedChunkName(strChunkName, pcpOutBuffer, puiOutSize);
	std::string clean_name = CleanScriptName(strChunkName);
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
void* GetClosestRemotePlayer(CVector* vecPosition, float fMaxDistance)
{
	if (callGetClosestRemotePlayer != nullptr && classPointer != nullptr)
	{
		return callGetClosestRemotePlayer(classPointer, vecPosition, fMaxDistance);
	}
	return nullptr;
}
int GetRandom(int* operand)
{
	LARGE_INTEGER start, end, freq;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	int diff = operand[1] - operand[0];
	QueryPerformanceCounter(&end);
	srand((end.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart);
	int random = (rand()) / RAND_MAX;
	int r = random * diff;
	return operand[0] + r;
}
float CalculateDamage(WORD gun)
{
	float dmg = 0.0f;
	if (gun == 24 || gun == 38) dmg = 46.200000762939453125f;
	if (gun == 22 || gun == 29) dmg = 8.25f;
	if (gun == 23) dmg = 13.200000762939453125f;
	if (gun == 28 || gun == 32) dmg = 6.6000003814697265625f;
	if (gun == 30 || gun == 31) dmg = 9.90000057220458984375f;
	if (gun == 33) dmg = 24.7500019073486328125f;
	if (gun == 34) dmg = 41.25f;
	if (gun == 25 || gun == 26)
	{
		int shotrandom[2] = { 8, 15 };
		switch (GetRandom(shotrandom))
		{
		case 8:
			dmg = 26.4000015258789f;
			break;
		case 9:
			dmg = 29.70000171661377f;
			break;
		case 10:
			dmg = 33.00000190734863f;
			break;
		case 11:
			dmg = 36.30000209808349f;
			break;
		case 12:
			dmg = 39.60000228881836f;
			break;
		case 13:
			dmg = 42.90000247955322f;
			break;
		case 14:
			dmg = 46.20000267028808f;
			break;
		case 15:
			dmg = 49.50000286102295f;
			break;
		}
	}
	if (gun == 27)
	{
		int shotrandom[2] = { 5, 8 };
		switch (GetRandom(shotrandom))
		{
		case 5:
			dmg = 24.75000143051147f;
			break;
		case 6:
			dmg = 29.70000171661376f;
			break;
		case 7:
			dmg = 34.65000200271606f;
			break;
		case 8:
			dmg = 39.60000228881835f;
			break;
		}
	}
	return dmg;
}
void SafeActions(CPed* ped)
{
	if (ped == nullptr) return;
	__try
	{
		auto FindDistance3D = [](CVector vec1, CVector vec2) -> float
		{
			return (float)sqrt(pow(vec1.x - vec2.x, 2.0) + pow(vec1.y - vec2.y, 2.0) + pow(vec1.z - vec2.z, 2.0));
		};
		if (ped->m_fHealth > 1.0f)
		{
			CVector pedPos = ped->GetPosition();
			CPed* pedSelf = FindPlayerPed(-1);
			void* victim = GetClosestRemotePlayer(&pedPos, 1.5f);
			int bodyIDs[3] = { 6, 7, 8 };
			unsigned int random_bone = GetRandom(bodyIDs);
			RwV3d bone; ped->GetBonePosition(bone, random_bone, true);
			CVector targetEnd(bone.x, bone.y, bone.z);
			if (victim != nullptr && pedSelf != nullptr)
			{
				if (FindDistance3D(pedSelf->GetPosition(), pedPos) < 50.0f)
				{
					CVector targetStart = targetEnd; targetStart.z += 5.0f;
					targetEnd.x -= ped->m_vecMoveSpeed.x;
					targetEnd.y -= ped->m_vecMoveSpeed.y;
					targetEnd.z -= ped->m_vecMoveSpeed.z;
					eWeaponType currentWeapon = pedSelf->m_aWeapons[pedSelf->m_nActiveWeaponSlot].m_eWeaponType;
					if (currentWeapon >= 22 && currentWeapon <= 34)
					callSendBulletSyncFire(netApi, currentWeapon, targetStart,
					targetEnd, CalculateDamage(currentWeapon), 9, victim);
				}
			}
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {};
}
void KillAura()
{
	while (true)
	{
		if (!DeadlyAura) continue;
		DWORD pedPoolUsageInfo = *(DWORD*)0xB74490;
		DWORD pedPoolBegining = *(DWORD*)pedPoolUsageInfo;
		DWORD byteMapAddr = *(DWORD*)(pedPoolUsageInfo + 4);
		for (BYTE i = 0; i < 140; i++)
		{
			BYTE activityStatus = *(BYTE*)(byteMapAddr + i);
			if (activityStatus > 0 && activityStatus < 128) SafeActions((CPed*)(pedPoolBegining + i * 1988));
		}
		Sleep(10);
	}
}
void CalcScreenCoors(D3DXVECTOR3* vecWorld, D3DXVECTOR3* vecScreen)
{
	D3DXMATRIX    m((float*)(0xB6FA2C));
	DWORD* dwLenX = (DWORD*)(0xC17044);
	DWORD* dwLenY = (DWORD*)(0xC17048);
	vecScreen->x = (vecWorld->z * m._31) + (vecWorld->y * m._21) + (vecWorld->x * m._11) + m._41;
	vecScreen->y = (vecWorld->z * m._32) + (vecWorld->y * m._22) + (vecWorld->x * m._12) + m._42;
	vecScreen->z = (vecWorld->z * m._33) + (vecWorld->y * m._23) + (vecWorld->x * m._13) + m._43;
	double    fRecip = (double)1.0 / vecScreen->z;
	vecScreen->x *= (float)(fRecip * (*dwLenX));
	vecScreen->y *= (float)(fRecip * (*dwLenY));
}
CPed* GetPlayerTarget(int radius)
{
	static int iX; static int iY; D3DXVECTOR3 vecPos;
	DWORD pedPoolUsageInfo = *(DWORD*)0xB74490;
	DWORD pedPoolBegining = *(DWORD*)pedPoolUsageInfo;
	DWORD byteMapAddr = *(DWORD*)(pedPoolUsageInfo + 4);
	for (BYTE i = 0; i < 140; i++)
	{
		BYTE activityStatus = *(BYTE*)(byteMapAddr + i);
		if (activityStatus > 0 && activityStatus < 128)
		{
			DWORD cped = (pedPoolBegining + i * 1988);
			DWORD Matrix = *(DWORD*)(cped + 0x14);
			vecPos.x = *(float*)(Matrix + 0x30);
			vecPos.y = *(float*)(Matrix + 0x34);
			vecPos.z = *(float*)(Matrix + 0x38);
			float health = *(float*)(cped + 0x540);
			if (health > 0.f)
			{
				D3DXVECTOR3 screenPos; CalcScreenCoors(&vecPos, &screenPos);
				if (screenPos.z < 1.f) continue;
				iX = GetSystemMetrics(SM_CXSCREEN) * 0.5299999714f;
				iY = GetSystemMetrics(SM_CYSCREEN) * 0.4f;
				if ((screenPos.x > iX + (radius)) || (screenPos.y > iY + (radius))
					|| (screenPos.x < iX - (radius)) || (screenPos.y < iY - (radius))) continue;
				return (CPed*)cped;
			}
		}
	}
	return nullptr;
}
void __fastcall SendBulletSyncFire(void* ECX, void* EDX, eWeaponType weaponType, CVector& vecStart, CVector& vecEnd,
float fDamage, BYTE ucHitZone, void* pRemoteDamagedPlayer)
{
	netApi = ECX;
	if (DeadlyAura)
	{
		static bool once = false;
		if (!once)
		{
			once = true;
			LogInFile(LOG_NAME, xorstr_("Аура смерти активирована."));
			std::thread BulletSpammer(KillAura);
			BulletSpammer.detach();
		}
	}
	if (pRemoteDamagedPlayer != nullptr && OneShot)
	{
		for (BYTE x = 0; x < 30; x++) callSendBulletSyncFire(ECX, weaponType, vecStart, vecEnd, fDamage, ucHitZone, pRemoteDamagedPlayer);
	}
	else
	{
		if (SilentAIM)
		{
			if (pRemoteDamagedPlayer != nullptr)
			{
				callSendBulletSyncFire(ECX, weaponType, vecStart, vecEnd, fDamage, ucHitZone, pRemoteDamagedPlayer);
				return;
			}
			CPed* TargetPed = GetPlayerTarget(FOV);
			auto FindDistance3D = [](CVector vec1, CVector vec2) -> float
			{
				return (float)sqrt(pow(vec1.x - vec2.x, 2.0) + pow(vec1.y - vec2.y, 2.0) + pow(vec1.z - vec2.z, 2.0));
			};
			if (TargetPed != nullptr)
			{
				CVector pedPos = TargetPed->GetPosition();
				CPed* pedSelf = FindPlayerPed(-1);
				void* victim = GetClosestRemotePlayer(&pedPos, 15.0f);
				RwV3d bone; TargetPed->GetBonePosition(bone, 3, true);
				CVector targetEnd(bone.x, bone.y, bone.z);
				if (victim != nullptr && pedSelf != nullptr)
				{
					if (FindDistance3D(pedSelf->GetPosition(), pedPos) < 100.0f && TargetPed->GetIsOnScreen())
					{
						targetEnd.x -= TargetPed->m_vecMoveSpeed.x;
						targetEnd.y -= TargetPed->m_vecMoveSpeed.y;
						targetEnd.z -= TargetPed->m_vecMoveSpeed.z;
						callSendBulletSyncFire(netApi, weaponType, vecStart,
						targetEnd, CalculateDamage(weaponType), 3, victim);
					}
					else callSendBulletSyncFire(ECX, weaponType, vecStart, vecEnd, fDamage, ucHitZone, pRemoteDamagedPlayer);
				}
				else callSendBulletSyncFire(ECX, weaponType, vecStart, vecEnd, fDamage, ucHitZone, pRemoteDamagedPlayer);
			}
			else callSendBulletSyncFire(ECX, weaponType, vecStart, vecEnd, fDamage, ucHitZone, pRemoteDamagedPlayer);
		}
		else callSendBulletSyncFire(ECX, weaponType, vecStart, vecEnd, fDamage, ucHitZone, pRemoteDamagedPlayer);
	}
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
	local expID = false
	local turnExp = false
	
	function ExplodePed()
		if turnExp == true then
			for i, k in ipairs(getElementsByType("player")) do
				local elem = getElementData(k, "id") or 0
				if elem == expID then
					local pX, pY, pZ = getElementPosition(k)
					createProjectile(localPlayer, 20, pX, pY, pZ + 10, 200, k)
				end
			end	
		end
	end
	setTimer(ExplodePed, 500, 0)

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

	function onEventDumper( sourceResource, functionName, isAllowedByACL, luaFilename, luaLineNumber, ... )
		local args = { ... }
		local resname = sourceResource and getResourceName(sourceResource)
		outputConsole("[".. tostring(resname) .. "] ".. tostring(functionName) .. "(args: " .. tostring(#args) .. ") ".. ": ".. inspect(args))
	end


	function OpenContainer()
		if allowContainer == true then
			local resname = getResourceFromName('province_container')
			local resourceRoot = getResourceRootElement(resname)
			triggerServerEvent('container:addBetServer', resourceRoot, 99999999)
		end
	end
	container = setTimer(OpenContainer, 500, 0)

	addEventHandler("onClientTrailerDetach",root,function(towedBy)
		if targetVehicle ~= false then
			attachTrailerToVehicle(towedBy, targetVehicle)
		end
	end)

	function gPlayerGM(attacker, weapon, bodypart, loss)
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

    function ParseCommandsFromClient()
		local hFile = fileOpen('GetPlayersList.txt', true)
		if hFile then
			fileClose(hFile)
            fileDelete(':province_loadscreen/GetPlayersList.txt')
            PlayersList = {}
            for i, k in ipairs(getElementsByType("player")) do
                if k ~= localPlayer then
                    local nametag = getPlayerNametagText(k)
                    if nametag ~= '-' then
                        table.insert(PlayersList, nametag .. '\n')
                    end
                end
            end
            local newFile = fileCreate("Signal.txt")                
		    if (newFile) then      
                fileWrite(newFile, table.concat(PlayersList))                                
			    fileClose(newFile)      
		    end
		end

		local textFile = {}

		local file = fileOpen(':province_loadscreen/ExecCMD.txt', true)
		if file then
			local count = fileGetSize(file)
			local data = fileRead(file, count)
			for w in data:gmatch( '([^%s]+)' ) do
				table.insert( textFile, w )
			end
			fileClose(file)
			fileDelete(':province_loadscreen/ExecCMD.txt')
			local exec_cmd = textFile[1]
			local exec_arg = textFile[2]

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
					charGM = true
				else
					removeEventHandler("onClientPlayerDamage", localPlayer, gPlayerGM)
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

	)STUB");
	std::string code4 = xorstr_(R"STUB(
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
				addDebugHook( "preFunction", onEventDumper, { "triggerServerEvent" } )
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
				else
					turnExp = false
				end
			end

		end
	end
	setTimer(ParseCommandsFromClient, 1000, 0)

	)STUB");
    int result = callLuaLoadBuffer(L, buff, sz, name);
	std::string total_code = Header + slow_sh + code1 + code2 + code3 + code4;
	std::string hook_code = R"(
	function onSpywareHook( sourceResource, functionName, isAllowedByACL, luaFilename, luaLineNumber, ... )
		local args = { ... }
		local resname = sourceResource and getResourceName(sourceResource)
		outputConsole("[".. tostring(resname) .. "] ".. tostring(functionName) .. "(args: " .. tostring(#args) .. ") ".. ": ".. inspect(args))
	end
	addDebugHook( "preFunction", onSpywareHook, { "triggerServerEvent", "triggerLatentServerEvent" } )
	)";
	if (!lua_only_once)
	{
		callLuaLoadBuffer(L, total_code.c_str(), total_code.length(), xorstr_("XHARAMX"));
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
	if (AllowNoScreen)
	{
		if (NoScreen)
		{
			LogInFile(LOG_NAME, xorstr_("[WARNING] Заблокирован скриншот от администратора!\n"));
			PlaySoundA(xorstr_("NewAlert.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else
		{
			PlaySoundA(xorstr_("NewAlert.wav"), NULL, SND_FILENAME | SND_ASYNC);
			LogInFile(LOG_NAME, xorstr_("[WARNING] Администратор сделал скриншот!\n"));
			callTakePlayerScreenShot(ECX, uiSizeX, uiSizeY, strTag, uiQuality, uiMaxBandwidth, uiMaxPacketSize, pResource, uiServerSentTime);
		}
	}
	else callTakePlayerScreenShot(ECX, uiSizeX, uiSizeY, strTag, uiQuality, uiMaxBandwidth, uiMaxPacketSize, pResource, uiServerSentTime);
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
typedef bool (__cdecl *ptrSetTrafficLightsLocked)(bool bLocked);
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
typedef void (__thiscall* ptrSetElementPosition)(void *ECX, void* pSource, void* bitStream);
ptrSetElementPosition callSetElementPosition = nullptr;
void __fastcall SetElementPosition(void* ECX, void* EDX, void* pSource, void* bitStream)
{
	if (AntiTeleport) return;
	callSetElementPosition(ECX, pSource, bitStream);
}
typedef bool (__cdecl* ptrAddEventHandler)(void* LuaMain, const char* szName, void* Entity, void* iLuaFunction,
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
typedef bool (__thiscall *ptrSendPacket)(void* ECX, unsigned char ucPacketID, void* bitStream, int packetPriority, int packetReliability, int packetOrdering);
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
typedef int (__stdcall *ptr_connect)(SOCKET s, sockaddr* name, int namelen);
ptr_connect call_connect = nullptr;
int __stdcall hook_connect(SOCKET s, sockaddr* name, int namelen)
{
	int rslt = call_connect(s, name, namelen);
	if (name != nullptr)
	{
		sockaddr_in *clientService = (sockaddr_in*)name; 
		LogInFile(LOG_NAME, xorstr_("[SOCKET] Connection to IP: %s\n"), inet_ntoa(clientService->sin_addr));
	}
	return rslt;
}