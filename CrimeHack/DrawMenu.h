void ApplyImGuiTheme()
{
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
    colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(8.00f, 8.00f);
    style.FramePadding = ImVec2(5.00f, 2.00f);
    style.CellPadding = ImVec2(6.00f, 6.00f);
    style.ItemSpacing = ImVec2(6.00f, 6.00f);
    style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
    style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
    style.IndentSpacing = 25;
    style.ScrollbarSize = 15;
    style.GrabMinSize = 10;
    style.WindowBorderSize = 1;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    style.FrameBorderSize = 1;
    style.TabBorderSize = 1;
    style.WindowRounding = 7;
    style.ChildRounding = 4;
    style.FrameRounding = 3;
    style.PopupRounding = 4;
    style.ScrollbarRounding = 9;
    style.GrabRounding = 3;
    style.LogSliderDeadzone = 4;
    style.TabRounding = 4;
}
enum TABS
{
    HACK_TAB1,
    ENEMY_TAB,
    HACK_TAB2,
    HACK_TAB3,
    OPTIONS_TAB,
};
int page = 0;
void ObtainLuaRecords()
{
    if (GetModuleHandleA(xorstr_("client.dll")) && ShowMenu)
    {
        FILE* hFile = fopen(std::string(GetGamePath() + xorstr_("\\GetPlayersList.txt")).c_str(), xorstr_("a+"));
        if (hFile) fclose(hFile);
        while (!IsFileExist(std::string(GetGamePath() + xorstr_("\\Signal.txt")).c_str())) Sleep(100);
        std::ifstream infile(std::string(GetGamePath() + xorstr_("\\Signal.txt")).c_str());
        if (infile.is_open())
        {
            PlayersList.clear();
            for (std::string line; std::getline(infile, line);)
            {
                PlayersList.push_back(line);
            }
            infile.close();
            DeleteFileA(std::string(GetGamePath() + xorstr_("\\Signal.txt")).c_str());
            for (auto& enemy : EnemyList)
            {
                enemy.second = false;
                for (const auto& it : PlayersList)
                {
                    if (enemy.first.find(it) != std::string::npos) enemy.second = true;
                }
            }
        }
    }
}
enum class LUA_CMD
{
    DROP_MARKER = 2911,
    PL_SPEC = 2922,
    CAR_FIX = 2933,
    CAR_FILL = 2944,
    PL_EAT = 2955,
    PL_MASK = 2966,
    PL_PAY = 2977,
    PL_GM = 2988,
    PL_HEAL = 2999,
    PL_ARMOR = 3011,
    CAR_FLIP = 3022,
    SET_MODEL = 3033,
    CAR_PLATE_TP = 3044,
    PL_ID_TP = 3055,
    LIC_MONORELS = 3066,
    LIC_TRAMWAY = 3077,
    LIC_B = 3088,
    LIC_C = 3099,
    LIC_D = 4011,
    PL_ALCO = 4022,
    PL_LOTTERY = 4033,
    PL_PEE = 4044,
    PL_ARMY_MED = 4055,
    PL_MED_MASK = 4066,
    PL_UNCUFF = 4077,
    PL_MILEAGE = 4088,
    EMPTY_CODE2 = 4099,
    CAR_CHARGE = 5011,
    CAR_ATTACH = 5022,
    CAR_SET_PLATE = 5033,
    PL_SHUTE = 5044,
    RENT_HOTEL = 5055,
    HOTEL_PAY_RENT = 5066,
    PL_REDUCE_DAMAGE = 5077,
    CAR_KICKER = 5088,
    GET_WANTED = 5099,
    PL_FISHING_POINT = 6011,
    PL_FISH_HOOK = 6022,
    PL_BUY_UDOCHKA = 6033,
    PL_BUY_BAITS = 6044,
    PL_SELL_FISH = 6055,
    PL_SET_INT = 6066,
    PL_FAKE_KILL = 6077,
    BANK_CREATE = 6088,
    BANK_PUT = 6099,
    BANK_GET = 7011,
    BANK_SEND = 7022,
    BANK_SET_NUMBER = 7033,
    SET_MODEL_NAME = 7044,
    REPLACE_MODEL_ID = 7055,
    DUMP_MODEL_ID = 7066,
    CAR_DETACH = 7077,
    GET_CONTAINER = 7088,
    VEH_GM = 7099,
    MARK_TP = 8011,
    BUNKER_TP = 8022,
    LES_TP = 8033,
    EMPTY_CODE = 8044,
    BUY_VESTA = 8055,
    SHOW_POLICE = 8066,
    TRIGGER_DUMPER = 8077,
    GET_CIGARETTE = 8088,
    PAY_HOUSE = 8099,
    PAY_GARAGE = 9011,
    SHOW_INCAS = 9022,
    SLOW_SH = 9033,
    DUMP_INTERIOR = 9055,
    BY_TP = 9066,
    ALLOW_TITLE = 9077,
    SET_COCK = 9088,
    ORDER_SPAM = 9099,
    ORDER_GET = 10100,
    ORDER_END = 10200,
};
void ExecuteLuaCommand(LUA_CMD cmd, std::string argument)
{
    char prepared_path[600]; memset(prepared_path, 0, sizeof(prepared_path));
    sprintf(prepared_path, xorstr_("%s\\ExecCMD.txt"), GetGamePath().c_str());
    FILE* hFile = fopen(prepared_path, xorstr_("a+"));
    if (hFile)
    {
        fprintf(hFile, xorstr_("%d\n%s"), cmd, argument.c_str());
        fclose(hFile);
    }
}
void SetAnotherHook()
{
    DbgHook = false;
    std::thread exec_hook(ExecuteLuaCommand, LUA_CMD::PL_FISH_HOOK, xorstr_("NONE"));
    exec_hook.detach(); Sleep(1500); DbgHook = true;
}
void SetAnotherHook2()
{
    static bool once_time = false;
    if (!once_time)
    {
        DbgHook = false;
        std::thread exec_hook(ExecuteLuaCommand, LUA_CMD::PL_FISH_HOOK, xorstr_("NONE"));
        exec_hook.detach(); Sleep(1500); DbgHook = true; once_time = true;
    }
    std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_FAKE_KILL, inp_txt9);
    exec_cmd.detach();
}
void GoFish()
{
    SetAnotherHook();
    std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_BUY_UDOCHKA, xorstr_("NONE"));
    exec_cmd.detach(); Sleep(1500);
    std::thread exec_cmd2(ExecuteLuaCommand, LUA_CMD::PL_BUY_BAITS, xorstr_("NONE"));
    exec_cmd2.detach(); Sleep(1500);
    sendMTAChat(xorstr_("fishing"), xorstr_(""), true, false, false);
    Sleep(1000);
    while (true)
    {
        if (!FisherBot) break;
        std::string log_line = ReadLastLogLine();
        if (log_line.find(xorstr_("Вы поймали рыбу")) != std::string::npos)
        {
            std::thread exec_cmd3(ExecuteLuaCommand, LUA_CMD::PL_BUY_BAITS, xorstr_("NONE"));
            exec_cmd3.detach(); Sleep(1500);
        }
        EmulateKeyPress(0x1, true);
        Sleep(50);
        EmulateKeyPress(0x1, false);
        Sleep(1000);
    }
}
void DumpTriggers()
{
    DbgHook = false;
    std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::TRIGGER_DUMPER, xorstr_("NONE"));
    exec_cmd.detach(); Sleep(3000); DbgHook = true;
}
void DumpCoords()
{
    CPed* ped = FindPlayerPed(-1);
    if (ped != nullptr)
    {
        CVector vec = ped->GetPosition();
        LogInFile(LOG_NAME, xorstr_("X: %f | Y: %f | Z: %f\n"), vec.x, vec.y, vec.z);
        std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::DUMP_INTERIOR, xorstr_("NONE"));
        exec_cmd.detach();
    }
}
void BankTransaction(std::string bank_id, std::string value)
{
    std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::BANK_SET_NUMBER, bank_id);
    exec_cmd.detach(); Sleep(2000);
    std::thread exec_cmd2(ExecuteLuaCommand, LUA_CMD::BANK_SEND, value);
    exec_cmd2.detach();
}
void LoadCustomModel(std::string model_id, std::string file_name)
{
    std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::SET_MODEL_NAME, file_name);
    exec_cmd.detach(); Sleep(2000);
    std::thread exec_cmd2(ExecuteLuaCommand, LUA_CMD::REPLACE_MODEL_ID, model_id);
    exec_cmd2.detach();
}
void SumkaTP()
{
    CPed* pidr = FindPlayerPed(-1);
    if (pidr)
    {
        CVector vec = pidr->GetPosition();
        pidr->SetPosn(CVector(863.673f, 1935.557f, 13.804f));
        Sleep(1000);
        pidr->SetPosn(vec);
    }
}
std::optional<HRESULT> on_present(const decltype(present_hook)& hook, IDirect3DDevice9* device_ptr,
const RECT*, const RECT*, HWND wnd, const RGNDATA*)
{
    static bool ImGui_inited = false;
    if (!ImGui_inited)
    {
        ImGui::CreateContext();
        ApplyImGuiTheme();
        ImGuiIO& io = ImGui::GetIO();
        ImFontConfig fontCfg = ImFontConfig();
        io.DeltaTime = 1.0f / 60.0f;
        fontCfg.RasterizerMultiply = 1.0f;
        fontCfg.OversampleV = 1;
        fontCfg.OversampleH = fontCfg.OversampleV;
        fontCfg.PixelSnapH = true;
        static const ImWchar ranges[] = { 0x0020, 0x00FF, 0x0400, 0x044F, 0x0 };
        io.Fonts->AddFontFromFileTTF(xorstr_("Shrift.otf"), 16.0f, &fontCfg, ranges);
        D3DXCreateTextureFromFileA(device_ptr, xorstr_("texture.jpg"), &texture);
        ImGui_ImplWin32_Init(**reinterpret_cast<HWND**>(0xC17054));
        ImGui_ImplDX9_Init(device_ptr);
        ImGui_inited = true;
    }
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    if (ShowMenu)
    {
        POINT p; GetCursorPos(&p); ScreenToClient(gameWnd, &p);
        ImGui::GetForegroundDrawList()->AddTriangleFilled(ImVec2(p.x - 10, p.y), ImVec2(p.x, p.y + 10), ImVec2(p.x + 10, p.y), ImColor(185, 17, 17));
        //ImGui::GetForegroundDrawList()->AddTriangle(ImVec2(p.x - 10, p.y), ImVec2(p.x, p.y + 10), ImVec2(p.x + 10, p.y), ImColor(185, 17, 17));
        ImGui::SetNextWindowSize(ImVec2(610, 510));
        const char* bank_items[] = { xorstr_("Create account"), xorstr_("Put money"), xorstr_("Get money"), xorstr_("Send money"), };
        const char* rank_items[] = { xorstr_("0"), xorstr_("1"), xorstr_("2"), xorstr_("3"), xorstr_("4") };
        static const char* rank_current_item = NULL;
        static const char* bank_current_item = NULL;
        static const char* current_select2 = "All players are Offline!";
        static bool Dummy3 = false;
        static bool MyDummy = false;
        static bool Dummy = false;
        static bool Dummy5 = false;
        static bool Dummy6 = false;
        static bool Dummy7 = false;
        static bool Dummy8 = false;
        static bool Dummy9 = false;
        static bool Dummy10 = false;
        static const char* current_select = "All enemies are Offline!";
        char capWin[350]; memset(capWin, 0, sizeof(capWin));
        sprintf(capWin, xorstr_("Crime Hack by NtKernelMC | build %s | vk.com/provhacks"), PLUGIN_VER);
        ImGui::Begin(capWin, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse);
        ImGui::Image(texture, ImVec2(610, 166));
        ImGui::BeginChild(xorstr_("tabs"), ImVec2(0, 25), false);
        if (ImGui::Button(cp1251_to_utf8(xorstr_("Читы 1")).c_str(), ImVec2(ImGui::GetWindowWidth() / 5 - 8, 25))) page = HACK_TAB1;
        ImGui::SameLine();
        if (ImGui::Button(cp1251_to_utf8(xorstr_("Читы 2")).c_str(), ImVec2(ImGui::GetWindowWidth() / 5 - 8, 25))) page = HACK_TAB2;
        ImGui::SameLine();
        if (ImGui::Button(cp1251_to_utf8(xorstr_("Читы 3")).c_str(), ImVec2(ImGui::GetWindowWidth() / 5 - 8, 25))) page = HACK_TAB3;
        ImGui::SameLine();
        if (ImGui::Button(cp1251_to_utf8(xorstr_("Черный список")).c_str(), ImVec2(ImGui::GetWindowWidth() / 5 - 8, 25))) page = ENEMY_TAB;
        ImGui::SameLine();
        if (ImGui::Button(cp1251_to_utf8(xorstr_("Служебное")).c_str(), ImVec2(ImGui::GetWindowWidth() / 5 - 8, 25))) page = OPTIONS_TAB;
        ImGui::EndChild();
        ImGui::BeginChild(xorstr_("main"), ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar);
        switch (page)
        {
        case HACK_TAB1:
            ImGui::Checkbox(cp1251_to_utf8(xorstr_("Аирбрэйк")).c_str(), &AirAllowed);
            ImGui::SameLine(); ImGui::Checkbox(cp1251_to_utf8(xorstr_("Коллизия")).c_str(), &ColHack);
            ImGui::SameLine(); 
            if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("Неуязвимая тачка")).c_str(), &CarGM))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::VEH_GM, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine(); ImGui::Checkbox(cp1251_to_utf8(xorstr_("Аура Смерти")).c_str(), &DeadlyAura);
            ImGui::Checkbox(cp1251_to_utf8(xorstr_("Сайлент аим")).c_str(), &SilentAIM);
            ImGui::SameLine(); ImGui::SliderFloat(xorstr_("FOV"), &FOV, 50.0, 500.0f);
            ImGui::Checkbox(cp1251_to_utf8(xorstr_("Ваншот")).c_str(), &OneShot);
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Накрутить патроны")).c_str()))
            {
                CPed* ped = FindPlayerPed(-1);
                if (ped)
                {
                    for (short x = 0; x < 13; x++)
                    {
                        if (ped->m_aWeapons[x].m_nTotalAmmo != NULL) ped->GiveWeapon(ped->m_aWeapons[x].m_eWeaponType, 9999, false);
                    }
                    MessageBeep(MB_ICONERROR);
                }
            }
            ImGui::PopStyleColor(3);
            ImGui::SameLine();
            ImGui::Checkbox(cp1251_to_utf8(xorstr_("Абузер машин")).c_str(), &TotalCar);
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            if (ImGui::Button(cp1251_to_utf8(xorstr_("ТП по метке")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::MARK_TP, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Узнать ID модели")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::DUMP_MODEL_ID, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            ImGui::Checkbox(cp1251_to_utf8(xorstr_("Спидхак")).c_str(), &SpeedHack);
            ImGui::SameLine(); ImGui::SliderFloat(cp1251_to_utf8(xorstr_("Макс.скорость")).c_str(), &MaxSpd, 150.0, 600.0f);
            ImGui::Checkbox(cp1251_to_utf8(xorstr_("Инвиз пешком")).c_str(), &PedInviz);
            ImGui::SameLine(); ImGui::Checkbox(cp1251_to_utf8(xorstr_("Инвиз в тачке")).c_str(), &VehInviz);
            ImGui::SameLine(); ImGui::Checkbox(cp1251_to_utf8(xorstr_("Тачка ездит перевернутой (Синхра)")).c_str(), &UpSide);
            ImGui::Checkbox(cp1251_to_utf8(xorstr_("Анти-штраф (Скорость)")).c_str(), &AntiRadar);
            ImGui::SameLine(); 
            if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("Анти-штраф (Светофор)")).c_str(), &AntiRed))
            {
                if (AntiRed)
                {
                    AntiRed = false;
                    SetTrafficLightState(5);
                    SetTrafficLightsLocked(true);
                    AntiRed = true;
                }
            }
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Загрузить модель")).c_str()))
            {
                std::thread exec_cmd(LoadCustomModel, inp_txt12, inp_txt13);
                exec_cmd.detach();
            }
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Умереть нахуй")).c_str()))
            {
                CPed* ped = FindPlayerPed();
                if (ped != nullptr) ped->m_fHealth = 0.0f;
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Ясная погода + день")).c_str()))
            {
                CWeather::ForceWeatherNow(WEATHER_EXTRASUNNY_LA);
                CClock::SetGameClock(12, 0, 1);
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("ТП в Бункер (Пистолет)")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::BUNKER_TP, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("ТП в Лес (Винтовка)")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::LES_TP, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            ImGui::InputText(cp1251_to_utf8(xorstr_("Имя файла")).c_str(), inp_txt12, sizeof(inp_txt12));
            ImGui::InputText(cp1251_to_utf8(xorstr_("ID Модели")).c_str(), inp_txt13, sizeof(inp_txt13));
            ImGui::InputText(cp1251_to_utf8(xorstr_("ID дома")).c_str(), inp_txt14, sizeof(inp_txt14));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Оплатить Дом")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PAY_HOUSE, inp_txt14);
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            break;
        case ENEMY_TAB:
            ImGui::BulletText(cp1251_to_utf8(xorstr_("Нажмите 2 раза на врага")).c_str());
            ImGui::SameLine(); ImGui::Indent(370);
            ImGui::BulletText(cp1251_to_utf8(xorstr_("Нажмите 2 раза на игрока")).c_str());
            ImGui::Unindent(370);
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_Header, ImVec4{ 0.26f, 0.59f, 0.98f, 0.35f });
            ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4{ 0.26f, 0.59f, 0.98f, 0.35f });
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4{ 0.26f, 0.59f, 0.98f, 0.50f });
            if (ImGui::BeginChild(xorstr_("ChildDrawList"), ImVec2(200, 150), true))
            {
                for (const auto& item : EnemyList)
                {
                    if ((strlen(FindEnemy) > 0 && item.first.find(FindEnemy) != std::string::npos) || strlen(FindEnemy) < 1)
                    {
                        if (item.second)
                        {
                            bool is_selected = (current_select == item.first.c_str());
                            if (ImGui::Selectable(item.first.c_str(), is_selected))
                            {
                                current_select = item.first.c_str();
                                if (is_selected)
                                {
                                    ImGui::SetItemDefaultFocus();
                                }
                            }
                        }
                    }
                }
                ImGui::EndChild();
            }
            ImGui::PopStyleColor(4);
            ImGui::SameLine(); ImGui::Indent(247);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Обновить")).c_str()))
            {
                std::thread ath(ObtainLuaRecords);
                ath.detach();
            }
            ImGui::PopStyleColor(3);
            ImGui::Unindent(247);
            ImGui::SameLine(); ImGui::Indent(370);
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_Header, ImVec4{ 0.26f, 0.59f, 0.98f, 0.35f });
            ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4{ 0.26f, 0.59f, 0.98f, 0.35f });
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4{ 0.26f, 0.59f, 0.98f, 0.50f });
            if (ImGui::BeginChild(xorstr_("ChildDrawList2"), ImVec2(200, 150), true))
            {
                for (const auto& item : PlayersList)
                {
                    if ((strlen(FindActor) > 0 && item.find(FindActor) != std::string::npos) || strlen(FindActor) < 1)
                    {
                        bool is_selected = (current_select2 == item.c_str());
                        if (ImGui::Selectable(item.c_str(), is_selected))
                        {
                            current_select2 = item.c_str();
                            if (is_selected)
                            {
                                ImGui::SetItemDefaultFocus();
                            }
                        }
                    }
                }
                ImGui::EndChild();
            }
            ImGui::PopStyleColor(4);
            ImGui::Unindent(370);
            ImGui::Spacing(); ImGui::Spacing();
            ImGui::PushItemWidth(200);
            ImGui::InputText(cp1251_to_utf8(xorstr_("                  Поиск")).c_str(), FindEnemy, sizeof(FindEnemy));
            ImGui::PopItemWidth();
            ImGui::SameLine();
            ImGui::PushItemWidth(200);
            ImGui::Indent(370);
            ImGui::InputText("##", FindActor, sizeof(FindActor));
            ImGui::Unindent(370);
            ImGui::PopItemWidth();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            ImGui::Spacing(); ImGui::Spacing();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Добавить врага")).c_str()))
            {
                if (!IsEnemyExist(current_select2) || EnemyList.empty())
                {
                    EnemyList.insert(std::pair<std::string, bool>(current_select2, true));
                    UpdateEnemyList();
                }
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Удалить врага")).c_str()))
            {
                if (IsEnemyExist(current_select) && !EnemyList.empty())
                {
                    auto enemy = EnemyList.find(current_select);
                    if (enemy != EnemyList.end())
                    {
                        EnemyList.erase(enemy);
                        UpdateEnemyList();
                    }
                }
            }
            ImGui::SameLine();
            ImGui::Indent(370);
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Метка")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::DROP_MARKER, current_select);
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Слежка")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_SPEC, current_select);
                exec_cmd.detach();
            }
            ImGui::Unindent(370);
            ImGui::PopStyleColor(3);
            break;
        case HACK_TAB2:
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Починка")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::CAR_FIX, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Заправка")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::CAR_FILL, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Веста")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::BUY_VESTA, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Маска")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_MASK, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Оплатить штрафы")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_PAY, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Зарядка")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::CAR_CHARGE, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Отцепить")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::CAR_DETACH, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("Неуязвимый персонаж")).c_str(), &Dummy))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_GM, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Лечение")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_HEAL, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Броня")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_ARMOR, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Переворот на колеса")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::CAR_FLIP, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            ImGui::InputText("[1]", inp_txt, sizeof(inp_txt));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Установить модель")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::SET_MODEL, inp_txt);
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            ImGui::InputText("[2]", inp_txt2, sizeof(inp_txt2));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("ТП по гос.номерам")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::CAR_PLATE_TP, inp_txt2);
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            ImGui::InputText("[3]", inp_txt3, sizeof(inp_txt3));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("ТП по ID игрока")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_ID_TP, inp_txt3);
                exec_cmd.detach();
            }
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Права Монорельса")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::LIC_MONORELS, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Права Трамвай")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::LIC_TRAMWAY, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Сижка")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::GET_CIGARETTE, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            ImGui::InputText("[4]", inp_txt4, sizeof(inp_txt4));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Выдать бухло")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_ALCO, inp_txt4);
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            ImGui::InputText("[5]", inp_txt5, sizeof(inp_txt5));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Прицепить")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::CAR_ATTACH, inp_txt5);
                exec_cmd.detach();
            }
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Мед.комиссия")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_ARMY_MED, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("Вор контейнера")).c_str(), &Dummy5))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::GET_CONTAINER, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Снять наручники")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_UNCUFF, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Узнать пробег")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_MILEAGE, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            ImGui::InputText(cp1251_to_utf8(xorstr_("ID гаража")).c_str(), inp_txt15, sizeof(inp_txt15));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Оплатить Гараж")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PAY_GARAGE, inp_txt15);
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            break;
        case HACK_TAB3:
            ImGui::InputText("[6]", inp_txt6, sizeof(inp_txt6));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Установить номера")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::CAR_SET_PLATE, inp_txt6);
                exec_cmd.detach();
            }
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Выдать парашют")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_SHUTE, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Арендовать отель")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::RENT_HOTEL, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Кто в розыске?")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::GET_WANTED, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("Показать мусоров")).c_str(), &Dummy8))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::SHOW_POLICE, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            ImGui::InputText("[7]", inp_txt7, sizeof(inp_txt7));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Продлить отель")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::HOTEL_PAY_RENT, inp_txt7);
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            ImGui::InputText("[8]", inp_txt8, sizeof(inp_txt8));
            ImGui::SameLine(); 
            if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("Уменьшитель урона")).c_str(), &Dummy3))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_REDUCE_DAMAGE, inp_txt8);
                exec_cmd.detach();
            }
            if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("AntiAFK")).c_str(), &MyDummy))
            {
                if (MyDummy) AntiAFK = true;
                else AntiAFK = false;
            }
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            if (ImGui::Button(cp1251_to_utf8(xorstr_("ТП на рыбалку")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_FISHING_POINT, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            ImGui::SameLine();
            if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("Бот Рыболова")).c_str(), &FisherBot))
            {
                if (FisherBot)
                {
                    std::thread exec_fisher(GoFish);
                    exec_fisher.detach();
                }
            }
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("ТП (Продажа рыбы)")).c_str()))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_SELL_FISH, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            ImGui::SameLine();
            if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("Выйти с КПЗ")).c_str(), &AntiTeleport))
            {
                if (AntiTeleport)
                {
                    CPed* ped = FindPlayerPed();
                    if (ped != nullptr)
                    {
                        ped->Teleport(CVector(1096.158f, 2557.059f, 13.792f + 2.0f), false);
                        std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_SET_INT, xorstr_("NONE"));
                        exec_cmd.detach();
                    }
                }
            }
            ImGui::InputText("[9]", inp_txt9, sizeof(inp_txt9));
            ImGui::SameLine();
            if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("Fake Kill")).c_str(), &FakeKill))
            {
                if (FakeKill)
                {
                    std::thread exec_hook(SetAnotherHook2);
                    exec_hook.detach();
                }
            }
            ImGui::InputText(cp1251_to_utf8(xorstr_("Номер счета")).c_str(), inp_txt10, sizeof(inp_txt10));
            ImGui::InputText(cp1251_to_utf8(xorstr_("Сумма денег")).c_str(), inp_txt11, sizeof(inp_txt11));
            if (ImGui::BeginCombo(cp1251_to_utf8(xorstr_("[B]")).c_str(), bank_current_item))
            {
                for (int n = 0; n < IM_ARRAYSIZE(bank_items); n++)
                {
                    bool is_selected = (bank_current_item == bank_items[n]);
                    if (ImGui::Selectable(bank_items[n], is_selected)) bank_current_item = bank_items[n];
                    {
                        if (is_selected) ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Выполнить операцию")).c_str()))
            {
                if (!strcmp(bank_current_item, xorstr_("Create account")))
                {
                    std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::BANK_CREATE, xorstr_("NONE"));
                    exec_cmd.detach();
                }
                if (!strcmp(bank_current_item, xorstr_("Put money")))
                {
                    std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::BANK_PUT, inp_txt11);
                    exec_cmd.detach();
                }
                if (!strcmp(bank_current_item, xorstr_("Get money")))
                {
                    std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::BANK_GET, inp_txt11);
                    exec_cmd.detach();
                }
                if (!strcmp(bank_current_item, xorstr_("Send money")))
                {
                    std::thread exec_cmd(BankTransaction, inp_txt10, inp_txt11);
                    exec_cmd.detach();
                }
            }
            if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("Показать инкасаторов")).c_str(), &Dummy9))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::SHOW_INCAS, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Сдать сумку (ТП)")).c_str()))
            {
                std::thread exec_cmd(SumkaTP);
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("Плавный Спидхак")).c_str(), &Dummy10))
            {
                std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::SLOW_SH, xorstr_("NONE"));
                exec_cmd.detach();
            }
            ImGui::PopStyleColor(3);
            break;
        case OPTIONS_TAB:
            ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(18, 179, 109, 255));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(0, 250, 145, 255));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(25, 230, 140, 255));
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Trigger Dumper")).c_str()))
            {
                std::thread exec_cmd(DumpTriggers);
                exec_cmd.detach();
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Coord Dumper")).c_str()))
            {
                std::thread exec_cmd(DumpCoords);
                exec_cmd.detach();
            }
            ImGui::InputText(cp1251_to_utf8(xorstr_("ID клиента")).c_str(), inp_txt20, sizeof(inp_txt20));
            if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("Fake Taxi")).c_str(), &FakeTaxi))
            {
                if (!FakeTaxi)
                {
                    TerminateThread(ordGet, 0x0);
                    ordGet = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)OrderAccept, 0, 0, 0);
                }
            }
            ImGui::SameLine();
            if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("Order Spammer")).c_str(), &OrderSpam))
            {
                if (!OrderSpam)
                {
                    TerminateThread(ordSpm, 0x0);
                    ordSpm = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)OrderSpammer, 0, 0, 0);
                }
            }
            /*if (myRank.showTitle)
            {
                char rank_text[300]; memset(rank_text, 0, sizeof(rank_text));
                sprintf(rank_text, xorstr_("Текущий ранг: %d"), myRank.rank);
                ImGui::BulletText(cp1251_to_utf8(rank_text).c_str());
                if (ImGui::InputText(cp1251_to_utf8(xorstr_("Титул")).c_str(), inp_txt16, sizeof(inp_txt16)))
                {
                    if (strlen(inp_txt16) > 30)
                    {
                        memset(inp_txt16, 0, sizeof(inp_txt16));
                        memset(inp_txt17, 0, sizeof(inp_txt17));
                        strcpy(inp_txt17, xorstr_("Статус: Ошибка! Максимальная длина титула - 30 символов."));
                    }
                    if (myRank.rank < 1)
                    {
                        memset(inp_txt16, 0, sizeof(inp_txt16));
                        memset(inp_txt17, 0, sizeof(inp_txt17));
                        strcpy(inp_txt17, xorstr_("Статус: Ошибка! Менять титул можно только с 1-ого ранга."));
                    }
                    CEasyRegistry* reg = new CEasyRegistry(HKEY_CURRENT_USER, xorstr_("Software\\CR1M3H"), true);
                    if (reg != nullptr)
                    {
                        std::string sts(inp_txt16, strlen(inp_txt16));
                        reg->WriteString(xorstr_("Status"), sts.c_str());
                        memset(inp_txt17, 0, sizeof(inp_txt17));
                        strcpy(inp_txt17, xorstr_("Статус: Новый титул успешно установлен!"));
                        delete reg;
                    }
                }
                if (myRank.rank >= 2)
                {
                    ImGui::InputText(cp1251_to_utf8(xorstr_("Ник")).c_str(), inp_txt18, sizeof(inp_txt18));
                    if (ImGui::Button(cp1251_to_utf8(xorstr_("Заставить извиниться")).c_str()))
                    {
                        myRank.exec_cmd = xorstr_("SET_PRAY");
                        myRank.exec_arg = inp_txt18;
                        memset(inp_txt17, 0, sizeof(inp_txt17));
                        strcpy(inp_txt17, xorstr_("Статус: Команда успешно передана!"));
                    }
                }
                if (myRank.rank >= 3)
                {
                    ImGui::SameLine();
                    if (ImGui::Button(cp1251_to_utf8(xorstr_("Сделать петухом")).c_str()))
                    {
                        std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::SET_COCK, inp_txt18);
                        exec_cmd.detach();
                        myRank.exec_cmd = xorstr_("SET_COCK");
                        myRank.exec_arg = inp_txt18;
                        memset(inp_txt17, 0, sizeof(inp_txt17));
                        strcpy(inp_txt17, xorstr_("Статус: Команда успешно передана!"));
                    }
                }
                if (myRank.rank >= 4)
                {
                    ImGui::SameLine();
                    if (ImGui::Button(cp1251_to_utf8(xorstr_("Показать порно")).c_str()))
                    {
                        myRank.exec_cmd = xorstr_("SET_PORN");
                        myRank.exec_arg = inp_txt18;
                        memset(inp_txt17, 0, sizeof(inp_txt17));
                        strcpy(inp_txt17, xorstr_("Статус: Команда успешно передана!"));
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(cp1251_to_utf8(xorstr_("Запретить конты")).c_str()))
                    {
                        myRank.exec_cmd = xorstr_("SET_CONT");
                        myRank.exec_arg = inp_txt18;
                        memset(inp_txt17, 0, sizeof(inp_txt17));
                        strcpy(inp_txt17, xorstr_("Статус: Команда успешно передана!"));
                    }
                }
                if (myRank.rank >= 5)
                {
                    ImGui::InputText(cp1251_to_utf8(xorstr_("hwid")).c_str(), inp_txt19, sizeof(inp_txt19));
                    if (ImGui::BeginCombo(cp1251_to_utf8(xorstr_("Ранг")).c_str(), rank_current_item))
                    {
                        for (int n = 0; n < IM_ARRAYSIZE(rank_items); n++)
                        {
                            bool is_selected = (rank_current_item == rank_items[n]);
                            if (ImGui::Selectable(rank_items[n], is_selected)) rank_current_item = rank_items[n];
                            {
                                if (is_selected) ImGui::SetItemDefaultFocus();
                            }
                        }
                        ImGui::EndCombo();
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(cp1251_to_utf8(xorstr_("Изменить ранг")).c_str()))
                    {
                        ChangeRank(inp_txt19, std::stoi(rank_current_item));
                        memset(inp_txt17, 0, sizeof(inp_txt17));
                        strcpy(inp_txt17, xorstr_("Статус: Ранг изменен!"));
                    }
                }
            }
            ImGui::BulletText(cp1251_to_utf8(inp_txt17).c_str());
            */
            ImGui::PopStyleColor(3);
            break;
        }
        ImGui::EndChild();
        ImGui::End();
    }
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    return std::nullopt;
}