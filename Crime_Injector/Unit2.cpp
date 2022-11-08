//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Registry.h"
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
    std::string user_key = AnsiString(Form2->Edit1->Text).c_str();
	if (user_key.empty() || user_key.length() < 6)
	{
		MessageBeep(MB_ICONERROR);
        MessageBoxW(0, L"Вы должны ввести ключ", L"Ошибка", MB_ICONERROR | MB_OK);
        return;
    }
    CEasyRegistry* creg = new CEasyRegistry(HKEY_CURRENT_USER, "Software\\CR1M3H", true);
	if (creg != nullptr)
	{
		creg->WriteString("RegisteredKey", user_key.c_str());
		delete creg; Form1->Button1->Caption = "Подгрузить чит в игру";
		Form2->Hide();
	}
}
//---------------------------------------------------------------------------
