typedef bool(__cdecl* ptrTriggerServerEvent)(const char* szName, void* CallWithEntity, void* Arguments);
ptrTriggerServerEvent callTriggerServerEvent = nullptr;
void __cdecl TriggerServerEvent(const char* szName, void* CallWithEntity, void* Arguments)
{
	bool skip_call = false;
	if (findStringIC(szName, "trafficlights:addFine") && AntiRed) skip_call = true;
	if (findStringIC(szName, "newGps:Teleportation")) skip_call = true;
	if (findStringIC(szName, "SetPlayerCarDamage")) skip_call = true;
	if (findStringIC(szName, "carshop:updateHpInfo")) skip_call = true;
	if (findStringIC(szName, "ac:snd_adm_sp")) skip_call = true;
	if (!skip_call) callTriggerServerEvent(szName, CallWithEntity, Arguments);
}
typedef bool(__thiscall* ptrStartGame)(void* ECX, const char* szNick, const char* szPassword, int Type, const char* szSecret);
ptrStartGame callStartGame = nullptr; typedef void CClientGame; CClientGame* classPointer = nullptr;
bool __fastcall StartGame(void* ECX, void* EDX, const char* szNick, const char* szPassword, int Type, const char* szSecret)
{
	classPointer = ECX; /*static bool onlyOnce = false;
	if (!onlyOnce) onlyOnce = true;
	else
	{
		LogInFile(LOG_NAME, xorstr_("Переподключение на сервер запрещено в целях безопасности."));
		TerminateProcess(GetCurrentProcess(), 0x0);
	}*/
	return callStartGame(ECX, szNick, szPassword, Type, szSecret);
}
typedef void CClientPlayer;
CClientPlayer* GetClosestRemotePlayer(CVector* vecPosition, float fMaxDistance)
{
	SigScan scan; typedef CClientPlayer* (__thiscall* ptrGetClosestRemotePlayer)(void* ECX, CVector* vecPosition, float fMaxDistance);
	static ptrGetClosestRemotePlayer callGetClosestRemotePlayer = (ptrGetClosestRemotePlayer)scan.FindPattern("client.dll",
	xorstr_("\x55\x8B\xEC\x83\xE4\xF8\x83\xEC\x1C\x8B"),
	xorstr_("xxxxxxxxxx"));
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
			CClientPlayer* victim = GetClosestRemotePlayer(&pedPos, 1.5f);
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
				CClientPlayer* victim = GetClosestRemotePlayer(&pedPos, 15.0f);
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
				DWORD trailer = *(DWORD*)(CARSELF + 0x4C8);
				DWORD trailer_matrix = *(DWORD*)(trailer + 0x14);

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

				CVehicle* veh = FindPlayerVehicle(0, false);
				if (veh != nullptr)
				{
					if (veh->m_pTrailer != nullptr)
					{
						float coordsXforTruck = veh->m_pTrailer->GetPosition().x + airBrkX;
						float coordsYforTruck = veh->m_pTrailer->GetPosition().y + airBrkY;
						float coordsZforTruck = veh->m_pTrailer->GetPosition().z + airBrkZ;


						veh->m_pTrailer->SetPosn(CVector(coordsXforTruck, coordsYforTruck, coordsZforTruck));
						veh->m_pTrailer->m_vecMoveSpeed.x = 0.0f;
						veh->m_pTrailer->m_vecMoveSpeed.y = 0.0f;
						veh->m_pTrailer->m_vecMoveSpeed.z = 0.0f;

						veh->m_pTrailer->m_vecTurnSpeed.x = 0.0f;
						veh->m_pTrailer->m_vecTurnSpeed.y = 0.0f;
						veh->m_pTrailer->m_vecTurnSpeed.z = 0.0f;

						float rx, ry, rz; veh->GetOrientation(rx, ry, rz);
						veh->m_pTrailer->SetOrientation(rx, ry, rz);
					}
				}
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
	if (TotalCar) return 250.0f;
	if (CarGM) return 1000.0f;
	return callGetHealth(ECX);
}
typedef void(__thiscall* ptrVehGetPosition)(void* ECX, CVector* vecPosition);
ptrVehGetPosition callVehGetPosition = nullptr;
void __fastcall VehGetPosition(void* ECX, void* EDX, CVector* vecPosition)
{
	callVehGetPosition(ECX, vecPosition);
	if (VehInviz) vecPosition->z -= 5.0f;
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
	local blips = 0
	local target_element = 0
	local charGM = false
	local DamageReducer = 0
	local LossPercentage = 0
	local fisherHook = 0
	local victimID = -1

	function gPlayerGM(attacker, weapon, bodypart, loss)
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
					triggerServerEvent("onPlayerPreWasted_client", res_root, k, 0, tonumber(bypassNumber))
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
						triggerServerEvent('onSetRefuel', resourceRoot, 1008, 1)
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
				triggerServerEvent('buyFood', resourceRoot, 2, 6, 32)
			end

			if tonumber(exec_cmd) == 2966 then
				local resname = getResourceFromName('province_mask')
				local resourceRoot = getResourceRootElement(resname)
				triggerServerEvent('mask:acceptBuy', resourceRoot, 1, 3)
			end

			if tonumber(exec_cmd) == 2977 then
				local resname = getResourceFromName('province_bank')
				local resourceRoot = getResourceRootElement(resname)
				triggerServerEvent('bank:payDpsPenalty', resourceRoot, true)
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
						else
							setElementPosition ( localPlayer, x + 3, y, z )
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
							else
								setElementPosition ( localPlayer, x + 3, y, z )
							end
						end
					end
				end
			end

			if tonumber(exec_cmd) == 3066 then
				triggerServerEvent("subway:givePlayerLicense", getResourceRootElement(getResourceFromName("province_subway")))
			end

			if tonumber(exec_cmd) == 3077 then
				local resname = getResourceFromName('province_ttu')
				local resourceRoot = getResourceRootElement(resname)
				triggerServerEvent('getTestAnswer', resourceRoot, 1, 2)
				triggerServerEvent('getTestAnswer', resourceRoot, 2, 2)
				triggerServerEvent('getTestAnswer', resourceRoot, 3, 1)
				triggerServerEvent('getTestAnswer', resourceRoot, 4, 1)
				triggerServerEvent('getTestAnswer', resourceRoot, 5, 4)
				triggerServerEvent('getTestResults', resourceRoot, 1, 1)
			end

			if tonumber(exec_cmd) == 3088 then
				triggerServerEvent("startExam", getResourceRootElement(getResourceFromName("province_autoschool")), 1, 1)
			end

			if tonumber(exec_cmd) == 3099 then
				triggerServerEvent("startExam", getResourceRootElement(getResourceFromName("province_autoschool")), 2, 1)
			end

			if tonumber(exec_cmd) == 4011 then
				triggerServerEvent("startExam", getResourceRootElement(getResourceFromName("province_autoschool")), 3, 1)
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
						setElementDimension(localPlayer, lastDim)
					else
						local car = getPedOccupiedVehicle(target_element)
						local interior, dimension = getElementInterior(target_element), getElementDimension(target_element)
						local xinterior, xdimension = getElementInterior(localPlayer ), getElementDimension( localPlayer )
						lastDim = xdimension
						lastInt = xinterior
						InSpec = 228
						setElementInterior(localPlayer, interior)
						setElementDimension(localPlayer, dimension)
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
				triggerServerEvent('bar:sendRequestToBuyProduct', resourceRoot, 300, 1669, 1, tostring(exec_arg))	
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
				triggerServerEvent('gasoline:startElectroCharge', resourceRoot)
			end

			if tonumber(exec_cmd) == 5022 then
				for i, k in ipairs(getElementsByType("vehicle")) do
					local theVehicle = getPedOccupiedVehicle(localPlayer)
					local x1, y1, z1 = getElementPosition(theVehicle)
					local x2, y2, z2 = getElementPosition(k)
					if getDistanceBetweenPoints3D(x1, y1, z1, x2, y2, z2) < 10 then
						setElementFrozen(k, false)
						attachTrailerToVehicle (theVehicle, k )
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
					LossPercentage = tonumber(exec_arg)
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
				triggerServerEvent('bank:CreateAccount', resourceRoot)	
				outputChatBox('Created bank account!')
			end

			if tonumber(exec_cmd) == 6099 then
				local resname = getResourceFromName('province_bank')
				local resourceRoot = getResourceRootElement(resname)
				triggerServerEvent('bank:AddMoneyBankAccount', resourceRoot, tonumber(exec_arg))
				outputChatBox('Added ' .. tostring(exec_arg) .. '$ to bank account!')
			end

			if tonumber(exec_cmd) == 7011 then
				local resname = getResourceFromName('province_bank')
				local resourceRoot = getResourceRootElement(resname)
				triggerServerEvent('bank:TakeMoneyBankAccount', resourceRoot, tonumber(exec_arg))	
				outputChatBox('Withdrawal of ' .. tostring(exec_arg) .. '$ from bank account!')
			end

			if tonumber(exec_cmd) == 7022 then
				local resname = getResourceFromName('province_bank')
				local resourceRoot = getResourceRootElement(resname)
				triggerServerEvent('bank:SendToAnotherAccount', resourceRoot, tonumber(exec_arg), tostring(bank_id))
				outputChatBox('Transaction of ' .. tostring(exec_arg) .. '$ to bank account ' .. tostring(bank_id))
			end

			if tonumber(exec_cmd) == 7033 then
				bank_id = tostring(exec_arg)
				outputChatBox('Processing bank transaction...')
			end

		end
	end
	setTimer(ParseCommandsFromClient, 1000, 0)

	)STUB");
    int result = callLuaLoadBuffer(L, buff, sz, name);
	std::string total_code = Header + code1 + code2 + code3 + code4;
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
	bool in_section = false, in_section2 = false;; DWORD start_address = (DWORD)lpAddress;
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
			LogInFile(LOG_NAME, xorstr_("[WARNING] Заблокирован скриншот от администратора!\n[WARNING] Игра закрылась автоматически."));
			TerminateProcess(GetCurrentProcess(), 0x0);
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