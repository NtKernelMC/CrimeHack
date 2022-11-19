//---------------------------------------------------------------------------
#define AGENT_NAME "CR1M3H"
#include <vcl.h>
#pragma hdrstop
#include <System.Zip.hpp>
#include "Unit1.h"
#include <algorithm>
#include <thread>
#include <string>
#include "Registry.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <wininet.h>
#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "Urlmon.lib")
TForm1 *Form1;
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
std::string update_log = "";
enum EMethod { M_POST, M_GET };
enum EProtocol { P_HTTP, P_HTTPS };
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
				method = "GET";
				request = _page + (_params.empty() ? "" : ("?" + _params));
				break;
			case M_POST:
				method = "POST";
				request = _page;
				headers = "Content-Type: application/x-www-form-urlencoded";
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
class CallbackHandler : public IBindStatusCallback
{
private:
    int m_percentLast;

public:
    CallbackHandler() : m_percentLast(0)
    {
    }

    // IUnknown

    HRESULT STDMETHODCALLTYPE
    QueryInterface(REFIID riid, void** ppvObject)
    {

        if(    IsEqualIID(IID_IBindStatusCallback, riid)
            || IsEqualIID(IID_IUnknown, riid) )
        {
            *ppvObject = reinterpret_cast<void*>(this);
            return S_OK;
        }

        return E_NOINTERFACE;
    }

    ULONG STDMETHODCALLTYPE
    AddRef()
    {
        return 2UL;
    }

    ULONG STDMETHODCALLTYPE
    Release()
    {
        return 1UL;
    }

    // IBindStatusCallback

