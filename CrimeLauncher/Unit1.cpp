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
					//const CHAR url[] = _T("https://provhacks.fun/get_update.php");
					// unzip
					//DeleteUrlCacheEntry(url);
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
	if (!IsDirectoryExists("C:\\ProgramData\\CrimeData")) CreateDirectoryA("C:\\ProgramData\\CrimeData", NULL);
	const CHAR url[] = _T("https://provhacks.fun/get_update.php");
	const CHAR filePath[] = _T("C:\\ProgramData\\CrimeData\\CrimeHack.zip");
	DeleteUrlCacheEntry(url);
    CallbackHandler callbackHandler;
    IBindStatusCallback* pBindStatusCallback = NULL;
    callbackHandler.QueryInterface(IID_IBindStatusCallback, reinterpret_cast<void**>(&pBindStatusCallback));
	HRESULT hr = URLDownloadToFileA(NULL, url, filePath, 0, pBindStatusCallback );
    if(SUCCEEDED(hr))
    {

    }
    else
	{

	}
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
    CEasyRegistry* creg = new CEasyRegistry(HKEY_CURRENT_USER, "Software\\CR1M3H", true);
	if (creg != nullptr)
	{
		std::string LastInstVer = creg->ReadString("LastVer");
        std::string LastInstPath = creg->ReadString("LastInstPath");
		if (LastInstVer.empty()) LastInstVer = "NONE";
		std::string host_lnk = "provhacks.fun";
		char params[2000]; memset(params, 0, sizeof(params));
		sprintf(params, "soft_ver=%s", LastInstVer.c_str());
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
                Form1->Label1->Caption = "Статус: Загружаем обновление...";
                std::thread tth(StartUpdate); tth.detach();
            }
		}
		else MessageBoxW(0, L"Нет связи с хостом! Брендмауер выключен?", L"Ошибка", MB_ICONERROR | MB_OK);
        delete creg;
	}
}
//---------------------------------------------------------------------------
