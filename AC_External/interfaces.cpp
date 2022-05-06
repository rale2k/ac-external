#include "includes.h"

Interfaces::Interfaces() {
	localplayer = ExtInterface<Interfaces::playerent>();
};

void Interfaces::initialize() {
	entitylist_base = utils::DMAAddy(base_address + interfaces->entity_list, { 0x0 });
	localplayer = ExtInterface<Interfaces::playerent>(utils::DMAAddy(localplayer_base, { 0x0 }), playerent_proxy);
}

int Interfaces::getPlayerCount() {
	int count{ utils::RPM<int>(base_address + player_count) - 1 };
	if (count < 0) { count = 0; };

	return count;
}

Matrix4x4 Interfaces::getViewMatrix() {
	return utils::RPM<Matrix4x4>(base_address + view_matrix);
}

bool Interfaces::isTeammate(ExtInterface<playerent> player) {
	int player_team = GET(player, team);
	int localplayer_team = GET(localplayer, team);

	return player_team == localplayer_team;
}

bool Interfaces::isDead(ExtInterface<playerent> player) {
	int is_dead = GET(player, dead);
	return is_dead == 1;
}

bool Interfaces::InFOV(ExtInterface<Interfaces::playerent> ent) {
	Vector2 screen_pos;
	Math::World2Screen(GET(ent, pos_head), overlay->width, overlay->height, screen_pos);

	return (0 < screen_pos.x && screen_pos.x < overlay->width) ;
}

bool Interfaces::FindNearestPlayer(Vector3& localplayer_pos, ExtInterface<Interfaces::playerent>& p) {
	bool found{ false };
	float lowest{ 9999.0f };
	for (size_t i = 1; i <= interfaces->getPlayerCount(); i++) {
		ExtInterface<Interfaces::playerent> current_p = ExtInterface<Interfaces::playerent>(utils::DMAAddy(interfaces->entitylist_base + i * 0x4, { 0x0 }),
			interfaces->playerent_proxy);
		if (isDead(current_p) || isTeammate(current_p)) { continue; };
		Vector3 cur_pos{ GET(current_p, pos_head) };

		if (!InFOV(current_p)) { continue; };

		float distance{ Math::CalcDistanceVec3(localplayer_pos, cur_pos) };

		if (distance < lowest) {
			lowest = distance;
			p = current_p;
			found = true;
		}
	}

	return found;
}

Interfaces* interfaces = new Interfaces;
