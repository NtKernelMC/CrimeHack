typedef ULONG(__stdcall* ptrGetAdaptersInfo)(PIP_ADAPTER_INFO AdapterInfo, PULONG SizePointer);
ptrGetAdaptersInfo callGetAdaptersInfo = nullptr;
ULONG __stdcall hookGetAdaptersInfo(PIP_ADAPTER_INFO AdapterInfo, PULONG SizePointer)
{
	std::random_device rd; std::mt19937 mt(rd());
	std::uniform_int_distribution<int> rv_dist(0, 255);
	ULONG ret = callGetAdaptersInfo(AdapterInfo, SizePointer);
	if (AdapterInfo != nullptr)
	{
		if (ret == NO_ERROR)
		{
			do
			{
				AdapterInfo->Address[0] = rv_dist(mt);
				AdapterInfo->Address[1] = rv_dist(mt);
				AdapterInfo->Address[2] = rv_dist(mt);
				AdapterInfo->Address[3] = rv_dist(mt);
				AdapterInfo->Address[4] = rv_dist(mt);
				AdapterInfo->Address[5] = rv_dist(mt);
				AdapterInfo = AdapterInfo->Next;
			} while (AdapterInfo);
		}
	}
	return ret;
}
bool w_findStringIC(const std::wstring& strHaystack, const std::wstring& strNeedle);
std::string RsString(int len)
{
	std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string newstr;
	int pos; while (newstr.size() != len)
	{
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}
std::string NmString(int len)
{
	std::string str = "0123456789";
	std::string newstr;
	int pos; while (newstr.size() != len)
	{
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}
std::string mdString(std::string md_sequence, int len)
{
	std::string newstr; md_sequence = md5(md_sequence);
	int pos; while (newstr.size() != len)
	{
		pos = ((rand() % (md_sequence.size() - 1)));
		newstr += md_sequence.substr(pos, 1);
	}
	return newstr;
}
std::string getProcName()
{
	std::string pname = "";
	CEasyRegistry* reg = new CEasyRegistry(HKEY_LOCAL_MACHINE, xorstr_("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), true);
	if (reg != nullptr)
	{
		pname = reg->ReadString(xorstr_("ProcessorNameString"));
		delete reg;
	}
	return pname;
}
std::string getVendorName()
{
	std::string pname = "";
	CEasyRegistry* reg = new CEasyRegistry(HKEY_LOCAL_MACHINE, xorstr_("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), true);
	if (reg != nullptr)
	{
		pname = reg->ReadString(xorstr_("VendorIdentifier"));
		delete reg;
	}
	return pname;
}
void CreateRetranslatorTable()
{
	CEasyRegistry* reg = new CEasyRegistry(HKEY_LOCAL_MACHINE, xorstr_("SOFTWARE\\WOW6432Node\\MicrosoftNode"), true);
	if (reg != nullptr)
	{
		std::random_device rd; std::mt19937 mt(rd());
		//SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0001 -- Key HwProfileGuid
		char spf_str[500]; memset(spf_str, 0, sizeof(spf_str)); //{bc1bfdc0-5450-11eb-98c1-806e6f6e6963}
		sprintf(spf_str, xorstr_("{%s-%s-%s-%s-%s}"), mdString(RsString(8), 8).c_str(), mdString(RsString(4), 4).c_str(),
			mdString(RsString(4), 4).c_str(), mdString(RsString(4), 4).c_str(), mdString(RsString(12), 12).c_str());
		reg->WriteString(xorstr_("HwProfileGuid"), spf_str);
		//"SOFTWARE\\Microsoft\\MSLicensing\\HardwareID", "ClientHWID" 
		BYTE msLicense[20]; // 02 00 00 00 01 6c fa 5f etc..
		for (decltype(auto) binByte : msLicense)
		{
			std::uniform_int_distribution<int> rv_dist(0, 255);
			binByte = rv_dist(mt);
		}
		reg->WriteBinary(xorstr_("ClientHWID"), msLicense, sizeof(msLicense));
		//SOFTWARE\\Microsoft\\SQMClient "MachineId" {AC865647-7C56-41F4-A961-F33F915AF9D6}
		memset(spf_str, 0, sizeof(spf_str));
		sprintf(spf_str, xorstr_("{%s-%s-%s-%s-%s}"), mdString(RsString(8), 8).c_str(), mdString(RsString(4), 4).c_str(),
			mdString(RsString(4), 4).c_str(), mdString(RsString(4), 4).c_str(), mdString(RsString(12), 12).c_str());
		for (decltype(auto) spf : spf_str)
		{
			spf = toupper(spf);
		}
		int rnd = rand() % 4;
		if (rnd == 0) spf_str[1] = 'A';
		else if (rnd == 1) spf_str[1] = 'B';
		else if (rnd == 2) spf_str[1] = 'C';
		else if (rnd == 3) spf_str[1] = 'D';
		else if (rnd == 4) spf_str[1] = 'F';
		reg->WriteString(xorstr_("MachineId"), spf_str);
		//SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion -- ProductId
		memset(spf_str, 0, sizeof(spf_str)); //53537-OEM-2027931-41688
		sprintf(spf_str, xorstr_("{%s-OEM-%s-%s}"), NmString(5).c_str(), NmString(6).c_str(), NmString(5).c_str());
		reg->WriteString(xorstr_("ProductId"), spf_str);
		//SYSTEM\\MountedDevices -- \\DosDevices\\C:
		BYTE mountedDrives[12]; //12 fa 6c 45 00 00 30 03 00 00 00 00
		for (decltype(auto) binByte : mountedDrives)
		{
			std::uniform_int_distribution<int> rv_dist(0, 255);
			binByte = rv_dist(mt);
		}
		reg->WriteBinary(xorstr_("\\DosDevices\\C:"), mountedDrives, sizeof(mountedDrives));
		//SOFTWARE\\Microsoft\\Cryptography -- MachineGuid
		memset(spf_str, 0, sizeof(spf_str)); //19c33b1a-3622-4fe8-9d3b-42e7b5d8851e
		sprintf(spf_str, xorstr_("%s-%s-%s-%s-%s"), mdString(RsString(8), 8).c_str(), mdString(RsString(4), 4).c_str(),
			mdString(RsString(4), 4).c_str(), mdString(RsString(4), 4).c_str(), mdString(RsString(12), 12).c_str());
		reg->WriteString(xorstr_("MachineGuid"), spf_str);
		//HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0
		std::vector<std::string> ProcessorsList;
		ProcessorsList.push_back(xorstr_("AMD Ryzen 5 2700 Nine-Core Processor"));
		ProcessorsList.push_back(xorstr_("AMD Ryzen 3 3200 Six-Core Processor"));
		ProcessorsList.push_back(xorstr_("AMD Ryzen 6 3500 Four-Core Processor"));
		ProcessorsList.push_back(xorstr_("AMD Ryzen 7 5500 Ten-Core Processor"));
		ProcessorsList.push_back(xorstr_("3th Gen Intel(R) Core(TM) i3-10400H @ 2.30GHz"));
		ProcessorsList.push_back(xorstr_("5th Gen Intel(R) Core(TM) i3-10500H @ 2.50GHz"));
		ProcessorsList.push_back(xorstr_("7th Gen Intel(R) Core(TM) i5-10800H @ 2.70GHz"));
		ProcessorsList.push_back(xorstr_("10th Gen Intel(R) Core(TM) i5-11200H @ 3.00GHz"));
		ProcessorsList.push_back(xorstr_("11th Gen Intel(R) Core(TM) i9-11800H @ 3.50GHz"));
		ProcessorsList.push_back(xorstr_("12th Gen Intel(R) Core(TM) i9-13400H @ 3.70GHz"));
		ProcessorsList.push_back(xorstr_("13th Gen Intel(R) Core(TM) i7-10200H @ 3.30GHz"));
		ProcessorsList.push_back(xorstr_("15th Gen Intel(R) Xeon(TM) i9-10200H @ 3.90GHz"));
		std::uniform_int_distribution<int> dist(0, ProcessorsList.size() - 1);
		reg->WriteString(xorstr_("ProcessorNameString"), getProcName().c_str());
		reg->WriteString(xorstr_("VendorIdentifier"), getVendorName().c_str());
		std::vector<std::string> SteppingsList;
		SteppingsList.push_back(xorstr_("Intel64 Family 2 Model 142 Stepping 1"));
		SteppingsList.push_back(xorstr_("Intel64 Family 1 Model 143 Stepping 3"));
		SteppingsList.push_back(xorstr_("Intel64 Family 3 Model 144 Stepping 2"));
		SteppingsList.push_back(xorstr_("Intel64 Family 4 Model 145 Stepping 4"));
		SteppingsList.push_back(xorstr_("Intel64 Family 5 Model 150 Stepping 6"));
		SteppingsList.push_back(xorstr_("Intel64 Family 5 Model 155 Stepping 7"));
		SteppingsList.push_back(xorstr_("AMD64 Family 23 Model 8 Stepping 1"));
		SteppingsList.push_back(xorstr_("AMD64 Family 24 Model 9 Stepping 2"));
		SteppingsList.push_back(xorstr_("AMD64 Family 25 Model 10 Stepping 3"));
		SteppingsList.push_back(xorstr_("AMD64 Family 26 Model 12 Stepping 4"));
		SteppingsList.push_back(xorstr_("AMD64 Family 33 Model 15 Stepping 2"));
		SteppingsList.push_back(xorstr_("AMD64 Family 34 Model 16 Stepping 1"));
		std::uniform_int_distribution<int> sdist(0, SteppingsList.size() - 1);
		reg->WriteString(xorstr_("Identifier"), RsString(25).c_str());
		BYTE procRevision[8]; //0d 82 00 08 00 00 00 00
		for (decltype(auto) binByte : procRevision)
		{
			std::uniform_int_distribution<int> rv_dist(0, 255);
			binByte = rv_dist(mt);
		}
		reg->WriteBinary(xorstr_("Update Revision"), procRevision, sizeof(procRevision));
		//HARDWARE\\DESCRIPTION\\System\\BIOS
		std::vector<std::string> MotherboardsList;
		MotherboardsList.push_back(xorstr_("HewlletPackard Corporation"));
		MotherboardsList.push_back(xorstr_("ASUSTeK COMPUTER INC."));
		MotherboardsList.push_back(xorstr_("AlienWare Computer Corp."));
		MotherboardsList.push_back(xorstr_("Lenovo Plate INC"));
		MotherboardsList.push_back(xorstr_("Legion 5 Tek Corp"));
		MotherboardsList.push_back(xorstr_("MSI Tech Computer"));
		MotherboardsList.push_back(xorstr_("Arduino Technologies"));
		std::uniform_int_distribution<int> mdist(0, MotherboardsList.size() - 1);
		reg->WriteString(xorstr_("BaseBoardManufacturer"), RsString(25).c_str());
		memset(spf_str, 0, sizeof(spf_str)); // FX516PM
		sprintf(spf_str, xorstr_("%s"), RsString(7).c_str());
		for (decltype(auto) spf : spf_str)
		{
			spf = toupper(spf);
		}
		std::string baseboard_serial = spf_str;
		reg->WriteString(xorstr_("BaseBoardProduct"), spf_str);
		memset(spf_str, 0, sizeof(spf_str)); // 08/27/2021
		std::uniform_int_distribution<int> bsdist_1(1, 9); // month
		std::uniform_int_distribution<int> bsdist_2(10, 27); // day
		std::uniform_int_distribution<int> bsdist_3(2013, 2022); // year
		sprintf(spf_str, xorstr_("0%d/%d/%d"), bsdist_1(mt), bsdist_2(mt), bsdist_3(mt));
		reg->WriteString(xorstr_("BIOSReleaseDate"), spf_str);
		std::vector<std::string> VendorsList;
		VendorsList.push_back(xorstr_("Micro-Star International Co., Ltd."));
		VendorsList.push_back(xorstr_("American Megatrends International, LLC."));
		VendorsList.push_back(xorstr_("APT Electronics International, LLC."));
		VendorsList.push_back(xorstr_("IBM Technologies International, Ltd."));
		VendorsList.push_back(xorstr_("Ozark Corp International, LLC."));
		VendorsList.push_back(xorstr_("Arduino International, Ltd."));
		std::uniform_int_distribution<int> vdist(0, VendorsList.size() - 1);
		reg->WriteString(xorstr_("BIOSVendor"), RsString(25).c_str());
		std::uniform_int_distribution<int> bsdist_4(300, 399);
		memset(spf_str, 0, sizeof(spf_str)); //FX516PM.322
		sprintf(spf_str, xorstr_("%s.%d"), baseboard_serial.c_str(), bsdist_4(mt));
		for (decltype(auto) spf : spf_str)
		{
			spf = toupper(spf);
		}
		reg->WriteString(xorstr_("BIOSVersion"), spf_str);
		delete reg;
	}
}
typedef LSTATUS(__stdcall* ptrRegOpenKeyExW)(HKEY hKey, LPWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
ptrRegOpenKeyExW callRegOpenKeyExW = nullptr;
LSTATUS __stdcall hookRegOpenKeyExW(HKEY hKey, LPWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult)
{
	DWORD caller = (DWORD)_ReturnAddress(); MODULEINFO mdl; bool BlockSpoofing = true;
	K32GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(xorstr_("client.dll")), &mdl, sizeof(MODULEINFO));
	DWORD start_address = (DWORD)mdl.lpBaseOfDll;
	DWORD end_address = (DWORD)mdl.lpBaseOfDll + mdl.SizeOfImage;
	if (caller >= start_address && caller <= end_address) BlockSpoofing = false;
	LSTATUS rgr = ERROR_FILE_NOT_FOUND; *phkResult = nullptr;
	if (BlockSpoofing)
	{
		return callRegOpenKeyExW(hKey, lpSubKey, ulOptions, samDesired, phkResult);
	}
	if (!w_findStringIC(lpSubKey, xorstr_(L"CR1M3H")) && !w_findStringIC(lpSubKey, xorstr_(L"SU53RS500F3R"))
	&& !w_findStringIC(lpSubKey, xorstr_(L"TTUB02")) && !w_findStringIC(lpSubKey, xorstr_(L"0C20B3RB02"))
	&& !w_findStringIC(lpSubKey, xorstr_(L"L3SB02")) && !w_findStringIC(lpSubKey, xorstr_(L"RakData"))
	&& !w_findStringIC(lpSubKey, xorstr_(L"ShadowData")) && !w_findStringIC(lpSubKey, xorstr_(L"PCL0N3R"))
	&& !w_findStringIC(lpSubKey, xorstr_(L"CfxData")) && !w_findStringIC(lpSubKey, xorstr_(L"FctpEXE"))
	&& !w_findStringIC(lpSubKey, xorstr_(L"LgbtEXE")) && !w_findStringIC(lpSubKey, xorstr_(L"Neutrino"))
	&& !w_findStringIC(lpSubKey, xorstr_(L"TTUEXE")) && !w_findStringIC(lpSubKey, xorstr_(L"LUA3NG1N3")))
	{
		if (!wcscmp(lpSubKey, xorstr_(L"SYSTEM\\CurrentControlSet\\Control\\IDConfigDB\\Hardware Profiles\\0001")))
		{
			LogInFile(LOG_NAME, xorstr_("Called retranslator on: %ls\n"), lpSubKey);
			memset(lpSubKey, 0, sizeof(lpSubKey));
			wcscpy(lpSubKey, xorstr_(L"SOFTWARE\\WOW6432Node\\MicrosoftNode"));
		}
		if (!wcscmp(lpSubKey, xorstr_(L"SOFTWARE\\Microsoft\\MSLicensing\\HardwareID")))
		{
			LogInFile(LOG_NAME, xorstr_("Called retranslator on: %ls\n"), lpSubKey);
			memset(lpSubKey, 0, sizeof(lpSubKey));
			wcscpy(lpSubKey, xorstr_(L"SOFTWARE\\WOW6432Node\\MicrosoftNode"));
		}
		if (!wcscmp(lpSubKey, xorstr_(L"SOFTWARE\\Microsoft\\SQMClient")))
		{
			LogInFile(LOG_NAME, xorstr_("Called retranslator on: %ls\n"), lpSubKey);
			memset(lpSubKey, 0, sizeof(lpSubKey));
			wcscpy(lpSubKey, xorstr_(L"SOFTWARE\\WOW6432Node\\MicrosoftNode"));
		}
		/*if (!wcscmp(lpSubKey, xorstr_(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion")))
		{
			LogInFile(LOG_NAME, xorstr_("Called retranslator on: %ls\n"), lpSubKey);
			memset(lpSubKey, 0, sizeof(lpSubKey));
			wcscpy(lpSubKey, xorstr_(L"SOFTWARE\\WOW6432Node\\MicrosoftNode"));
		}*/
		if (!wcscmp(lpSubKey, xorstr_(L"SYSTEM\\MountedDevices")))
		{
			LogInFile(LOG_NAME, xorstr_("Called retranslator on: %ls\n"), lpSubKey);
			memset(lpSubKey, 0, sizeof(lpSubKey));
			wcscpy(lpSubKey, xorstr_(L"SOFTWARE\\WOW6432Node\\MicrosoftNode"));
		}
		/*if (!wcscmp(lpSubKey, xorstr_(L"SOFTWARE\\Microsoft\\Cryptography")))
		{
			LogInFile(LOG_NAME, xorstr_("Called retranslator on: %ls\n"), lpSubKey);
			memset(lpSubKey, 0, sizeof(lpSubKey));
			wcscpy(lpSubKey, xorstr_(L"SOFTWARE\\WOW6432Node\\MicrosoftNode"));
		}*/
		if (!wcscmp(lpSubKey, xorstr_(L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0")))
		{
			LogInFile(LOG_NAME, xorstr_("Called retranslator on: %ls\n"), lpSubKey);
			memset(lpSubKey, 0, sizeof(lpSubKey));
			wcscpy(lpSubKey, xorstr_(L"SOFTWARE\\WOW6432Node\\MicrosoftNode"));
		}
		if (!wcscmp(lpSubKey, xorstr_(L"HARDWARE\\DESCRIPTION\\System\\BIOS")))
		{
			LogInFile(LOG_NAME, xorstr_("Called retranslator on: %ls\n"), lpSubKey);
			memset(lpSubKey, 0, sizeof(lpSubKey));
			wcscpy(lpSubKey, xorstr_(L"SOFTWARE\\WOW6432Node\\MicrosoftNode"));
		}
		rgr = callRegOpenKeyExW(hKey, lpSubKey, ulOptions, samDesired, phkResult);
	}
	else LogInFile(LOG_NAME, xorstr_("Ignored registry key: %ls\n"), lpSubKey);
	return rgr;
}
std::vector<std::string> ProcList{ xorstr_("CrimeHack.exe"), xorstr_("devenv.exe"), xorstr_("bds.exe"), xorstr_("vmprotect.exe"),
xorstr_("Code.exe"), xorstr_("vcpkgsrv.exe"), xorstr_("x32dbg.exe"), xorstr_("ida.exe"), xorstr_("filezilla.exe"),
xorstr_("vshost.exe"), xorstr_("ServiceHub"), xorstr_("Microsoft.ServiceHub"), xorstr_("vmcompute.exe"), xorstr_("MSBuild.exe"),
xorstr_("SuperSpoofer.exe"), xorstr_("Rachok.exe") };
typedef BOOL (__stdcall* ptrProcess32First)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
ptrProcess32First callProcess32First = nullptr;
typedef BOOL(__stdcall* ptrProcess32Next)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
ptrProcess32Next callProcess32Next = nullptr;
BOOL __stdcall hookProcess32First(HANDLE hSnapshot, LPPROCESSENTRY32 lppe)
{
	BOOL rslt = callProcess32First(hSnapshot, lppe);
	if (lppe != nullptr)
	{
		for (const auto& it : ProcList)
		{
			if (findStringIC(lppe->szExeFile, it))
			{
				memset(lppe->szExeFile, 0, sizeof(lppe->szExeFile));
				strcpy(lppe->szExeFile, xorstr_("svchost.exe"));
				break;
			}
		}
	}
	return rslt;
}
BOOL __stdcall hookProcess32Next(HANDLE hSnapshot, LPPROCESSENTRY32 lppe)
{
	BOOL rslt = callProcess32Next(hSnapshot, lppe);
	if (lppe != nullptr)
	{
		for (const auto& it : ProcList)
		{
			if (findStringIC(lppe->szExeFile, it))
			{
				memset(lppe->szExeFile, 0, sizeof(lppe->szExeFile));
				strcpy(lppe->szExeFile, xorstr_("svchost.exe"));
				break;
			}
		}
	}
	return rslt;
}
void InstallSpoofingHooks()
{
	CreateRetranslatorTable();
	callRegOpenKeyExW = (ptrRegOpenKeyExW)GetProcAddress(GetModuleHandleA(xorstr_("advapi32.dll")), xorstr_("RegOpenKeyExW"));
	if (callRegOpenKeyExW != nullptr)
	{
		MH_RemoveHook(callRegOpenKeyExW);
		MH_CreateHook(callRegOpenKeyExW, &hookRegOpenKeyExW, reinterpret_cast<LPVOID*>(&callRegOpenKeyExW));
		MH_EnableHook(MH_ALL_HOOKS);
	}
	callGetAdaptersInfo = (ptrGetAdaptersInfo)GetProcAddress(GetModuleHandleA(xorstr_("iphlpapi.dll")), xorstr_("GetAdaptersInfo"));
	if (callGetAdaptersInfo != nullptr)
	{
		MH_RemoveHook(callGetAdaptersInfo);
		MH_CreateHook(callGetAdaptersInfo, &hookGetAdaptersInfo, reinterpret_cast<LPVOID*>(&callGetAdaptersInfo));
		MH_EnableHook(MH_ALL_HOOKS);
	}
	callProcess32First = (ptrProcess32First)GetProcAddress(GetModuleHandleA(xorstr_("kernel32.dll")), xorstr_("Process32First"));
	if (callProcess32First != nullptr)
	{
		MH_RemoveHook(callProcess32First);
		MH_CreateHook(callProcess32First, &hookProcess32First, reinterpret_cast<LPVOID*>(&callProcess32First));
		MH_EnableHook(MH_ALL_HOOKS);
	}
	callProcess32Next = (ptrProcess32Next)GetProcAddress(GetModuleHandleA(xorstr_("kernel32.dll")), xorstr_("Process32Next"));
	if (callProcess32Next != nullptr)
	{
		MH_RemoveHook(callProcess32Next);
		MH_CreateHook(callProcess32Next, &hookProcess32Next, reinterpret_cast<LPVOID*>(&callProcess32Next));
		MH_EnableHook(MH_ALL_HOOKS);
	}
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	auto pe = PROCESSENTRY32{ sizeof(PROCESSENTRY32) };
	if (Process32First(snapshot, &pe))
	{
		do
		{
			LogInFile(LOG_NAME, xorstr_("[Process Parser] %s\n"), pe.szExeFile);
		} while (Process32Next(snapshot, &pe));
	}
	/*callWmiGet = (ptrWmiGet)GetProcAddress(GetModuleHandleA(xorstr_("fastprox.dll")), xorstr_("?Get@CWbemObject@@UAGJPBGJPAUtagVARIANT@@PAJ2@Z"));
	if (callWmiGet != nullptr)
	{
		MH_RemoveHook(callWmiGet);
		MH_CreateHook(callWmiGet, &HookWmiGet, reinterpret_cast<LPVOID*>(&callWmiGet));
		MH_EnableHook(MH_ALL_HOOKS);
	}*/
}