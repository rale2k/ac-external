#include "includes.h"

Features::Features() {}

void Features::initialize() {
	while (1) {
		if (GetAsyncKeyState(VK_NUMPAD7) & 1) { aimbot = !aimbot; }

		if (GetAsyncKeyState(VK_NUMPAD9) & 1) { autoshoot = !autoshoot; }

		if (GetAsyncKeyState(VK_NUMPAD8) & 1) { esp = !esp; }

		if (GetAsyncKeyState(VK_NUMPAD1) & 1) { features->NoRecoil(); }

		if (GetAsyncKeyState(VK_NUMPAD2) & 1) { features->Silencer(); }

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

void Features::AimBot() {
	while (1) {
		if (!aimbot && !interfaces->isDead(interfaces->localplayer) && interfaces->getPlayerCount() > 1) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}

		Vector3 localplayer_pos{ GET(interfaces->localplayer, pos_head) };

		ExtInterface<Interfaces::playerent> player;

		if (!interfaces->FindNearestPlayer(localplayer_pos, player)) { continue; };

		Vector3 target_pos{ GET(player, pos_head) };

		Vector2 new_viewangles{ Math::CalcAngles(localplayer_pos, target_pos) };

		SET(interfaces->localplayer, viewangles, new_viewangles);

		if (GetForegroundWindow() == overlay->game && autoshoot) {
			SET(interfaces->localplayer, attack, true);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		if (autoshoot) { SET(interfaces->localplayer, attack, false); };
	}
}
 
void Features::ESP(Paint* paint) {
	for (int i = 1; i <= interfaces->getPlayerCount(); i++) {
		ExtInterface<Interfaces::playerent> player{ utils::DMAAddy(interfaces->entitylist_base + i * 0x4 , { 0x0 }),
													interfaces->playerent_proxy };

		if (interfaces->isDead(player)) {
			continue;
		}

		String16 name{ GET(player, name) };
		int health{ GET(player, health) };
		if (health < 0) { health = 0; }

		Vector3 pos_head{ GET(player, pos_head) };
		Vector3 pos_feet{ GET(player, pos_feet)	};

		pos_head.z += 0.7f;

		Vector2 screen_head{};
		Vector2 screen_feet{};

		if (!Math::World2Screen(pos_head, overlay->width, overlay->height, screen_head)
			|| !Math::World2Screen(pos_feet, overlay->width, overlay->height, screen_feet)) {
			continue; 
		}

		float width{ (screen_feet.y - screen_head.y) / 4.0f };

		RECT rect{
			screen_feet.x - width,
			screen_head.y - 3.0f,
			screen_feet.x + width,
			screen_feet.y + 3.0f,
		};
		
		RECT rect2{
			screen_head.x,
			screen_head.y + width / 4.0f,
			screen_head.x + 1.0f,
			screen_head.y + width / 4.0f + 2.0f,
		};


		D2D1::ColorF::Enum color;
			
		if(interfaces->isTeammate(player)) { 
			color = D2D1::ColorF::DeepSkyBlue;
		}
		else {
			color = D2D1::ColorF::Red;
		}

		paint->drawRectHollow(rect, color);

		paint->drawRectHollow(rect2, color);

		paint->drawText(name.toString(), screen_feet.x, rect.bottom);
		paint->drawText(std::string{ std::to_string(health) + "HP" }, screen_feet.x, rect.bottom + 15.0f);
	}
}

void Features::NoRecoil() {	
	static uint32_t recoil_offset = 0x6226D;
	static uint32_t punch_offset = 0x625A4;

	static unsigned int size = 7;

	if (!no_recoil) {
		// disable aimpunch
		mem::PatchEx((BYTE*)base_address + punch_offset,
			(BYTE*)"\x0F\xBF\x48\x40\x90\x90\x90", size, h_process);

		// disable recoil
		mem::PatchEx((BYTE*)base_address + recoil_offset,
			(BYTE*)"\x0F\xBF\x47\x40\x90\x90\x90\x0F\xBF\x4F\x40\x90\x90\x90", size * 2, h_process);

	}
	else {
		// aimpunch
		mem::PatchEx((BYTE*)base_address + punch_offset, (BYTE*)"\x0F\xBF\x88\x16\x01\x00\x00", size, h_process);
		// recoil
		mem::PatchEx((BYTE*)base_address + recoil_offset,
			(BYTE*)"\x0F\xBF\x87\x20\x01\x00\x00\x0F\xBF\x87\x22\x01\x00\x00", size * 2, h_process);
	}

	no_recoil = !no_recoil;
}

void Features::Silencer() {
	static uint32_t shot_pitch_offset = 0x61D73;

	static unsigned int size = 7;

	if (!silencer) {
		mem::PatchEx((BYTE*)base_address + shot_pitch_offset, (BYTE*)"\x0F\xB7\x50\x40\x90\x90\x90", size, h_process);
	}
	else {
		mem::PatchEx((BYTE*)base_address + shot_pitch_offset, (BYTE*)"\x0F\xB7\x90\x04\x01\x00\x00", size, h_process);
	}
	
	silencer = !silencer;
}

Features* features = new Features;