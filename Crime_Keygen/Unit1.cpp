//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <string>
#include <algorithm>
#include "Unit1.h"
#include "MD5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
std::string GenerateLifeTimeKey(std::string total_hwid)
{
	DWORD total_size = total_hwid.length();
	DWORD block_1_size = total_size / 5;
	DWORD block_2_size = total_size / 4;
	DWORD block_3_size = total_size / 3;
	DWORD block_4_size = total_size / 2;
	std::string hwid_hash = md5(total_hwid); hwid_hash = md5(hwid_hash);
	std::string block_1(hwid_hash); block_1.resize(block_1_size);
	std::string block_2(hwid_hash); block_2.resize(block_2_size);
	std::string block_3(hwid_hash); block_3.resize(block_3_size);
	std::string block_4(hwid_hash); block_4.resize(block_4_size);
	std::reverse(block_1.begin(), block_1.end());
	std::reverse(block_3.begin(), block_3.end());
	std::reverse(block_4.begin(), block_4.end());
	block_1 = md5(block_1); block_2 = md5(block_2);
	block_3 = md5(block_3); block_3 = md5(block_3);
	block_4 = md5(block_4); block_4 = md5(block_4);
	block_2 = md5(block_1 + block_3 + block_4);
	block_1 = md5(block_2 + block_3 + block_1);
	block_3 = md5(block_1 + block_2 + block_4);
	block_3 = md5(block_3 + block_1 + block_4);
	block_1.resize(4); block_2.resize(4);
	block_3.resize(4); block_4.resize(4);
	std::transform(block_1.begin(), block_1.end(), block_1.begin(), ::toupper);
	std::transform(block_2.begin(), block_2.end(), block_2.begin(), ::toupper);
	std::transform(block_3.begin(), block_3.end(), block_3.begin(), ::toupper);
	std::transform(block_4.begin(), block_4.end(), block_4.begin(), ::toupper);
	char genKey[256]; memset(genKey, 0, sizeof(genKey));
	sprintf(genKey, "CH-%s-%sA-%s-%sLF", block_1.c_str(), block_2.c_str(), block_3.c_str(), block_4.c_str());
	return genKey;
}
std::string GenerateDemoKey(std::string total_hwid)
{
	DWORD total_size = total_hwid.length();
	DWORD block_1_size = total_size / 5;
	DWORD block_2_size = total_size / 4;
	DWORD block_3_size = total_size / 3;
	DWORD block_4_size = total_size / 2;
	std::string hwid_hash = md5(total_hwid);
	std::string block_1(hwid_hash); block_1.resize(block_1_size);
	std::string block_2(hwid_hash); block_2.resize(block_2_size);
	std::string block_3(hwid_hash); block_3.resize(block_3_size);
	std::string block_4(hwid_hash); block_4.resize(block_4_size);
	std::reverse(block_1.begin(), block_1.end());
	std::reverse(block_3.begin(), block_3.end());
	block_2 = md5(block_2);
	block_4 = md5(block_4);
	block_1 = md5(block_1);
	block_3 = md5(block_2 + block_4 + block_1);
	block_1 = md5(block_2 + block_3 + block_4);
	block_1 = md5(block_1 + block_1 + block_1);
	block_4 = md5(block_4 + block_4 + block_3);
	block_1.resize(4); block_2.resize(4);
	block_3.resize(4); block_4.resize(4);
	std::transform(block_1.begin(), block_1.end(), block_1.begin(), ::toupper);
	std::transform(block_2.begin(), block_2.end(), block_2.begin(), ::toupper);
	std::transform(block_3.begin(), block_3.end(), block_3.begin(), ::toupper);
	std::transform(block_4.begin(), block_4.end(), block_4.begin(), ::toupper);
	char genKey[256]; memset(genKey, 0, sizeof(genKey));
	sprintf(genKey, "CH-%s-%sB-%s-%sDM", block_1.c_str(), block_2.c_str(), block_3.c_str(), block_4.c_str());
	return genKey;
}
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	AnsiString ans(Form1->Edit1->Text);
	if (ans.Length() < 5)
	{
        MessageBoxA(0, "Вы забыли ввести HWID покупателя!", "ERROR", MB_ICONERROR | MB_OK);
		return;
	}
	DeleteFileA("CrimeKey.reg");
	FILE *hFile = fopen("CrimeKey.reg", "a+");
	if (hFile)
	{
		fprintf(hFile, "Windows Registry Editor Version 5.00\n");
		fprintf(hFile, "\n[HKEY_CURRENT_USER\\SOFTWARE\\CR1M3H]\n");
		fprintf(hFile, "\"FirstUse\"=dword:00000000\n");
		std::string gKey = "";
		if (Form1->RadioButton1->Checked) gKey = GenerateDemoKey(ans.c_str());
		else if (Form1->RadioButton2->Checked) gKey = GenerateLifeTimeKey(ans.c_str());
		fprintf(hFile, "\"RegisteredKey\"=\"%s\"", gKey.c_str());
		fclose(hFile);
    }
}
//---------------------------------------------------------------------------