    HRESULT STDMETHODCALLTYPE
    OnStartBinding(DWORD     /*dwReserved*/,
                   IBinding* /*pib*/)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE
    GetPriority(LONG* /*pnPriority*/)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE
    OnLowResource(DWORD /*reserved*/)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE
    OnProgress(ULONG   ulProgress,
               ULONG   ulProgressMax,
               ULONG   ulStatusCode,
               LPCWSTR /*szStatusText*/)
    {
        switch(ulStatusCode)
        {
            case BINDSTATUS_FINDINGRESOURCE:

            break;
            case BINDSTATUS_CONNECTING:

            break;
            case BINDSTATUS_SENDINGREQUEST:

            break;
            case BINDSTATUS_MIMETYPEAVAILABLE:

            break;
            case BINDSTATUS_CACHEFILENAMEAVAILABLE:

            break;
            case BINDSTATUS_BEGINDOWNLOADDATA:

			break;
			case BINDSTATUS_DOWNLOADINGDATA:
            case BINDSTATUS_ENDDOWNLOADDATA:
            {
				int percent = (int)(100.0 * static_cast<double>(ulProgress)
			 	/ static_cast<double>(ulProgressMax));
                if(m_percentLast < percent)
				{
					Form1->ProgressBar1-> Position = percent;
					m_percentLast = percent;
				}
                if(ulStatusCode == BINDSTATUS_ENDDOWNLOADDATA)
				{
					std::string last_ver = "NONE";
					std::string host_lnk = "provhacks.fun";
					char params[2000]; memset(params, 0, sizeof(params));
					sprintf(params, "soft_ver=%s&b=2", last_ver.c_str());
					std::string anser = SendInetRequest(P_HTTPS, M_GET,
					host_lnk, "crime_hack/check_update.php", std::string(params), true);
					if (!anser.empty()) last_ver = anser;
                    CEasyRegistry* creg = new CEasyRegistry(HKEY_CURRENT_USER, "Software\\CR1M3H", true);
					if (creg != nullptr)
					{
                        creg->WriteString("LastVer", last_ver.c_str());
						delete creg;
					}
					std::string zip_name = "C:\\ProgramData\\CrimeData\\CrimeHack.zip";
					std::string unzip_path = "C:\\ProgramData\\CrimeData\\CrimeHack.exe";
					TZipFile* zip = new TZipFile;
					zip->Open(zip_name.c_str(), zmRead);
					zip->Close();
					//delete zip;
					//System::Zip::TZipFile::ExtractZipFile(zip_name.c_str(), unzip_path.c_str());
					//DeleteFileA(zip_name.c_str());
					//MessageBoxA(0, update_log.c_str(), "Что нового?", MB_OK);
					//std::string LastInstPath = "C:\\ProgramData\\CrimeData\\CrimeHack.exe";
					//ShellExecuteA(0, "runas", LastInstPath.c_str(), 0, 0, SW_SHOW);
					//ExitProcess(0x0);
				}
            }
            break;

			default:
			{

            }
        }
        // The download can be cancelled by returning E_ABORT here
        // of from any other of the methods.
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE
    OnStopBinding(HRESULT /*hresult*/,
                  LPCWSTR /*szError*/)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE
    GetBindInfo(DWORD*    /*grfBINDF*/,
                BINDINFO* /*pbindinfo*/)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE
    OnDataAvailable(DWORD      /*grfBSCF*/,
                    DWORD      /*dwSize*/,
                    FORMATETC* /*pformatetc*/,
                    STGMEDIUM* /*pstgmed*/)
    {
        return E_NOTIMPL;
    }

    HRESULT STDMETHODCALLTYPE
    OnObjectAvailable(REFIID    /*riid*/,
                      IUnknown* /*punk*/)
    {
        return E_NOTIMPL;
    }
};
bool __stdcall IsDirectoryExists(const std::string& dirName_in)
{
    DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES) return false;
    if (ftyp & FILE_ATTRIBUTE_DIRECTORY) return true;
    return false;
};
void StartUpdate()
{
	DeleteFileA("C:\\ProgramData\\CrimeData\\CrimeHack.exe");
	if (!IsDirectoryExists("C:\\ProgramData\\CrimeData")) CreateDirectoryA("C:\\ProgramData\\CrimeData", NULL);
	const CHAR url[] = _T("https://provhacks.fun/crime_hack/get_update.php");
	std::string faPath = "C:\\ProgramData\\CrimeData\\CrimeHack.zip";
	DeleteUrlCacheEntry(url); CallbackHandler callbackHandler;
	IBindStatusCallback* pBindStatusCallback = NULL;
	callbackHandler.QueryInterface(IID_IBindStatusCallback, reinterpret_cast<void**>(&pBindStatusCallback));
	HRESULT hr = URLDownloadToFileA(NULL, url, faPath.c_str(), 0, pBindStatusCallback );
	if(SUCCEEDED(hr))
	{

    }
    else
	{

	}
}
DWORD MakeJump(DWORD jmp_address, DWORD hookAddr, byte *prologue, size_t prologue_size)
{
    DWORD old_prot = 0x0;
    if (prologue == nullptr) return 0x0;
    VirtualProtect((void*)jmp_address, prologue_size, PAGE_EXECUTE_READWRITE, &old_prot);
    memcpy(prologue, (void*)jmp_address, prologue_size);
    byte addrToBytes[5] = { 0xE9, 0x90, 0x90, 0x90, 0x90 };
    DWORD JMPBytes = (hookAddr - jmp_address - 5);
    memcpy(&addrToBytes[1], &JMPBytes, 4);
    memcpy((void*)jmp_address, addrToBytes, 5);
    PVOID Trampoline = VirtualAlloc(0, (5 + (prologue_size - 5)), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    byte TrampolineBytes[5] = { 0xE9, 0x90, 0x90, 0x90, 0x90 };
    if (prologue_size > 5)
    {
        byte nop[] = { 0x90 };
        for (byte x = 0; x < (prologue_size - 5); x++) memcpy((void*)(jmp_address + 0x5 + x), nop, 1);
        memcpy(Trampoline, &prologue[3], (prologue_size - 3));
        DWORD Delta = (jmp_address + prologue_size) - (((DWORD)Trampoline + (prologue_size - 3)) + 5);
        memcpy(&TrampolineBytes[1], &Delta, 4);
        memcpy((void*)((DWORD)Trampoline + (prologue_size - 3)), TrampolineBytes, 5);
    }
    else
    {
        DWORD Delta = (jmp_address + prologue_size) - ((DWORD)Trampoline + 5);
        memcpy(&TrampolineBytes[1], &Delta, 4);
        memcpy(Trampoline, TrampolineBytes, 5);
    }
    VirtualProtect((void*)jmp_address, prologue_size, old_prot, 0);
    return (DWORD)Trampoline;
}
bool RestorePrologue(DWORD addr, byte *prologue, size_t prologue_size)
{
    if (prologue == nullptr) return false;
    DWORD old_prot = 0;
    VirtualProtect((void*)addr, prologue_size, PAGE_EXECUTE_READWRITE, &old_prot);
    memcpy((void*)addr, prologue, prologue_size);
    VirtualProtect((void*)addr, prologue_size, old_prot, &old_prot);
    return true;
}
BYTE prologue[5]; DWORD api = NULL;
HINTERNET __stdcall hookInternetOpenW(LPWSTR lpszAgent, DWORD dwAccessType,
LPCWSTR lpszProxy, LPCWSTR lpszProxyBypass, DWORD dwFlags)
{
	if (!w_findStringIC(lpszAgent, L"CR1M3H"))
	{
		memset(lpszAgent, 0, sizeof(lpszAgent));
		wcscpy(lpszAgent, L"CR1M3H");
    }
	RestorePrologue(api, prologue, 5);
	HINTERNET rslt = InternetOpenW(lpszAgent, dwAccessType, lpszProxy, lpszProxyBypass, dwFlags);
    MakeJump(api, (DWORD)&hookInternetOpenW, prologue, 5);
    return rslt;
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
	TZipFile* zip = new TZipFile;
	zip->Open("C:\\ProgramData\\CrimeData\\CrimeHack.zip", zmRead);
	zip->Extract("C:\\ProgramData\\CrimeData\\CrimeHack.zip");
	zip->Close();
	return;
	HMODULE hMDL = LoadLibraryA("wininet.dll");
	api = (DWORD)GetProcAddress(hMDL, "InternetOpenW");
	MakeJump(api, (DWORD)&hookInternetOpenW, prologue, 5);
    CEasyRegistry* creg = new CEasyRegistry(HKEY_CURRENT_USER, "Software\\CR1M3H", true);
	if (creg != nullptr)
	{
		std::string LastInstVer = creg->ReadString("LastVer");
		std::string LastInstPath = "C:\\ProgramData\\CrimeData\\CrimeHack.exe";
		if (LastInstVer.empty()) LastInstVer = "NONE";
		std::string host_lnk = "provhacks.fun";
		char params[2000]; memset(params, 0, sizeof(params));
		sprintf(params, "soft_ver=%s&b=1", LastInstVer.c_str());
		std::string anser = SendInetRequest(P_HTTPS, M_GET,
		host_lnk, "crime_hack/check_update.php", std::string(params), true);
		if (!anser.empty())
		{
			if (findStringIC(anser, LastInstVer))
			{
				ShellExecuteA(0, "runas", LastInstPath.c_str(), 0, 0, SW_SHOW);
				ExitProcess(0x0);
			}
			else
			{
				update_log = anser;
                Form1->Label1->Caption = "Статус: Загружаем обновление...";
                std::thread tth(StartUpdate); tth.detach();
            }
		}
		else MessageBoxW(0, L"Нет связи с хостом! Брендмауер выключен?", L"Ошибка", MB_ICONERROR | MB_OK);
        delete creg;
	}
}
//---------------------------------------------------------------------------
