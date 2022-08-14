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
    CPP_TAB,
    ENEMY_TAB,
    LUA_TAB,
    LOGS_TAB,
    UPDATE_TAB
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
};
void ExecuteLuaCommand(LUA_CMD cmd, std::string argument)
{
    char prepared_path[600]; memset(prepared_path, 0, sizeof(prepared_path));
    sprintf(prepared_path, xorstr_("%s\\ExecCMD_%d.txt"), GetGamePath().c_str(), cmd);
    FILE* hFile = fopen(prepared_path, xorstr_("a+"));
    if (hFile)
    {
        fwrite(argument.c_str(), 1, argument.length(), hFile);
        fclose(hFile);
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
        ImGui::SetNextWindowSize(ImVec2(610, 500));
        char capWin[350]; memset(capWin, 0, sizeof(capWin));
        sprintf(capWin, xorstr_("Crime Hack by NtKernelMC | build %s | vk.com/provhacks"), PLUGIN_VER);
        ImGui::Begin(capWin, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse);
        ImGui::Image(texture, ImVec2(610, 166));
        ImGui::BeginChild(xorstr_("tabs"), ImVec2(0, 25), false);
        if (ImGui::Button(cp1251_to_utf8(xorstr_("C++ читы")).c_str(), ImVec2(ImGui::GetWindowWidth() / 5 - 8, 25))) page = CPP_TAB;
        ImGui::SameLine();
        if (ImGui::Button(cp1251_to_utf8(xorstr_("Черный список")).c_str(), ImVec2(ImGui::GetWindowWidth() / 5 - 8, 25))) page = ENEMY_TAB;
        ImGui::SameLine();
        if (ImGui::Button(cp1251_to_utf8(xorstr_("Lua читы")).c_str(), ImVec2(ImGui::GetWindowWidth() / 5 - 8, 25))) page = LUA_TAB;
        ImGui::SameLine();
        if (ImGui::Button(cp1251_to_utf8(xorstr_("Логи")).c_str(), ImVec2(ImGui::GetWindowWidth() / 5 - 8, 25))) page = LOGS_TAB;
        ImGui::SameLine();
        if (ImGui::Button(cp1251_to_utf8(xorstr_("Обновление")).c_str(), ImVec2(ImGui::GetWindowWidth() / 5 - 8, 25))) page = UPDATE_TAB;
        ImGui::EndChild();
        ImGui::BeginChild(xorstr_("main"), ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar);
        switch (page)
        {
        case CPP_TAB:
            ImGui::Checkbox(cp1251_to_utf8(xorstr_("Аирбрэйк")).c_str(), &AirAllowed);
            ImGui::SameLine(); ImGui::Checkbox(cp1251_to_utf8(xorstr_("Коллизия")).c_str(), &ColHack);
            ImGui::SameLine(); 
            ImGui::Checkbox(cp1251_to_utf8(xorstr_("Заморозить HP Тачек")).c_str(), &CarGM);
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
            ImGui::Checkbox(cp1251_to_utf8(xorstr_("Тоталер тачек")).c_str(), &TotalCar);
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
            if (ImGui::Button(cp1251_to_utf8(xorstr_("ТП по метке")).c_str()))
            {
                for (int i = 0; i < (0xAF * 0x28); i += 0x28)
                {
                    if (*(short*)(0xBA873D + i) == 4611)
                    {
                        BYTE icon = *(BYTE*)((0xBA86F0 + 36) + 0x28 + i);
                        float* pos = (float*)(0xBA86F8 + 0x28 + i);
                        CVector dest(*pos, *(pos + 1), *(pos + 2));
                        if (icon == 41)
                        {
                            DWORD PEDSELF = *(DWORD*)0xB6F5F0;
                            BYTE pedState = *(BYTE*)(PEDSELF + 0x46C);
                            if (pedState != 1 && pedState != 9)
                            {
                                CPed* ped = FindPlayerPed();
                                if (ped != nullptr) ped->Teleport(dest, false);
                            }
                            else
                            {
                                CVehicle* veh = FindPlayerVehicle(0, false);
                                if (veh != nullptr) veh->Teleport(dest, false);
                            }
                        }
                    }
                }
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
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.0f, 0.0f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.7f, 0.0f, 0.0f, 1.0f });
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
                CPed* ped = FindPlayerPed();
                if (ped != nullptr) ped->Teleport(CVector(213.91273498535f, 1115.1557617188f, 24.144750595093f), false);
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("ТП в Лес (Винтовка)")).c_str()))
            {
                CPed* ped = FindPlayerPed();
                if (ped != nullptr) ped->Teleport(CVector(-100.92771911621f, -1241.4100341797f, 6.9533462524414f), false);
            }
            ImGui::PopStyleColor(3);
            break;
        case ENEMY_TAB:
            if (LuaAllowed)
            {
                ImGui::BulletText(cp1251_to_utf8(xorstr_("Нажмите 2 раза на врага")).c_str());
                ImGui::SameLine(); ImGui::Indent(370);
                ImGui::BulletText(cp1251_to_utf8(xorstr_("Нажмите 2 раза на игрока")).c_str());
                ImGui::Unindent(370);
                static const char* current_select = "All enemies are Offline!";
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
                static const char* current_select2 = "All players are Offline!";
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
            }
            else ImGui::BulletText(cp1251_to_utf8(xorstr_("Разрешите использовать Lua читы в настройках инжектора!")).c_str());
            break;
        case LUA_TAB:
            if (LuaAllowed)
            {
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
                if (ImGui::Button(cp1251_to_utf8(xorstr_("Еда")).c_str()))
                {
                    std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_EAT, xorstr_("NONE"));
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
                static bool Dummy = false;
                if (ImGui::Checkbox(cp1251_to_utf8(xorstr_("Неуязвимый персонаж")).c_str(), &Dummy))
                {
                    std::thread exec_cmd(ExecuteLuaCommand, LUA_CMD::PL_GM, xorstr_("NONE"));
                    exec_cmd.detach();
                }
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
            }
            else ImGui::BulletText(cp1251_to_utf8(xorstr_("Разрешите Lua читы в настройках инжектора!")).c_str());
            break;
        case LOGS_TAB:
            ImGui::Text(ReadHackLog().c_str());
            break;
        case UPDATE_TAB:
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Проверить актуальность")).c_str()))
            {
                char params[3000]; std::string host_lnk = xorstr_("kuprey123.beget.tech");
                memset(params, 0, sizeof(params));
                sprintf(params, xorstr_("soft_ver=%s"), PLUGIN_VER);
                std::string sc_ans = SendInetRequest(P_HTTP, M_GET, host_lnk, xorstr_("crime_hack/check_update.php"), std::string(params), true);
                memset(upd_txt, 0, sizeof(upd_txt));
                strcpy(upd_txt, sc_ans.c_str());
            }
            ImGui::SameLine();
            if (ImGui::Button(cp1251_to_utf8(xorstr_("Загрузить обновление")).c_str()))
            {
                ShellExecuteA(0, 0, xorstr_("https://drive.google.com/file/d/1jd--lAR6CbL3Y5ffGGdYH3t0HHSAFur9/view?usp=sharing"), 0, 0, SW_SHOW);
            }
            ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
            ImGui::BulletText(cp1251_to_utf8(upd_txt).c_str());
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