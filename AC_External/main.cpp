#include "includes.h"

HANDLE h_process;
uintptr_t base_address;
uintptr_t localplayer_base; 

void Features() {
    features->initialize();
}

void AimBot() {
    features->AimBot();
}

void Render() {
    overlay->Initialize();
}

void Console() {
        utils::ClearScreen();
        std::cout << "==========================" << '\n';
        std::cout << "    Ass Cube external" << '\n';
        std::cout << "==========================" << '\n';

        std::cout << "NAME:       " << GET(interfaces->localplayer, name);
        std::cout << "                          " << '\n';
        std::cout << "HP:         " << GET(interfaces->localplayer, health);
        std::cout << "                          " << '\n';
        std::cout << "ARMOR:      " << GET(interfaces->localplayer, armor);
        std::cout << "                          " << '\n';
        std::cout << "NADES:      " << GET(interfaces->localplayer, grenades);
        std::cout << "                          " << '\n';
        std::cout << "POS(head):  " << GET(interfaces->localplayer, pos_head);
        std::cout << "                          " << '\n';
        std::cout << "VIEWANGLES: " << GET(interfaces->localplayer, viewangles);
        std::cout << "                          " << '\n';
        std::cout << "PLAYERS: " << interfaces->getPlayerCount() + 1;

        std::cout << "\n==========================" << "\n\n";
        std::cout << "[NUM7]Aimbot ([NUM9]) Autoshoot ( no visibility check :( )" << '\n';
        std::cout << "[NUM8]ESP" << "\n";
        std::cout << "[NUM1]No Recoil/Punch" << '\n';
        std::cout << "[NUM2]Silencer (clientside)" << "\n\n";
}

int main() {   
    static std::wstring game_process{ L"ac_client.exe" };
    DWORD pid = utils::GetProcessID(game_process);

    std::cout << "Waiting for game..";
    while (pid == 0) {
        std::cout << ".";
        Sleep(2000);
        pid = utils::GetProcessID(game_process);
    }

    h_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    base_address = utils::GetModuleBaseAddress(pid, game_process);
    localplayer_base = base_address + 0x10f4f4;

    interfaces->initialize();

    std::thread thread_overlay{ Render };
    thread_overlay.detach();

    std::thread thread_features{ Features };
    thread_features.detach();

    std::thread thread_aimbot{ AimBot };
    thread_aimbot.detach();

    int player_count{ 0 };
    while (1) {
        Console();
        // ghetto fix to prevent entitylist ptr being initialized to garbage when u load into a solo lobby
        int new_player_count = interfaces->getPlayerCount();

        if (player_count != new_player_count) {
            player_count = new_player_count;
            interfaces->initialize();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    // no exit routines, only way to exit is to just close the cheat manually
    return 0;
}
