#pragma once

// Kind of a misleading name, but I couldn't think of anything better
class Interfaces {
public:
	// Offsets for things that cant really be solved with interfaces
	uintptr_t view_matrix{ 0x101AE8 };
	uintptr_t local_player{ 0x10F4F4 };
	uintptr_t entity_list{ 0x10F4F8 };
	uintptr_t player_count{0x10F500};

	class playerent {
	public:
		int32_t vtable; //0x0000
		Vector3 pos_head; //0x0004
		char pad_0010[24]; //0x0010
		Vector3 movement; //0x0028
		Vector3 pos_feet; //0x0034
		Vector2 viewangles; //0x0040
		char pad_0048[176]; //0x0048
		int32_t health; //0x00F8
		int32_t armor; //0x00FC
		char pad_0100[20]; //0x0100
		uint32_t pistolammo_reserve; //0x0114
		uint32_t carbineammo_reserve; //0x0118
		uint32_t shotgunammo_reserve; //0x011C
		uint32_t smgammo_reserve; //0x0120
		uint32_t sniperammo_reserve; //0x0124
		char pad_0128[20]; //0x0128
		uint32_t pistolammo_active; //0x013C
		uint32_t carbineammo_active; //0x0140
		uint32_t shotgunammo_active; //0x0144
		uint32_t smgammo_active; //0x0148
		uint32_t sniperammo_active; //0x014C
		char pad_0150[8]; //0x0150
		uint32_t grenades; //0x0158
		char pad_015C[164]; //0x015C
		int32_t deaths; //0x0200
		int32_t kills; //0x0204
		char pad_0208[28]; //0x0208
		bool attack; //0x0224
		String16 name; //0x0225
		char pad_0234[246]; //0x0234
		int32_t team; //0x032C
		char pad_0330[8]; //0x0330
		int32_t dead; //0x0338
		char pad_033C[56]; //0x033C
		class weapon* currentweapon; //0x0374
		char pad_0378[656]; //0x0378	
	};

	uintptr_t entitylist_base;

	ExtInterface<playerent> localplayer;

	// Proxies for ExtInterfaces
	Interfaces::playerent* playerent_proxy = new Interfaces::playerent;

	bool FindNearestPlayer(Vector3& localplayer_pos, ExtInterface<Interfaces::playerent>& p);
	int getPlayerCount();
	Matrix4x4 getViewMatrix();
	bool isTeammate(ExtInterface<playerent> player);
	bool isDead(ExtInterface<playerent> player);
	bool InFOV(ExtInterface<Interfaces::playerent> ent);
	// bool IsVisible(ExtInterface<playerent> player);

	void initialize();
	Interfaces();
};

extern Interfaces* interfaces;